#include "World.h"


TBaluMaterial* TBaluWorld::CreateMaterial(char* mat_name)
{
	auto iter = materials.find(mat_name);
	if (iter == materials.end())
	{
		materials[mat_name].SetName(mat_name);
		return &materials[mat_name];
	}
	else
	{
		throw std::invalid_argument("Материал с данным имененем уже существует");
	}
}

TBaluSprite* TBaluWorld::CreateSprite(char* sprite_name)
{
	auto iter = sprites.find(sprite_name);
	if (iter == sprites.end())
	{
		sprites[sprite_name].SetName(sprite_name);
		return &sprites[sprite_name];
	}
	else
	{
		throw std::invalid_argument("Спрайт с данным имененем уже существует");
	}
}
TBaluClass* TBaluWorld::CreateClass(char* class_name)
{
	auto iter = classes.find(class_name);
	if (iter == classes.end())
	{
		classes[class_name].SetName(class_name);
		return &classes[class_name];
	}
	else
	{
		throw std::invalid_argument("Класс с данным имененем уже существует");
	}
}
TBaluScene* TBaluWorld::CreateScene(char* scene_name)
{
	auto iter = scenes.find(scene_name);
	if (iter == scenes.end())
	{
		scenes[scene_name].SetName(scene_name);
		return &scenes[scene_name];
	}
	else
	{
		throw std::invalid_argument("Сцена с данным имененем уже существует");
	}
}

TBaluScene* TBaluWorld::GetScene(char* scene_name)
{
	auto iter = scenes.find(scene_name);
	if (iter != scenes.end())
	{
		return &iter->second;
	}
	else
	{
		throw std::invalid_argument("Сцена с данным имененем отсутсвует");
	}
}
