#pragma once

#include "../../Interface.h"

#include "Render/Render.h"

namespace BaluEngine
{
	namespace WorldInstance
	{
		namespace Internal
		{
			class TComposerStage : public IComposerStage
			{
				friend class TComposer;
				TComposer* composer;
				IScene* scene_instance;
				WorldDef::IViewport* viewport;
				TView view;
				//TODO effects, etc.
			public:
				void MoveFront();
				void MoveBack();
				void MoveForward();
				void MoveBackward();
			};


			class TComposer : public IComposer
			{
				class TPrivate;
				std::unique_ptr<TPrivate> p;
			public:
				TComposer();
				//TComposer(TRender* render);
				TComposerStage* AddToRender(IScene* scene_instance, WorldDef::IViewport* viewport);
				void RemoveFromRender(IComposerStage* stage);

				void Render(TRender* render);
				~TComposer();
			};
		}
	}
}