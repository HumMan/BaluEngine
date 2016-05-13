#pragma once

#include <string>
#include <map>
#include <memory>

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

	class IProperties
	{
	public:
		virtual bool HasProperty(const std::string& name, PropertyType& type) = 0;
		virtual void SetBool(const std::string& name, bool value) = 0;
		virtual bool GetBool(const std::string& name) = 0;
	};

#ifdef BALUENGINEDLL_EXPORTS

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

template<class T>
class TPropertyValue : public TProperty
{
protected:
	T value;
public:
	TPropertyValue()
	{

	}
	TPropertyValue(const T& value)
	{
		this->value = value;
	}
	T* GetValue()
	{
		return &value;
	}
	void SetValue(const T& value)
	{
		this->value = value;
	}
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

}
