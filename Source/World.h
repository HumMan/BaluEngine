#pragma once

#include "Material.h"
#include "Sprite.h"
#include "Class.h"
#include "Scene.h"

#include <map>

class TBaluWorld
{
private:
	std::map<std::string, TBaluMaterial> materials;
	std::map<std::string, TBaluSprite> sprites;
	std::map<std::string, TBaluClass> classes;
	std::map<std::string, TBaluScene> scenes;
public:
	virtual ~TBaluWorld();

	TBaluMaterial* CreateMaterial(char* mat_name);
	TBaluSprite* CreateSprite(char* sprite_name);
	TBaluClass* CreateClass(char* class_name);
	TBaluScene* CreateScene(char* scene_name);

	TBaluScene* GetScene(char* scene_name);

	TVec2 ScreenToWorld(const TVec2& v);
	TVec2 WorldToScreen(const TVec2& v);

	void SetAcitveScene();
};