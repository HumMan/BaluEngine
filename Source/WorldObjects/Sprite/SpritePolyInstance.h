#pragma once

#include "SpritePoly.h"

#include <World\RenderCommand.h>

#include "../../BaluLib/Source/BVolumes/AABB.h"

#include "../Material/MaterialInstance.h"

#include "ISpritePolygonInstance.h"

#include <World\Layers.h>

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
	int layer;
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

	void Render(std::vector<TRenderCommand>& commands, TLayersManagerInstance& layers);

	void UpdateTransform(TBaluTransformWithScale global);
	void UpdateAnimation();

	TBaluSpritePolygon* GetSpritePolygon();

	void SetActiveAnimation(std::string);
};