
#include "EditorInterfaces.h"

#include "EditorUtils\SceneEditor\sceneEditor.h"

EngineInterface::IAbstractEditor* CreateSceneEditor(EngineInterface::IBaluWorld* world, EngineInterface::IBaluScene* source_scene, EngineInterface::IBaluSceneInstance* source_scene_instance)
{
	auto result = new TSceneEditor();
	result->Initialize(world, source_scene, source_scene_instance);
	return result;
}

void DestroySceneEditor(EngineInterface::IAbstractEditor*)
{

}