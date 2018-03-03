#pragma once

namespace BaluEngine
{
	namespace WorldInstance
	{
		class ISceneObjectInstance
		{
		public:
		};


		class IScene
		{
		public:
			virtual bool PointCollide(BaluLib::TVec2 scene_space_point, ISceneObjectInstance* &result) = 0;
			virtual WorldDef::IScene* GetSource() = 0;
			virtual IWorld* GetWorld() = 0;
			virtual WorldDef::IViewport* GetViewport(std::string name) = 0;
			//virtual void QueryAABB(BaluLib::TAABB2 frustum, std::vector<TRenderCommand>& results, std::vector<IGUIVisual*>& gui) = 0;
			//virtual TSceneObjectInstance* CreateInstance(TSceneObject* use_class, TBaluTransform transform, TVec2 scale) = 0;
			virtual void DestroyInstance(ISceneObjectInstance*) = 0;
		};
	}
}
