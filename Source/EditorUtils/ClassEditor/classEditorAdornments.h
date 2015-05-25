#pragma once


#include <memory>

#include "..\..\EngineInterfaces.h"


using namespace EngineInterface;

class TDrawingHelper;
class IVisualAdornment;

class TSpriteInstanceAdornmentPrivate;

class TClassSpriteAdornment
{
	std::unique_ptr<TSpriteInstanceAdornmentPrivate> p;
public:
	TClassSpriteAdornment(EngineInterface::IBaluSceneInstance* scene_instance, IVisualAdornment* visual, TDrawingHelper* drawing_helper);

	static EngineInterface::IBaluClass* TClassSpriteAdornment::CreateClass(EngineInterface::IBaluWorld* world, EngineInterface::IBaluScene* scene, TSpriteInstanceAdornmentPrivate* data);
	~TClassSpriteAdornment();
};