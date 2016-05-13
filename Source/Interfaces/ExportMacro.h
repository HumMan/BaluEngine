#pragma once

#if defined(_MSC_VER)
    //  Microsoft 
    #ifdef BALUENGINEDLL_EXPORTS
    #define BALUENGINEDLL_API __declspec(dllexport) 
    #else
    #define BALUENGINEDLL_API __declspec(dllimport) 
    #endif
#elif defined(_GCC)
    //  GCC
    #ifdef BALUENGINEDLL_EXPORTS
    #define EXPORT __attribute__((visibility("default")))
    #else
    #define IMPORT 
    #endif
#else
    #ifdef BALUENGINEDLL_EXPORTS
    //  do nothing and hope for the best?
    #define BALUENGINEDLL_API
    #else
    #define BALUENGINEDLL_API 
    #endif
    #pragma warning Unknown dynamic link import/export semantics.
#endif
