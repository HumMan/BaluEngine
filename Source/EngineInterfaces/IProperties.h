#pragma once

#include <string>

namespace EngineInterface
{
	class IProperties;
	class IBaluSceneClassInstance;

	class IBaluWorldObject
	{
	public:
		virtual IProperties* GetProperties() = 0;
		virtual std::string GetName() = 0;
	};

	enum class PropertyType
	{
		Bool,
		Int,
		Float,
		String,
		SceneClassInstance,
	};


#ifdef BALU_ENGINE_SCRIPT_CLASSES

	void PropertyType_register(TClassRegistryParams& params)
	{
		auto scl = RegisterClass(params,
			"enum PropertyType\n"
			"{\n"
			"Bool,\n"
			"Int,\n"
			"Float,\n"
			"String,\n"
			"SceneClassInstance,\n"
			"}\n"
			);
	}
	static bool PropertyType_registered = TScriptClassesRegistry::Register("PropertyType", PropertyType_register);
#endif

	class IProperties
	{
	public:
		virtual bool HasProperty(const std::string& name, PropertyType& type) = 0;
		virtual void SetBool(const std::string& name, bool value) = 0;
		virtual bool GetBool(const std::string& name) = 0;
		virtual void SetSceneClassInstance(const std::string& name, IBaluSceneClassInstance* value) = 0;
		virtual IBaluSceneClassInstance* GetSceneClassInstance(const std::string& name) = 0;
	};


#ifdef BALU_ENGINE_SCRIPT_CLASSES

	void IProperties_HasProperty(std::vector<TStaticValue> &static_fields, std::vector<TStackValue> &formal_params, TStackValue& result, TStackValue& object)
	{
		auto obj = ((IProperties*)object.get());
		auto name = *(((TString*)formal_params[0].get())->v);
		auto type = *((PropertyType*)formal_params[1].get());
		*(bool*)result.get() = obj->HasProperty(name, type);
	}
	void IProperties_GetBool(std::vector<TStaticValue> &static_fields, std::vector<TStackValue> &formal_params, TStackValue& result, TStackValue& object)
	{
		auto obj = ((IProperties*)object.get());
		auto name = *(((TString*)formal_params[0].get())->v);
		*(bool*)result.get() = obj->GetBool(name);
	}

	void IProperties_register(TClassRegistryParams& params)
	{
		auto scl = RegisterExternClass(params,
			"class extern IProperties\n"
			"{\n"
			"func HasProperty(string name, PropertyType type):bool;\n"
			"func GetBool(string name):bool;\n"
			"}\n",
			sizeof(TFrame));
		RegisterMethod(params, scl, "HasProperty", TFrame_GetLeftBottom);
		RegisterMethod(params, scl, "GetBool", IProperties_GetBool);
	}
	static bool IProperties_registered = TScriptClassesRegistry::Register("IProperties", IProperties_register);
#endif

}