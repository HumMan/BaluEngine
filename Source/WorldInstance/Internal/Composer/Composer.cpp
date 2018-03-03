#include "IComposer.h"

#include <Render/Render.h>

#include "baluRender.h"

#include "Objects/Scene/ISceneInstance.h"

using namespace EngineInterface;

#include <WorldDef/Objects/Material/IMaterial.h>

namespace EngineInterface
{
	class TComposerPrivate
	{
	public:
		std::vector<TComposerStage> stages;
	};
}

TComposerStage* TComposer::AddToRender(EngineInterface::IBaluSceneInstance* scene_instance, EngineInterface::IViewport* viewport)
{
	p->stages.emplace_back();
	p->stages.back().scene_instance = scene_instance;
	p->stages.back().viewport = viewport;
	return nullptr;
}

void TComposer::RemoveFromRender(EngineInterface::IComposerStage* stage)
{

}

void TComposer::Render(EngineInterface::TRender* render)
{
	auto internal_render = render->GetInternalRender();
	auto screen = TScreen(internal_render->Get.Viewport());

	for (auto& v : p->stages)
	{
		auto main_viewport = v.viewport;

		std::vector<TRenderCommand> render_commands;
		std::vector<IGUIVisual*> gui_draw;
		auto viewport_aabb = main_viewport->GetAABB();
		v.scene_instance->QueryAABB(viewport_aabb, render_commands, gui_draw);

		//TODO где то нужно хранить viewport_view
		auto main_viewport_view = TView(TVec2(0.5, 0.5), TVec2(1, 1));

		render->EnableScissor(true);
		render->SetScissorRect(screen, main_viewport_view);
		render->Render(render_commands, gui_draw, main_viewport);

		TDrawingHelperContext drawing_context;
		drawing_context.screen = &screen;
		drawing_context.view = &main_viewport_view;
		drawing_context.viewport = main_viewport;

		(dynamic_cast<TBaluSceneInstance*>(v.scene_instance))->DoDebugDraw(drawing_context);
		render->EnableScissor(false);
	}		
}

TComposer::TComposer()
{
	p = std::unique_ptr<TComposerPrivate>(new TComposerPrivate());
}

TComposer::~TComposer()
{

}
