#include "World.h"

TBaluPolygonShape* TBaluPhysShapeFactory::CreatePolygonShape()
{
	return new TBaluPolygonShape();
}

TBaluCircleShape* TBaluPhysShapeFactory::CreateCircleShape(float radius)
{
	return new TBaluCircleShape(radius);
}

TBaluCircleShape* TBaluPhysShapeFactory::CreateCircleShape(float radius, TVec2 pos)
{
	return new TBaluCircleShape(radius,pos);
}

TBaluBoxShape* TBaluPhysShapeFactory::CreateBoxShape(float width, float height)
{
	return new TBaluBoxShape(width, height);
}

//void TScreen::AddView(TView view)
//{
//	views.push_back(view);
//}
//
//int TScreen::GetViewsCount()
//{
//	return views.size();
//}
//
//TView TScreen::GetView(int i)
//{
//	return views[i];
//}
//
//void TScreen::RemoveView(int i)
//{
//	views.erase(views.begin()+i);
//}

TBaluWorld::TBaluWorld()
{
	callback_active_type.active_type = 0;
}

bool TBaluWorld::TryFindClass(char* class_name, TBaluClass*& result)
{
	auto iter = classes.find(class_name);
	if (iter == classes.end())
	{
		return false;
	}
	else
	{
		return result = (TBaluClass*)&iter->second;
	}
}

bool TBaluWorld::TryFindClass(char* class_name, EngineInterface::IBaluClass*& result)
{
	TBaluClass* r;
	auto result0 = TryFindClass(class_name, r);
	result = dynamic_cast<EngineInterface::IBaluClass*>(r);
	return result0;
}

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

TBaluPhysShapeFactory* TBaluWorld::GetPhysShapeFactory()
{
	return &shape_factory;
}

void TBaluWorld::OnMouseDown(CallbackWithData<MouseUpDownCallback> callback)
{
	mouse_down_callbacks.push_back(callback);
}

void TBaluWorld::OnMouseUp(CallbackWithData<MouseUpDownCallback> callback)
{
	mouse_up_callbacks.push_back(callback);
}

void TBaluWorld::OnMouseMove(CallbackWithData<MouseUpDownCallback> callback)
{
	mouse_move_callbacks.push_back(callback);
}