#include "spriteEditorScene.h"

#include "../../EditableBox/OBBGuiInstance.h"
#include "../../SimpleSprite/SpriteGuiInstance.h"

#include "../../Scene/SceneInstance.h"

void TSpriteEditorScene::Initialize(IBaluWorld* world, IBaluSprite* source_sprite, IBaluSceneInstance* editor_scene_instance, TDrawingHelper* drawing_helper)
{
	this->source_sprite = source_sprite;
	this->editor_scene_instance = editor_scene_instance;
	this->drawing_helper = drawing_helper;

	boundary_box_contour = new TOBBContour(dynamic_cast<TBaluSceneInstance*>(editor_scene_instance));
	boundary_box = new TBoundaryBoxAdornment(dynamic_cast<TBaluSceneInstance*>(editor_scene_instance));
	boundary_box->enable = false;

	sprite_adornment=(new TSimpleSpriteInstance(dynamic_cast<TBaluSceneInstance*>(editor_scene_instance), dynamic_cast<TBaluSprite*>(source_sprite)));

	sprite_polygon_adornment = new TSpritePolygonAdornmentInstance(dynamic_cast<TBaluSceneInstance*>(editor_scene_instance));
	sprite_polygon_adornment->SetVisible(false);
}

void TSpriteEditorScene::Deinitialize()
{
	source_sprite = nullptr;
	drawing_helper = nullptr;
	//sprite_adornment.reset();
}