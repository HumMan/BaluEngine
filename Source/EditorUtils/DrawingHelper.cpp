#include "DrawingHelper.h"

#include "nanovg.h"

#include "../EngineInterfaces/IScene.h"

#include "../nanovg_support.h"

#include "EditorControlsModel.h"

using namespace EngineInterface;

TDrawingHelper::TDrawingHelper(TScreen* screen, TView* view, IViewport* viewport, IBaluScene* scene)
{
	this->context = GetContext();
	this->scene = scene;
	this->viewport = viewport;
	this->view = view;
	this->screen = screen;
}

TVec2 TDrawingHelper::FromScreenPixelsToScene(TVec2i screen_pixels)
{
	
	auto screen_coords = screen->FromScreenPixels2(screen_pixels);
	auto view_coord = screen->FromScreenToView(*view, screen_coords);
	auto scene_coord = scene->FromViewportToScene(viewport, view_coord);
	return scene_coord;
}

TVec2i TDrawingHelper::FromSceneToScreenPixels(TVec2 scene_coordinates)
{
	auto viewport_coord = scene->FromSceneToViewport(viewport, scene_coordinates);
	auto screen_coord = screen->FromViewToScreen(*view, viewport_coord);
	auto screen_pixels = screen->ToScreenPixels(screen_coord);
	return screen_pixels;
}

//
//void TDrawingHelper::SetTransform(TBaluTransform transform)
//{
//	this->transform = transform;
//}

void TDrawingHelper::Render(const TPointAdornment* p)
{
	auto c = FromSceneToScreenPixels(p->pos);

	//auto transform = params->poly->GetGlobalTransform();
	auto transform = TBaluTransform(TVec2(c[0], c[1]), TRot(0));

	float cornerRadius = 3.0f;
	NVGpaint shadowPaint;
	NVGpaint headerPaint;

	nvgBeginPath(context);
	//TODO from scene space to screen
	//nvgCircle(vg, transform.position[0], transform.position[1], 4.0f);
	nvgCircle(context, transform.position[0], transform.position[1], 5.0f);
	nvgFillColor(context, nvgRGBA(0, 160, 192, 255));
	nvgFill(context);

	nvgBeginPath(context);
	nvgCircle(context, transform.position[0], transform.position[1], 3.0f);
	nvgFillColor(context, nvgRGBA(220, 220, 220, 255));
	nvgFill(context);
}

void TDrawingHelper::Render(const TOBBAdornment*)
{

}


//TDrawingHelper::TDrawingHelper(TBaluRender* render, TEditorResourses* resources)
//{
//	this->render = render;
//	this->resources = resources;
//}
//
//void TDrawingHelper::DrawClass(TBaluClass* balu_class)
//{
//	for (int i = 0; i < balu_class->bodies.size(); i++)
//	{
//		DrawPhysBody(balu_class->bodies[i]->body);
//	}
//	for (int i = 0; i < balu_class->sprites.size(); i++)
//	{
//		DrawSprite(balu_class->sprites[i]->sprite);
//	}
//}
//
//void TDrawingHelper::DrawPhysBody(TBaluPhysBodyDef* body)
//{
//	for (int i = 0; i < body->fixtures.size(); i++)
//	{
//		{
//			auto sh = dynamic_cast<TBaluPolygonShapeDef*>(body->fixtures[i].get());
//			if (sh != nullptr)
//				DrawPolygon(sh);
//		}
//		{
//			auto sh = dynamic_cast<TBaluCircleShapeDef*>(body->fixtures[i].get());
//			if (sh != nullptr)
//				DrawCircle(sh);
//		}
//	}
//}
//
//void TDrawingHelper::DrawSprite(TBaluSpriteDef* sprite)
//{
//	for (int i = 0; i < sprite->polygons.size(); i++)
//	{
//		DrawSpritePolygon(sprite->polygons[i].get());
//	}
//}
//
//void TDrawingHelper::DrawSpritePolygon(TBaluSpritePolygonDef* polygon)
//{
//	ActivateMaterial(polygon->material);
//
//	std::vector<TVec2> pos, tex;
//	//pos.push_back(TVec2(0, 0));
//	auto ang = polygon->transform.angle;
//	auto rot_mat = TMatrix2(*(TVec2*)&ang.GetXAxis(), *(TVec2*)&ang.GetYAxis());
//	for (int i = 0; i < polygon->polygon_vertices.size(); i++)
//	{
//		pos.push_back(rot_mat*(*(TVec2*)&polygon->polygon_vertices[i]) + polygon->transform.position);
//	}
//	for (int i = 0; i < polygon->tex_coordinates.size(); i++)
//	{
//		tex.push_back(polygon->tex_coordinates[i]);
//	}
//
//	TStreamsDesc desc;
//	desc.AddStream(TStream::Vertex, TDataType::Float, 2, &*pos.begin());
//	desc.AddStream(TStream::TexCoord, TDataType::Float, 2, &*tex.begin());
//	//render->Set.PolygonMode(TPolygonMode::Line);
//	render->Draw(desc, TPrimitive::TriangleFan, polygon->polygon_vertices.size());
//
//	DeactivateMaterial(polygon->material);
//}
//
//void TDrawingHelper::DrawPolygon(TBaluPolygonShapeDef* polygon)
//{
//	std::vector<TVec2> pos, tex;
//	//pos.push_back(TVec2(0, 0));
//	auto ang = polygon->transform.angle;
//	auto rot_mat = TMatrix2(*(TVec2*)&ang.GetXAxis(), *(TVec2*)&ang.GetYAxis());
//	for (int i = 0; i < polygon->b2shape.m_count; i++)
//	{
//		pos.push_back(rot_mat*(*(TVec2*)&polygon->b2shape.m_vertices[i]) + polygon->transform.position);
//	}
//	tex = pos;
//	TStreamsDesc desc;
//	desc.AddStream(TStream::Vertex, TDataType::Float, 2, &*pos.begin());
//	desc.AddStream(TStream::TexCoord, TDataType::Float, 2, &*tex.begin());
//	//render->Set.PolygonMode(TPolygonMode::Line);
//	render->Draw(desc, TPrimitive::TriangleFan, polygon->b2shape.m_count);
//}
//
//void TDrawingHelper::DrawCircle(TBaluCircleShapeDef* circle)
//{
//	std::vector<TVec2> pos, tex;
//
//	TSphere<float, 2> sp(circle->transform.position, circle->b2shape.m_radius);
//	sp.DrawLines(pos);
//	TStreamsDesc desc;
//	desc.AddStream(TStream::Vertex, TDataType::Float, 2, &*pos.begin());
//	render->Set.PolygonMode(TPolygonMode::Line);
//	render->Draw(desc, TPrimitive::Lines, pos.size());
//	render->Set.PolygonMode(TPolygonMode::Fill);
//}
//
//void TDrawingHelper::DrawBoundary(TOBB<float, 2> boundary,bool fill)
//{
//	if (fill)
//	{
//		std::vector<TVec2> pos,tex;
//		std::vector<unsigned int> indices;
//		boundary.DrawTriangles(pos,indices);
//		tex = pos;
//		TStreamsDesc desc;
//		desc.Clear();
//		desc.AddStream(TStream::Vertex, TDataType::Float, 2, &*pos.begin());
//		desc.AddStream(TStream::TexCoord, TDataType::Float, 2, &*tex.begin());
//		desc.AddStream(TStream::Index, TDataType::UInt, 1, &*indices.begin());
//		render->Draw(desc, TPrimitive::Triangles, indices.size());
//	}
//	else
//	{
//		std::vector<TVec2> v;
//		boundary.DrawLines(v);
//		TStreamsDesc desc;
//		desc.Clear();
//		desc.AddStream(TStream::Vertex, TDataType::Float, 2, &*v.begin());
//		render->Draw(desc, TPrimitive::Lines, v.size());
//	}
//}
//
//void TDrawingHelper::DrawLine(TVec2 p0, TVec2 p1)
//{
//	TVec2 v[2] = { p0, p1 };
//	TStreamsDesc desc;
//	desc.AddStream(TStream::Vertex, TDataType::Float, 2, &v[0]);
//	render->Draw(desc, TPrimitive::Lines, 2);
//}
//
//void TDrawingHelper::DrawPoint(TVec2 p)
//{
//	TVec2 v[1] = { p };
//	TStreamsDesc desc;
//	desc.AddStream(TStream::Vertex, TDataType::Float, 2, &v[0]);
//
//	render->Set.PointSize(5);
//
//	render->Draw(desc, TPrimitive::Points, 1);
//
//	render->Set.PointSize(1);
//}
//
//
//void TDrawingHelper::DrawSpritePolygonContour(TBaluSpritePolygonDef* sprite)
//{
//	TStreamsDesc desc;
//	desc.Clear();
//	desc.AddStream(TStream::Vertex, TDataType::Float, 2, &*sprite->polygon_vertices.begin());
//	desc.AddStream(TStream::TexCoord, TDataType::Float, 2, &*sprite->tex_coordinates.begin());
//	render->Draw(desc, TPrimitive::LineLoop, sprite->polygon_vertices.size());
//}
//
//void TDrawingHelper::ActivateMaterial(TBaluMaterialDef* material)
//{
//	if (material == nullptr)
//		return;
//	if (material->image_path == "")
//		material->image_path = "Textures/Crate005_ebox.png";//TODO текстура отсутствует
//	if (material->image_path != "")
//	{
//		TTextureId tex_id = resources->CreateTextureFromFile(material->image_path);
//		render->Texture.Enable(true);
//		if (material->blend_mode == TBaluMaterialDef::TTransparentMode::TM_ALPHA_BLEND)
//		{
//			render->Blend.Enable(true);
//			render->Blend.Func("sc*sa+dc*(1-sa)");
//			//render->Blend.Func(TBlendEquation::BE_SRC_ALPHA, TBlendFunc::BF_ADD, TBlendEquation::BE_ONE_MINUS_SRC_ALPHA);
//		}
//		if (material->blend_mode == TBaluMaterialDef::TTransparentMode::TM_ALPHA_TEST)
//		{
//			render->AlphaTest.Enable(true);
//			render->AlphaTest.Func(">=", 0.5);
//		}
//		render->Texture.SetFilter(tex_id, (TBaluRenderEnums::TTexFilter)material->texture_filter, (TBaluRenderEnums::TTexClamp)material->texture_clamp);
//		render->Texture.Bind(tex_id);
//	}
//}
//
//void TDrawingHelper::DeactivateMaterial(TBaluMaterialDef* material)
//{
//	if (material == nullptr)
//		return;
//	render->Texture.Enable(false);
//	render->Blend.Enable(false);
//	render->AlphaTest.Enable(false);
//}
//
//void TDrawingHelper::SetSelectedPointColor()
//{
//	render->Set.Color(0, 1, 0, use_global_alpha?global_alpha:1);
//}
//void TDrawingHelper::SetSelectedBoundaryColor()
//{
//	render->Set.Color(1, 0, 0, use_global_alpha ? global_alpha : 1);
//}
//void TDrawingHelper::UnsetColor()
//{
//	render->Set.Color(1, 1, 1, use_global_alpha ? global_alpha : 1);
//}
//
//void TDrawingHelper::SetGlobalAlphaColor()
//{
//	render->Set.Color(1, 1, 1, use_global_alpha ? global_alpha : 1);
//}
//
//void TDrawingHelper::SetGlobalAlpha(float alpha)
//{
//	global_alpha = alpha;
//	use_global_alpha = true;
//	render->Blend.Enable(true);
//	render->Blend.Func("sc*sa+dc*(1-sa)");
//}
//
//void TDrawingHelper::UnsetGlobalAlpha()
//{
//	global_alpha = 1;
//	use_global_alpha = false;
//	render->Blend.Enable(false);
//}
//
//void TDrawingHelper::PushTransform()
//{
//	
//}
//void TDrawingHelper::PopTransform()
//{
//	render->Set.ModelView(last_transform);
//}
//void TDrawingHelper::SetTransform(TVec2 transform)
//{
//	last_transform = render->Get.ModelView();
//	auto mat = last_transform;
//	mat.SetOffset(mat.GetOffset() + TVec3(transform, 0));
//	render->Set.ModelView(mat);
//}