
#include "WorldObjectEditor.h"

#include <vcclr.h>
#include <msclr\marshal_cppstd.h>

#include <baluLib.h>
#include <assert.h>

#include "../Source/EngineInterfaces.h"
#include "../Source/EditorInterfaces.h"

namespace Editor
{

	void BaluEditorControl::Render()
	{
		p->director->Render();
	}

	void BaluEditorControl::SetViewport(int width, int height)
	{
		p->director->SetViewport(TVec2i(width, height));
	}


	void BaluEditorControl::Resize(int width, int height)
	{
		*p->screen = TVec2i(width, height);
		p->director->SetScreenSize(p->screen->size);
	}



	void BaluEditorControl::SetEditedWorldNode(TWolrdTreeNodeTag^ node)
	{
		if (p->active_edited_object != nullptr)
			DestroyEditorOfWorldObject(p->active_edited_object);

		DestroyEditorScene();

		CreateEditorScene();

		p->drawing_context.screen = p->screen;
		p->drawing_context.view = &p->main_viewport_view;
		p->drawing_context.viewport = p->main_viewport;

		p->active_editor = CreateEditorOfWorldObject(node->world_object);

		auto& tools = p->active_editor->GetAvailableTools();
		p->active_editor->SetActiveTool(tools[0].tool.get());
		TUtils::CreateEditorToolsToolBar(EditorToolsBar, tools, p->active_editor, this);
	}

	bool BaluEditorControl::CanSetSelectedAsWork()
	{
		assert(p->active_editor != nullptr);
		return p->active_editor != nullptr && p->active_editor->CanSetSelectedAsWork();
	}
	void BaluEditorControl::SetSelectedAsWork()
	{
		assert(p->active_editor != nullptr);
		if (p->active_editor != nullptr)
			p->active_editor->SetSelectedAsWork();

		auto &tools = p->active_editor->GetAvailableTools();
		TUtils::CreateEditorToolsToolBar(EditorToolsBar, tools, p->active_editor, this);
	}

	bool BaluEditorControl::CanEndSelectedAsWork()
	{
		assert(p->active_editor != nullptr);
		return p->active_editor != nullptr && p->active_editor->CanEndSelectedAsWork();
	}
	void BaluEditorControl::EndSelectedAsWork()
	{
		assert(p->active_editor != nullptr);
		if (p->active_editor != nullptr)
			p->active_editor->EndSelectedAsWork();
	}

	void BaluEditorControl::SetToolSelectedObject(String^ name)
	{
		auto str_name = msclr::interop::marshal_as<std::string>(name);
		EngineInterface::IBaluWorldObject* obj = nullptr;
		for (auto& v : p->active_selection_list)
			if (v->GetName() == str_name)
				obj = v;
		assert(obj != nullptr);
		p->active_editor->GetActiveTool()->SetSelectedObject(obj);
		//engine->SetToolSelectedObject();
	}


	bool BaluEditorControl::ToolNeedObjectSelect(std::vector<IBaluWorldObject*>& selection_list)
	{
		selection_list.clear();
		assert(p->active_editor != nullptr);
		if (p->active_editor != nullptr)
		{
			auto need_obj = p->active_editor->GetActiveTool()->NeedObjectSelect();
			switch (need_obj)
			{
			case TWorldObjectType::Material:
				for (const auto& v : p->world->GetMaterials())
					selection_list.push_back(dynamic_cast<IBaluWorldObject*>(v.second));
				break;
			case TWorldObjectType::Sprite:
				for (const auto& v : p->world->GetSprites())
					selection_list.push_back(dynamic_cast<IBaluWorldObject*>(v.second));
				break;
			case TWorldObjectType::Class:
				for (const auto& v : p->world->GetClasses())
					selection_list.push_back(dynamic_cast<IBaluWorldObject*>(v.second));
				break;
			default:
				assert(false);
				return false;
				break;
			}
			p->active_selection_list = selection_list;
			return true;
		}
		p->active_selection_list.clear();
		return false;
	}


	void BaluEditorControl::CreateEditorScene()
	{
		auto editor_scene = p->world->CreateScene("EditorScene");
		dynamic_cast<IBaluWorldObject*>(editor_scene)->GetProperties()->SetBool("editor_temp_object", true);

		if (editor_scene->FindViewport("main_viewport") == nullptr)
		{
			p->main_viewport = editor_scene->CreateViewport("main_viewport");
			p->main_viewport->SetTransform(TBaluTransform(TVec2(0, 0), TRot(0)));
			p->main_viewport->SetAspectRatio(1);
			p->main_viewport->SetWidth(20);

		}
		p->world->GetCallbacksActiveType().active_type = TCallbacksActiveType::EDITOR;


		//auto callback = CallbackWithData<RenderWorldCallback>(RenderWorld, &p->world->GetCallbacksActiveType(), p, TCallbacksActiveType::EDITOR);
		//p->world->SetRenderWorldCallback(callback);

		p->world->AddOnWorldStart(CallbackWithData<OnStartWorldCallback>(WorldStart_source, &p->world->GetCallbacksActiveType(), TCallbacksActiveType::DEFAULT));
		p->world->AddOnViewportResize(CallbackWithData<ViewportResizeCallback>(ViewportResize_source, &p->world->GetCallbacksActiveType(), TCallbacksActiveType::DEFAULT));

		p->world_instance = CreateWorldInstance(p->world, p->director->GetResources());

		p->scene_instance = p->world_instance->RunScene(editor_scene);

		p->world_instance->GetComposer()->AddToRender(p->scene_instance, editor_scene->FindViewport("main_viewport"));

		p->screen = new TScreen(p->director->GetScreenSize());
		p->director->SetSymulatePhysics(false);
		p->main_viewport_view = TView(TVec2(0.5, 0.5), TVec2(1, 1));
		p->director->SetWorldInstance(p->world_instance);

	}

	void BaluEditorControl::DestroyEditorScene()
	{
		delete p->screen;
		DestroyWorldInstance(p->world_instance);
		p->world_instance = nullptr;
		IBaluScene* result;
		if (p->world != nullptr)
		{
			if (p->world->TryFind("EditorScene", result))
				p->world->DestroyScene("EditorScene");
		}
	}


	void BaluEditorControl::BeginFrame()
	{
		p->director->Step(0.01);
		p->director->BeginFrame();
	}
	void BaluEditorControl::EndFrame()
	{
		p->director->EndFrame();
	}


	void BaluEditorControl::MouseDown(MouseEventArgs^ e)
	{
		if (p->world_instance != nullptr)
		{
			if (e->Button == MouseButtons::Middle&&!p->viewport_drag_active)
			{
				p->viewport_drag_active = true;
				p->viewport_drag_last_mouse_pos = Convert(e).location;
				p->viewport_drag_last_pos = p->main_viewport->GetTransform().position;
			}

			p->world_instance->MouseDown(Convert(e));
		}
	}

	TVec2 ToSceneCoord(BaluEditorControlPrivate* p, TVec2i location)
	{
		auto screen_coords = p->screen->FromScreenPixels2(location);
		auto view_coord = p->screen->FromScreenToView(p->main_viewport_view, screen_coords);
		auto scene_coord = IBaluScene::FromViewportToScene(p->main_viewport, view_coord);
		return scene_coord;
	}

	void BaluEditorControl::MouseMove(MouseEventArgs^ e)
	{
		if (p->world_instance != nullptr)
		{
			if (p->viewport_drag_active)
			{
				auto t = p->main_viewport->GetTransform();
				auto mouse_pos_diff = Convert(e).location - p->viewport_drag_last_mouse_pos;

				auto old_scene_coord = ToSceneCoord(p, p->viewport_drag_last_mouse_pos);
				auto new_scene_coord = ToSceneCoord(p, Convert(e).location);

				t.position = p->viewport_drag_last_pos - (new_scene_coord - old_scene_coord);
				p->main_viewport->SetTransform(t);
			}
			p->world_instance->MouseMove(Convert(e));
		}
	}

	void BaluEditorControl::MouseUp(MouseEventArgs^ e)
	{
		if (p->world_instance != nullptr)
		{
			if (e->Button == MouseButtons::Middle&&p->viewport_drag_active)
			{
				p->viewport_drag_active = false;
			}
			p->world_instance->MouseUp(Convert(e));
		}
	}

	void BaluEditorControl::MouseWheel(MouseEventArgs^ e)
	{
		if (p->world_instance != nullptr)
		{
			p->world_instance->MouseVerticalWheel(e->Delta);
			if (p->main_viewport != nullptr)
			{
				p->main_viewport->SetWidth(p->main_viewport->GetSize()[0] * (e->Delta>0 ? 1.1 : 0.9));
			}
		}
	}
}