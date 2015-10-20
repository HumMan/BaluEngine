#pragma once

#include <World\Layers.h>

#include "../Class/IClass.h"
#include "../../BaluLib/Source/BVolumes/AABB.h"
#include <Interfaces\exportMacro.h>

namespace EngineInterface
{

	class TViewport : public IViewport
	{
		TBaluTransform transform;
		float aspect; //отношение высоты к ширине (0.5 широкий экран)
		float width;
	public:
		TBaluTransform GetTransform()
		{
			return transform;
		}

		void SetTransform(TBaluTransform transform)
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

		void Save(pugi::xml_node& parent_node, const int version);
		void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world);
	};

	class IBaluScene: public virtual IBaluWorldObject
	{
	public:
		BALUENGINEDLL_API static TVec2 FromViewportToScene(IViewport* viewport, TVec2 viewport_coord);
		BALUENGINEDLL_API static TVec2 FromSceneToViewport(IViewport* viewport, TVec2 scene_coord);

		static std::string GetDefaultName()
		{
			return "scene";
		}

		virtual TLayersManager* GetLayers() = 0;

		virtual IViewport* CreateViewport(const std::string& name) = 0;
		virtual IViewport* FindViewport(const std::string& name) = 0;

		virtual int GetInstancesCount() = 0;
		virtual TSceneObject* GetInstance(int index) = 0;

		virtual TSceneObject* CreateInstance(IBaluClass* balu_class) = 0;
		virtual void DestroyInstance(TSceneObject* instance) = 0;
	};

#ifdef BALUENGINEDLL_EXPORTS
	class TBaluScene : public IBaluScene, public TBaluWorldObject, public TChangeListenerArray
	{
	private:
		std::vector<std::unique_ptr<TSceneObject>> instances;

		std::map<std::string, TViewport> viewports;

		TLayersManager layers;

		TProperties properties;
		TBaluWorld* world;
	public:
		TLayersManager* GetLayers()
		{
			return &layers;
		}
		TBaluScene(const char* name, TBaluWorld* world);
		IProperties* GetProperties();

		TViewport* CreateViewport(const std::string& name);
		TViewport* FindViewport(const std::string& name);

		int GetInstancesCount();
		TSceneObject* GetInstance(int index);

		TSceneObject* CreateInstance(TBaluClass* balu_class);
		TSceneObject* CreateInstance(IBaluClass* balu_class);

		void DestroyInstance(TSceneObject*);

		void Save(pugi::xml_node& parent_node, const int version);
		void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world);

		IAbstractEditor* CreateEditor(TDrawingHelperContext drawing_context, IBaluWorldInstance* world_instance);
};
#endif

}