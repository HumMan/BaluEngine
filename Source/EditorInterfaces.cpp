
#include "EditorInterfaces.h"

#include "EditorUtils\SceneEditor\sceneEditor.h"
#include "EditorUtils\SpriteEditor\spriteEditor.h"

EngineInterface::IAbstractEditor* CreateSceneEditor(TDrawingHelperContext drawing_context, EngineInterface::IBaluWorld* world, EngineInterface::IBaluScene* edited_scene, EngineInterface::IBaluSceneInstance* editor_scene_instance)
{
	auto result = new TSceneEditor();
	result->Initialize(drawing_context, world, edited_scene, editor_scene_instance);
	return result;
}

void DestroySceneEditor(EngineInterface::IAbstractEditor* editor)
{
	auto ed = dynamic_cast<TSceneEditor*>(editor);
	ed->Deinitialize();
	delete ed;
}

EngineInterface::IAbstractEditor* CreateSpriteEditor(TDrawingHelperContext drawing_context, EngineInterface::IBaluWorld* world, EngineInterface::IBaluSprite* edited_sprite, EngineInterface::IBaluSceneInstance* editor_scene_instance)
{
	auto result = new TSpriteEditor();
	result->Initialize(drawing_context, world, edited_sprite, editor_scene_instance);
	return result;
}

void DestroySpriteEditor(EngineInterface::IAbstractEditor* editor)
{
	auto ed = dynamic_cast<TSpriteEditor*>(editor);
	ed->Deinitialize();
	delete ed;
}