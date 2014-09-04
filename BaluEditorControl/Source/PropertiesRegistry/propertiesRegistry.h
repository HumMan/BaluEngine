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
		TPropertiesObject^ CreateProperties(TWorldObjectDef* obj_def);
	};
}
