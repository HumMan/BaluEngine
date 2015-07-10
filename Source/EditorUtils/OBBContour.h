//#pragma once
//
//#include <memory>
//
//#include "..\EngineInterfaces.h"
//
//#include "DrawingHelper.h"
//
//using namespace EngineInterface;
//
//class TOBBContourPrivate;
//
//class TOBBContour
//{
//	std::unique_ptr<TOBBContourPrivate> p;
//public:
//
//	TOBBContour(IBaluSceneInstance* editor_scene_instance, TDrawingHelper* drawing_helper);
//
//	void SetBox(TOBB2 box);
//
//	void SetEnable(bool enable);
//
//	static EngineInterface::IBaluClass* TOBBContour::CreateClass(EngineInterface::IBaluWorld* world, EngineInterface::IBaluScene* scene, TOBBContourPrivate* data);
//	~TOBBContour();
//};