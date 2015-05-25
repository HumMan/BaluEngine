#pragma once

#include <vector>
#include <memory>

#include "../../EngineInterfaces/IClass.h"
#include "../../EngineInterfaces/IClassInstance.h"
#include "../../EngineInterfaces/IWorld.h"

using namespace EngineInterface;

#include "classEditorAdornments.h"

#include "../BoundaryEditor.h"

#include "../OBBContour.h"

class TClassEditorScene
{
private:
	std::unique_ptr<TClassSpriteAdornment> adornment_instance;


public:
	IBaluClass* source_class; //������������� �����

	IBaluSceneInstance* editor_scene_instance; //����� ���������
	IBaluInstance* editor_scene_class_instance; //��������� �������������� ������ �� ����� ���������
	IBaluClassSprite* selected_instance_source;
	IBaluSpriteInstance* selected_instance;

	TDrawingHelper* drawing_helper;

	TBoundaryBoxAdornment boundary_box;
	std::unique_ptr<TOBBContour> boundary_box_contour;
	IBaluSpriteInstance* hightlighted_instance;
public:
	void Initialize(IBaluWorld* world, IBaluClass* source_class, IBaluSceneInstance* source_scene_instance, TDrawingHelper* drawing_helper);
	void Deinitialize();
};