
#ifndef BALU_ENGINE_DISABLE_PRAGMA_ONCE
#pragma once
#endif

#include <string>
#include <map>
#include <memory>

#if !defined(BALU_ENGINE_SCRIPT_CLASSES)  && !defined(BALU_ENGINE_DISABLE_PRAGMA_ONCE)
#endif

namespace pugi
{
	class xml_node;
}

namespace EngineInterface
{
	class TBaluWorld;
}

namespace EngineInterface
{

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	enum class PropertyType
	{
		Bool,
		Int,
		Float,
		String,
		Color,
		ColorWithAlpha,
		TransparentMode,
		AlphaTestFunc,
		BlendFunc,
		BlendEquation,
		TexFilter,
		TexClamp,
		Size,
		TransformWithScale,
		Transform,
		Scale,
		Pos,
		Rotation,
		Material,
		PhysShapeType,
		Layer,
		Properties,
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
	};

#ifndef BALU_ENGINE_DLL_INTERFACE

	class TProperty
	{
	public:
		virtual const char* GetTypeString() = 0;
		virtual EngineInterface::PropertyType GetType() = 0;
		void Save(pugi::xml_node& parent_node, const int version);
		virtual void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world);
		virtual ~TProperty();
	};

	typedef TProperty*(*PropertyClone)();
	class PropertiesFactory
	{
	public:
		static bool Register(const char* name, PropertyClone clone);
		static TProperty* Create(const char* name);
	};

	class TProperties : public EngineInterface::IProperties
	{
	public:

		std::map<std::string, std::unique_ptr<TProperty>> properties;

		template<class T>
		void Get(const std::string& name, T*& value)
		{
			auto it = properties.find(name);
			if (it == properties.end())
			{
				throw std::invalid_argument("Неправильное имя свойства");
			}
			auto ptr = dynamic_cast<TPropertyValue<T>*>(it->second.get());
			if (ptr == nullptr)
				throw std::invalid_argument("Неправильный тип свойства");
			value = ptr->GetValue();
		}
		bool is_wrapper;
	public:
		TProperties();
		TProperties(bool is_wrapper);
		void AddProperty(const char* name, TProperty* prop);
		bool HasProperty(const std::string& name, EngineInterface::PropertyType& type);
		void SetBool(const std::string& name, bool value);
		bool GetBool(const std::string& name);
		void Save(pugi::xml_node& parent_node, const int version);
		void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world);
	};
#endif

#endif

#ifdef BALU_ENGINE_SCRIPT_CLASSES	
	BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, IProperties, "IProperties");
	MUnpackRA2(WrapValue<bool>, WrapInterface<IProperties>, HasProperty, TStringWrapper<std::string _COMMA const std::string&>, WrapValue<PropertyType _COMMA PropertyType&>);
	MUnpackRA1(WrapValue<bool>, WrapInterface<IProperties>, GetBool, TStringWrapper<std::string _COMMA const std::string&>);
	MUnpackA2(WrapInterface<IProperties>, SetBool, TStringWrapper<std::string _COMMA const std::string&>, WrapValue<bool>);
	BALU_ENGINE_SCRIPT_END_CLASS;
#endif

}