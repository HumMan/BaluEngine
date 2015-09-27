#pragma once

#include <vector>
#include <memory>

#include "../../EngineInterfaces/IClass.h"
#include "../../EngineInterfaces/IClassInstance.h"
#include "../../EngineInterfaces/IWorld.h"

using namespace EngineInterface;

#include "../../SpecialClasses/OBBGuiInstance.h"
#include "../../SpecialClasses/BoxGuiInstance.h"

#include "../../EngineInterfaces/ISceneInstance.h"

class TClassEditorScene
{
public:
	IBaluClass* source_class; //������������� �����

	IBaluSceneInstance* editor_scene_instance; //����� ���������
	IBaluInstance* editor_scene_class_instance; //��������� �������������� ������ �� ����� ���������
	IBaluClassSpriteInstance* selected_instance_source;
	IBaluClassInstanceSpriteInstance* selected_instance;

	TDrawingHelper* drawing_helper;

	TBoundaryBoxAdornment* boundary_box;
	TOBBContour* boundary_box_contour;

	IBaluClassInstanceSpriteInstance* hightlighted_instance;
public:
	void Initialize(IBaluWorld* world, IBaluClass* source_class, IBaluSceneInstance* source_scene_instance, TDrawingHelper* drawing_helper);
	void Deinitialize();
};