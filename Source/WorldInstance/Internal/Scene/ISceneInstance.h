#pragma once

#include "../../Interface.h"

#include "Render/Render.h"

namespace BaluEngine
{
	namespace WorldInstance
	{
		namespace Internal
		{
			/*struct TCollisionInfo
			{
				b2Fixture *A, *B;
				TCollisionInfo() {}
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
			};*/

			class TScene : public IScene/*, public IChangeListener*/
			{
			private:
				//TResources * resources;

				//std::unique_ptr<b2World> phys_world;

				//DebugDraw phys_debug;

				TScene* source;
				std::vector<std::unique_ptr<ISceneObjectInstance>> instances;

				std::map<std::string, WorldDef::IViewport> viewports;

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

				IWorld* world;

				//TContactsHolder contact_listener;
			public:
				//TResources * GetResources()
				//{
				//	return resources;
				//}
				//b2World* GetPhysWorld()
				//{
				//	return phys_world.get();
				//}
				bool PointCollide(BaluLib::TVec2 scene_space_point, ISceneObjectInstance* &result);

				WorldDef::IScene* GetSource();
				IWorld* GetWorld();

				WorldDef::IViewport* GetViewport(std::string name);

				TScene(IWorld* world, WorldDef::IScene* source/*, TResources* resources*/);
				TScene(IWorld* world/*, TResources* resources, TLayersManager* layers = nullptr*/);
				//TSceneInstance(TSceneInstance&& right);
				~TScene();

				//TSceneObjectInstance* CreateInstance(TSceneObject* use_class, TBaluTransform transform, TVec2 scale);
				//IBaluTransformedClassInstance* CreateInstance(TSceneObject* use_class, TBaluTransform transform, TVec2 scale);
				void AddInstance(WorldDef::ISceneObject*);
				void DestroyInstance(ISceneObjectInstance*);

				void QueryAABB(TAABB2 frustum, std::vector<ISpritePolygonInstance*>& results);
				void QueryAABB(TAABB2 frustum, std::vector<TRenderCommand>& results, std::vector<IGUIVisual*>& gui);


				void PhysStep(float step);

				void OnProcessCollisions();
				void OnStep(float step);

				void UpdateTransform();

				//void DoDebugDraw(TDrawingHelperContext drawing_context);
			};

		}
	}
}
