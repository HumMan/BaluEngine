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
	

public:
	IBaluSprite* source_sprite;
	IBaluSceneInstance* editor_scene_instance;

	TDrawingHelper* drawing_helper;

	IBaluInstance* selected_instance;
	IBaluSpriteInstance* selected_instance_source;

	std::unique_ptr<TSpritePolygonAdornment> sprite_polygon_adornment;
	std::unique_ptr<TSpriteAdornment> sprite_adornment;

	std::unique_ptr<TSpriteOBBAdornment> obb_adornment;
	TBoundaryBoxAdornment boundary_box;
	std::unique_ptr<TOBBContour> boundary_box_contour;

	IBaluWorld* world;

	void Initialize(IBaluWorld* world, IBaluSprite* source_sprite, IBaluSceneInstance* editor_scene_instance, TDrawingHelper* drawing_helper);
	void Deinitialize();
};