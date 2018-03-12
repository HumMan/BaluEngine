#pragma once

#include "../../Interface.h"

namespace BaluEngine
{
	namespace WorldInstance
	{
		namespace Internal
		{

			//class IScriptInstance
			//{
			//public:
			//	virtual bool HasErrors() = 0;
			//};

			//class TScriptInstance
			//{
			//private:
			//	/*TScript * source;
			//	TSMethod* compiled_script;*/
			//public:
			//	//TScript * GetSource();
			//	//TScriptInstance();
			//	//TScriptInstance(TScript* source, TSMethod* compiled_script);
			//	//TSMethod* GetCompiledScript();
			//};


			class TScriptInstance: public IEventsEditorInstance// : public IScriptInstance
			{
			private:
				class TPrivate;
				std::unique_ptr<TPrivate> p;
			public:
				void Compile();

				TScriptInstance(WorldDef::IEventsEditor* source);
				~TScriptInstance();

				void MouseDown(WorldDef::TMouseEventArgs e);
				void MouseMove(WorldDef::TMouseEventArgs e);
				void MouseUp(WorldDef::TMouseEventArgs e);
				void MouseVerticalWheel(int amount);
				
				void PrePhysStep();

				void KeyDown(WorldDef::TKey key);
				void KeyUp(WorldDef::TKey key);

				//void AddMouseEventListener(TMouseEventListener*);
				//void RemoveMouseEventListener(TMouseEventListener*);

				void ViewportResize(IDirector* director, BaluLib::TVec2i old_size, BaluLib::TVec2i new_size);

				void WorldStart(IWorld* world_instance, IComposer* composer);

				void Collide(ITransformedClassInstance* object,
						ITransformedSpriteInstance* obj_a, ITransformedClassInstance* obj_b);

				//void CallMouseUp(IWorld world, WorldDef::TMouseEventArgs event);
				//void CallMouseDown(IWorld world, WorldDef::TMouseEventArgs event);
				//void CallMouseMove(IWorld world, WorldDef::TMouseEventArgs event);
				//void CallWorldStart(IWorld world, IComposer* composer);
				//void CallViewportResize(IDirector* director, BaluLib::TVec2i old_size, BaluLib::TVec2i new_size);
				//void CallBeforePhysics();
				//void CallKeyDown(WorldDef::TKey key);
				//void CallKeyUp(WorldDef::TKey key);


				//bool HasErrors();
				//std::vector<std::string> GetErrors();
				//TBaluScriptInstance(std::string assets_dir);
				//~TBaluScriptInstance();
				//TScriptInstance CompileMethod(TScript* script, const char* code);
				//void CallViewportResize(IDirector* director, BaluLib::TVec2i old_size, BaluLib::TVec2i new_size);
				//void CallWorldStart(IBaluWorldInstance* world_instance, IComposer* composer);
				////KeyUp KeyDown BeforePhysicsStep
				//void CallInstanceEvent( IBaluTransformedClassInstance* obj);
				//void CallMouseEvent(TMouseEventArgs* e);
				//void CallKeyUpEvent(TKey key);
				//void CallKeyDownEvent(TKey key);
				//void CallCollide(IBaluTransformedClassInstance* object,
				//	IBaluTransformedSpriteInstance* obj_a, IBaluTransformedClassInstance* obj_b);

				//std::string AddName(std::string format, std::string name)
				//{
				//	size_t size = format.size() + name.size();
				//	std::unique_ptr<char> buf(new char[size]);
				//	sprintf(buf.get(), format.c_str());
				//	return buf.get();
				//}
			};
		}
	}
}


