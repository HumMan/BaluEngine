#pragma once

#include <memory>

namespace EngineInterface
{
	class IBaluClass;
	class IBaluWorld;
	class IBaluScene;
	class IBaluSceneInstance;
}

class TClassInstanceAdornmentPrivate;

class TClassInstanceAdornment
{
	std::unique_ptr<TClassInstanceAdornmentPrivate> p;
public:

	TClassInstanceAdornment(EngineInterface::IBaluSceneInstance* scene_instance);

	//IBaluSceneClassInstance* GetSource(){ return class_instance; }
	//TClassInstanceAdornment(IBaluSceneClassInstance* class_instance);
	//void OnBoxChange(TOBB<float, 2> old_box, TOBB<float, 2> new_box);
	//void Render(TDrawingHelper* drawing_helper);
	//bool IsCollideWithAdornment(TVec2 world_cursor_location);
	//bool IsCollideWithObject(TVec2 world_cursor_location);

	static EngineInterface::IBaluClass* TClassInstanceAdornment::CreateClass(EngineInterface::IBaluWorld* world, EngineInterface::IBaluScene* scene);
};