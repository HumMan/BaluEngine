
#ifndef BALU_ENGINE_DISABLE_PRAGMA_ONCE
#pragma once
#endif

#include <World\Layers.h>

#ifndef BALU_ENGINE_SCRIPT_CLASSES

#ifndef BALU_ENGINE_DISABLE_PRAGMA_ONCE
#include "../Class/IClass.h"
#endif

#include "../../BaluLib/Source/BVolumes/AABB.h"

#include <Interfaces\exportMacro.h>
#endif

namespace EngineInterface
{

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	class IBaluSceneClassInstance
	{
	public:
		virtual ~IBaluSceneClassInstance(){}
		virtual void SetTransform(TBaluTransform transform) = 0;
		virtual void SetScale(TVec2 scale) = 0;
		virtual TBaluTransform GetTransform() = 0;
		virtual TVec2 GetScale() = 0;
		virtual IBaluClass* GetClass() = 0;
	};
#endif

#ifndef BALU_ENGINE_SCRIPT_CLASSES

	class TViewport : public EngineInterface::IViewport
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

	class IBaluScene
	{
	public:
		BALUENGINEDLL_API static TVec2 FromViewportToScene(EngineInterface::IViewport* viewport, TVec2 viewport_coord);
		BALUENGINEDLL_API static TVec2 FromSceneToViewport(EngineInterface::IViewport* viewport, TVec2 scene_coord);

		static std::string GetDefaultName()
		{
			return "scene";
		}

		virtual TLayersManager* GetLayers() = 0;

		virtual IViewport* CreateViewport(std::string name)=0;
		virtual IViewport* FindViewport(std::string name)=0;

		virtual std::string GetName() = 0;
		virtual void SetName(std::string name) = 0;

		virtual int GetInstancesCount() = 0;
		virtual TSceneObject* GetInstance(int index) = 0;

		virtual TSceneObject* CreateInstance(IBaluClass* balu_class) = 0;
		virtual void DestroyInstance(TSceneObject* instance) = 0;
	};
#endif

#ifdef BALU_ENGINE_SCRIPT_CLASSES	
	BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, IBaluScene, "IScene");
	MUnpackRA1(WrapPointer<IViewport>, TYPE, FindViewport, TString);
	BALU_ENGINE_SCRIPT_END_CLASS;
#endif

}