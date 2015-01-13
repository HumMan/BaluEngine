#pragma once

#include <string>

namespace EngineInterface
{
	class IBaluSprite
	{
	public:
		virtual std::string GetName() = 0;
		virtual void SetName(std::string name) = 0;
	};

	class IBaluWorld
	{
	public:
		//virtual TBaluMaterial* CreateMaterial(char* mat_name) = 0;
		virtual IBaluSprite* CreateSprite(char* sprite_name) = 0;
		//virtual TBaluClass* CreateClass(char* class_name) = 0;
		//virtual TBaluScene* CreateScene(char* scene_name) = 0;

		//virtual TBaluScene* GetScene(char* scene_name) = 0;
	};
}
#include "exportMacro.h"

BALUENGINEDLL_API EngineInterface::IBaluWorld* CreateWorld();