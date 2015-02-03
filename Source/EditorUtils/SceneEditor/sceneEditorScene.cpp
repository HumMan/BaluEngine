#include "sceneEditorScene.h"



void TSceneEditorScene::Initialize(IBaluWorld* world, IBaluScene* source_scene)
{
	//this->source_scene = source_scene;

	adornment_instance = std::make_unique<TClassInstanceAdornment>(editor_temp_scene_instance);

	//for (int i = 0; i < source_scene->GetInstancesCount(); i++)
	//{
	//	auto v = source_scene->GetInstance(i);
	//	auto new_box = new TClassInstanceAdornment(v);
	//	scene.boundaries.emplace_back(std::unique_ptr<TClassInstanceAdornment>(new_box));
	//}
}

//void TClassInstanceAdornment::OnBoxChange(TOBB<float, 2> old_box, TOBB<float, 2> new_box)
//{
	//class_instance->instance_transform.position = new_box.GetPos();

	//auto orient = new_box.GetOrient();
	//sprite_polygon_def->transform.angle.c = orient[0][0];
	//sprite_polygon_def->transform.angle.s = orient[0][1];

	//auto old_aabb = old_box.GetLocalAABB();
	//auto new_aabb = new_box.GetLocalAABB();

	//auto trans = new_aabb.GetSize() / old_aabb.GetSize();

	//for (int i = 0; i < sprite_polygon_def->polygon_vertices.size(); i++)
	//{
	//	sprite_polygon_def->polygon_vertices[i][0] *= trans[0];
	//	sprite_polygon_def->polygon_vertices[i][1] *= trans[1];
	//}
//}