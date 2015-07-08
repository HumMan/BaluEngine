
#pragma once

#include <memory>
#include <vector>

#include "EngineInterfaces\ICallbacks.h"

#include "EngineInterfaces\IScriptInstance.h"

class TBaluScriptInstancePrivate;

namespace EngineInterface
{
	class IComposer;
	class IBaluInstance;
}

class TBaluScriptInstance : public EngineInterface::IBaluScriptInstance
{
private:
	std::unique_ptr<TBaluScriptInstancePrivate> p;
public:

	bool HasErrors();
	std::vector<std::string> GetErrors();
	TBaluScriptInstance(std::string assets_dir);
	~TBaluScriptInstance();
	EngineInterface::TScriptInstance CompileMethod(EngineInterface::TScript* script, const char* code);
	void CallViewportResize(EngineInterface::TScriptInstance &viewport_resize_callback, EngineInterface::IDirector* director, TVec2i old_size, TVec2i new_size);
	void CallWorldStart(EngineInterface::TScriptInstance &script_instance, EngineInterface::IBaluWorldInstance* world_instance, EngineInterface::IComposer* composer);
	//KeyUp KeyDown BeforePhysicsStep
	void CallInstanceEvent(EngineInterface::TScriptInstance& script_instance, EngineInterface::IBaluInstance* obj);
	void CallMouseEvent(EngineInterface::TScriptInstance &callback, EngineInterface::TMouseEventArgs* e);
	void CallCollide(EngineInterface::TScriptInstance &callback, EngineInterface::IBaluPhysShapeInstance* obj_a, EngineInterface::IBaluInstance* obj_b);

	//std::string GetEventSignature(EngineInterface::TEventType event_type);

	std::string AddName(std::string format, std::string name)
	{
		size_t size = format.size() + name.size();
		std::unique_ptr<char> buf(new char[size]);
		sprintf_s(buf.get(), size*sizeof(char), format.c_str());
		return buf.get();
	}
};