#pragma once

#include "SpritePoly.h"

#include "RenderCommand.h"

#include "../../BaluLib/Source/BVolumes/AABB.h"

#include "MaterialInstance.h"

#include "EngineInterfaces\ISpritePolygonInstance.h"

using namespace EngineInterface;

class TBaluSpritePolygonInstance: public EngineInterface::IBaluSpritePolygonInstance
{
private:
	TMaterialInstance material;
	TBaluSpritePolygon* source;
	
	std::vector<TVec2> vertices; //in scene coordinates
	std::vector<TVec2> tex_coords;
	
	std::string active_animation_line;

	int active_desc_index;
	int active_frame_index;

	float animation_time_from_start;
	
	void NextFrame();

	void UpdateGeometry();

	bool enable;
public:

	bool IsEnable()
	{
		return enable;
	}

	void SetEnable(bool enable)
	{
		this->enable = enable;
	}

	TBaluSpritePolygonInstance(TBaluSpritePolygon* source, TResources* resources);

	//void QueryAABB(TAABB2 frustum, std::vector<TBaluSpritePolygonInstance>& results);

	void Render(TRenderCommand& command);

	void UpdateTransform(TBaluTransformWithScale parent, TBaluTransformWithScale class_transform, TBaluTransformWithScale sprite_transform);
	void UpdateAnimation();

	TBaluSpritePolygon* GetSpritePolygon();

	void SetActiveAnimation(std::string);
};