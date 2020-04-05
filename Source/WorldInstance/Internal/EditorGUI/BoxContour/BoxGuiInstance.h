#pragma once

#include <WorldDef/Internal/EditorGUI/BoxGui.h>

#include "../../../Interface.h"

#include <Render/RenderCommand.h>

namespace BaluEngine
{
	namespace WorldInstance
	{
		namespace Internal
		{

			class TOBBContourPrivate;

			class TOBBContour : public ISceneObjectInstance, public WorldDef::Internal::TBoxGui, public IGUIVisual
			{
			public:	
				void Render(TDrawingHelper* helper)const;
			};
		}
	}
}
