#pragma once

#include <memory>

#include "..\..\EngineInterfaces.h"

using namespace EngineInterface;

class TDrawingHelper;
class IVisualAdornment;

class TClassInstanceAdornmentPrivate;

class TClassInstanceAdornment
{
	std::unique_ptr<TClassInstanceAdornmentPrivate> p;
public:

	TClassInstanceAdornment(EngineInterface::IBaluSceneInstance* scene_instance, IVisualAdornment* visual, TDrawingHelper* drawing_helper);

	static EngineInterface::IBaluClass* TClassInstanceAdornment::CreateClass(EngineInterface::IBaluWorld* world, EngineInterface::IBaluScene* scene, TClassInstanceAdornmentPrivate* data);
	~TClassInstanceAdornment();
};

