#include "Scene.h"

#include "../Class/Class.h"

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
	:layers(this), TWorldObject(world, name)
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
	instances.push_back(std::unique_ptr<TTransformedClass>(new TTransformedClass(balu_class)));
	TChangeListenerArray::OnElementAdded(TWorldObjectSubType::SceneClassInstance);
	return instances.back().get();
}

void TScene::DestroyInstance(ISceneObject* instance)
{
	auto iter = std::find_if(instances.begin(), instances.end(), 
		[&](std::unique_ptr<ISceneObject>& p){return p.get() == instance; });
	if (iter != instances.end())
	{
		instances.erase(iter);
	}
	else
	{
		throw std::invalid_argument("������ �� ��������� �� ������ �����");
	}
}