#pragma once


#include <vector>
#include <memory>

#include "../../EngineInterfaces/ISprite.h"
#include "../../EngineInterfaces/ISceneInstance.h"
#include "../../EngineInterfaces/IWorld.h"

using namespace EngineInterface;

#include "../../SpecialClasses/OBBGuiInstance.h"
#include "../../SpecialClasses/BoxGuiInstance.h"
#include "../../SpecialClasses/PolygonGuiInstance.h"
#include "../../SpecialClasses/SpriteGuiInstance.h"

#include "../../EngineInterfaces/ISceneInstance.h"

class TSpriteEditorScene
{
private:
	

public:
	IBaluSprite* source_sprite; //редактируемый спрайт
	IBaluSceneInstance* editor_scene_instance; //сцена редактора

	TDrawingHelper* drawing_helper;

	//IBaluInstance* selected_instance;
	//IBaluClassSpriteInstance* selected_instance_source;

	TSpritePolygonAdornmentInstance* sprite_polygon_adornment; //отображение контрола редактирования геометрии срайта
	TSimpleSpriteInstance* sprite_adornment; //отображение редактируемого спрайта

	TBoundaryBoxAdornment* boundary_box;//OBB геометрии спрайта или физики

	TOBBContour* boundary_box_contour;

	void Initialize(IBaluWorld* world, IBaluSprite* source_sprite, IBaluSceneInstance* editor_scene_instance, TDrawingHelper* drawing_helper);
	void Deinitialize();
};