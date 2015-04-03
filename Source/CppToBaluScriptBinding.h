#pragma once

template<class T>
class WrapPointer
{
public:
	typedef T* PassInMethodAs;
	typedef T TypeForGetName;
	typedef T InterfaceType;
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
class WrapInterface
{
public:
	typedef T InterfaceType;
	typedef T TypeForGetName;
	typedef T* PassInMethodAs;
	T* obj;
	WrapInterface(T* copy_from_cpp)
	{
		obj = copy_from_cpp;
	}
	T& GetCppValue()
	{
		return *obj;
	}
};

template<class T, class pass_as = T>
class WrapValue
{
public:
	typedef T InterfaceType;
	typedef T TypeForGetName;
	typedef pass_as PassInMethodAs;
	T obj;
	WrapValue(const T& copy_from_cpp)
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

#define DECL_SCRIPT_TYPE(cpp_class, script_type)\
template<>\
struct CppTypeToScript < cpp_class >\
	{\
	static const char* Get()\
		{\
		return script_type;\
		}\
	};
}
#define BALU_ENGINE_SCRIPT_BEGIN_CLASS(interface_wrapper_template, interface_type, script_name)\
	DECL_SCRIPT_TYPE(interface_wrapper_template<interface_type>::TypeForGetName, script_name);\
	void interface_type##_register(TClassRegistryParams& params);\
	static bool interface_type##_registered = TScriptClassesRegistry::Register(CppTypeToScript<interface_wrapper_template<interface_type>::TypeForGetName>::Get(), interface_type##_register);\
	void interface_type##_register(TClassRegistryParams& params)\
		{\
		typedef interface_wrapper_template<interface_type> TYPE;\
		std::vector<Unpacker*> methods;

#define BALU_ENGINE_SCRIPT_END_CLASS(interface_wrapper)\
	auto scl = RegisterExternClass2(params, CppTypeToScript<interface_wrapper::TypeForGetName>::Get(), sizeof(interface_wrapper::InterfaceType), methods);\
		}
	
#pragma push_macro("new")
#undef new

#include "../BindingMacroGenerator/UnpackTemplates.h"

#pragma pop_macro("new")