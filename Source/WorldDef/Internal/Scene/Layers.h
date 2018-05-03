#pragma once

#include "../../Interface.h"

#include "../Common/Common.h"

namespace BaluEngine
{
	namespace WorldDef
	{
		namespace Internal
		{


			class TLayersManager;

			class TLayer: public TProperties, public ILayer
			{
			private:
				TLayersManager * manager;
			protected:
				void InitAllProperties()
				{
					InitProperty_Alpha();
					InitProperty_Visible();
					InitProperty_Order();
					InitProperty_Alpha();
					InitProperty_Locked();
					InitProperty_VisibleInEditor();
				}
			public:

				BALU_ENGINE_REGISTER_PROPERTY(Name, PropertyType::String, "Default")
				BALU_ENGINE_REGISTER_PROPERTY(Visible, PropertyType::Bool, true)
				BALU_ENGINE_REGISTER_PROPERTY(Order, PropertyType::Int, 0)
				BALU_ENGINE_REGISTER_PROPERTY(Alpha, PropertyType::Float, 1)
				BALU_ENGINE_REGISTER_PROPERTY(Locked, PropertyType::Bool, false)
				BALU_ENGINE_REGISTER_PROPERTY(VisibleInEditor, PropertyType::String, true)

				TLayer();
				TLayer(std::string name, bool visible);

				void Save(pugi::xml_node& parent_node, const int version)const;
				void Load(const pugi::xml_node& instance_node, const int version, IWorld* world);
			};

			class TLayersManager :public ILayersManager
			{
			private:
				IScene * scene;
				std::vector<std::unique_ptr<TLayer>> layers;

				std::vector<ILayersManagerChangeListener*> listeners;
			public:
				TLayersManager(IScene* scene);
				IScene* GetScene()
				{
					return scene;
				}
				void AddListener(ILayersManagerChangeListener* listener)
				{
					auto it = std::find(listeners.begin(), listeners.end(), listener);
					assert(it == listeners.end());
					listeners.push_back(listener);
				}
				void RemoveListener(ILayersManagerChangeListener* listener)
				{
					auto it = std::find(listeners.begin(), listeners.end(), listener);
					assert(it != listeners.end());
					listeners.erase(it);
				}
				ILayer* GetLayer(int id);
				int GetLayersCount();
				ILayer* AddLayer(int after_id, const std::string& name);
				void RemoveLayer(int layer_id);
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
			};*/
		}
	}
}
