#pragma once

#include <string>
#include <map>
#include <set>
#include <vector>
#include <assert.h>
#include <algorithm>

#include <Interfaces/ExportMacro.h>

namespace EngineInterface
{
	class TBaluSceneInstance;
	class TBaluScene;
}

namespace EngineInterface
{

	class TLayersManager;

	class BALUENGINEDLL_API TLayer
	{
	private:
		TLayersManager* manager;

		std::string name;
		bool visible;
		int order;

		float alpha;
		bool locked;
		bool editor_visible;
	public:
		TLayer();
		TLayer(std::string name, bool visible);
		std::string GetName();
		void SetName(std::string name);
		bool IsVisible();
		void SetIsVisible(bool visible);
		int GetOrder();
		void SetOrder(int order);
		float GetAlpha();
		void SetAlpha(float alpha);
		bool IsLocked();
		void SetIsLocked(bool is_locked);
		bool IsVisibleInEditor();
		void SetIsVisibleInEditor(bool is_editor_visible);
	};

	class TLayersManagerChangeListener
	{
	public:
		virtual void LayerAdded(int layer_id) = 0;
		virtual void LayerRemoved(int layer_id) = 0;
		virtual void LayerChanged(int layer_id) = 0;
	};

	class BALUENGINEDLL_API TLayersManager
	{
	private:
		TBaluScene* scene;
		std::vector<TLayer> layers;

		std::vector<TLayersManagerChangeListener*> listeners;
	public:
		TLayersManager(TBaluScene* scene)
		{
			layers.push_back(TLayer("Default", true));
			this->scene = scene;
		}
		TBaluScene* GetScene()
		{
			return scene;
		}
		void AddListener(TLayersManagerChangeListener* listener)
		{
			auto it = std::find(listeners.begin(), listeners.end(), listener);
			assert(it == listeners.end());
			listeners.push_back(listener);
		}
		void RemoveListener(TLayersManagerChangeListener* listener)
		{
			auto it = std::find(listeners.begin(), listeners.end(), listener);
			assert(it != listeners.end());
			listeners.erase(it);
		}
		TLayer GetLayer(int id);
		int GetLayersCount();
		void SetLayer(int id, TLayer layer);
		void AddLayer(TLayer layer, int after_id);
		void RemoveLayer(int layer_id);
		void MoveObjects(int from_layer_id, int to_layer_id);
	};

	/*class TInstanceLayersManagerChangeListener : public TLayersManagerChangeListener
	{
		TLayersManagerInstance* manager;
	public:
		TInstanceLayersManagerChangeListener(TLayersManagerInstance* manager);
		virtual void LayerReordered(int layer_id, int after_id);
		virtual void LayerAdded(int layer_id);
		virtual void LayerRemoved(int layer_id);
		virtual void LayerChanged(int layer_id);
	};

	class BALUENGINEDLL_API TLayersManagerInstance
	{
		friend class TInstanceLayersManagerChangeListener;
	private:
		TLayersManager* source;
		TBaluSceneInstance* scene;
		std::vector<TLayerInstance> layers;
		TInstanceLayersManagerChangeListener source_changes_listener;
	public:
		TLayersManagerInstance(TLayersManager* source);
		~TLayersManagerInstance();
		TLayersManager* GetSource();
		std::vector<TLayerInstance> GetLayers()
		{
			return layers;
		}
		void SetLayer(int id, TLayerInstance layer)
		{
			layers[id] = layer;
		}
	};*/
}
