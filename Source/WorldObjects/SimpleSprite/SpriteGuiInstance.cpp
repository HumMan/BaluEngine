
#include "SpriteGuiInstance.h"

#include "..\Sprite\ISpriteInstance.h"
#include "..\Scene\ISceneInstance.h"

using namespace EngineInterface;

TSimpleSpriteInstance::TSimpleSpriteInstance(TBaluSceneInstance* scene, TBaluSprite* source)
	:TSceneObjectInstance(scene)
{
	
	this->scene = scene;
	this->source = source;
	sprite_instance_source.reset(new TBaluTransformedSprite(source));
	sprite_instance.reset(new TBaluTransformedSpriteInstance(sprite_instance_source.get(), scene->GetResources(), this));
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
	sprite_instance->UpdateTransform(this->instance_transform);
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
