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
	};

	enum class PropertyType
	{
		Bool,
		Int,
		Float,
		String,
		SceneClassInstance
	};

	class IProperties
	{
	public:
		virtual void SetBool(const std::string& name, bool value) = 0;
		virtual bool GetBool(const std::string& name) = 0;
		virtual void SetSceneClassInstance(const std::string& name, IBaluSceneClassInstance* value) = 0;
		virtual IBaluSceneClassInstance* GetSceneClassInstance(const std::string& name) = 0;
	};
}