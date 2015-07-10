#pragma once

#include <baluLib.h>
#include "../EngineInterfaces/IMaterialInstance.h"
#include "BoxGui.h"

#include "..\RenderCommand.h"

#include "..\EngineInterfaces\IWorld.h"

using namespace EngineInterface;

class TOBBContourPrivate;

class TOBBContour: public EngineInterface::TSceneObjectInstance, public TBoxGuiDef, public EngineInterface::IGUIVisual
{
public:
	bool enable;

	void SetBox(TOBB2 box);

	void SetEnable(bool enable);

	void Render(TDrawingHelper* helper)const;
};