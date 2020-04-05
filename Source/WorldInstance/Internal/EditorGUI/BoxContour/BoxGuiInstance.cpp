
#include "BoxGuiInstance.h"

#include <Render/DrawingHelper.h>

using namespace BaluEngine;
using namespace BaluEngine::WorldInstance;
using namespace BaluEngine::WorldInstance::Internal;

void TOBBContour::Render(TDrawingHelper* helper)const
{
	if (enable)
	{
		helper->RenderBoxCountour(boundary, 1);
	}
}

//TOBBContour::TOBBContour(TSceneInstance* scene)
//	:TSceneObjectInstance(scene)
//{
//	enable = false;
//}
