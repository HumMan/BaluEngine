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
			class TSceneObjectInstance : public virtual ISceneObjectInstance
			{
			private:
				class TPrivate;
				std::unique_ptr<TPrivate> p;
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
				virtual void UpdateTransform() {};
				//virtual void OnMouseUp(TMouseEventArgs e, TVec2 scene_cursor_location) {};
				//virtual void OnMouseDown(TMouseEventArgs e, TVec2 scene_cursor_location) {};
				//virtual void OnMouseMove(TMouseEventArgs e, TVec2 scene_cursor_location) {};
				virtual ~TSceneObjectInstance();
				WorldDef::IRuntimeProperties* GetProperties();
			};

			typedef ISceneObjectInstance*(*SceneObjectInstanceClone)(WorldDef::ISceneObject* source_def, IScene* scene);
			class SceneObjectInstanceFactory
			{
			public:
				static bool Register(const char* name, SceneObjectInstanceClone clone);
				static void UnregisterAll();
				static ISceneObjectInstance* Create(const char* name, WorldDef::ISceneObject* param, IScene* scene);
			};

			

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

				TScene(IWorld* world, WorldDef::IScene* source, TResources* resources);
				TScene(IWorld* world, TResources* resources/*, TLayersManager* layers = nullptr*/);
				//TSceneInstance(TSceneInstance&& right);
				~TScene();

				//TSceneObjectInstance* CreateInstance(WorldDef::ISceneObject* use_class, WorldDef::TTransform transform, BaluLib::TVec2 scale);

				//void AddInstance(ISceneObjectInstance*);
				//void DestroyInstance(ISceneObjectInstance*);

				void QueryAABB(BaluLib::TAABB2 frustum, std::vector<ISpritePolygonInstance*>& results);
				void QueryAABB(BaluLib::TAABB2 frustum, std::vector<TRenderCommand>& results, std::vector<IGUIVisual*>& gui);

				size_t GetInstancesCount();
				ISceneObjectInstance* GetInstance(size_t index);

				void PhysStep(float step);

				void OnProcessCollisions();
				void OnStep(float step);

				void UpdateTransform();

				void DoDebugDraw(TDrawingHelperContext drawing_context);
			};

		}
	}
}
