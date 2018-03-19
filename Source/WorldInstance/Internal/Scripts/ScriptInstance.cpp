#include "IScriptInstance.h"

#include "ScriptClassesRegistry.h"

#include <Windows.h>

#include <fstream>
#include <streambuf>

#include <vector>

#include "../Include/baluScript.h"

#include "../submodules/BaluScript/Source/TreeRunner/TreeRunner.h"

#include "../../../Common/IDirector.h"

using namespace BaluEngine;
using namespace BaluEngine::WorldInstance;

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
	std::unique_ptr<TSyntaxAnalyzer> syntax;
	std::vector<TStaticValue> static_objects;
	std::vector<std::string> errors;
	IWorld* world;
};

TScriptInstance::TScriptInstance(IWorld* world, WorldDef::IEventsEditor* source)
{
	p.reset(new TPrivate());
	p->source = source;
	p->world = world;
}

TScriptInstance::~TScriptInstance()
{
	TreeRunner::DeinitializeStatic(p->static_objects);
}

void TScriptInstance::MouseDown(WorldDef::TMouseEventArgs e)
{
	{
		auto type = WorldDef::GlobalCallbackType::MouseDown;
		for (int i = 0; i < p->source->GlobalGetCount(type); i++)
		{
			auto method = p->syntax->GetMethod((std::string("func static Script.GlobalCallback.") +
				GetMethodSignature(WorldDef::GlobalCallbackSignature[(int)type], i, true)).c_str());
			ns_Script::ns_GlobalCallback::callScriptFromC_MouseDown_(&p->static_objects, method, *p->syntax.get(), p->world, e);
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
		ns_Script::ns_GlobalCallback::callScriptFromC_MouseMove_(&p->static_objects, method, *p->syntax.get(), p->world, e);
	}
}
void TScriptInstance::MouseUp(WorldDef::TMouseEventArgs e)
{
	auto type = WorldDef::GlobalCallbackType::MouseUp;
	for (int i = 0; i < p->source->GlobalGetCount(type); i++)
	{
		auto method = p->syntax->GetMethod((std::string("func static Script.GlobalCallback.") +
			GetMethodSignature(WorldDef::GlobalCallbackSignature[(int)type], i, true)).c_str());
		ns_Script::ns_GlobalCallback::callScriptFromC_MouseUp_(&p->static_objects, method, *p->syntax.get(), p->world, e );
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
			ns_Script::ns_GlobalCallback::callScriptFromC_BeforePhysics_(&p->static_objects, method, *p->syntax.get());
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
				auto class_instance = dynamic_cast<ITransformedClassInstance*>(instance);
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
							ns_Script::ns_ClassCallback::callScriptFromC_BeforePhysics_(&p->static_objects, method, *p->syntax.get(), class_instance);
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
			ns_Script::ns_GlobalCallback::callScriptFromC_KeyDown_(&p->static_objects, method, *p->syntax.get(), key);
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
				ns_Script::ns_GlobalKeyCallback::callScriptFromC_KeyDown_(&p->static_objects, method, *p->syntax.get());
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
				auto class_instance = dynamic_cast<ITransformedClassInstance*>(instance);
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
							ns_Script::ns_ClassKeyCallback::callScriptFromC_KeyDown_(&p->static_objects, method, *p->syntax.get(), class_instance);
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
			ns_Script::ns_GlobalCallback::callScriptFromC_KeyUp_(&p->static_objects, method, *p->syntax.get(), key);
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
				ns_Script::ns_GlobalKeyCallback::callScriptFromC_KeyUp_(&p->static_objects, method, *p->syntax.get());
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
				auto class_instance = dynamic_cast<ITransformedClassInstance*>(instance);
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
							ns_Script::ns_ClassKeyCallback::callScriptFromC_KeyUp_(&p->static_objects, method, *p->syntax.get(), class_instance);
						}
					}
				}
			}
		}
	}
}

void TScriptInstance::OnCreate(ITransformedClassInstance* object)
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
			ns_Script::ns_ClassCallback::callScriptFromC_Created_(&p->static_objects, method, *p->syntax.get(), object);
		}
	}

}

void TScriptInstance::ViewportResize(IDirector* director, BaluLib::TVec2i old_size, BaluLib::TVec2i new_size)
{
	auto type = WorldDef::GlobalCallbackType::ViewportResize;
	for (int i = 0; i < p->source->GlobalGetCount(type); i++)
	{
		auto method = p->syntax->GetMethod((std::string("func static Script.GlobalCallback.") +
			GetMethodSignature(WorldDef::GlobalCallbackSignature[(int)type], i, true)).c_str());
		ns_Script::ns_GlobalCallback::callScriptFromC_ViewportResize_(&p->static_objects, method, *p->syntax.get(), director, old_size, new_size);
	}
}

void TScriptInstance::WorldStart(IWorld* world_instance, IComposer* composer)
{
	auto type = WorldDef::GlobalCallbackType::WorldStart;
	for (int i = 0; i < p->source->GlobalGetCount(type); i++)
	{
		auto method = p->syntax->GetMethod((std::string("func static Script.GlobalCallback.") +
			GetMethodSignature(WorldDef::GlobalCallbackSignature[(int)type], i, true)).c_str());
		ns_Script::ns_GlobalCallback::callScriptFromC_WorldStart_(&p->static_objects, method, *p->syntax.get(), world_instance, composer);
	}
}

void TScriptInstance::Collide(ITransformedClassInstance* object,
	ITransformedSpriteInstance* obj_a, ITransformedClassInstance* obj_b)
{
	int index = -1;
	for (int i = 0; i < p->source->OnCollideGetCount(); i++)
	{
		auto& t = p->source->OnCollideGet(i);
		if (t.source_class == object->GetClass()->GetSource()->GetName() &&
			t.with_class == obj_b->GetClass()->GetSource()->GetName() &&
			object->GetClass()->ContainsSprite(obj_a)==t.source_sprite_id)
		{
			index = i;
			break;
		}
	}
	if (index != -1)
	{
		auto method = p->syntax->GetMethod((std::string("func static Script.OnCollideCallback.") +
			GetMethodSignature(WorldDef::CollideCallbackSignature[0], 0, true)).c_str());

		ns_Script::ns_OnCollideCallback::callScriptFromC_Collide(&p->static_objects, method, *p->syntax.get(),
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
				source += PrintMethod(k, WorldDef::CollideCallbackSignature[0],	callback.script);
			}

			source += "}\n";
		}
		
		p->syntax.reset(new TSyntaxAnalyzer());
		p->syntax->Compile(source.c_str(), external_classes, external_bindings);

		TreeRunner::InitializeStaticClassFields(p->syntax->GetStaticFields(), p->static_objects);
		TreeRunner::InitializeStaticVariables(p->syntax->GetStaticVariables(), p->static_objects);
	}
	catch (std::string s)
	{
		printf(s.c_str());
	}

	printf("All done");
}