
#include "abstractEditor.h"

#include <WorldObjects\Scene\SceneEditor\sceneEditor.h>
#include <WorldObjects\Class\ClassEditor\classEditor.h>
#include <WorldObjects\Sprite\SpriteEditor\spriteEditor.h>
#include <WorldObjects\Material\MaterialEditor\materialEditor.h>

#include <easylogging++.h>

#include <ctime>

#include <pugixml.hpp>

namespace EngineInterface
{
	EngineInterface::IAbstractEditor* CreateSceneEditor(TDrawingHelperContext drawing_context, EngineInterface::IBaluWorld* world, EngineInterface::IBaluScene* edited_scene, EngineInterface::IBaluSceneInstance* editor_scene_instance)
	{
		auto result = new TSceneEditor();
		result->Initialize(drawing_context, world, edited_scene, editor_scene_instance);
		return result;
	}

	void DestroySceneEditor(EngineInterface::IAbstractEditor* editor)
	{
		auto ed = dynamic_cast<TSceneEditor*>(editor);
		ed->Deinitialize();
		delete ed;
	}

	EngineInterface::IAbstractEditor* CreateClassEditor(TDrawingHelperContext drawing_context, EngineInterface::IBaluWorld* world, EngineInterface::IBaluClass* edited_class, EngineInterface::IBaluSceneInstance* editor_scene_instance)
	{
		auto result = new TClassEditor();
		result->Initialize(drawing_context, world, edited_class, editor_scene_instance);
		return result;
	}

	void DestroyClassEditor(EngineInterface::IAbstractEditor* editor)
	{
		auto ed = dynamic_cast<TClassEditor*>(editor);
		ed->Deinitialize();
		delete ed;
	}

	EngineInterface::IAbstractEditor* CreateSpriteEditor(TDrawingHelperContext drawing_context, EngineInterface::IBaluWorld* world, EngineInterface::IBaluSprite* edited_sprite, EngineInterface::IBaluSceneInstance* editor_scene_instance)
	{
		auto result = new TSpriteEditor();
		result->Initialize(drawing_context, world, edited_sprite, editor_scene_instance);
		return result;
	}

	void DestroySpriteEditor(EngineInterface::IAbstractEditor* editor)
	{
		auto ed = dynamic_cast<TSpriteEditor*>(editor);
		ed->Deinitialize();
		delete ed;
	}

	EngineInterface::IAbstractEditor* CreateMaterialEditor(TDrawingHelperContext drawing_context, EngineInterface::IBaluWorld* world, EngineInterface::IBaluMaterial* edited_material, EngineInterface::IBaluSceneInstance* editor_scene_instance)
	{
		auto result = new TMaterialEditor();
		result->Initialize(drawing_context, world, edited_material, editor_scene_instance);
		return result;
	}

	void DestroyMaterialEditor(EngineInterface::IAbstractEditor* editor)
	{
		auto ed = dynamic_cast<TMaterialEditor*>(editor);
		ed->Deinitialize();
		delete ed;
	}
	void ConfigureLogging()
	{
		time_t now = time(0);

		struct tm timeinfo;
		localtime_s(&timeinfo, &now);

		char dt[200];
		ctime_s(dt, 200, &now);
		
		std::string s = std::string("logs/") + dt + ".log";
		std::replace(s.begin(), s.end(), ':', '-');
		std::replace(s.begin(), s.end(), '\n', ' ');

		el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Filename, s);
	}
	void WriteInfoToLog(char* message)
	{
		LOG(INFO) << message;
	}

	std::wstring as_wide(std::string utf_8_string)
	{
		return pugi::as_wide(utf_8_string);
	}
	std::string as_utf8(std::wstring wide_string)
	{
		return pugi::as_utf8(wide_string);
	}
}

void TSelectionChangeListeners::EmitOnSelectionChange(EngineInterface::IProperties* new_selection)
{
	for (auto& v : this->selection_listeners)
		v->OnSelectionChange(new_selection);
}

void TSelectionChangeListeners::AddSelectionChangeListener(ISelectionChangeListener* listener)
{
	assert(std::find(this->selection_listeners.begin(), this->selection_listeners.end(), listener) == this->selection_listeners.end());
	this->selection_listeners.push_back(listener);
}

void TSelectionChangeListeners::RemoveSelectionChangeListener(ISelectionChangeListener* listener)
{
	assert(std::find(this->selection_listeners.begin(), this->selection_listeners.end(), listener) != this->selection_listeners.end());
	this->selection_listeners.erase(std::find(this->selection_listeners.begin(), this->selection_listeners.end(), listener));
}
