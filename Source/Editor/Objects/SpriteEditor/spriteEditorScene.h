#pragma once


#include <vector>
#include <memory>

#include <WorldDef/Objects/Sprite/ISprite.h>
#include <WorldInstance/Objects/Scene/ISceneInstance.h>
#include <WorldDef/IWorld.h>

using namespace EngineInterface;

#include "../../EditorGUI/EditableBox/OBBGuiInstance.h"
#include "../../EditorGUI/BoxContour/BoxGuiInstance.h"
#include "../../EditorGUI/PolygonLine/PolygonGuiInstance.h"
#include "../../EditorGUI/SimpleSprite/SpriteGuiInstance.h"

class TSpriteEditorScene
{
private:
	

public:
	IBaluSprite* source_sprite; //редактируемый спрайт
	IBaluSceneInstance* editor_scene_instance; //сцена редактора

	TDrawingHelper* drawing_helper;

	TSpritePolygonAdornmentInstance* sprite_polygon_adornment; //отображение контрола редактирования геометрии срайта
	TSimpleSpriteInstance* sprite_adornment; //отображение редактируемого спрайта

	TBoundaryBoxAdornment* boundary_box;//OBB геометрии спрайта или физики

	TOBBContour* boundary_box_contour;

	void Initialize(IBaluWorld* world, IBaluSprite* source_sprite, IBaluSceneInstance* editor_scene_instance, TDrawingHelper* drawing_helper);
	void Deinitialize();
};