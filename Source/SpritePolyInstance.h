#pragma once

#include "SpritePoly.h"

#include "RenderCommand.h"

#include "../BaluLib/Source/BVolumes/AABB.h"

#include "MaterialInstance.h"

class TBaluSpritePolygonInstance
{
private:
	TMaterialInstance material;
	TBaluSpritePolygon* source;
	
	TBaluTransform local;
	TBaluTransform global;

	//compiled geometry
	bool is_dirty;
	//std::vector<int> indices;
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

	TBaluSpritePolygonInstance(TBaluSpritePolygon* source, TResourses* resources);

	void QueryAABB(TAABB2 frustum, std::vector<TBaluSpritePolygonInstance>& results);

	void Render(TRenderCommand& command);

	void UpdateTransform(TBaluTransform parent);
	void UpdateAnimation();

	void SetSpritePolygon(std::string name);
	TBaluSpritePolygon* GetSpritePolygon();

	void SetActiveAnimation(std::string);
};