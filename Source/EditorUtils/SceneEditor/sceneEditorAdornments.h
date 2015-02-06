#pragma once

#include <memory>

#include "..\..\EngineInterfaces.h"

using namespace EngineInterface;

class TClassInstanceAdornmentPrivate;

class TClassInstanceAdornmentStateItem
{

};

class TClassInstanceAdornmentState
{
public:

};

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
	IBaluInstance* GetInstance();
	~TClassInstanceAdornment();
};