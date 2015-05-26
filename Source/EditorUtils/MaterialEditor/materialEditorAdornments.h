#pragma once

#include <memory>

#include "..\..\EngineInterfaces.h"

using namespace EngineInterface;

class TDrawingHelper;
class IVisualAdornment;

class TMaterialInstanceAdornmentPrivate;

class TMaterialInstanceAdornment
{
	std::unique_ptr<TMaterialInstanceAdornmentPrivate> p;
public:

	TMaterialInstanceAdornment(EngineInterface::IBaluWorld* world, EngineInterface::IBaluSceneInstance* scene_instance, EngineInterface::IBaluMaterial* material);
	~TMaterialInstanceAdornment();
};
