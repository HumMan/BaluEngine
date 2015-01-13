#pragma once

#include "Material.h"
#include "Sprite.h"
#include "Class.h"
#include "Scene.h"

#include <map>

#include "EngineInterfaces.h"

class TBaluWorld : public EngineInterface::IBaluWorld
{
private:
	std::map<std::string, TBaluMaterial> materials;
	std::map<std::string, TBaluSprite> sprites;
	std::map<std::string, TBaluClass> classes;
	std::map<std::string, TBaluScene> scenes;
public:

	TBaluMaterial* CreateMaterial(char* mat_name);
	TBaluSprite* CreateSprite(char* sprite_name);
	TBaluClass* CreateClass(char* class_name);
	TBaluScene* CreateScene(char* scene_name);

	TBaluScene* GetScene(char* scene_name);
};