
#include "LayersManager.h"

#include <baluLib.h>
#include <assert.h>

#include <Interfaces\BaluEngineInterface.h>

#include "Converters.h"

#include <vcclr.h>
#include <msclr\marshal_cppstd.h>

namespace Editor
{

	class TLayersManagerEditorListener : public TLayersManagerChangeListener
	{
		gcroot<TLayersManager^> editor;
	public:
		TLayersManagerEditorListener(TLayersManager^ editor)
		{
			this->editor = editor;
		}
		virtual void LayerReordered(int layer_id, int after_id)
		{
			editor->Perform_GUI_Notify_LayersChange(TLayersChangeType::Reorder, layer_id, after_id);
		}
		virtual void LayerAdded(int layer_id)
		{
			editor->Perform_GUI_Notify_LayersChange(TLayersChangeType::Add, layer_id, -1);
		}
		virtual void LayerRemoved(int layer_id)
		{
			editor->Perform_GUI_Notify_LayersChange(TLayersChangeType::Remove, layer_id, -1);
		}
		virtual void LayerChanged(int layer_id)
		{
			editor->Perform_GUI_Notify_LayersChange(TLayersChangeType::Change, layer_id, -1);
		}
	};

	class TLayersManagerPrivate
	{
	public:
		//source edited world
		IBaluWorld* world;

		//local objects
		IDirector* director;

		IBaluSceneInstance* scene_instance;
		IBaluScene* source_scene;

		std::unique_ptr<TLayersManagerEditorListener> layers_change_listener;
		
		TLayersManagerPrivate()
		{
			world = nullptr;

			director = nullptr;
			scene_instance = nullptr;
			source_scene = nullptr;
		}
	};

	TLayersManager::TLayersManager(TWorldDirector^ world_director)
	{
		EngineInterface::WriteInfoToLog("Initializing TLayersManager");

		this->director = world_director;
		world_director->RegisterEditor(this);

		director->Notify_LayersManager_SceneChange += gcnew Editor::TNotify_LayersManager_SceneChange(this, &Editor::TLayersManager::OnLayersManagerSceneChange);

		p = new TLayersManagerPrivate();
		
		p->world = world_director->GetWorld();
		p->layers_change_listener.reset(new TLayersManagerEditorListener(this));
		WriteInfoToLog("Initializing TLayersManager success");
	}

	void TLayersManager::Destroy()
	{
		delete p;
	}
	IBaluSceneInstance* TLayersManager::GetActiveScene()
	{
		return p->scene_instance;
	}
	void TLayersManager::OnLayersManagerSceneChange(TEditor^ sender, IBaluSceneInstance* scene_instance)
	{
		if (p->scene_instance != scene_instance)
		{
			if (p->scene_instance != nullptr)
			{
				p->source_scene->GetLayers()->RemoveListener(p->layers_change_listener.get());
			}
			p->scene_instance = scene_instance;
			if (scene_instance != nullptr)
			{
				p->source_scene = (IBaluScene*)p->scene_instance->GetSource()->GetLayers()->GetScene();
				p->source_scene->GetLayers()->AddListener(p->layers_change_listener.get());
			}
		}
		GUI_Notify_LayersManagerSceneChange(sender, scene_instance != nullptr);
	}
	void TLayersManager::AddLayer()
	{
		p->scene_instance->GetSource()->GetLayers()->AddLayer(TLayer(), -1);
	}
	void TLayersManager::RemoveLayer(int id)
	{
		p->scene_instance->GetSource()->GetLayers()->RemoveLayer(id);
	}
	int TLayersManager::GetLayersCount()
	{
		return p->scene_instance->GetSource()->GetLayers()->GetLayersCount();
	}
	TLayerDesc^ TLayersManager::GetLayer(int id)
	{
		auto v = p->scene_instance->GetSource()->GetLayers()->GetLayer(id);
		TLayerDesc^ desc = gcnew TLayerDesc();
		desc->alpha = v.GetAlpha();
		desc->locked = v.IsLocked();
		desc->visible_in_editor = v.IsVisibleInEditor();
		desc->name = Converters::ToClrString(v.GetName());
		desc->visible = v.IsVisible();

		return desc;
	}
	void TLayersManager::SetLayer(int id, TLayerDesc^ desc)
	{
		TLayer layer;
		layer.SetIsVisible(desc->visible);
		layer.SetName(Converters::FromClrString( desc->name));
		layer.SetAlpha(desc->alpha);
		layer.SetIsLocked(desc->locked);
		layer.SetIsVisibleInEditor(desc->visible_in_editor);
		p->scene_instance->GetSource()->GetLayers()->SetLayer(id, layer);
	}
}