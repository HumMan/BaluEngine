#include "Render.h"

#include "baluRender.h"


//#include <GL\glew.h>
//#include <GL\wglew.h>

#include "nanovg_support.h"

#include "MaterialInstance.h"

#include "ScriptInstance.h"

#include <nanovg.h>

#include "EditorUtils\DrawingHelper.h"

using namespace TBaluRenderEnums;

TRender::TRender(TBaluRender* internal_render)
{
	render = internal_render;
	nanovg_init();
}

TRender::~TRender()
{
	nanovg_deinit();
}

void TRender::Render(std::vector<TRenderCommand>& render_commands, std::vector<IGUIVisual*>& gui, EngineInterface::IViewport* viewport)
{
	//render->Set.ModelView(TMatrix4::GetOrtho(TVec2(0, 0), TVec2(20, 20), -1, 1));
	render->Set.ModelView(TMatrix4::GetOrtho(viewport->GetTransform().position, viewport->GetSize(), -1, 1));
	//render->AlphaTest.Enable(true);
	//render->AlphaTest.Func(TAlphaTestFunc::AT_GREATER, 0.9);
	render->Blend.Enable(true);
	render->Blend.Func(TBlendEquation::BE_SRC_ALPHA, TBlendFunc::BF_ADD, TBlendEquation::BE_ONE_MINUS_SRC_ALPHA);
	//render->Set.PolygonMode(TBaluRenderEnums::TPolygonMode::Line);
	std::sort(render_commands.begin(), render_commands.end(),
		[&](TRenderCommand& l, TRenderCommand& r){return l.layer > r.layer; });

	//int current_layer = render_commands.front().layer;
	for (int i = 0; i < render_commands.size(); i++)
	{ 
		auto& c = render_commands[i];
		assert(c.vertices_count > 0);
		{
			auto tex = c.material_id->GetTexture();
			render->Texture.Bind(*(TTextureId*)&tex);
			TStreamsDesc streams;
			streams.AddStream(TStream::Vertex, TDataType::Float, 2, c.vertices);
			streams.AddStream(TStream::TexCoord, TDataType::Float, 2, c.tex_coords);
			//streams.AddStream(TStream::Color, TDataType::Float, 4, c.colors);
			render->Draw(streams, TPrimitive::Triangles, c.vertices_count);
			if (c.draw_triangles_grid)
			{
				render->Texture.Enable(false);
				render->Set.PolygonMode(TPolygonMode::Line);
				render->Draw(streams, TPrimitive::Triangles, c.vertices_count);
				render->Set.PolygonMode(TPolygonMode::Fill);
				render->Texture.Enable(true);
			}
		}
	}

	render->Blend.Enable(false);
	//glDisable(GL_DEPTH_TEST);

	render->Set.PolygonMode(TBaluRenderEnums::TPolygonMode::Fill);

	auto vg_context = GetNanoVGContext();
	//render_test();

	//render->Depth.Test(false);

	begin_frame(render->ScreenSize());

	TDrawingHelperContext drawing_context;

	drawing_context.viewport = viewport;
	auto screen = TScreen(this->GetInternalRender()->Get.Viewport());
	drawing_context.screen = &screen;
	auto main_viewport_view = TView(TVec2(0.5, 0.5), TVec2(1, 1));
	drawing_context.view = &main_viewport_view;

	auto drawing_helper = TDrawingHelper(drawing_context);

	for each (auto& v in gui)
	{
		v->Render(&drawing_helper);
	}
	end_frame();
}

void TRender::EnableScissor(bool enable)
{
	render->ScissorRect.Enable(enable);
}

void TRender::SetScissorRect(TScreen screen, TView view)
{
	auto p0 = screen.ToScreenPixels(screen.FromViewToScreen(view, TVec2(0, 0)));
	auto p1 = screen.ToScreenPixels(screen.FromViewToScreen(view, TVec2(1, 1)));
	//render->ScissorRect.Box(p0, p1);
}