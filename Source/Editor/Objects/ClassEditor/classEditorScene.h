#pragma once

#include <vector>
#include <memory>

#include <WorldDef/Objects/Class/IClass.h>
#include <WorldInstance/Objects/Class/IClassInstance.h>

using namespace EngineInterface;

#include "../../EditorGui/EditableBox/OBBGuiInstance.h"
#include "../../EditorGui/BoxContour/BoxGuiInstance.h"

#include <WorldInstance/Objects/Scene/ISceneInstance.h>

class TClassEditorScene
{
public:
	IBaluClass* source_class; //������������� �����

	IBaluSceneInstance* editor_scene_instance; //����� ���������
	std::unique_ptr<TBaluTransformedClass> transformed_class;
	IBaluTransformedClassInstance* editor_scene_class_instance; //��������� �������������� ������ �� ����� ���������
	IBaluTransformedSprite* selected_instance_source;
	IBaluTransformedSpriteInstance* selected_instance;

	TDrawingHelper* drawing_helper;

	TBoundaryBoxAdornment* boundary_box;
	TOBBContour* boundary_box_contour;

	IBaluTransformedSpriteInstance* hightlighted_instance;
public:
	void Initialize(IBaluWorld* world, IBaluClass* source_class, IBaluSceneInstance* source_scene_instance, TDrawingHelper* drawing_helper);
	void Deinitialize();
};