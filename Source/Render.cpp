#include "Render.h"

#include "baluRender.h"


//#include <GL\glew.h>
//#include <GL\wglew.h>

#include "nanovg_support.h"

#include "MaterialInstance.h"

#include <nanovg.h>

using namespace TBaluRenderEnums;

TRender::TRender(TBaluRender* internal_render)
{
	render = internal_render;
	nanovg_init();
}

void TRender::Render(std::vector<TRenderCommand>& render_commands, std::vector<TCustomDrawCommand>& custom_draw_commands, EngineInterface::IViewport* viewport)
{
	//render->Set.ModelView(TMatrix4::GetOrtho(TVec2(0, 0), TVec2(20, 20), -1, 1));
	render->Set.ModelView(TMatrix4::GetOrtho(viewport->GetTransform().position, viewport->GetSize(), -1, 1));
	//render->AlphaTest.Enable(true);
	//render->AlphaTest.Func(TAlphaTestFunc::AT_GREATER, 0.9);
	render->Blend.Enable(true);
	render->Blend.Func(TBlendEquation::BE_SRC_ALPHA, TBlendFunc::BF_ADD, TBlendEquation::BE_ONE_MINUS_SRC_ALPHA);
	//render->Set.PolygonMode(TBaluRenderEnums::TPolygonMode::Line);
	for (int i = 0; i < render_commands.size(); i++)
	{ 
		auto& c = render_commands[i];
		if (c.vertices_count > 0)
		{
			auto tex = c.material_id->GetTexture();
			render->Texture.Bind(*(TTextureId*)&tex);
			TStreamsDesc streams;
			streams.AddStream(TStream::Vertex, TDataType::Float, 2, c.vertices);
			streams.AddStream(TStream::TexCoord, TDataType::Float, 2, c.tex_coords);
			//streams.AddStream(TStream::Color, TDataType::Float, 4, c.colors);
			render->Draw(streams, TPrimitive::Triangles, c.vertices_count);
		}
	}

	render->Blend.Enable(false);
	//glDisable(GL_DEPTH_TEST);

	render->Set.PolygonMode(TBaluRenderEnums::TPolygonMode::Fill);

	auto vg_context = GetContext();
	//render_test();

	//render->Depth.Test(false);

	begin_frame(render->ScreenSize());

	//nvgBeginPath(vg_context);
	//nvgRoundedRect(vg_context, 10, 10, 500, 500, 5);
	//nvgFillColor(vg_context, nvgRGBA(28, 30, 34, 192));
	////	nvgFillColor(vg, nvgRGBA(0,0,0,128));
	//nvgFill(vg_context);

	//nvgFontSize(vg_context, 168.0f);
	//nvgFontFace(vg_context, "sans-bold");
	//nvgTextAlign(vg_context, NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);

	////nvgFontBlur(vg_context, 2);
	//nvgFillColor(vg_context, nvgRGBA(220, 220, 220, 160));
	//nvgText(vg_context, 200, 200, "TEST", NULL);

	//
	for (int i = 0; i < custom_draw_commands.size(); i++)
	{
		custom_draw_commands[i].command.Execute(vg_context, &custom_draw_commands[i]);
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