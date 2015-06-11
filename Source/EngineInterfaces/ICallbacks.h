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

	typedef void(*MouseCallback)(void* user_data, TMouseEventArgs* e);
	typedef void(*OnStartWorldCallback)(void* user_data, EngineInterface::IBaluWorldInstance* world_instance, EngineInterface::IComposer* composer);
	typedef void(*ViewportResizeCallback)(void* user_data, EngineInterface::IDirector* director, TVec2i old_size, TVec2i new_size);
	typedef void(*CollideCallback)(void* user_data, EngineInterface::IBaluPhysShapeInstance* source, EngineInterface::IBaluInstance* obstacle);
	typedef void(*KeyUpDownCallback)(void* user_data, EngineInterface::IBaluInstance* object);
	typedef void(*BeforePhysicsCallback)(void* user_data, EngineInterface::IBaluInstance* object);
	typedef void(*TCustomDrawCallback)(void* user_data, NVGcontext* vg, TCustomDrawCommand* params);

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
		static inline const char* Get(TEventType index)
		{
			char* values[] =
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