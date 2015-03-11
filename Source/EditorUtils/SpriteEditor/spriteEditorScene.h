#pragma once


#include <vector>
#include <memory>

#include "../../EngineInterfaces/ISprite.h"
#include "../../EngineInterfaces/ISceneInstance.h"
#include "../../EngineInterfaces/IWorld.h"

using namespace EngineInterface;

#include "spriteEditorAdornments.h"

#include "../BoundaryEditor.h"

#include "../OBBContour.h"

class TSpriteEditorScene
{
private:
	std::unique_ptr<TSpritePolygonAdornment> sprite_polygon_adornment;
	std::unique_ptr<TSpritePolygonOBBAdornment> sprite_polygon_obb_adornment;

public:
	IBaluSprite* source_sprite;
	IBaluSceneInstance* editor_scene_instance;

	TDrawingHelper* drawing_helper;

	IBaluInstance* selected_instance;
	IBaluSpriteInstance* selected_instance_source;

	TBoundaryBoxAdornment boundary_box;
	std::unique_ptr<TOBBContour> boundary_box_contour;
	IBaluInstance* hightlighted_instance;

	void Initialize(IBaluWorld* world, IBaluSprite* source_sprite, IBaluSceneInstance* editor_scene_instance, TDrawingHelper* drawing_helper)
	{
		this->source_sprite = source_sprite;
		this->editor_scene_instance = editor_scene_instance;
		this->drawing_helper = drawing_helper;

		sprite_polygon_adornment = std::make_unique<TSpritePolygonAdornment>(editor_scene_instance, source_sprite, drawing_helper);
		sprite_polygon_obb_adornment = std::make_unique<TSpritePolygonOBBAdornment>(editor_scene_instance, (IVisualAdornment*)&boundary_box, drawing_helper);
		boundary_box_contour = std::make_unique<TOBBContour>(editor_scene_instance, drawing_helper);
		//auto t = source_scene->GetInstance(0)->GetTransform();

		boundary_box.enable = false;
	}
};