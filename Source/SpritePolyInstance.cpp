#include "SpritePolyInstance.h"

void TBaluSpritePolygonInstance::UpdateGeometry()
{

}

void TBaluSpritePolygonInstance::SetSpritePolygon(std::string name)
{

}

TBaluSpritePolygon* TBaluSpritePolygonInstance::GetSpritePolygon()
{
	return source;
}

TBaluSpritePolygonInstance::TBaluSpritePolygonInstance(TBaluSpritePolygon* source)
{
	this->source = source;
	local = source->GetTransform();
	vertices = source->GetVertices();
}

void TBaluSpritePolygonInstance::QueryAABB(TAABB2 frustum, std::vector<TBaluSpritePolygonInstance>& results)
{

}

void TBaluSpritePolygonInstance::Render(TRenderCommand& command)
{
	command.vertices = &vertices[0];
	command.vertices_count = vertices.size();
}

void TBaluSpritePolygonInstance::UpdateTransform(TBaluTransform parent)
{
	global.position = parent.position + local.position;
	global.angle = b2Rot(parent.angle.GetAngle() + local.angle.GetAngle());

	vertices = source->GetVertices();

	for (int i = 0; i < vertices.size(); i++)
	{
		vertices[i] = global.GetOrientation()*vertices[i] + global.position;
	}
}

