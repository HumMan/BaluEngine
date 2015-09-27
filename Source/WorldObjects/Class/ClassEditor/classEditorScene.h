#pragma once

#include <vector>
#include <memory>

#include "../IClass.h"
#include "../IClassInstance.h"
#include <EngineInterfaces/IWorld.h>

using namespace EngineInterface;

#include "../../EditableBox/OBBGuiInstance.h"
#include "../../BoxContour/BoxGuiInstance.h"

#include "../../Scene/ISceneInstance.h"

class TClassEditorScene
{
public:
	IBaluClass* source_class; //редактируемый класс

	IBaluSceneInstance* editor_scene_instance; //сцена редактора
	IBaluInstance* editor_scene_class_instance; //экземпл€р редактируемого класса на сцене редактора
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