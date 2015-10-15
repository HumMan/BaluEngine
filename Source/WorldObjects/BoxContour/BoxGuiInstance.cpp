
#include "BoxGuiInstance.h"

#include <EditorUtils\DrawingHelper.h>

#include "..\Scene\ISceneInstance.h"

void TOBBContour::SetBox(TOBB2 box)
{
	boundary = box;
}

void TOBBContour::SetEnable(bool enable)
{
	this->enable = enable;
}

void TOBBContour::Render(TDrawingHelper* helper)const
{
	if (enable)
	{
		helper->RenderBoxCountour(boundary, 1);
	}
}

TOBBContour::TOBBContour(TBaluSceneInstance* scene)
	:TSceneObjectInstance(scene)
{
	enable = false;
}