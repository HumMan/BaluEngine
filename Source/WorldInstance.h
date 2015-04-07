#pragma once

#include "World.h"
#include "SceneInstance.h"
#include "Composer.h"

#include "baluScript.h"

#include "EngineInterfaces\IWorldInstance.h"

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
		params.push_back(TStackValue(false, syntax->sem_base_class->GetClass(syntax->lexer.GetIdFromName("vec2i"))));
		params.push_back(TStackValue(false, syntax->sem_base_class->GetClass(syntax->lexer.GetIdFromName("vec2i"))));
		*(EngineInterface::IDirector**)params[0].get() = director;
		*(TVec2i*)params[1].get() = old_size;
		*(TVec2i*)params[2].get() = new_size;
		TStackValue result, object;
		viewport_resize_callback.GetCompiledScript()->Run(static_objects, params, result, object);
	}
	//void CallMethod(CallbackWithData<RenderWorldCallback> render_world_callback, EngineInterface::IDirector* director, EngineInterface::IBaluWorldInstance* world, TRender* render)
	//{
	//	std::vector<TStackValue> params;
	//	params.push_back(TStackValue(false, syntax->sem_base_class->GetClass(syntax->lexer.GetIdFromName("IDirector"))));
	//	params.push_back(TStackValue(false, syntax->sem_base_class->GetClass(syntax->lexer.GetIdFromName("IWorldInstance"))));
	//	params.push_back(TStackValue(false, syntax->sem_base_class->GetClass(syntax->lexer.GetIdFromName("IRender"))));
	//	*(EngineInterface::IDirector**)params[0].get() = director;
	//	*(EngineInterface::IBaluWorldInstance**)params[1].get() = world;
	//	*(TRender**)params[2].get() = render;

	//	TStackValue result, object;
	//	render_world_callback.GetCompiledScript()->Run(static_objects, params, result, object);
	//}

	void CallMethod(CallbackWithData<OnStartWorldCallback> start_world_callback, EngineInterface::IBaluWorldInstance* world_instance, EngineInterface::IComposer* composer)
	{
		std::vector<TStackValue> params;
		params.push_back(TStackValue(false, syntax->sem_base_class->GetClass(syntax->lexer.GetIdFromName("IWorldInstance"))));
		params.push_back(TStackValue(false, syntax->sem_base_class->GetClass(syntax->lexer.GetIdFromName("IComposer"))));
		*(EngineInterface::IBaluWorldInstance**)params[0].get() = world_instance;
		*(EngineInterface::IComposer**)params[1].get() = composer;

		TStackValue result, object;
		start_world_callback.GetCompiledScript()->Run(static_objects, params, result, object);
	}
	void CallMethod(CallbackWithData<KeyUpDownCallback>callback, TBaluInstance* obj)
	{
		std::vector<TStackValue> params;
		params.push_back(TStackValue(false, syntax->sem_base_class->GetClass(syntax->lexer.GetIdFromName("IClassInstance"))));
		*(EngineInterface::IBaluInstance**)params[0].get() = obj;

		TStackValue result, object;
		callback.GetCompiledScript()->Run(static_objects, params, result, object);
	}
};

class TBaluWorldInstance : public EngineInterface::IBaluWorldInstance
{
private:
	TBaluWorld* source;
	std::vector<std::unique_ptr<TBaluSceneInstance>> instances;
	TResources* resources;
	TBaluScriptInstance script_engine;
	TComposer composer;
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
	//void Render(TDirector* director, TRender* render);

	void UpdateTransform();
	void DebugDraw();

	void CompileScripts();

	TComposer* GetComposer()
	{
		return &composer;
	}
};