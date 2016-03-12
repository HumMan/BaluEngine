#include "IEventsEditorInstance.h"

#include "IScriptInstance.h"

#include <Common/IDirector.h>

#include <pugixml.hpp>

using namespace pugi;
using namespace EngineInterface;
//
//
//void TBaluSceneInstance::OnKeyDown(TKey key)
//{
//	for (int i = 0; i < instances.size(); i++)
//	{
//		auto class_instance = dynamic_cast<TBaluTransformedClassInstance*>(instances[i].get());
//		if (class_instance != nullptr)
//			class_instance->GetClass()->GetScripts()->DoKeyDown(key, class_instance);
//	}
//}
//
//void TBaluSceneInstance::OnMouseUp(EngineInterface::TMouseEventArgs e, TVec2 scene_cursor_location)
//{
//	for (int i = 0; i < instances.size(); i++)
//	{
//		instances[i]->OnMouseUp(e, scene_cursor_location);
//	}
//}
//void TBaluSceneInstance::OnMouseDown(EngineInterface::TMouseEventArgs e, TVec2 scene_cursor_location)
//{
//	for (int i = 0; i < instances.size(); i++)
//	{
//		instances[i]->OnMouseDown(e, scene_cursor_location);
//	}
//}
//void TBaluSceneInstance::OnMouseMove(EngineInterface::TMouseEventArgs e, TVec2 scene_cursor_location)
//{
//	for (int i = 0; i < instances.size(); i++)
//	{
//		instances[i]->OnMouseMove(e, scene_cursor_location);
//	}
//}
//void TBaluSceneInstance::OnPrePhysStep()
//{
//	for (int i = 0; i < instances.size(); i++)
//	{
//		auto class_instance = dynamic_cast<TBaluTransformedClassInstance*>(instances[i].get());
//		if (class_instance != nullptr)
//			class_instance->GetClass()->GetScripts()->DoBeforePhysicsStep(class_instance);
//	}
//}
//void TBaluWorldInstance::OnPrePhysStep()
//{
//	for (int i = 0; i < scene_instances.size(); i++)
//		scene_instances[i]->OnPrePhysStep();
//}
//void TBaluWorldInstance::OnProcessCollisions()
//{
//	for (int i = 0; i < scene_instances.size(); i++)
//		scene_instances[i]->OnProcessCollisions();
//}
//
//void TBaluWorldInstance::KeyDown(TKey key)
//{
//	for (int i = 0; i < scene_instances.size(); i++)
//		scene_instances[i]->OnKeyDown(key);
//}
//
//void TBaluWorldInstance::KeyUp(TKey key)
//{
//	for (int i = 0; i < instances.size(); i++)
//		instances[i]->OnKeyUp(key);
//}
//
void TEventsEditorInstance::MouseDown(TMouseEventArgs e)
{
	for (auto& v : OnMouseEventListeners)
		v->OnMouseDown(e);
	for (auto& v : mouse_down_callbacks)
	{
		script_engine->CallMouseEvent(v, &e);
	}
}

void TEventsEditorInstance::MouseMove(TMouseEventArgs e)
{
	for (auto& v : OnMouseEventListeners)
		v->OnMouseMove(e);
	for (auto& v : mouse_move_callbacks)
	{
		script_engine->CallMouseEvent(v, &e);
	}
}

void TEventsEditorInstance::MouseUp(TMouseEventArgs e)
{
	for (auto& v : OnMouseEventListeners)
		v->OnMouseUp(e);
	for (auto& v : mouse_up_callbacks)
	{
		script_engine->CallMouseEvent(v, &e);
	}
}

void TEventsEditorInstance::MouseVerticalWheel(int amount)
{

}
void TEventsEditorInstance::AddMouseEventListener(TMouseEventListener* listener)
{
	auto it = std::find(OnMouseEventListeners.begin(), OnMouseEventListeners.end(), listener);
	if (it != OnMouseEventListeners.end())
		assert(false);
	OnMouseEventListeners.push_back(listener);
}

void TEventsEditorInstance::RemoveMouseEventListener(TMouseEventListener* listener)
{
	auto it = std::find(OnMouseEventListeners.begin(), OnMouseEventListeners.end(), listener);
	if (it == OnMouseEventListeners.end())
		assert(false);
	OnMouseEventListeners.erase(it);
}


bool TEventsEditorInstance::CompileScripts()
{
	try
	{
		for (auto& v : source->on_start_world_callback)
		{
			auto method_body = v.GetScriptSource();
			std::string method = std::string("func static StartWorld(IWorldInstance world_instance, IComposer composer)\n{\n") + method_body + "\n}\n";
			on_start_world_callback.push_back(script_engine->CompileMethod(&v, method.c_str()));
		}
		for (auto& v : source->viewport_resize_callback)
		{
			auto method_body = v.GetScriptSource();
			std::string method = std::string("func static ViewportResize(IDirector director, vec2i old_size, vec2i new_size)\n{\n") + method_body + "\n}\n";
			this->viewport_resize_callback.push_back(script_engine->CompileMethod(&v, method.c_str()));
		}

		for (auto& v : source->mouse_up_callbacks)
		{
			auto method_body = v.GetScriptSource();
			std::string method = std::string("") + method_body + "";
			this->mouse_up_callbacks.push_back(script_engine->CompileMethod(&v, method.c_str()));
		}
		for (auto& v : source->mouse_down_callbacks)
		{
			auto method_body = v.GetScriptSource();
			std::string method = std::string("") + method_body + "";
			this->mouse_down_callbacks.push_back(script_engine->CompileMethod(&v, method.c_str()));
		}
		for (auto& v : source->mouse_move_callbacks)
		{
			auto method_body = v.GetScriptSource();
			std::string method = std::string("") + method_body + "";
			this->mouse_move_callbacks.push_back(script_engine->CompileMethod(&v, method.c_str()));
		}
	}
	catch (std::string ex)
	{
		return false;
	}
	return true;
}

void TEventsEditorInstance::ViewportResize(TDirector* director, TVec2i old_size, TVec2i new_size)
{
	for (auto& v : viewport_resize_callback)
		script_engine->CallViewportResize(v, director, old_size, new_size);
}

void TEventsEditorInstance::WorldStart(IBaluWorldInstance* world_instance, IComposer* composer)
{
	for (auto& v : on_start_world_callback)
	{
		script_engine->CallWorldStart(v, world_instance, composer);
	}
}

bool TEventsEditorInstance::CheckScriptErrors(std::vector<std::string>& errors_list)
{
	try
	{
		for (auto& v : source->on_start_world_callback)
		{
			auto method_body = v.GetScriptSource();
			std::string method = std::string("func static StartWorld(IWorldInstance world_instance, IComposer composer)\n{\n") + method_body + "\n}\n";
			script_engine->CompileMethod(&v, method.c_str());
		}
		for (auto& v : source->viewport_resize_callback)
		{
			auto method_body = v.GetScriptSource();
			std::string method = std::string("func static ViewportResize(IDirector director, vec2i old_size, vec2i new_size)\n{\n") + method_body + "\n}\n";
			script_engine->CompileMethod(&v, method.c_str());
		}

		for (auto& v : source->mouse_up_callbacks)
		{
			auto method_body = v.GetScriptSource();
			std::string method = std::string("") + method_body + "";
			script_engine->CompileMethod(&v, method.c_str());
		}
		for (auto& v : source->mouse_down_callbacks)
		{
			auto method_body = v.GetScriptSource();
			std::string method = std::string("") + method_body + "";
			script_engine->CompileMethod(&v, method.c_str());
		}
		for (auto& v : source->mouse_move_callbacks)
		{
			auto method_body = v.GetScriptSource();
			std::string method = std::string("") + method_body + "";
			script_engine->CompileMethod(&v, method.c_str());
		}
		for (auto& v : source->before_physics_callbacks)
		{
			auto method_body = std::get<0>(v).GetScriptSource();
			std::string method = std::string("func static BeforePhys(IInstance object)\n{\n") + method_body + "\n}\n";
			before_physics_callbacks.push_back(std::make_tuple(script_engine->CompileMethod(&std::get<0>(v), method.c_str()), std::get<1>(v)));
		}
		for (auto& s : source->GetOnKeyDown())
		{
			for (auto& v : s.second)
			{
				auto method_body = std::get<0>(v).GetScriptSource();
				std::string method = std::string("func static KeyDown(IInstance object)\n{\n") + method_body + "\n}\n";
				on_key_down_callbacks[s.first].push_back(std::make_tuple(script_engine->CompileMethod(&std::get<0>(v), method.c_str()), std::get<1>(v)));
			}
		}
		for (auto& s : source->GetOnKeyUp())
		{
			for (auto& v : s.second)
			{
				auto method_body = std::get<0>(v).GetScriptSource();
				std::string method = std::string("func static KeyUp(IInstance object)\n{\n") + method_body + "\n}\n";
				on_key_up_callbacks[s.first].push_back(std::make_tuple(script_engine->CompileMethod(&std::get<0>(v), method.c_str()), std::get<1>(v)));
			}
		}
		for (auto& v : source->GetOnCollide())
		{
			auto method_body = v.script.GetScriptSource();
			std::string method = std::string("func static Collide(IInstance object, IClassInstanceSpriteInstance sprite, IInstance obstancle)\n{\n") + method_body + "\n}\n";
			on_collide_callbacks.push_back(TSpriteWithClassCollideInstance(v.sprite, v.with_class, script_engine->CompileMethod(&v.script, method.c_str())));
		}
	}
	catch (std::string ex)
	{
		errors_list = script_engine->GetErrors();
		return false;
	}
	return true;
}

//void TEventsEditorInstance::DoKeyDown(TKey key, TBaluTransformedClassInstance* instance)
//{
	//for (auto& v : on_key_down_callbacks)
	//{
	//	if (v.first == key)
	//	{
	//		script_engine->CallInstanceEvent(std::get<1>(v), instance);
	//	}
	//}
//}
//
//void TBaluClassCompiledScripts::DoKeyUp(TKey key, TBaluTransformedClassInstance* instance)
//{
//	for (auto& v : on_key_up_callbacks)
//	{
//		if (v.first == key)
//		{
//			world_instance->GetScriptEngine()->CallInstanceEvent(v.second, instance);
//		}
//	}
//}
//
//void TBaluClassCompiledScripts::DoBeforePhysicsStep(TBaluTransformedClassInstance* instance)
//{
//	for (auto& i : before_physics_callbacks)
//	{
//		world_instance->GetScriptEngine()->CallInstanceEvent(i, instance);
//	}
//}
//
//void TBaluClassCompiledScripts::DoCollide(TBaluTransformedClassInstance* source_object, TBaluTransformedSpriteInstance* obj_a, TBaluTransformedClassInstance* obstancle)
//{
//	for (auto& i : on_collide_callbacks)
//	{
//		if (i.sprite == obj_a->GetSource()->GetSprite() && i.with_class == obstancle->GetClass()->GetSource())
//			world_instance->GetScriptEngine()->CallCollide(i.script, source_object, obj_a, obstancle);
//	}
//}
//
//TBaluClassCompiledScripts::TBaluClassCompiledScripts(TBaluWorldInstance* world_instance, TBaluClass* source)
//{
//	this->world_instance = world_instance;
//	this->source = source;
//}
//
//void TBaluClassCompiledScripts::CheckScriptErrors(TBaluClass* source, TBaluScriptInstance* script_engine, std::vector<std::string>& errors_list)
//{
//	for (auto& v : source->GetOnBeforePhysicsStep())
//	{
//		auto method_body = v.GetScriptSource();
//		std::string method = std::string("func static BeforePhys(IInstance object)\n{\n") + method_body + "\n}\n";
//		script_engine->CompileMethod(&v, method.c_str());
//	}
//	for (auto& s : source->GetOnKeyDown())
//	{
//		for (auto& v : s.second)
//		{
//			auto method_body = v.GetScriptSource();
//			std::string method = std::string("func static KeyDown(IInstance object)\n{\n") + method_body + "\n}\n";
//			script_engine->CompileMethod(&v, method.c_str());
//		}
//	}
//	for (auto& s : source->GetOnKeyUp())
//	{
//		for (auto& v : s.second)
//		{
//			auto method_body = v.GetScriptSource();
//			std::string method = std::string("func static KeyUp(IInstance object)\n{\n") + method_body + "\n}\n";
//			script_engine->CompileMethod(&v, method.c_str());
//		}
//	}
//	for (auto& v : source->GetOnCollide())
//	{
//		auto method_body = v.script.GetScriptSource();
//		std::string method = std::string("func static Collide(IPhysShapeInstance source, IInstance obstancle)\n{\n") + method_body + "\n}\n";
//		script_engine->CompileMethod(&v.script, method.c_str());
//	}
//}

TEventsEditorInstance::TEventsEditorInstance(TEventsEditor* source, std::string assets_dir)
{
	this->source = source;

	this->script_engine.reset(new TBaluScriptInstance(assets_dir));
}
TEventsEditorInstance::~TEventsEditorInstance()
{

}