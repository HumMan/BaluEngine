#pragma once

#include "SpritePoly.h"

#include "RenderCommand.h"

#include "../BaluLib/Source/BVolumes/AABB.h"

class TBaluSpritePolygonInstance
{
private:
	TBaluSpritePolygon* source;
	
	TBaluTransform local;
	TBaluTransform global;

	//compiled geometry
	bool is_dirty;
	std::vector<int> indices;
	std::vector<TVec2> vertices; //in scene coordinates
	
	void TriangulateGeometry();
public:
	void QueryAABB(TAABB2 frustum, std::vector<TBaluSpritePolygonInstance>& results);

	void Render(TRenderCommand& command);
	void UpdateTransform(TBaluTransform parent_transform);
	void SetSpritePolygon(std::string name);
	TBaluSpritePolygon* GetSpritePolygon();
};