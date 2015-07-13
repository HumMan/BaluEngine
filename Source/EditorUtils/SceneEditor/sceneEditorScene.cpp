#include "sceneEditorScene.h"
#include "../../SpecialClasses/OBBGuiInstance.h"

void TSceneEditorScene::Initialize(IBaluWorld* world, IBaluScene* source_scene, IBaluSceneInstance* editor_scene_instance, TDrawingHelper* drawing_helper)
{
	this->source_scene = source_scene;
	this->editor_scene_instance = editor_scene_instance;
	this->drawing_helper = drawing_helper;

	//adornment_instance = std::make_unique<TClassInstanceAdornment>(editor_scene_instance, (IVisualAdornment*)&boundary_box, drawing_helper);
	boundary_box_contour = new TOBBContour();
	//auto t = source_scene->GetInstance(0)->GetTransform();

	boundary_box = new TBoundaryBoxAdornment();

	boundary_box->enable = false;

	//boundary_box.SetBoundary(TOBB2(t.position, t.GetOrientation(), TAABB2(TVec2(0, 0), TVec2(1, 1))));

	//for (int i = 0; i < source_scene->GetInstancesCount(); i++)
	//{
	//	auto v = source_scene->GetInstance(i);
	//	auto new_box = new TClassInstanceAdornment(v);
	//	scene.boundaries.emplace_back(std::unique_ptr<TClassInstanceAdornment>(new_box));
	//}
}

void TSceneEditorScene::Deinitialize()
{
	source_scene = nullptr;
	drawing_helper = nullptr;
	//adornment_instance.reset();
	//boundary_box_contour.reset();
}