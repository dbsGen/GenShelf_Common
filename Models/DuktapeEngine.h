//
//  DuktapeEngine.hpp
//  GenS
//
//  Created by mac on 2017/6/25.
//  Copyright © 2017年 gen. All rights reserved.
//

#ifndef DuktapeEngine_hpp
#define DuktapeEngine_hpp

#include <core/Singleton.h>
#include "../nl_define.h"

using namespace hicore;

namespace nl {
    CLASS_BEGIN_TN(DuktapeEngine, Singleton, 1, DuktapeEngine)
    
    static void fatal_handler(void *udata, const char *msg);
    
    Variant process(void *context);
    
public:
    METHOD Variant eval(const char *script);
    
    protected:
        ON_LOADED_BEGIN(cls, Singleton<DuktapeEngine>)
            ADD_METHOD(cls, DuktapeEngine, eval);
        ON_LOADED_END
    CLASS_END
}

#endif /* DuktapeEngine_hpp */
