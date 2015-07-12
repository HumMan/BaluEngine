#include "classEditorScene.h"

#include "../../EngineInterfaces/ISceneInstance.h"

void TClassEditorScene::Initialize(IBaluWorld* world, IBaluClass* source_class, IBaluSceneInstance* source_scene_instance, TDrawingHelper* drawing_helper)
{
	this->source_class = source_class;
	this->editor_scene_instance = source_scene_instance;
	this->drawing_helper = drawing_helper;

	//TODO добавление объктов на сцену и удаление с неё
	boundary_box_contour = new TOBBContour();

	//TODO uncomment
	//this->editor_scene_class_instance = dynamic_cast<IBaluInstance*>(editor_scene_instance->CreateInstance(dynamic_cast<TSceneObject*>(source_class), TBaluTransform(), TVec2(1, 1)));

	boundary_box->enable = false;
}

void TClassEditorScene::Deinitialize()
{
	source_class = nullptr;
	drawing_helper = nullptr;
	boundary_box_contour = nullptr;
	boundary_box = nullptr;
}