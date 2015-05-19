
#include "WorldObjectEditor.h"

#include <baluLib.h>
#include <assert.h>

#include "../Source/EngineInterfaces.h"
#include "../Source/EditorInterfaces.h"

namespace Editor
{

	class TWorldObjectEditorPrivate
	{

	};

	void TWorldObjectEditor::Render()
	{
		p->director->Render();
	}

	void TWorldObjectEditor::SetViewport(int width, int height)
	{
		p->director->SetViewport(TVec2i(width, height));
	}


	void TWorldObjectEditor::Resize(int width, int height)
	{
		*p->screen = TVec2i(width, height);
		p->director->SetScreenSize(p->screen->size);
	}



	void TWorldObjectEditor::SetEditedWorldNode(TWolrdTreeNodeTag^ node)
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

	bool TWorldObjectEditor::CanSetSelectedAsWork()
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

	bool TWorldObjectEditor::CanEndSelectedAsWork()
	{
		assert(p->active_editor != nullptr);
		return p->active_editor != nullptr && p->active_editor->CanEndSelectedAsWork();
	}
	void TWorldObjectEditor::EndSelectedAsWork()
	{
		assert(p->active_editor != nullptr);
		if (p->active_editor != nullptr)
			p->active_editor->EndSelectedAsWork();
	}

	void TWorldObjectEditor::SetToolSelectedObject(String^ name)
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


	bool TWorldObjectEditor::ToolNeedObjectSelect(std::vector<IBaluWorldObject*>& selection_list)
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


	void TWorldObjectEditor::CreateEditorScene()
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

	void TWorldObjectEditor::DestroyEditorScene()
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


	void TWorldObjectEditor::BeginFrame()
	{
		p->director->Step(0.01);
		p->director->BeginFrame();
	}
	void TWorldObjectEditor::EndFrame()
	{
		p->director->EndFrame();
	}


	void TWorldObjectEditor::MouseDown(MouseEventArgs^ e)
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

	void TWorldObjectEditor::MouseMove(MouseEventArgs^ e)
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

	void TWorldObjectEditor::MouseUp(MouseEventArgs^ e)
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

	void TWorldObjectEditor::MouseWheel(MouseEventArgs^ e)
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


	IAbstractEditor* TWorldObjectEditor::CreateEditorOfWorldObject(IBaluWorldObject* obj)
	{
		//if ((dynamic_cast<IBaluMaterial*>(obj)) != nullptr)
		//	return new TMaterialEditor();

		//if ((dynamic_cast<TBaluSpritePolygonDef*>(obj)) != nullptr)
		//	return new TSpritePolygonEditor();

		p->active_edited_object = obj;

		if ((dynamic_cast<IBaluSprite*>(obj)) != nullptr)
			return CreateSpriteEditor(p->drawing_context, p->world, dynamic_cast<IBaluSprite*>(obj), p->scene_instance);

		//if ((dynamic_cast<IBaluClass*>(obj)) != nullptr)
		//	return new TClassEditor();

		if ((dynamic_cast<IBaluScene*>(obj)) != nullptr)
			return CreateSceneEditor(p->drawing_context, p->world, dynamic_cast<IBaluScene*>(obj), p->scene_instance);

		return nullptr;
	}

	void TWorldObjectEditor::DestroyEditorOfWorldObject(IBaluWorldObject* obj)
	{
		//if ((dynamic_cast<IBaluMaterial*>(obj)) != nullptr)
		//	return new TMaterialEditor();

		//if ((dynamic_cast<TBaluSpritePolygonDef*>(obj)) != nullptr)
		//	return new TSpritePolygonEditor();

		p->active_edited_object = nullptr;

		if ((dynamic_cast<IBaluSprite*>(obj)) != nullptr)
			return DestroySpriteEditor(p->active_editor);

		//if ((dynamic_cast<IBaluClass*>(obj)) != nullptr)
		//	return new TClassEditor();

		if ((dynamic_cast<IBaluScene*>(obj)) != nullptr)
			DestroySceneEditor(p->active_editor);
	}
	TMouseEventArgs TWorldObjectEditor::Convert(MouseEventArgs^ e)
	{
		TMouseEventArgs result;
		switch (e->Button)
		{
		case MouseButtons::Left:
			result.button = TMouseButton::Left; break;
		case MouseButtons::Middle:
			result.button = TMouseButton::Middle; break;
		case MouseButtons::Right:
			result.button = TMouseButton::Right; break;
		}
		result.location[0] = e->X;
		result.location[1] = e->Y;
		return result;
	}
}