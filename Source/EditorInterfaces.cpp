
#include "EditorInterfaces.h"

#include "EditorUtils\SceneEditor\sceneEditor.h"

EngineInterface::IAbstractEditor* CreateSceneEditor(TDrawingHelperContext drawing_context, EngineInterface::IBaluWorld* world, EngineInterface::IBaluScene* source_scene, EngineInterface::IBaluSceneInstance* source_scene_instance)
{
	auto result = new TSceneEditor();
	result->Initialize(drawing_context, world, source_scene, source_scene_instance);
	return result;
}

void DestroySceneEditor(EngineInterface::IAbstractEditor*)
{

}