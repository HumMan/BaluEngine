#ifndef BALU_ENGINE_SCRIPT_CLASSES
#pragma once
#endif

#include <Interfaces\ExportMacro.h>
#include <baluLib.h>
using namespace BaluLib;

#if !defined(BALU_ENGINE_SCRIPT_CLASSES) && !defined(BALU_ENGINE_DLL_INTERFACES) && !defined(BALU_ENGINE_DISABLE_PRAGMA_ONCE)

#endif

class NVGcontext;
class TSMethod;

namespace pugi
{
	class xml_node;
}

namespace EngineInterface
{
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

	enum class TScriptActiveType
	{
		DEFAULT = 0,
		EDITOR = 1
	};

	class BALUENGINEDLL_API TScript
	{
	private:
		std::string script_source;
		TScriptActiveType script_type;
	public:
		TScript();
		TScript(std::string script_source);
		TScript(std::string script_source, TScriptActiveType script_type);
		TScriptActiveType GetScriptType();
		void SetScriptType(TScriptActiveType type);
		std::string GetScriptSource();
		void SetScriptSource(const char* source);
		void SaveToXML(pugi::xml_node& parent_node, const int version);
		void LoadFromXML(const pugi::xml_node& document_node, const int version);
	};

	class BALUENGINEDLL_API TScriptInstance
	{
	private:
		TScript* source;
		TSMethod* compiled_script;
	public:
		TScript* GetSource();
		TScriptInstance();
		TScriptInstance(TScript* source, TSMethod* compiled_script);
		TSMethod* GetCompiledScript();
	};
}