#pragma once

#include <string>

namespace EngineInterface
{
	class IProperties;
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
	};

	class IProperties
	{
	public:
		virtual void SetBool(std::string name, bool value) = 0;
		virtual bool GetBool(std::string name) = 0;
	};
}