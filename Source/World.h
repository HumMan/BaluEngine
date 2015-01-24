#pragma once

#include "Material.h"
#include "Sprite.h"
#include "Class.h"
#include "Scene.h"

#include <map>

#include "EngineInterfaces.h"

class TBaluPhysShapeFactory : public EngineInterface::IBaluPhysShapeFactory
{
public:
	TBaluPolygonShape* CreatePolygonShape();
	TBaluCircleShape* CreateCircleShape(float radius);
	TBaluCircleShape* CreateCircleShape(float radius, TVec2 pos);
	TBaluBoxShape* CreateBoxShape(float width, float height);
};

class TBaluWorld : public EngineInterface::IBaluWorld
{
private:
	std::map<std::string, TBaluMaterial> materials;
	std::map<std::string, TBaluSprite> sprites;
	std::map<std::string, TBaluClass> classes;
	std::map<std::string, TBaluScene> scenes;

	TBaluPhysShapeFactory shape_factory;
public:

	TBaluMaterial* CreateMaterial(char* mat_name);
	TBaluSprite* CreateSprite(char* sprite_name);
	TBaluClass* CreateClass(char* class_name);
	TBaluScene* CreateScene(char* scene_name);

	TBaluScene* GetScene(char* scene_name);

	TBaluPhysShapeFactory* GetPhysShapeFactory();
};