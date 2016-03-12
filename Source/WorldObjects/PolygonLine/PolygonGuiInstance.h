#pragma once

#include <baluLib.h>
#include "../Material/IMaterialInstance.h"
#include "PolygonGui.h"

#include <Render/RenderCommand.h>

#include <World\IWorld.h>

using namespace EngineInterface;

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