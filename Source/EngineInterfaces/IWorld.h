#pragma once

#include "IMaterial.h"
#include "ISprite.h"
#include "IClass.h"
#include "IScene.h"

namespace EngineInterface
{
	class IBaluWorld
	{
	public:
		virtual IBaluMaterial* CreateMaterial(char* mat_name) = 0;
		virtual IBaluSprite* CreateSprite(char* sprite_name) = 0;
		virtual IBaluClass* CreateClass(char* class_name) = 0;
		virtual IBaluScene* CreateScene(char* scene_name) = 0;

		virtual IBaluScene* GetScene(char* scene_name) = 0;

		virtual IBaluPhysShapeFactory* GetPhysShapeFactory() = 0;
	};
}