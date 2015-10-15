#pragma once


#include <vector>
#include <memory>

#include "../ISprite.h"
#include "../../Scene/ISceneInstance.h"
#include <World/IWorld.h>

using namespace EngineInterface;

#include "../../EditableBox/OBBGuiInstance.h"
#include "../../BoxContour/BoxGuiInstance.h"
#include "../../PolygonLine/PolygonGuiInstance.h"
#include "../../SimpleSprite/SpriteGuiInstance.h"

#include "../../Scene/ISceneInstance.h"

class TSpriteEditorScene
{
private:
	

public:
	IBaluSprite* source_sprite; //������������� ������
	IBaluSceneInstance* editor_scene_instance; //����� ���������

	TDrawingHelper* drawing_helper;

	//IBaluTransformedClassInstance* selected_instance;
	//IBaluTransformedSprite* selected_instance_source;

	TSpritePolygonAdornmentInstance* sprite_polygon_adornment; //����������� �������� �������������� ��������� ������
	TSimpleSpriteInstance* sprite_adornment; //����������� �������������� �������

	TBoundaryBoxAdornment* boundary_box;//OBB ��������� ������� ��� ������

	TOBBContour* boundary_box_contour;

	void Initialize(IBaluWorld* world, IBaluSprite* source_sprite, IBaluSceneInstance* editor_scene_instance, TDrawingHelper* drawing_helper);
	void Deinitialize();
};