#pragma once

#ifdef BALUENGINEDLL_EXPORTS
#define BALUENGINEDLL_API __declspec(dllexport) 
#else
#define BALUENGINEDLL_API __declspec(dllimport) 
#endif