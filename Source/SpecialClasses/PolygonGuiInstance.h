#pragma once

#include <baluLib.h>
#include "../EngineInterfaces/IMaterialInstance.h"
#include "PolygonGui.h"

#include "..\RenderCommand.h"

#include "..\EngineInterfaces\IWorld.h"

class TSpritePolygonAdornmentInstance : public TSpritePolygonAdornment, public EngineInterface::TSceneObjectInstance, public EngineInterface::IGUIVisual
{
public:
	void Render(TDrawingHelper* drawing_helper);
};