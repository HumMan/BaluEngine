#pragma once

#include "../abstractEditor.h"
#include "../BoundaryEditor.h"

#include "../../EngineInterfaces/IScene.h"

using namespace EngineInterface;

class TClassInstanceAdornment : public  TBoundaryBoxAdornment
{
	IBaluSceneClassInstance* class_instance;
public:
	IBaluSceneClassInstance* GetSource(){ return class_instance; }
	TClassInstanceAdornment(IBaluSceneClassInstance* class_instance);
	void OnBoxChange(TOBB<float, 2> old_box, TOBB<float, 2> new_box);
	void Render(TDrawingHelper* drawing_helper);
	bool IsCollideWithAdornment(TVec2 world_cursor_location);
	bool IsCollideWithObject(TVec2 world_cursor_location);
};