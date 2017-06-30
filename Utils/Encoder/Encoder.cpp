//
//  URLCoder.cpp
//  GenS
//
//  Created by gen on 29/06/2017.
//  Copyright © 2017 gen. All rights reserved.
//

#include "Encoder.h"
#include <iconv.h>

using namespace nl;

const char Encoder_hex[]="0123456789ABCDEF";

bool is_non_symbol(char c)
{
    if(c == '\0') return true; //we want to write null regardless
    int c_int = (int)c;
    return (c_int >= 48 && c_int <= 57) || (c_int >= 65 && c_int <= 90) || (c_int >= 97 && c_int <= 122);
}

string Encoder::urlEncode(const char *str) {
    stringstream ss;
    const char *ch = str;
    unsigned char c;
    while ((c = *ch)) {
        if (is_non_symbol(c)) {
            ss << c;
        }else {
            ss << '%';
            ss << Encoder_hex[c/16];
            ss << Encoder_hex[c%16];
        }
        ++ch;
    }
    return ss.str();
}

#define UTF_8 "utf-8"

string Encoder::urlEncodeWithEncoding(const char *str, const char *encoding) {
    if (strcmp(encoding, UTF_8) != 0) {
        iconv_t cd = iconv_open(encoding, "utf-8");
        if (cd) {
            const char *instr = str;
            size_t inlen = strlen(instr);
            size_t outlen = 4 * inlen;
            char *oristr = (char*)malloc(outlen);
            char *outstr = oristr;
            
            iconv(cd, (char**)&instr, &inlen, &outstr, &outlen);
            
            string ret = urlEncode(oristr);
            
            free(oristr);
            
            iconv_close(cd);
            return ret;
        }
    }
    return urlEncode(str);
}

string Encoder::decode(const hicore::Ref<hicore::Data> &data, const char *encoding) {
    iconv_t cd = iconv_open("utf-8", encoding);
    if (cd) {
        const char *instr = data->text();
        size_t inlen = data->getSize();
        size_t outlen = 2 * inlen;
        char *oristr = (char*)malloc(outlen);
        char *outstr = oristr;
        
        iconv(cd, (char**)&instr, &inlen, &outstr, &outlen);
        
        string ret(oristr);
        
        free(oristr);
        
        iconv_close(cd);
        return ret;
    }
    return string();
}
