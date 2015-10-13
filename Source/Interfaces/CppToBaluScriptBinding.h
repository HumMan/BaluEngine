#pragma once

#include <baluScript.h>

template<class T>
class WrapInterface
{
public:
	typedef T* CppType;
	typedef T InterfaceType;
	typedef T TypeForGetName;	

	T* obj;
	void FromCppValue(T* copy_from_cpp)
	{
		obj = copy_from_cpp;
	}
	T& GetInterface()
	{
		return *obj;
	}
	T*& ToCppValue()
	{
		return obj;
	}
};

template<class T, class pass_as = T>
class WrapValue
{
public:
	typedef pass_as CppType;
	typedef T InterfaceType;
	typedef T TypeForGetName;

	T obj;
	void FromCppValue(const T& copy_from_cpp)
	{
		obj = copy_from_cpp;
	}
	T& ToCppValue()
	{
		return obj;
	}
	T& GetInterface()
	{
		return obj;
	}
};

class WrapString
{
public:
	typedef const std::string& CppType;
	typedef std::string InterfaceType;
	typedef std::string TypeForGetName;
	
	TStringWrapper<std::string> obj;
	void FromCppValue(const std::string& copy_from_cpp)
	{
		obj.Init(copy_from_cpp);
	}
	std::string& ToCppValue()
	{
		return obj.GetCppValue();
	}
	std::string& GetInterface()
	{
		return obj.GetCppValue();
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
		binding->size = sizeof(interface_wrapper_template<interface_type>::CppType);\
		std::vector<Unpacker*> methods;\
		TScriptClassesRegistry::RegisterClassBinding(binding);

#define BALU_ENGINE_SCRIPT_END_CLASS\
		binding->SetMethods(methods); return true; }
	
#pragma push_macro("new")
#undef new

#include "../BindingMacroGenerator/UnpackTemplates.h"

#pragma pop_macro("new")