#pragma once

#include <baluLib.h>

#include "../Source/EngineInterfaces.h"
#include "../Source/EditorInterfaces.h"

using namespace EngineInterface;


namespace Editor
{
	public ref class TPropertiesObject
	{
	};

	public ref class TPropertiesRegistry
	{
	public:
		static TPropertiesObject^ CreateProperties(IBaluWorld* world, IBaluWorldObject* obj_def);
	};
}
