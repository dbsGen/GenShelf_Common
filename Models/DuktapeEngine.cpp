//
//  DuktapeEngine.cpp
//  GenS
//
//  Created by mac on 2017/6/25.
//  Copyright © 2017年 gen. All rights reserved.
//

#include "DuktapeEngine.h"
#include <core/Data.h>
#include <core/Array.h>
#include <duktape/duktape.h>

using namespace nl;

int duktape_log(duk_context *ctx) {
    int n = duk_get_top(ctx);

    if (n > 0) {
        const char *chs = duk_to_string(ctx, 0);
        LOG(i, "%s", chs);
    }

    duk_push_number(ctx, 0);
    return 1;  /* one return value */
}

DuktapeEngine::DuktapeEngine() {
    context = duk_create_heap(NULL, NULL, NULL, this,
                              &DuktapeEngine::fatal_handler);
    duk_push_global_object((duk_context*)context);
    duk_push_c_function((duk_context*)context, duktape_log, DUK_VARARGS);
    duk_put_prop_string((duk_context*)context, -2 /*idx:global*/, "c_log");
    duk_pop((duk_context*)context);
}

DuktapeEngine::~DuktapeEngine() {
    duk_destroy_heap((duk_context*)context);
}

void DuktapeEngine::fatal_handler(void *udata, const char *msg) {
    LOG(w, "Duktape: %s", msg);
}

Variant DuktapeEngine::process(void *context) {
    duk_context *ctx = (duk_context*)context;

    Variant ret;
    if (duk_is_string(ctx, -1)) {
        ret = duk_get_string(ctx, -1);
    }else if (duk_is_number(ctx, -1)) {
        ret = duk_get_number(ctx, -1);
    }else if (duk_is_boolean(ctx, -1)) {
        ret = duk_get_boolean(ctx, -1);
    }else if (duk_is_array(ctx, -1)) {
        if (duk_get_prop_string(ctx, -1, "length")) {
            duk_int_t len = duk_get_int(ctx, -1);
            duk_pop(ctx);
            Array arr;

            for (int i = 0; i < len; ++i) {
                if (duk_get_prop_index(ctx, -1, i)) {
                    arr->push_back(process(context));
                    duk_pop(ctx);
                }
            }
            ret = arr;
        }
    }
    return ret;
}

Variant DuktapeEngine::eval(const char *script) {
    duk_context *ctx = (duk_context*)context;
    duk_peval_string(ctx, script);

    Variant ret = process(ctx);

    duk_pop(ctx);

    return ret;
}

Variant DuktapeEngine::fileEval(const string &filepath) {
    duk_context *ctx = (duk_context*)context;

    FileData data(filepath);
    duk_peval_string(ctx, data.text());

    Variant ret = process(ctx);

    duk_pop(ctx);

    return ret;
}

