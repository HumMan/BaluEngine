
#include "BoxGuiInstance.h"

#include <EditorUtils\DrawingHelper.h>

#include "..\Scene\SceneInstance.h"

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
{
	enable = false;
	scene->AddInstance(this);
}