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
			virtual IComposerStage* AddToRender(IScene* scene_instance, WorldDef::IViewport* viewport) = 0;
			virtual void RemoveFromRender(IComposerStage* stage) = 0;
			virtual ~IComposer() {}
		};
	}
}




