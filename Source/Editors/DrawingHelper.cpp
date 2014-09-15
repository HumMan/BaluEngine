#include <baluRender.h>

#include "DrawingHelper.h"
#include "BoundaryEditor.h"
#include "editorResourses.h"

TDrawingHelper::TDrawingHelper(TBaluRender* render, TEditorResourses* resources)
{
	this->render = render;
	this->resources = resources;
}

void TDrawingHelper::DrawSprite(TBaluSpriteDef* sprite)
{
	std::vector<TVec2> pos, tex;
	pos.push_back(TVec2(0, 0));
	pos.insert(pos.end(), sprite->polygon_vertices.begin(), sprite->polygon_vertices.end());
	pos.insert(pos.end(), sprite->polygon_vertices[0]);
	tex = pos;
	TStreamsDesc desc;
	desc.AddStream(TStream::Vertex, TDataType::Float, 2, &*pos.begin());
	desc.AddStream(TStream::TexCoord, TDataType::Float, 2, &*tex.begin());
	//render->Set.PolygonMode(TPolygonMode::Line);
	render->Draw(desc, TPrimitive::TriangleFan, sprite->polygon_vertices.size() + 2);
}

void TDrawingHelper::DrawBoundary(TOBB<float, 2> boundary)
{
	std::vector<TVec2> v;
	boundary.DrawLines(v);
	TStreamsDesc desc;
	desc.Clear();
	desc.AddStream(TStream::Vertex, TDataType::Float, 2, &*v.begin());
	render->Draw(desc, TPrimitive::Lines, v.size());
}

void TDrawingHelper::DrawLine(TVec2 p0, TVec2 p1)
{
	TVec2 v[2] = { p0, p1 };
	TStreamsDesc desc;
	desc.AddStream(TStream::Vertex, TDataType::Float, 2, &v[0]);
	render->Draw(desc, TPrimitive::Lines, 2);
}

void TDrawingHelper::DrawPoint(TVec2 p)
{
	TVec2 v[1] = { p };
	TStreamsDesc desc;
	desc.AddStream(TStream::Vertex, TDataType::Float, 2, &v[0]);

	render->Set.PointSize(5);

	render->Draw(desc, TPrimitive::Points, 1);

	render->Set.PointSize(1);
}


void TDrawingHelper::DrawSpriteContour(TBaluSpriteDef* sprite)
{
	TStreamsDesc desc;
	desc.Clear();
	desc.AddStream(TStream::Vertex, TDataType::Float, 2, &*sprite->polygon_vertices.begin());
	desc.AddStream(TStream::TexCoord, TDataType::Float, 2, &*sprite->tex_coordinates.begin());
	render->Draw(desc, TPrimitive::LineLoop, sprite->polygon_vertices.size());
}

void TDrawingHelper::ActivateMaterial(TBaluMaterialDef* material)
{
	TTextureId tex_id = resources->CreateTextureFromFile(material->image_path);
	render->Texture.Enable(true);
	render->Texture.Bind(tex_id);
}

void TDrawingHelper::DeactivateMaterial(TBaluMaterialDef* material)
{
	render->Texture.Enable(false);
}

void TDrawingHelper::SetSelectedPointColor()
{
	render->Set.Color(0, 1, 0);
}
void TDrawingHelper::SetSelectedBoundaryColor()
{
	render->Set.Color(1, 0, 0);
}
void TDrawingHelper::UnsetColor()
{
	render->Set.Color(1, 1, 1, 1);
}