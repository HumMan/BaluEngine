#include "Scene.h"

#include "../Class/Class.h"

#include "SceneCommands.h"

using namespace BaluEngine::WorldDef;
using namespace BaluEngine::WorldDef::Internal;
using namespace BaluLib;

#include <algorithm>

TVec2 IScene::FromViewportToScene(IViewport* viewport, TVec2 viewport_coord)
{
	return ((viewport_coord - TVec2(0.5, 0.5))).ComponentMul(viewport->GetAABB().GetSize()) + viewport->GetAABB().GetPosition();
}

TVec2 IScene::FromSceneToViewport(IViewport* viewport, TVec2 scene_coord)
{
	//return (scene_coord - viewport->GetAABB().GetPosition()) / viewport->GetAABB().GetSize();
	return ((scene_coord - viewport->GetAABB().GetPosition()) / viewport->GetAABB().GetSize())+TVec2(0.5,0.5);
}

TViewport* TScene::CreateViewport(const std::string& name)
{
	auto it = viewports.find(name);
	if(it != viewports.end())
		throw std::invalid_argument("Viewport � ������ ������ ��� ����������");
	return &(viewports[name]);
}

TScene::TScene(const char* name, IWorld* world)
	:TWorldObject(world, name)
{
}

TViewport* TScene::FindViewport(const std::string& name)
{
	auto it = viewports.find(name);
	if (it == viewports.end())
		return nullptr;
	return &it->second;
}

int TScene::GetInstancesCount()
{
	return instances.size();
}
ISceneObject* TScene::GetInstance(int index)
{
	return instances[index].get();
}

ISceneObject* TScene::CreateInstance(IClass* _balu_class)
{
	auto balu_class = dynamic_cast<TClass*>(_balu_class);
	auto new_instance = new TTransformedClass(balu_class, this);
	instances.push_back(std::unique_ptr<TTransformedClass>(new_instance));

	if (world->GetCommandList()->CanAddCommands())
	{
		auto command = new CreateSceneObject(world, this, instances.size() - 1, new_instance);
		world->GetCommandList()->AddCommmand(command);
	}

	return instances.back().get();
}

void TScene::InsertInstance(ISceneObject* obj, int index)
{
	instances.insert(instances.begin() + index, std::unique_ptr<ISceneObject>(obj));

	if (world->GetCommandList()->CanAddCommands())
	{
		auto command = new CreateSceneObject(world, this, index, obj);
		world->GetCommandList()->AddCommmand(command);
	}
}

int TScene::GetInstanceIndex(ISceneObject* instance)const
{
	auto iter = std::find_if(instances.begin(), instances.end(),
		[&](const std::unique_ptr<ISceneObject>& p) {return p.get() == instance; });

	return std::distance(instances.begin(), iter);
}

void TScene::DestroyInstance(int index)
{
	auto iter = instances.begin() + index;
	if (world->GetCommandList()->CanAddCommands())
	{
		auto command = new DestroySceneObject(world, this, index, iter->get());
		world->GetCommandList()->AddCommmand(command);
	}

	instances.erase(iter);
}

void TScene::DestroyInstance(ISceneObject* instance)
{
	auto iter = std::find_if(instances.begin(), instances.end(), 
		[&](std::unique_ptr<ISceneObject>& p){return p.get() == instance; });
	if (iter != instances.end())
	{
		if (world->GetCommandList()->CanAddCommands())
		{
			auto command = new DestroySceneObject(world, this, std::distance(instances.begin(), iter), iter->get());
			world->GetCommandList()->AddCommmand(command);
		}

		instances.erase(iter);
	}
	else
	{
		throw std::invalid_argument("������ �� ��������� �� ������ �����");
	}
}