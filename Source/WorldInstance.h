#pragma once

#include "World.h"
#include "SceneInstance.h"

#include "baluScript.h"

class TDirector;

class TBaluScriptInstance
{
private:
	std::unique_ptr<TSyntaxAnalyzer> syntax;
	std::vector<TStaticValue> static_objects;
	std::vector < std::unique_ptr<TSMethod>> smethods;
	std::vector<std::string> errors;

	TTime time;
public:

	bool HasErrors()
	{
		return errors.size() >= 0;
	}
	std::vector<std::string> GetErrors()
	{
		return errors;
	}
	TBaluScriptInstance();
	std::vector<TStaticValue>* GetStaticObjects()
	{
		return &static_objects;
	}
	void CreateMethod(TScriptData* script_data, const char* code);
	void CallMethod(CallbackWithData<ViewportResizeCallback> viewport_resize_callback, EngineInterface::IDirector* director, TVec2i old_size, TVec2i new_size)
	{
		std::vector<TStackValue> params;
		params.push_back(TStackValue(false, syntax->sem_base_class->GetClass(syntax->lexer.GetIdFromName("IDirector"))));
		params.push_back(TStackValue(false, syntax->sem_base_class->GetClass(syntax->lexer.GetIdFromName("vec2"))));
		params.push_back(TStackValue(false, syntax->sem_base_class->GetClass(syntax->lexer.GetIdFromName("vec2"))));
		*(EngineInterface::IDirector**)params[0].get() = director;
		*(TVec2i*)params[1].get() = old_size;
		*(TVec2i*)params[2].get() = new_size;
		TStackValue result, object;
		viewport_resize_callback.GetCompiledScript()->Run(static_objects, params, result, object);
	}
	void CallMethod(CallbackWithData<RenderWorldCallback> render_world_callback, EngineInterface::IDirector* director, EngineInterface::IBaluWorldInstance* world, TRender* render)
	{

	}
};

class TBaluWorldInstance : public EngineInterface::IBaluWorldInstance
{
private:
	TBaluWorld* source;
	std::vector<std::unique_ptr<TBaluSceneInstance>> instances;
	TResources* resources;
	TBaluScriptInstance script_engine;
public:
	TBaluWorld* GetSource();

	TBaluWorldInstance(TBaluWorld* source, TResources* resources);

	TBaluSceneInstance* RunScene(TBaluScene* scene_source);
	void StopScene(TBaluSceneInstance*);

	EngineInterface::IBaluSceneInstance* RunScene(EngineInterface::IBaluScene* scene_source);
	int GetSceneInstancesCount()
	{
		return instances.size();
	}
	TBaluSceneInstance* GetSceneInstance(int index)
	{
		return instances[index].get();
	}
	void StopScene(EngineInterface::IBaluSceneInstance*);

	void OnPrePhysStep();
	void PhysStep(float step);

	void OnProcessCollisions();
	void OnStep(float step);

	void KeyDown(TKey key);
	void KeyUp(TKey key);

	void MouseDown(TMouseEventArgs e);
	void MouseMove(TMouseEventArgs e);
	void MouseUp(TMouseEventArgs e);
	void MouseVerticalWheel(int amount);

	void ViewportResize(TDirector* director, TVec2i old_size, TVec2i new_size);
	void Render(TDirector* director, TRender* render);

	void UpdateTransform();
	void DebugDraw();

	void CompileScripts();
};