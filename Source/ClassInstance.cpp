#include "ClassInstance.h"

TBaluInstance::TBaluInstance(TBaluClass* source)
{

}

void TBaluInstance::SetTransform(TBaluTransform transform)
{

}

TAABB2 TBaluInstance::GetAABB()
{
	//TODO
	return TAABB2();
}

void TBaluInstance::QueryAABB(TAABB2 frustum, std::vector<TBaluSpritePolygonInstance>& results)
{

}