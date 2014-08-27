#include "abstractEditor.h"
#include "spriteEditor.h"

void DrawSprite(TBaluRender* render, TBaluSpriteDef* sprite)
{
	std::vector<TVec2> pos, tex;
	pos.push_back(TVec2(0, 0));
	pos.insert(pos.end(), sprite->polygon_vertices.begin(), sprite->polygon_vertices.end());
	pos.insert(pos.end(), sprite->polygon_vertices[0]);
	tex = pos;
	TStreamsDesc desc;
	desc.AddStream(TStream::Vertex, TDataType::Float, 2, &*pos.begin());
	desc.AddStream(TStream::TexCoord, TDataType::Float, 2, &*tex.begin());
	render->Draw(desc, TPrimitive::TriangleFan, sprite->polygon_vertices.size() + 2);
}

void DrawBoundary(TOBB<float, 2> boundary, TBaluRender* render)
{
	std::vector<TVec2> v;
	boundary.DrawLines(v);
	TStreamsDesc desc;
	desc.Clear();
	desc.AddStream(TStream::Vertex, TDataType::Float, 2, &*v.begin());
	render->Draw(desc, TPrimitive::Lines, v.size());
}

void TBoundaryObjectBehaivor::Render(TBaluRender* render)
{
	if (object_under_cursor)
		render->Set.Color(1, 1, 0);
	DrawBoundary(boundary, render);
	if (object_under_cursor)
		render->Set.Color(1, 1, 1);
	for (TControlPoint& v : control_points)
	{
		switch (v.type)
		{
		case TControlType::Pivot:
			DrawPoint(render, v.pos);
			break;
		case TControlType::Resize:
			DrawPoint(render, v.pos);
			break;
		case TControlType::Rotate:
			DrawPoint(render, v.pos);
			break;
		default:
			break;
		}
	}
	if (point_under_cursor != -1)
	{
		render->Set.Color(1, 0, 0);
		DrawPoint(render, control_points[point_under_cursor].pos);
		render->Set.Color(1, 1, 1);
	}
}

void DrawLine(TBaluRender* render, TVec2 p0, TVec2 p1)
{
	TVec2 v[2] = { p0, p1 };
	TStreamsDesc desc;
	desc.AddStream(TStream::Vertex, TDataType::Float, 2, &v[0]);
	render->Draw(desc, TPrimitive::Lines, 2);
}

void DrawPoint(TBaluRender* render, TVec2 p)
{
	TVec2 v[1] = { p };
	TStreamsDesc desc;
	desc.AddStream(TStream::Vertex, TDataType::Float, 2, &v[0]);

	render->Set.PointSize(5);

	render->Draw(desc, TPrimitive::Points, 1);

	render->Set.PointSize(1);
}


void DrawSpriteContour(TBaluRender* render, TBaluSpriteDef* sprite)
{
	TStreamsDesc desc;
	desc.Clear();
	desc.AddStream(TStream::Vertex, TDataType::Float, 2, &*sprite->polygon_vertices.begin());
	desc.AddStream(TStream::TexCoord, TDataType::Float, 2, &*sprite->tex_coordinates.begin());
	render->Draw(desc, TPrimitive::LineLoop, sprite->polygon_vertices.size());
}

void ActivateMaterial(TBaluRender* render, TBaluMaterialDef* material)
{
	if (material->text_id.IsNull())
	{
		material->text_id = render->Texture.Create(material->image_path.c_str());
	}
	render->Texture.Enable(true);
	render->Texture.Bind(material->text_id);
}

void DeactivateMaterial(TBaluRender* render, TBaluMaterialDef* material)
{
	render->Texture.Enable(false);
}