#pragma once

#include <baluLib.h>

#include "SpriteGui.h"

#include <Common/RenderCommand.h>

#include <World\IWorld.h>
#include "../Material/IMaterialInstance.h"

#include <memory>
namespace EngineInterface
{
	class TBaluTransformedSpriteInstance;
	class TBaluTransformedSprite;
	class TBaluSprite;
}
using namespace EngineInterface;

class TSimpleSpriteInstance : public EngineInterface::TSceneObjectInstance
{
	std::unique_ptr<TBaluTransformedSprite> sprite_instance_source;
	std::unique_ptr<TBaluTransformedSpriteInstance> sprite_instance;
	TBaluTransformWithScale instance_transform;

	TBaluSceneInstance* scene;
	TBaluSprite* source;
public:
	TSimpleSpriteInstance(TBaluSceneInstance* scene, TBaluSprite* source);
	virtual TOBB2 GetOBB();
	virtual void SetTransform(TBaluTransform transform){ instance_transform.transform = transform; }
	virtual TBaluTransform GetTransform(){ return instance_transform.transform; }
	virtual TVec2 GetScale(){ return instance_transform.scale; }
	virtual void SetScale(TVec2 scale){ instance_transform.scale = scale; }
	virtual bool PointCollide(TVec2 scene_space_point);
	virtual void UpdateTransform();
	virtual void QueryAABB(TAABB2 frustum, std::vector<TBaluSpritePolygonInstance*>& results);
	virtual ~TSimpleSpriteInstance();
};