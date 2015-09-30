#pragma once

#include <baluLib.h>

#include <Interfaces\BaluEngineInterface.h>

using namespace EngineInterface;

namespace Editor
{
	public ref class TPropertiesObject
	{
	};

	public ref class TPropertiesRegistry
	{
	public:
		static TPropertiesObject^ CreateProperties(IBaluWorld* world, TBaluWorldObject* obj_def);
	};
}
