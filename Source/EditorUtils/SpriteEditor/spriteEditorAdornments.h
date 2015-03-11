#pragma once

#include <memory>

#include "..\..\EngineInterfaces.h"

using namespace EngineInterface;

class TDrawingHelper;
class IVisualAdornment;

class TSpritePolygonAdornmentPrivate;
class TSpritePolygonOBBAdornmentPrivate;

class TSpritePolygonOBBAdornment
{
	std::unique_ptr<TSpritePolygonOBBAdornmentPrivate> p;
public:
	TSpritePolygonOBBAdornment(EngineInterface::IBaluSceneInstance* scene_instance, IVisualAdornment* visual, TDrawingHelper* drawing_helper);

	static EngineInterface::IBaluClass* TSpritePolygonOBBAdornment::CreateClass(EngineInterface::IBaluWorld* world, EngineInterface::IBaluScene* scene, TSpritePolygonOBBAdornmentPrivate* data);
	~TSpritePolygonOBBAdornment();
};

class TSpritePolygonAdornment
{
	std::unique_ptr<TSpritePolygonAdornmentPrivate> p;
public:
	TSpritePolygonAdornment(EngineInterface::IBaluSceneInstance* scene_instance, EngineInterface::IBaluSprite* visual, TDrawingHelper* drawing_helper);

	static EngineInterface::IBaluClass* TSpritePolygonAdornment::CreateClass(EngineInterface::IBaluWorld* world, EngineInterface::IBaluScene* scene, TSpritePolygonAdornmentPrivate* data);
	~TSpritePolygonAdornment();
};