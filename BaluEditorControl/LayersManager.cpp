
#include "LayersManager.h"

#include <baluLib.h>
#include <assert.h>

#include "../Source/EngineInterfaces.h"
#include "../Source/EditorInterfaces.h"

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
			editor->OnLayersManagerSceneChange(editor, editor->GetActiveScene());
		}
		virtual void LayerAdded(int layer_id)
		{
			editor->OnLayersManagerSceneChange(editor, editor->GetActiveScene());
		}
		virtual void LayerRemoved(int layer_id)
		{
			editor->OnLayersManagerSceneChange(editor, editor->GetActiveScene());
		}
		virtual void LayerChanged(int layer_id)
		{
			editor->OnLayersManagerSceneChange(editor, editor->GetActiveScene());
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
		WriteInfoToLog("Initializing TLayersManager");

		this->director = world_director;
		world_director->RegisterEditor(this);

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
				p->source_scene = (IBaluScene*)p->scene_instance->GetLayers()->GetSource()->GetScene();
				p->scene_instance->GetLayers()->GetSource()->AddListener(p->layers_change_listener.get());
			}
		}
		LayersManagerSceneChange(sender, scene_instance!=nullptr);
	}
	void TLayersManager::AddLayer()
	{
		p->scene_instance->GetLayers()->GetSource()->AddLayer(TLayer(), -1);
	}
	void TLayersManager::RemoveLayer(int id)
	{
		p->scene_instance->GetLayers()->GetSource()->RemoveLayer(id);
	}
	int TLayersManager::GetLayersCount()
	{
		return p->scene_instance->GetLayers()->GetLayers().size();
	}
	TLayerDesc^ TLayersManager::GetLayer(int id)
	{
		auto v = p->scene_instance->GetLayers()->GetLayers()[id];
		TLayerDesc^ desc = gcnew TLayerDesc();
		desc->alpha = v.GetAlpha();
		desc->locked = v.IsLocked();
		desc->visible_in_editor = v.IsVisibleInEditor();

		auto vs = p->scene_instance->GetLayers()->GetSource()->GetLayer(id);
		desc->name = Converters::ToClrString(vs.GetName());
		desc->visible = vs.IsVisible();

		return desc;
	}
	void TLayersManager::SetLayer(int id, TLayerDesc^ desc)
	{
		TLayer layer;
		layer.SetIsVisible(desc->visible);
		layer.SetName(Converters::FromClrString( desc->name));
		p->scene_instance->GetLayers()->GetSource()->SetLayer(id, layer);
		TLayerInstance layer_inst;
		layer_inst.SetAlpha(desc->alpha);
		layer_inst.SetIsLocked(desc->locked);
		layer_inst.SetIsVisibleInEditor(desc->visible_in_editor);
		p->scene_instance->GetLayers()->SetLayer(id, layer_inst);
	}
}