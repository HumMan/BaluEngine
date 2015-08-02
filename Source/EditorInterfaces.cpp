
#include "EditorInterfaces.h"

#include "EditorUtils\SceneEditor\sceneEditor.h"
#include "EditorUtils\ClassEditor\classEditor.h"
#include "EditorUtils\SpriteEditor\spriteEditor.h"
#include "EditorUtils\MaterialEditor\materialEditor.h"

#include <easylogging++.h>

#include <ctime>

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
}