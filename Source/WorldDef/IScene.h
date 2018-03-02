#pragma once

namespace BaluEngine
{
	namespace WorldDef
	{
		class IScene : public virtual IWorldObject
		{
		public:
			static BaluLib::TVec2 FromViewportToScene(IViewport* viewport, BaluLib::TVec2 viewport_coord);
			static BaluLib::TVec2 FromSceneToViewport(IViewport* viewport, BaluLib::TVec2 scene_coord);

			static std::string GetDefaultName()
			{
				return "scene";
			}

			//virtual TLayersManager* GetLayers() = 0;

			virtual IViewport* CreateViewport(const std::string& name) = 0;
			virtual IViewport* FindViewport(const std::string& name) = 0;

			virtual int GetInstancesCount() = 0;
			virtual ISceneObject* GetInstance(int index) = 0;

			virtual ISceneObject* CreateInstance(IClass* balu_class) = 0;
			virtual void DestroyInstance(ISceneObject* instance) = 0;
		};
	}
}