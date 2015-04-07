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
	typedef T* PassInMethodAs;
	typedef T InterfaceType;
	typedef T TypeForGetName;	
	T* obj;
	WrapInterface(T* copy_from_cpp)
	{
		obj = copy_from_cpp;
	}
	T& GetInterface()
	{
		return *obj;
	}
	T*& GetCppValue()
	{
		return obj;
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
	T& GetInterface()
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
	bool interface_type##_register();\
	static bool interface_type##_registered =interface_type##_register();\
	bool interface_type##_register()\
		{\
		typedef interface_wrapper_template<interface_type> TYPE;\
		TClassBinding* binding = new TClassBinding();\
		binding->class_name = CppTypeToScript<interface_wrapper_template<interface_type>::TypeForGetName>::Get();\
		binding->size = sizeof(interface_wrapper_template<interface_type>::InterfaceType);\
		std::vector<Unpacker*> methods;\
		TScriptClassesRegistry::RegisterClassBinding(binding);

#define BALU_ENGINE_SCRIPT_END_CLASS\
		binding->SetMethods(methods); return true; }
	
#pragma push_macro("new")
#undef new

#include "../BindingMacroGenerator/UnpackTemplates.h"

#pragma pop_macro("new")