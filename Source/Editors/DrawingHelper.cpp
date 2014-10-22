#include <baluRender.h>

#include "DrawingHelper.h"
#include "BoundaryEditor.h"
#include "editorResourses.h"

using namespace TBaluRenderEnums;

TDrawingHelper::TDrawingHelper(TBaluRender* render, TEditorResourses* resources)
{
	this->render = render;
	this->resources = resources;
}

//void TDrawingHelper::DrawSpritePolygon(TBaluSpritePolygonDef* sprite)
//{
//	std::vector<TVec2> pos, tex;
//	pos.push_back(TVec2(0, 0));
//	pos.insert(pos.end(), sprite->polygon_vertices.begin(), sprite->polygon_vertices.end());
//	pos.insert(pos.end(), sprite->polygon_vertices[0]);
//	tex = pos;
//	TStreamsDesc desc;
//	desc.AddStream(TStream::Vertex, TDataType::Float, 2, &*pos.begin());
//	desc.AddStream(TStream::TexCoord, TDataType::Float, 2, &*tex.begin());
//	//render->Set.PolygonMode(TPolygonMode::Line);
//	render->Draw(desc, TPrimitive::TriangleFan, sprite->polygon_vertices.size() + 2);
//}

void TDrawingHelper::DrawSpritePolygon(TBaluSpritePolygonDef* polygon)
{
	std::vector<TVec2> pos, tex;
	//pos.push_back(TVec2(0, 0));
	auto ang = polygon->transform.angle;
	auto rot_mat = TMatrix2(*(TVec2*)&ang.GetXAxis(), *(TVec2*)&ang.GetYAxis());
	for (int i = 0; i < polygon->polygon_vertices.size(); i++)
	{
		pos.push_back(rot_mat*(*(TVec2*)&polygon->polygon_vertices[i]) + polygon->transform.position);
	}
	for (int i = 0; i < polygon->tex_coordinates.size(); i++)
	{
		tex.push_back(polygon->tex_coordinates[i]);
	}

	TStreamsDesc desc;
	desc.AddStream(TStream::Vertex, TDataType::Float, 2, &*pos.begin());
	//desc.AddStream(TStream::TexCoord, TDataType::Float, 2, &*tex.begin());
	//render->Set.PolygonMode(TPolygonMode::Line);
	render->Draw(desc, TPrimitive::TriangleFan, polygon->polygon_vertices.size());
}

void TDrawingHelper::DrawPolygon(TBaluPolygonShapeDef* polygon)
{
	std::vector<TVec2> pos, tex;
	//pos.push_back(TVec2(0, 0));
	auto ang = polygon->transform.angle;
	auto rot_mat = TMatrix2(*(TVec2*)&ang.GetXAxis(), *(TVec2*)&ang.GetYAxis());
	for (int i = 0; i < polygon->b2shape.m_count; i++)
	{
		pos.push_back(rot_mat*(*(TVec2*)&polygon->b2shape.m_vertices[i]) + polygon->transform.position);
	}
	tex = pos;
	TStreamsDesc desc;
	desc.AddStream(TStream::Vertex, TDataType::Float, 2, &*pos.begin());
	desc.AddStream(TStream::TexCoord, TDataType::Float, 2, &*tex.begin());
	//render->Set.PolygonMode(TPolygonMode::Line);
	render->Draw(desc, TPrimitive::TriangleFan, polygon->b2shape.m_count);
}

void TDrawingHelper::DrawCircle(TBaluCircleShapeDef* circle)
{
	std::vector<TVec2> pos, tex;

	TSphere<float, 2> sp(circle->transform.position, circle->b2shape.m_radius);
	sp.DrawLines(pos);
	TStreamsDesc desc;
	desc.AddStream(TStream::Vertex, TDataType::Float, 2, &*pos.begin());
	render->Set.PolygonMode(TPolygonMode::Line);
	render->Draw(desc, TPrimitive::Lines, pos.size());
	render->Set.PolygonMode(TPolygonMode::Fill);
}

void TDrawingHelper::DrawBoundary(TOBB<float, 2> boundary,bool fill)
{
	if (fill)
	{
		std::vector<TVec2> pos,tex;
		std::vector<unsigned int> indices;
		boundary.DrawTriangles(pos,indices);
		tex = pos;
		TStreamsDesc desc;
		desc.Clear();
		desc.AddStream(TStream::Vertex, TDataType::Float, 2, &*pos.begin());
		desc.AddStream(TStream::TexCoord, TDataType::Float, 2, &*tex.begin());
		desc.AddStream(TStream::Index, TDataType::UInt, 1, &*indices.begin());
		render->Draw(desc, TPrimitive::Triangles, indices.size());
	}
	else
	{
		std::vector<TVec2> v;
		boundary.DrawLines(v);
		TStreamsDesc desc;
		desc.Clear();
		desc.AddStream(TStream::Vertex, TDataType::Float, 2, &*v.begin());
		render->Draw(desc, TPrimitive::Lines, v.size());
	}
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


void TDrawingHelper::DrawSpritePolygonContour(TBaluSpritePolygonDef* sprite)
{
	TStreamsDesc desc;
	desc.Clear();
	desc.AddStream(TStream::Vertex, TDataType::Float, 2, &*sprite->polygon_vertices.begin());
	//desc.AddStream(TStream::TexCoord, TDataType::Float, 2, &*sprite->tex_coordinates.begin());
	render->Draw(desc, TPrimitive::LineLoop, sprite->polygon_vertices.size());
}

void TDrawingHelper::ActivateMaterial(TBaluMaterialDef* material)
{
	if (material->image_path == "")
		material->image_path = "Textures/Crate005_ebox.png";//TODO текстура отсутствует
	if (material->image_path != "")
	{
		TTextureId tex_id = resources->CreateTextureFromFile(material->image_path);
		render->Texture.Enable(true);
		if (material->blend_mode == TBaluMaterialDef::TTransparentMode::TM_ALPHA_BLEND)
		{
			render->Blend.Enable(true);
			render->Blend.Func("sc*sa+dc*(1-sa)");
			//render->Blend.Func(TBlendEquation::BE_SRC_ALPHA, TBlendFunc::BF_ADD, TBlendEquation::BE_ONE_MINUS_SRC_ALPHA);
		}
		if (material->blend_mode == TBaluMaterialDef::TTransparentMode::TM_ALPHA_TEST)
		{
			render->AlphaTest.Enable(true);
			render->AlphaTest.Func(">=", 0.5);
		}
		render->Texture.SetFilter(tex_id, (TBaluRenderEnums::TTexFilter)material->texture_filter, (TBaluRenderEnums::TTexClamp)material->texture_clamp);
		render->Texture.Bind(tex_id);
	}
}

void TDrawingHelper::DeactivateMaterial(TBaluMaterialDef* material)
{
	render->Texture.Enable(false);
	render->Blend.Enable(false);
	render->AlphaTest.Enable(false);
}

void TDrawingHelper::SetSelectedPointColor()
{
	render->Set.Color(0, 1, 0, use_global_alpha?global_alpha:1);
}
void TDrawingHelper::SetSelectedBoundaryColor()
{
	render->Set.Color(1, 0, 0, use_global_alpha ? global_alpha : 1);
}
void TDrawingHelper::UnsetColor()
{
	render->Set.Color(1, 1, 1, use_global_alpha ? global_alpha : 1);
}

void TDrawingHelper::SetGlobalAlphaColor()
{
	render->Set.Color(1, 1, 1, use_global_alpha ? global_alpha : 1);
}

void TDrawingHelper::SetGlobalAlpha(float alpha)
{
	global_alpha = alpha;
	use_global_alpha = true;
	render->Blend.Enable(true);
	render->Blend.Func("sc*sa+dc*(1-sa)");
}

void TDrawingHelper::UnsetGlobalAlpha()
{
	global_alpha = 1;
	use_global_alpha = false;
	render->Blend.Enable(false);
}