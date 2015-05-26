
#ifndef BALU_ENGINE_DISABLE_PRAGMA_ONCE
#pragma once
#endif


#ifndef BALU_ENGINE_SCRIPT_CLASSES

#include <string>

namespace EngineInterface
{
	class IProperties;
	class IBaluSceneClassInstance;
	class IBaluClassSpriteInstance;
}

#endif

namespace EngineInterface
{

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	enum class PropertyType
	{
		Bool,
		Int,
		Float,
		String,
		SceneClassInstance,
		ClassSpriteInstance,
	};
#endif


#ifdef BALU_ENGINE_SCRIPT_CLASSES

	DECL_SCRIPT_TYPE(PropertyType, "PropertyType");

	void PropertyType_register(TClassRegistryParams& params)
	{
		auto scl = RegisterEnum(params,
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
	static bool PropertyType_registered = TScriptClassesRegistry::RegisterEnum("PropertyType", PropertyType_register);
#endif

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	class IProperties
	{
	public:
		virtual bool HasProperty(const std::string& name, PropertyType& type) = 0;
		virtual void SetBool(const std::string& name, bool value) = 0;
		virtual bool GetBool(const std::string& name) = 0;
		virtual void SetSceneClassInstance(const std::string& name, IBaluSceneClassInstance* value) = 0;
		virtual IBaluSceneClassInstance* GetSceneClassInstance(const std::string& name) = 0;
		virtual void SetClassSpriteInstance(const std::string& name, IBaluClassSpriteInstance* value) = 0;
		virtual IBaluClassSpriteInstance* GetClassSpriteInstance(const std::string& name) = 0;
	};
#endif

#ifdef BALU_ENGINE_SCRIPT_CLASSES	
	BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, IProperties, "IProperties");
	MUnpackRA2(WrapValue<bool>, WrapInterface<IProperties>, HasProperty, TStringWrapper<std::string _COMMA const std::string&>, WrapValue<PropertyType _COMMA PropertyType&>);
	MUnpackRA1(WrapValue<bool>, WrapInterface<IProperties>, GetBool, TStringWrapper<std::string _COMMA const std::string&>);
	MUnpackA2(WrapInterface<IProperties>, SetBool, TStringWrapper<std::string _COMMA const std::string&>, WrapValue<bool>);
	BALU_ENGINE_SCRIPT_END_CLASS;
#endif

}