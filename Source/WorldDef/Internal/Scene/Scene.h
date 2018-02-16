#pragma once

#include "../../Interface.h"

namespace BaluEngine
{
	namespace WorldDef
	{
		namespace Internal
		{

			class TViewport : public IViewport
			{
				TTransform transform;
				float aspect; //отношение высоты к ширине (0.5 широкий экран)
				float width;
			public:
				TTransform GetTransform()
				{
					return transform;
				}

				void SetTransform(TTransform transform)
				{
					this->transform = transform;
				}
				void SetAspectRatio(float aspect)
				{
					this->aspect = aspect;
				}
				void SetWidth(float width)
				{
					this->width = width;
				}
				TAABB2 GetAABB()
				{
					TAABB2 aabb(TVec2(0, 0), TVec2(width, width * aspect)*0.5);

					return TOBB<float, 2>(transform.position, transform.GetOrientation(), aabb).GetAABB();
				}
				TVec2 GetSize()
				{
					return TVec2(width, width * aspect);
				}
				void SetSize(TVec2 size)
				{
					width = size[0];
					aspect = size[1] / size[0];
				}

				void Save(pugi::xml_node& parent_node, const int version)const;
				void Load(const pugi::xml_node& instance_node, const int version, IWorld* world);
			};

			class IScene : public virtual IWorldObject
			{
			public:
				static TVec2 FromViewportToScene(IViewport* viewport, TVec2 viewport_coord);
				static TVec2 FromSceneToViewport(IViewport* viewport, TVec2 scene_coord);

				static std::string GetDefaultName()
				{
					return "scene";
				}

				virtual TLayersManager* GetLayers() = 0;

				virtual IViewport* CreateViewport(const std::string& name) = 0;
				virtual IViewport* FindViewport(const std::string& name) = 0;

				virtual int GetInstancesCount() = 0;
				virtual TSceneObject* GetInstance(int index) = 0;

				virtual TSceneObject* CreateInstance(IClass* balu_class) = 0;
				virtual void DestroyInstance(TSceneObject* instance) = 0;
			};

			class TBaluScene : public IScene, public TWorldObject, public TChangeListenerArray
			{
			private:
				std::vector<std::unique_ptr<TSceneObject>> instances;

				std::map<std::string, TViewport> viewports;

				TLayersManager layers;

				TProperties properties;
				TWorld* world;
			public:
				static TWorldObjectType GetWorldObjectType()
				{
					return TWorldObjectType::Scene;
				}
				TLayersManager* GetLayers()
				{
					return &layers;
				}
				TBaluScene(const char* name, IWorld* world);
				IProperties* GetProperties();

				TViewport* CreateViewport(const std::string& name);
				TViewport* FindViewport(const std::string& name);

				int GetInstancesCount();
				TSceneObject* GetInstance(int index);

				TSceneObject* CreateInstance(TClass* balu_class);
				TSceneObject* CreateInstance(IClass* balu_class);

				void DestroyInstance(TSceneObject*);

				void Save(pugi::xml_node& parent_node, const int version)const;
				void Load(const pugi::xml_node& instance_node, const int version, IWorld* world);
			};

		}
	}
}
