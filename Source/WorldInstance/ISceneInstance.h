#pragma once

namespace BaluEngine
{
	namespace WorldInstance
	{
		class ISceneObjectInstance
		{
		public:
			virtual ~ISceneObjectInstance() {};
		};


		class IScene
		{
		public:
			virtual bool PointCollide(BaluLib::TVec2 scene_space_point, ISceneObjectInstance* &result) = 0;
			virtual WorldDef::IScene* GetSource() = 0;
			virtual IWorld* GetWorld() = 0;
			virtual WorldDef::IViewport* GetViewport(std::string name) = 0;
			void QueryAABB(BaluLib::TAABB2 frustum, std::vector<ISpritePolygonInstance*>& results);
			//void QueryAABB(BaluLib::TAABB2 frustum, std::vector<TRenderCommand>& results, std::vector<IGUIVisual*>& gui);

			//virtual ISceneObjectInstance* CreateInstance(WorldDef::ISceneObject* use_class, WorldDef::TTransform transform, BaluLib::TVec2 scale) = 0;
			virtual void DestroyInstance(ISceneObjectInstance*) = 0;
		};
	}
}
