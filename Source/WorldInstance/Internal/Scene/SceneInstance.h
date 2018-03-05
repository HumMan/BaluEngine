#pragma once

#include "../../Interface.h"

#include "Render/Render.h"
#include "Render/DrawingHelper.h"

class b2World;

namespace BaluEngine
{
	namespace WorldInstance
	{
		namespace Internal
		{
			class TSceneObjectInstance : public ISceneObjectInstance
			{
			private:
				IScene * scene;
			public:
				IScene * GetScene();
				TSceneObjectInstance(IScene* scene);
				virtual void QueryAABB(BaluLib::TAABB2 frustum, std::vector<ISpritePolygonInstance*>& results) {}
				virtual BaluLib::TOBB2 GetOBB() = 0;
				virtual void SetTransform(WorldDef::TTransform transform) {}
				virtual WorldDef::ISceneObject* GetSource() { return nullptr; };
				virtual WorldDef::TTransform GetTransform() { return WorldDef::TTransform(); }
				virtual BaluLib::TVec2 GetScale() { return BaluLib::TVec2(); }
				virtual void SetScale(BaluLib::TVec2 scale) {}
				virtual bool PointCollide(BaluLib::TVec2 scene_space_point) = 0;
				//virtual void UpdateTransform() {};
				//virtual void OnMouseUp(TMouseEventArgs e, TVec2 scene_cursor_location) {};
				//virtual void OnMouseDown(TMouseEventArgs e, TVec2 scene_cursor_location) {};
				//virtual void OnMouseMove(TMouseEventArgs e, TVec2 scene_cursor_location) {};
				virtual ~TSceneObjectInstance() {}
			};

			typedef ISceneObjectInstance*(*SceneObjectInstanceClone)(WorldDef::ISceneObject* source_def, IScene* scene);
			class SceneObjectInstanceFactory
			{
			public:
				static bool Register(const char* name, SceneObjectInstanceClone clone);
				static void UnregisterAll();
				static ISceneObjectInstance* Create(const char* name, WorldDef::ISceneObject* param, IScene* scene);
			};

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
				class TPrivate;
				std::unique_ptr<TPrivate> p;
			public:
				TResources * GetResources();
				b2World* GetPhysWorld();
				bool PointCollide(BaluLib::TVec2 scene_space_point, ISceneObjectInstance* &result);

				WorldDef::IScene* GetSource();
				IWorld* GetWorld();

				WorldDef::IViewport* GetViewport(std::string name);

				TScene(IWorld* world, WorldDef::IScene* source/*, TResources* resources*/);
				TScene(IWorld* world/*, TResources* resources, TLayersManager* layers = nullptr*/);
				//TSceneInstance(TSceneInstance&& right);
				~TScene();

				//TSceneObjectInstance* CreateInstance(WorldDef::ISceneObject* use_class, WorldDef::TTransform transform, BaluLib::TVec2 scale);

				void AddInstance(ISceneObjectInstance*);
				void DestroyInstance(ISceneObjectInstance*);

				void QueryAABB(BaluLib::TAABB2 frustum, std::vector<ISpritePolygonInstance*>& results);
				void QueryAABB(BaluLib::TAABB2 frustum, std::vector<TRenderCommand>& results, std::vector<IGUIVisual*>& gui);


				void PhysStep(float step);

				void OnProcessCollisions();
				void OnStep(float step);

				void UpdateTransform();

				void DoDebugDraw(TDrawingHelperContext drawing_context);
			};

		}
	}
}
