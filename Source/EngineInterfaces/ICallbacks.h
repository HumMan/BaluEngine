#pragma once

#include "../../../BaluLib/Source/Math/vec.h"

#include "../Callbacks.h"

class NVGcontext;

namespace EngineInterface
{
	class IBaluWorldInstance;
	class IDirector;
	class IComposer;

	class TMouseEventArgs;

	class IBaluPhysShapeInstance;
	class IBaluInstance;
	class TCustomDrawCommand;

	typedef void(*MouseCallback)(TCallbackData* callback, TMouseEventArgs* e);
	typedef void(*OnStartWorldCallback)(TCallbackData* data, EngineInterface::IBaluWorldInstance* world_instance, EngineInterface::IComposer* composer);
	typedef void(*ViewportResizeCallback)(TCallbackData* data, EngineInterface::IDirector* director, TVec2i old_size, TVec2i new_size);
	typedef void(*CollideCallback)(TCallbackData* callback, EngineInterface::IBaluPhysShapeInstance* source, EngineInterface::IBaluInstance* obstacle);
	typedef void(*KeyUpDownCallback)(TCallbackData* data, EngineInterface::IBaluInstance* object);
	typedef void(*BeforePhysicsCallback)(TCallbackData* data, EngineInterface::IBaluInstance* object);
	typedef void(*TCustomDrawCallback)(TCallbackData* callback, NVGcontext* vg, TCustomDrawCommand* params);
}