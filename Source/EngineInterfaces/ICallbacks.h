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

	enum class TEventType
	{
		OnWorldStart,
		OnViewportResize,
		OnGlobalMouseMove,
		OnGlobalMouseUp,
		OnGlobalMouseDown,
		OnClassBeforePhys,
		OnClassKeyDown,
		OnClassKeyUp,
		OnSpriteCollide,
		End
	};

	class TEventTypeString
	{
	public:
		static inline const std::string Get(TEventType index)
		{
			std::string values[] =
			{
				"OnWorldStart",
				"OnViewportResize",
				"OnGlobalMouseMove",
				"OnGlobalMouseUp",
				"OnGlobalMouseDown",
				"OnClassBeforePhys",
				"OnClassKeyDown",
				"OnClassKeyUp",
				"OnSpriteCollide",
			};
			return values[(int)index];
		}
		static inline TEventType From(std::string name)
		{
			for (int i = 0; i < (int)TEventType::End; i++)
			{
				if (Get((TEventType)i) == name)
					return (TEventType)i;
			}
			return TEventType::End;
		}
	};

	class TEventSignature
	{
	public:
		static inline const std::string Get(TEventType index)
		{
			const char* EventSignatures[] =
			{
				"func static StartWorld%s(IWorldInstance world_instance, IComposer composer)",
				"func static ViewportResize%s(IDirector director, vec2i old_size, vec2i new_size)",
				"func static MouseMove%s(IWorldInstance world_instance, TMouseEventArgs event)",
				"func static MouseUp%s(IWorldInstance world_instance, TMouseEventArgs event)",
				"func static MouseDown%s(IWorldInstance world_instance, TMouseEventArgs event)",
				"func static BeforePhys%s(IInstance object)",
				"func static KeyDown%s(IInstance object)",
				"func static KeyUp%s(IInstance object)",
				"func static Collide%s(IPhysShapeInstance source, IInstance obstancle)"
			};

			return EventSignatures[(int)index];
		}
	};
}