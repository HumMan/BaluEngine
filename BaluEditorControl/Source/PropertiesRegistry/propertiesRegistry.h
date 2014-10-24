#pragma once

#include <baluEngine.h>

namespace Editor
{
	public ref class TPropertiesObject
	{
	};

	public ref class TPropertiesRegistry
	{
	public:
		static TPropertiesObject^ CreateProperties(TBaluWorldDef* world, TWorldObjectDef* obj_def);
	};
}
