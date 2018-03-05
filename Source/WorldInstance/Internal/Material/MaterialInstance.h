#pragma once

#include "../../Interface.h"

namespace BaluEngine
{
	namespace WorldInstance
	{
		namespace Internal
		{

			class TMaterialInstance //: public IChangeListener
			{
				TBaluTexture texture;
				WorldDef::IMaterial* source;
				TResources* resources;

				virtual void SourceChanged();
			public:
				TMaterialInstance(WorldDef::IMaterial* source, TResources* resources);
				~TMaterialInstance();
				TBaluTexture GetTexture();
			};
		}
	}
}