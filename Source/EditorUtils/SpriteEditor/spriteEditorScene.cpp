#include "spriteEditorScene.h"

void TSpriteEditorScene::Initialize(IBaluWorld* world, IBaluSprite* source_sprite, IBaluSceneInstance* editor_scene_instance, TDrawingHelper* drawing_helper)
{
	this->source_sprite = source_sprite;
	this->editor_scene_instance = editor_scene_instance;
	this->drawing_helper = drawing_helper;

	//TODO uncomment
	//sprite_polygon_adornment = std::make_unique<TSpritePolygonAdornment>(editor_scene_instance, source_sprite, drawing_helper);
	//sprite_adornment = std::make_unique<TSpriteAdornment>(editor_scene_instance, source_sprite, drawing_helper);
//	obb_adornment = std::make_unique<TSpriteOBBAdornment>(editor_scene_instance, &boundary_box, drawing_helper);
	//obb_adornment = std::make_unique<TSpriteOBBAdornment>(editor_scene_instance, (IVisualAdornment*)&boundary_box, drawing_helper);
	//boundary_box_contour = std::make_unique<TOBBContour>(editor_scene_instance, drawing_helper);
	//auto t = source_scene->GetInstance(0)->GetTransform();

	boundary_box->enable = false;
}

void TSpriteEditorScene::Deinitialize()
{
	source_sprite = nullptr;
	drawing_helper = nullptr;
	//sprite_adornment.reset();
}