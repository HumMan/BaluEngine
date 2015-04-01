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

//
//#define MUnpackRp(ret_type, interface_type, method_name) \
//methods.push_back(SetName(#method_name, new UnpackR<WrapPointer<ret_type>, ret_type*, WrapPointer<interface_type>\
//,&interface_type::method_name>));
//
//template<class Tresult_type, class TCppResult, class Tobject_type, TCppResult(Tobject_type::Arg::*CppMethod)()>
//class UnpackR : public Unpacker
//{
//public:
//	std::string GetSyntax()
//	{
//		char buf[255];
//		sprintf_s(buf, "func %s:%s;", func_name, CppTypeToScript<Tresult_type::Arg>::Get());
//		return buf;
//	}
//	static void Run(std::vector<TStaticValue> &static_fields, std::vector<TStackValue> &formal_params, TStackValue& result, TStackValue& object)
//	{
//		result.get_as<Tresult_type>() = Tresult_type(((object.get_as<Tobject_type>().GetCppValue()).*CppMethod)());
//
//	}
//	TExternalSMethod GetUnpackMethod()
//	{
//		return Run;
//	}
//};
//
//template<class Tresult_type, class TCppResult, class Tobject_type
//	, class Ta0, class Ta0_cpp
//	, TCppResult(Tobject_type::Arg::*CppMethod)(Ta0_cpp)>
//class UnpackRA1 : public Unpacker
//{
//public:
//	std::string GetSyntax()
//	{
//		char buf[255];
//		sprintf_s(buf, "func %s(%s a0):%s;", func_name
//			, CppTypeToScript<Ta0::Arg>::Get()
//			, CppTypeToScript<Tresult_type::Arg>::Get()
//			);
//		return buf;
//	}
//	static void Run(std::vector<TStaticValue> &static_fields, std::vector<TStackValue> &formal_params, TStackValue& result, TStackValue& object)
//	{		
//		result.get_as<Tresult_type>() = Tresult_type(((object.get_as<Tobject_type>().GetCppValue()).*CppMethod)
//			(
//			formal_params[0].get_as<Ta0>().GetCppValue()
//			));
//	}
//	TExternalSMethod GetUnpackMethod()
//	{
//		return Run;
//	}
//};

//template<class Tobject_type, void (Tobject_type::*SomeMethod)(), class Targ0>
//class UnpackA1 : public Unpacker
//{
//public:
//	std::string GetSyntax()
//	{
//		char buf[255];
//		sprintf_s(buf, "func %s(%s);", func_name, Targ0::GetScriptClassName());
//		return buf;
//	}
//	static void Run(std::vector<TStaticValue> &static_fields, std::vector<TStackValue> &formal_params, TStackValue& result, TStackValue& object)
//	{
//		((*object.get_as<Tobject_type*>())->*SomeMethod)(formal_params[0].get_as<Targ0>());
//	}
//	TExternalSMethod GetUnpackMethod()
//	{
//		return Run;
//	}
//};