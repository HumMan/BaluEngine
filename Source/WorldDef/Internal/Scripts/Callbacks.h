#pragma once

#include <Interfaces/ExportMacro.h>
#include <baluLib.h>
#include <string>
using namespace BaluLib;

class NVGcontext;
class TSMethod;

namespace pugi
{
	class xml_node;
}

namespace EngineInterface
{

	enum TKey :int
	{
		Left,
		Right,
		Up,
		Down
	};

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

	class BALUENGINEDLL_API TScript
	{
	private:
		std::string script_source;
	public:
		TScript();
		TScript(std::string script_source);
		std::string GetScriptSource();
		void SetScriptSource(const char* source);
		void SaveToXML(pugi::xml_node& parent_node, const int version);
		void LoadFromXML(const pugi::xml_node& document_node, const int version);
	};

	
}
