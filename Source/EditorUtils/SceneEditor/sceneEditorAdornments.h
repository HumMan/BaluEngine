#pragma once

#include <memory>

#include "..\..\EngineInterfaces.h"

using namespace EngineInterface;



//class TClassInstanceAdornmentStateItem
//{
//
//};
//
//class TClassInstanceAdornmentState
//{
//public:
//
//};

class TDrawingHelper;
class IVisualAdornment;

class TClassInstanceAdornmentPrivate;

class TClassInstanceAdornment
{
	std::unique_ptr<TClassInstanceAdornmentPrivate> p;
public:

	TClassInstanceAdornment(EngineInterface::IBaluSceneInstance* scene_instance, IVisualAdornment* visual, TDrawingHelper* drawing_helper);

	//IBaluSceneClassInstance* GetSource(){ return class_instance; }
	//TClassInstanceAdornment(IBaluSceneClassInstance* class_instance);
	//void OnBoxChange(TOBB<float, 2> old_box, TOBB<float, 2> new_box);
	//void Render(TDrawingHelper* drawing_helper);
	//bool IsCollideWithAdornment(TVec2 world_cursor_location);
	//bool IsCollideWithObject(TVec2 world_cursor_location);

	static EngineInterface::IBaluClass* TClassInstanceAdornment::CreateClass(EngineInterface::IBaluWorld* world, EngineInterface::IBaluScene* scene, TClassInstanceAdornmentPrivate* data);
	//IBaluInstance* GetInstance();
	~TClassInstanceAdornment();
};

class TOBBContourPrivate;

class TOBBContour
{
	std::unique_ptr<TOBBContourPrivate> p;
public:

	TOBBContour(IBaluSceneInstance* scene_instance, TDrawingHelper* drawing_helper);

	void SetBox(TOBB2 box);

	void SetEnable(bool enable);

	static EngineInterface::IBaluClass* TOBBContour::CreateClass(EngineInterface::IBaluWorld* world, EngineInterface::IBaluScene* scene, TOBBContourPrivate* data);
	~TOBBContour();
};