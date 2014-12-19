#pragma once

#include "Sprite.h"

#include "Class.h"

#include "SpritePolyInstance.h"
#include "PhysShapeInstance.h"

class TBaluSpriteInstance
{
	TBaluClass::TBaluSpriteInstance* source;
	TBaluTransform local;
	TBaluTransform global;
	
	TBaluSprite* sprite;
	
	std::unique_ptr<TBaluPhysShapeInstance> phys_shape;
	TBaluSpritePolygonInstance polygon;
	
	TAABB2 GetAABB();

	void GetSpriteGeometry(std::vector<int> index, std::vector<TVec2> vertex);
	void GetSpriteGeometrySize(int& indices, int& vertices);

	void PlayAnimation(std::string animation_name, bool loop);
	void PauseAnimation(bool pause);
	void StopAnimation();

	void QueryAABB(TAABB2 frustum, std::vector<TBaluSpritePolygonInstance>& results);
};