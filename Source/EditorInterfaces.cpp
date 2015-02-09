
#include "EditorInterfaces.h"

#include "EditorUtils\SceneEditor\sceneEditor.h"

EngineInterface::IAbstractEditor* CreateSceneEditor(TScreen* screen, TView* view, EngineInterface::IViewport* viewport, EngineInterface::IBaluWorld* world, EngineInterface::IBaluScene* source_scene, EngineInterface::IBaluSceneInstance* source_scene_instance)
{
	auto result = new TSceneEditor();
	result->Initialize(screen, view, viewport, world, source_scene, source_scene_instance);
	return result;
}

void DestroySceneEditor(EngineInterface::IAbstractEditor*)
{

}