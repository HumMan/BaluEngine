#pragma once

namespace BaluEngine
{
	namespace WorldInstance
	{

		class IComposerStage
		{
		public:
			virtual ~IComposerStage() {}
		};

		class IComposer
		{
		public:
			virtual IComposerStage* AddToRender(std::shared_ptr<IScene> scene_instance, WorldDef::IViewport* viewport) = 0;
			virtual void RemoveFromRender(std::shared_ptr<IComposerStage> stage) = 0;
			virtual ~IComposer() {}
		};
	}
}




