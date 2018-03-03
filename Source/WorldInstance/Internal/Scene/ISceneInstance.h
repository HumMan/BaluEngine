#pragma once

#include <WorldDef/Objects/Scene/Layers.h>
#include <Render/RenderCommand.h>
#include <WorldDef/Objects/Scene/IScene.h>

#include "../Class/IClassInstance.h"
#include "../Material/IMaterialInstance.h"

#ifdef BALUENGINEDLL_EXPORTS
#include "Utils/DebugDraw.h"
#endif

namespace EngineInterface
{
	class IBaluWorldInstance;
	class TSceneObjectInstance;
	class IGUIVisual;
}

namespace EngineInterface
{

	class IBaluSceneInstance
	{
	public:
		virtual bool PointCollide(TVec2 scene_space_point, TSceneObjectInstance* &result) = 0;
		virtual IBaluScene* GetSource()=0;
		virtual IBaluWorldInstance* GetWorld()=0;
		virtual IViewport* GetViewport(std::string name)=0;
		virtual void QueryAABB(TAABB2 frustum, std::vector<TRenderCommand>& results, std::vector<IGUIVisual*>& gui) = 0;
		//virtual TSceneObjectInstance* CreateInstance(TSceneObject* use_class, TBaluTransform transform, TVec2 scale) = 0;
		virtual void DestroyInstance(TSceneObjectInstance*) = 0;
	};

#ifdef BALUENGINEDLL_EXPORTS
	struct TCollisionInfo
	{
		b2Fixture *A, *B;
		TCollisionInfo(){}
		TCollisionInfo(b2Fixture* A, b2Fixture* B)
		{
			this->A = A;
			this->B = B;
		}
		bool operator==(const TCollisionInfo& r)const
		{
			return (A == r.A && B == r.B) || (A == r.B && B == r.A);
		}
	};

	class TContactsHolder : public b2ContactListener
	{
	public:
		std::vector<TCollisionInfo> contacts;
		std::vector<TCollisionInfo> in_step_contacts;

		void AddContact(TCollisionInfo collision)
		{
			auto it = std::find(contacts.begin(), contacts.end(), collision);
			if (it == contacts.end())
			{
				contacts.push_back(collision);
			}
		}
		void RemoveContact(TCollisionInfo collision)
		{
			auto it = std::find(contacts.begin(), contacts.end(), collision);
			if (it != contacts.end())
			{
				contacts.erase(it);
			}
		}
		void AddInStepContact(TCollisionInfo collision)
		{
			auto it = std::find(in_step_contacts.begin(), in_step_contacts.end(), collision);
			if (it == in_step_contacts.end())
			{
				in_step_contacts.push_back(collision);
			}
		}
		void RemoveInStepContact(TCollisionInfo collision)
		{
			auto it = std::find(in_step_contacts.begin(), in_step_contacts.end(), collision);
			if (it != in_step_contacts.end())
			{
				in_step_contacts.erase(it);
			}
		}

		void BeginContact(b2Contact* contact);
		void EndContact(b2Contact* contact);
		void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
		void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);

		void BeforePhysStep()
		{
			in_step_contacts.clear();
		}
		void OnProcessCollisions();
	};

	class TSceneInstance : public IBaluSceneInstance, public IChangeListener
	{
	private:
		TResources* resources;

		std::unique_ptr<b2World> phys_world;

		DebugDraw phys_debug;

		TScene* source;
		std::vector<std::unique_ptr<TSceneObjectInstance>> instances;

		std::map<std::string, TViewport> viewports;

		//struct TCollisionInfo
		//{
		//	TBaluPhysShapeInstance *A, *B;
		//	TCollisionInfo(){}
		//	TCollisionInfo(TBaluPhysShapeInstance* A, TBaluPhysShapeInstance* B)
		//	{
		//		this->A = A;
		//		this->B = B;
		//	}
		//};
		//std::vector<TCollisionInfo> begin_contact, end_contact;

		TBaluWorldInstance* world;

		TContactsHolder contact_listener;
	public:
		TResources* GetResources()
		{
			return resources;
		}
		b2World* GetPhysWorld()
		{
			return phys_world.get();
		}
		bool PointCollide(TVec2 scene_space_point, TSceneObjectInstance* &result);

		TScene* GetSource();
		IBaluWorldInstance* GetWorld();

		TViewport* GetViewport(std::string name);

		TSceneInstance(TBaluWorldInstance* world, TScene* source, TResources* resources);
		TSceneInstance(TBaluWorldInstance* world, TResources* resources, TLayersManager* layers = nullptr);
		//TSceneInstance(TSceneInstance&& right);
		~TSceneInstance();

		//TSceneObjectInstance* CreateInstance(TSceneObject* use_class, TBaluTransform transform, TVec2 scale);
		//IBaluTransformedClassInstance* CreateInstance(TSceneObject* use_class, TBaluTransform transform, TVec2 scale);
		void AddInstance(TSceneObjectInstance*);
		void DestroyInstance(TSceneObjectInstance*);

		void QueryAABB(TAABB2 frustum, std::vector<TSpritePolygonInstance*>& results);
		void QueryAABB(TAABB2 frustum, std::vector<TRenderCommand>& results, std::vector<IGUIVisual*>& gui);

		
		void PhysStep(float step);

		void OnProcessCollisions();
		void OnStep(float step);
		
		void UpdateTransform();

		void DoDebugDraw(TDrawingHelperContext drawing_context);
};
#endif

}
