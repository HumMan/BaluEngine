#pragma once

namespace BaluEngine
{
	namespace WorldInstance
	{
		class ISceneObjectInstance
		{
		public:
			virtual ~ISceneObjectInstance() {};
			virtual std::shared_ptr<WorldDef::IRuntimeProperties> GetProperties() = 0;
		};


		class IScene
		{
		public:
			virtual bool PointCollide(BaluLib::TVec2 scene_space_point, std::shared_ptr<ISceneObjectInstance> &result) = 0;
			virtual WorldDef::IScene* GetSource() = 0;
			virtual std::shared_ptr < IWorld> GetWorld() = 0;
			virtual WorldDef::IViewport* GetViewport(std::string name) = 0;
			void QueryAABB(BaluLib::TAABB2 frustum, std::vector< std::shared_ptr<ISpritePolygonInstance>>& results);
			//void QueryAABB(BaluLib::TAABB2 frustum, std::vector<TRenderCommand>& results, std::vector<IGUIVisual*>& gui);

			//virtual ISceneObjectInstance* CreateInstance(WorldDef::ISceneObject* use_class, WorldDef::TTransform transform, BaluLib::TVec2 scale) = 0;
			//virtual void DestroyInstance(ISceneObjectInstance*) = 0;

			virtual size_t GetInstancesCount()=0;
			virtual std::shared_ptr < ISceneObjectInstance> GetInstance(size_t index)=0;
			virtual void SetCollideListener(ISceneContactListener* contacts_listener)=0;
			virtual ~IScene() {};
		};

		class ISceneContactListener
		{
		public:
			virtual void ProcessCollision(
				std::shared_ptr<ITransformedClassInstance> instance_a,
				std::shared_ptr<ITransformedSpriteInstance> sprite_a,
				std::shared_ptr<ITransformedClassInstance> instance_b) = 0;
		};
	}
}
