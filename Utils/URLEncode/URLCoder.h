//
//  URLCoder.hpp
//  GenS
//
//  Created by gen on 29/06/2017.
//  Copyright © 2017 gen. All rights reserved.
//

#ifndef URLCoder_hpp
#define URLCoder_hpp

#include <core/Object.h>
#include "../../nl_define.h"


namespace nl {
    CLASS_BEGIN_0_NV(URLCoder)
    
    public:
        METHOD static string encode(const char *);
        METHOD static string encodeWithEncoding(const char *, const char *encoding);
    
    protected:
        ON_LOADED_BEGIN(cls, HObject)
            ADD_METHOD(cls, URLCoder, encode);
            ADD_METHOD(cls, URLCoder, encodeWithEncoding);
        ON_LOADED_END
    CLASS_END
}

#endif /* URLCoder_hpp */
