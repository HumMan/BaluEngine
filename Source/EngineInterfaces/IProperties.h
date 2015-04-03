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

	DECL_SCRIPT_TYPE(PropertyType, "PropertyType");

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
	BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, IProperties, "IProperties");
	MUnpackRA2(WrapValue<bool>, WrapInterface<IProperties>, HasProperty, TStringWrapper<std::string _COMMA const std::string&>, WrapValue<PropertyType _COMMA PropertyType&>);
	MUnpackRA1(WrapValue<bool>, WrapInterface<IProperties>, GetBool, TStringWrapper<std::string _COMMA const std::string&>);
	MUnpackA2(WrapInterface<IProperties>, SetBool, TStringWrapper<std::string _COMMA const std::string&>, WrapValue<bool>);
	BALU_ENGINE_SCRIPT_END_CLASS(WrapInterface<IProperties>);
#endif

}