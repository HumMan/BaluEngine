#pragma once

#include <memory>

#include "..\..\EngineInterfaces.h"

using namespace EngineInterface;

class TDrawingHelper;
class IVisualAdornment;

class TSpritePolygonAdornmentPrivate;
class TSpritePolygonOBBAdornmentPrivate;

class TSpriteOBBAdornment
{
	std::unique_ptr<TSpritePolygonOBBAdornmentPrivate> p;
public:
	TSpriteOBBAdornment(EngineInterface::IBaluSceneInstance* scene_instance, IVisualAdornment* visual, TDrawingHelper* drawing_helper);

	static EngineInterface::IBaluClass* TSpriteOBBAdornment::CreateClass(EngineInterface::IBaluWorld* world, EngineInterface::IBaluScene* scene, TSpritePolygonOBBAdornmentPrivate* data);
	~TSpriteOBBAdornment();
};

class TSpritePolygonAdornment
{
	std::unique_ptr<TSpritePolygonAdornmentPrivate> p;
public:
	TSpritePolygonAdornment(EngineInterface::IBaluSceneInstance* scene_instance, EngineInterface::IBaluSprite* visual, TDrawingHelper* drawing_helper);

	static EngineInterface::IBaluClass* TSpritePolygonAdornment::CreateClass(EngineInterface::IBaluWorld* world, EngineInterface::IBaluScene* scene, TSpritePolygonAdornmentPrivate* data);
	~TSpritePolygonAdornment();
};

class TSpriteAdornmentPrivate;
class TSpriteAdornment
{
	std::unique_ptr<TSpriteAdornmentPrivate> p;
public:
	TSpriteAdornment(EngineInterface::IBaluSceneInstance* scene_instance, EngineInterface::IBaluSprite* visual, TDrawingHelper* drawing_helper);

	static EngineInterface::IBaluClass* TSpriteAdornment::CreateClass(EngineInterface::IBaluWorld* world, EngineInterface::IBaluScene* scene, TSpriteAdornmentPrivate* data);
	~TSpriteAdornment();
};