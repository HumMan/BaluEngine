
#include "SpriteGuiInstance.h"

#include "..\Sprite\SpriteInstance.h"
#include "..\Scene\SceneInstance.h"


TSimpleSpriteInstance::TSimpleSpriteInstance(TBaluSceneInstance* scene, TBaluSprite* source)
{
	scene->AddInstance(this);
	this->scene = scene;
	this->source = source;
	sprite_instance_source.reset(new TBaluClassSpriteInstance(source));
	//TODO сделать что-то с nullptr
	sprite_instance.reset(new TBaluClassInstanceSpriteInstance(sprite_instance_source.get(), nullptr, scene->GetResources()));
}
TOBB2 TSimpleSpriteInstance::GetOBB()
{
	return instance_transform.ToGlobal( sprite_instance->GetOBB());
}
bool TSimpleSpriteInstance::PointCollide(TVec2 scene_space_point)
{
	return sprite_instance_source->PointCollide(instance_transform.ToLocal(scene_space_point));
}

void TSimpleSpriteInstance::UpdateTransform()
{
	sprite_instance->UpdateTranform(this->instance_transform);
}
TSimpleSpriteInstance::~TSimpleSpriteInstance()
{
}

void TSimpleSpriteInstance::QueryAABB(TAABB2 frustum, std::vector<TBaluSpritePolygonInstance*>& results)
{
		if (sprite_instance->GetPolygon()->IsEnable())
		{
			results.push_back(sprite_instance->GetPolygon());
		}
}
