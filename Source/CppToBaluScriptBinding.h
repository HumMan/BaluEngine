#pragma once

template<class T>
class WrapPointer
{
public:
	typedef T Arg;
	T* obj;
	WrapPointer(T* copy_from_cpp)
	{
		obj = copy_from_cpp;
	}
	T& GetCppValue()
	{
		return *obj;
	}
};

template<class T>
class WrapValue
{
public:
	typedef T Arg;
	T obj;
	WrapValue(T copy_from_cpp)
	{
		obj = copy_from_cpp;
	}
	T& GetCppValue()
	{
		return obj;
	}
};

namespace EngineInterface
{
	// default implementation
	template <typename T>
	struct CppTypeToScript;
}

#define DECL_SCRIPT_TYPE(cpp_class, script_type)\
template<>\
struct CppTypeToScript < cpp_class >\
{\
	static const char* Get()\
	{\
		return script_type;\
	}\
};


#include "../BindingMacroGenerator/UnpackTemplates.h"