#include "IScriptInstance.h"

#include "ScriptClassesRegistry.h"

#include <fstream>
#include <streambuf>

#include <vector>

#include "../Include/baluScript.h"

#include "../submodules/BaluScript/Source/TreeRunner/TreeRunner.h"

#include "../../../Common/IDirector.h"

using namespace BaluEngine;
using namespace BaluEngine::WorldInstance;
using namespace BaluEngine::WorldInstance::Internal;

std::string Convert_TString_to_stdstring(const TString& value)
{
	return value.AsStdString();
}

TString Convert_stdstring_to_TString(const std::string& value)
{
	TString result;
	result.Init(value);
	return result;
}

#include "../../../BindingGenerator/external_bindings.h"

std::string GetMethodSignature(std::string value, int index, bool trim_start = false)
{
	char buf[200];
	sprintf(buf, value.c_str(), std::to_string(index).c_str());
	const auto start = "func static ";
	if (trim_start)
		return std::string(buf).substr(strlen(start));
	else
		return buf;
}

std::string PrintMethod(int index, std::string value, std::string code)
{
	auto result = GetMethodSignature(value, index) + "\n{\n";
	result += code;
	result += "\n}\n";
	return result;
}

using namespace BaluEngine;
using namespace BaluEngine::WorldInstance;
using namespace BaluEngine::WorldInstance::Internal;

class TScriptInstance::TPrivate
{
public:
	WorldDef::IEventsEditor* source;
	ISyntaxAnalyzer* syntax;
	std::vector<std::string> errors;
	std::shared_ptr < IWorld> world;

	TGlobalRunContext global_context;

	std::vector<IMouseEventListener*> OnMouseEventListeners;
};

TScriptInstance::TScriptInstance(std::shared_ptr < IWorld> world, WorldDef::IEventsEditor* source)
{
	p.reset(new TPrivate());
	p->source = source;
	p->world = world;
}

TScriptInstance::~TScriptInstance()
{
	TreeRunner::DeinitializeStatic(p->global_context);
	ISyntaxAnalyzer::Destroy(p->syntax);
}

void TScriptInstance::AddMouseEventListener(IMouseEventListener* listener)
{
	auto it = std::find(p->OnMouseEventListeners.begin(), p->OnMouseEventListeners.end(), listener);
	if (it != p->OnMouseEventListeners.end())
		assert(false);
	p->OnMouseEventListeners.push_back(listener);
}

void TScriptInstance::RemoveMouseEventListener(IMouseEventListener* listener)
{
	auto it = std::find(p->OnMouseEventListeners.begin(), p->OnMouseEventListeners.end(), listener);
	if (it == p->OnMouseEventListeners.end())
		assert(false);
	p->OnMouseEventListeners.erase(it);
}

void TScriptInstance::MouseDown(WorldDef::TMouseEventArgs e)
{
	{
		auto type = WorldDef::GlobalCallbackType::MouseDown;
		for (int i = 0; i < p->source->GlobalGetCount(type); i++)
		{
			auto method = p->syntax->GetMethod((std::string("func static Script.GlobalCallback.") +
				GetMethodSignature(WorldDef::GlobalCallbackSignature[(int)type], i, true)).c_str());
			ns_Script::ns_GlobalCallback::callScriptFromC_MouseDown_(p->global_context, method, p->syntax, p->world, e);
		}
	}
}
void TScriptInstance::MouseMove(WorldDef::TMouseEventArgs e)
{
	auto type = WorldDef::GlobalCallbackType::MouseMove;
	for (int i = 0; i < p->source->GlobalGetCount(type); i++)
	{
		auto method = p->syntax->GetMethod((std::string("func static Script.GlobalCallback.") +
			GetMethodSignature(WorldDef::GlobalCallbackSignature[(int)type], i, true)).c_str());
		ns_Script::ns_GlobalCallback::callScriptFromC_MouseMove_(p->global_context, method, p->syntax, p->world, e);
	}
}
void TScriptInstance::MouseUp(WorldDef::TMouseEventArgs e)
{
	auto type = WorldDef::GlobalCallbackType::MouseUp;
	for (int i = 0; i < p->source->GlobalGetCount(type); i++)
	{
		auto method = p->syntax->GetMethod((std::string("func static Script.GlobalCallback.") +
			GetMethodSignature(WorldDef::GlobalCallbackSignature[(int)type], i, true)).c_str());
		ns_Script::ns_GlobalCallback::callScriptFromC_MouseUp_(p->global_context, method, p->syntax, p->world, e);
	}
}
void TScriptInstance::MouseVerticalWheel(int amount)
{

}

void TScriptInstance::PrePhysStep()
{
	{
		auto type = WorldDef::GlobalCallbackType::BeforePhysics;
		for (int i = 0; i < p->source->GlobalGetCount(type); i++)
		{
			auto method = p->syntax->GetMethod((std::string("func static Script.GlobalCallback.") +
				GetMethodSignature(WorldDef::GlobalCallbackSignature[(int)type], i, true)).c_str());
			ns_Script::ns_GlobalCallback::callScriptFromC_BeforePhysics_(p->global_context, method, p->syntax);
		}
	}
	{
		for (int scene_index = 0; scene_index < p->world->GetSceneCount(); scene_index++)
		{
			auto scene = p->world->GetScene(scene_index);
			auto count = scene->GetInstancesCount();
			for (size_t i = 0; i < count; i++)
			{
				auto instance = scene->GetInstance(i);
				auto class_instance = std::dynamic_pointer_cast<ITransformedClassInstance>(instance);
				if (class_instance != nullptr)
				{
					auto type = WorldDef::ClassCallbackType::BeforePhysics;
					auto class_def = class_instance->GetClass()->GetSource();
					for (int k = 0; k < p->source->ClassGetCount(type); k++)
					{
						auto t = p->source->ClassGet(type, k);
						if (std::get<0>(t) == class_def->GetName())
						{
							auto method = p->syntax->GetMethod((std::string("func static Script.ClassCallback.") +
								GetMethodSignature(WorldDef::ClassCallbackSignature[(int)type], k, true)).c_str());
							ns_Script::ns_ClassCallback::callScriptFromC_BeforePhysics_(p->global_context, method, p->syntax, class_instance);
						}
					}
				}
			}
		}
	}
}

void TScriptInstance::KeyDown(WorldDef::TKey key)
{
	{
		auto type = WorldDef::GlobalCallbackType::KeyDown;
		for (int i = 0; i < p->source->GlobalGetCount(type); i++)
		{
			auto method = p->syntax->GetMethod((std::string("func static Script.GlobalCallback.") +
				GetMethodSignature(WorldDef::GlobalCallbackSignature[(int)type], i, true)).c_str());
			ns_Script::ns_GlobalCallback::callScriptFromC_KeyDown_(p->global_context, method, p->syntax, key);
		}
	}
	{
		auto type = WorldDef::GlobalKeyCallbackType::KeyDown;
		for (int i = 0; i < p->source->GlobalKeyGetCount(type); i++)
		{
			auto t = p->source->GlobalKeyGet(type, i);
			if (std::get<0>(t) == key)
			{
				auto method = p->syntax->GetMethod((std::string("func static Script.GlobalKeyCallback.") +
					GetMethodSignature(WorldDef::GlobalKeyCallbackSignature[(int)type], i, true)).c_str());
				ns_Script::ns_GlobalKeyCallback::callScriptFromC_KeyDown_(p->global_context, method, p->syntax);
			}
		}
	}
	{
		for (int scene_index = 0; scene_index < p->world->GetSceneCount(); scene_index++)
		{
			auto scene = p->world->GetScene(scene_index);
			auto count = scene->GetInstancesCount();
			for (size_t i = 0; i < count; i++)
			{
				auto instance = scene->GetInstance(i);
				auto class_instance = std::dynamic_pointer_cast<ITransformedClassInstance>(instance);
				if (class_instance != nullptr)
				{
					auto type = WorldDef::ClassKeyCallbackType::KeyDown;
					auto class_def = class_instance->GetClass()->GetSource();
					for (int k = 0; k < p->source->ClassKeyGetCount(type); k++)
					{
						auto t = p->source->ClassKeyGet(type, k);
						if (std::get<0>(t) == key && std::get<2>(t) == class_def->GetName())
						{
							auto method = p->syntax->GetMethod((std::string("func static Script.ClassKeyCallback.") +
								GetMethodSignature(WorldDef::ClassKeyCallbackSignature[(int)type], k, true)).c_str());
							ns_Script::ns_ClassKeyCallback::callScriptFromC_KeyDown_(p->global_context, method, p->syntax, class_instance);
						}
					}
				}
			}
		}
	}
}

void TScriptInstance::KeyUp(WorldDef::TKey key)
{
	{
		auto type = WorldDef::GlobalCallbackType::KeyUp;
		for (int i = 0; i < p->source->GlobalGetCount(type); i++)
		{
			auto method = p->syntax->GetMethod((std::string("func static Script.GlobalCallback.") +
				GetMethodSignature(WorldDef::GlobalCallbackSignature[(int)type], i, true)).c_str());
			ns_Script::ns_GlobalCallback::callScriptFromC_KeyUp_(p->global_context, method, p->syntax, key);
		}
	}
	{
		auto type = WorldDef::GlobalKeyCallbackType::KeyUp;
		for (int i = 0; i < p->source->GlobalKeyGetCount(type); i++)
		{
			auto t = p->source->GlobalKeyGet(type, i);
			if (std::get<0>(t) == key)
			{
				auto method = p->syntax->GetMethod((std::string("func static Script.GlobalKeyCallback.") +
					GetMethodSignature(WorldDef::GlobalKeyCallbackSignature[(int)type], i, true)).c_str());
				ns_Script::ns_GlobalKeyCallback::callScriptFromC_KeyUp_(p->global_context, method, p->syntax);
			}
		}
	}
	{
		for (int scene_index = 0; scene_index < p->world->GetSceneCount(); scene_index++)
		{
			auto scene = p->world->GetScene(scene_index);
			auto count = scene->GetInstancesCount();
			for (size_t i = 0; i < count; i++)
			{
				auto instance = scene->GetInstance(i);
				auto class_instance = std::dynamic_pointer_cast<ITransformedClassInstance>(instance);
				if (class_instance != nullptr)
				{
					auto type = WorldDef::ClassKeyCallbackType::KeyUp;
					auto class_def = class_instance->GetClass()->GetSource();
					for (int k = 0; k < p->source->ClassKeyGetCount(type); k++)
					{
						auto t = p->source->ClassKeyGet(type, k);
						if (std::get<0>(t) == key && std::get<2>(t) == class_def->GetName())
						{
							auto method = p->syntax->GetMethod((std::string("func static Script.ClassKeyCallback.") +
								GetMethodSignature(WorldDef::ClassKeyCallbackSignature[(int)type], k, true)).c_str());
							ns_Script::ns_ClassKeyCallback::callScriptFromC_KeyUp_(p->global_context, method, p->syntax, class_instance);
						}
					}
				}
			}
		}
	}
}

void TScriptInstance::OnCreate(std::shared_ptr<ITransformedClassInstance> object)
{
	auto type = WorldDef::ClassCallbackType::Created;
	for (int i = 0; i < p->source->ClassGetCount(type); i++)
	{
		auto class_def = object->GetClass()->GetSource();
		auto t = p->source->ClassGet(type, i);
		if (std::get<0>(t) == class_def->GetName())
		{
			auto method = p->syntax->GetMethod((std::string("func static Script.ClassCallback.") +
				GetMethodSignature(WorldDef::ClassCallbackSignature[(int)type], i, true)).c_str());
			ns_Script::ns_ClassCallback::callScriptFromC_Created_(p->global_context, method, p->syntax, object);
		}
	}

}

void TScriptInstance::ViewportResize(std::shared_ptr<IDirector> director, BaluLib::TVec2i old_size, BaluLib::TVec2i new_size)
{
	auto type = WorldDef::GlobalCallbackType::ViewportResize;
	for (int i = 0; i < p->source->GlobalGetCount(type); i++)
	{
		auto method = p->syntax->GetMethod((std::string("func static Script.GlobalCallback.") +
			GetMethodSignature(WorldDef::GlobalCallbackSignature[(int)type], i, true)).c_str());
		ns_Script::ns_GlobalCallback::callScriptFromC_ViewportResize_(p->global_context, method, p->syntax, director, old_size, new_size);
	}
}

void TScriptInstance::WorldStart(std::shared_ptr<IWorld> world_instance, std::shared_ptr<IComposer> composer)
{
	auto type = WorldDef::GlobalCallbackType::WorldStart;
	for (int i = 0; i < p->source->GlobalGetCount(type); i++)
	{
		auto method = p->syntax->GetMethod((std::string("func static Script.GlobalCallback.") +
			GetMethodSignature(WorldDef::GlobalCallbackSignature[(int)type], i, true)).c_str());
		ns_Script::ns_GlobalCallback::callScriptFromC_WorldStart_(p->global_context, method, p->syntax, world_instance, composer);
	}
}

void TScriptInstance::ProcessCollision(std::shared_ptr<ITransformedClassInstance> object,
	std::shared_ptr < ITransformedSpriteInstance> obj_a, std::shared_ptr < ITransformedClassInstance> obj_b)
{
	int index = -1;
	for (int i = 0; i < p->source->OnCollideGetCount(); i++)
	{
		auto& t = p->source->OnCollideGet(i);
		if (t.source_class == object->GetClass()->GetSource()->GetName() &&
			t.with_class == obj_b->GetClass()->GetSource()->GetName() &&
			object->GetClass()->ContainsSprite(obj_a) == t.source_sprite_id)
		{
			index = i;
			break;
		}
	}
	if (index != -1)
	{
		auto method = p->syntax->GetMethod((std::string("func static Script.OnCollideCallback.") +
			GetMethodSignature(WorldDef::CollideCallbackSignature[0], 0, true)).c_str());

		ns_Script::ns_OnCollideCallback::callScriptFromC_Collide(p->global_context, method, p->syntax,
			object, obj_a->GetPhysShape(), obj_b);
	}
}

void TScriptInstance::Compile()
{
	try
	{
		std::string source;

		for (auto& v : BaluEngine::WorldInstance::Internal::TScriptClassesRegistry::get_enum_registry())
		{
			source += v.source;
		}

		std::vector<std::string> result;

		std::vector<SemanticApi::TExternalClassDecl> external_classes;

		for (auto& v : BaluEngine::WorldInstance::Internal::TScriptClassesRegistry::get_external_class_registry())
		{
			SemanticApi::TExternalClassDecl t;
			t.size = LexerIntSizeOf(v.size);
			t.source = v.source;
			external_classes.push_back(t);
		}

		std::vector<SemanticApi::TExternalSMethod> external_bindings = ns_Script::Register();

		{
			source += "class GlobalCallback\n{\n";
			for (int i = 0; i < (int)WorldDef::GlobalCallbackType::Count; i++)
			{
				for (int k = 0; k < p->source->GlobalGetCount((WorldDef::GlobalCallbackType)i); k++)
					source += PrintMethod(k, WorldDef::GlobalCallbackSignature[i],
						p->source->GlobalGet((WorldDef::GlobalCallbackType)i, k));
			}
			source += "}\n";

			source += "class GlobalKeyCallback\n{\n";
			for (int i = 0; i < (int)WorldDef::GlobalKeyCallbackType::Count; i++)
			{
				for (int k = 0; k < p->source->GlobalKeyGetCount((WorldDef::GlobalKeyCallbackType)i); k++)
					source += PrintMethod(k, WorldDef::GlobalKeyCallbackSignature[i],
						std::get<1>(p->source->GlobalKeyGet((WorldDef::GlobalKeyCallbackType)i, k)));
			}
			source += "}\n";

			source += "class ClassCallback\n{\n";
			for (int i = 0; i < (int)WorldDef::ClassCallbackType::Count; i++)
			{
				for (int k = 0; k < p->source->ClassGetCount((WorldDef::ClassCallbackType)i); k++)
					source += PrintMethod(k, WorldDef::ClassCallbackSignature[i],
						std::get<1>(p->source->ClassGet((WorldDef::ClassCallbackType)i, k)));
			}
			source += "}\n";

			source += "class ClassKeyCallback\n{\n";
			for (int i = 0; i < (int)WorldDef::ClassKeyCallbackType::Count; i++)
			{
				for (int k = 0; k < p->source->ClassKeyGetCount((WorldDef::ClassKeyCallbackType)i); k++)
					source += PrintMethod(k, WorldDef::ClassKeyCallbackSignature[i],
						std::get<1>(p->source->ClassKeyGet((WorldDef::ClassKeyCallbackType)i, k)));
			}
			source += "}\n";

			source += "class OnCollideCallback\n{\n";

			for (int k = 0; k < p->source->OnCollideGetCount(); k++)
			{
				auto callback = p->source->OnCollideGet(k);
				source += PrintMethod(k, WorldDef::CollideCallbackSignature[0], callback.script);
			}

			source += "}\n";
		}

		p->syntax = ISyntaxAnalyzer::Create();
		p->syntax->Compile(source.c_str(), external_classes, external_bindings);

		TreeRunner::InitializeStaticClassFields(p->syntax->GetStaticFields(), p->global_context);
		TreeRunner::InitializeStaticVariables(p->syntax->GetStaticVariables(), p->global_context);
	}
	catch (std::string s)
	{
		printf(s.c_str());
	}

	printf("All done");
}