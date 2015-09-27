#pragma once

#include <baluLib.h>
#include "../EngineInterfaces/IMaterialInstance.h"
#include "PolygonGui.h"

#include "..\RenderCommand.h"

#include "..\EngineInterfaces\IWorld.h"

class TSpritePolygonAdornmentInstance : public TSpritePolygonAdornment, public EngineInterface::TSceneObjectInstance, public EngineInterface::IGUIVisual
{
public:
	virtual void Render(TDrawingHelper* drawing_helper)const;

	TSpritePolygonAdornmentInstance(TBaluSceneInstance* scene);
	TOBB2 GetOBB()
	{
		return TOBB2();
	}
	bool PointCollide(TVec2 scene_space_point)
	{
		return false;
	}
};