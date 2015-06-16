
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
	//std::vector<TStaticValue>* GetStaticObjects();
	//void CreateMethod(EngineInterface::TCallbackInstance* script_data, const char* code);

	void CallMethod(EngineInterface::TScript &viewport_resize_callback, EngineInterface::IDirector* director, TVec2i old_size, TVec2i new_size);
	void CallMethod(EngineInterface::TScript &start_world_callback, EngineInterface::IBaluWorldInstance* world_instance, EngineInterface::IComposer* composer);
	void CallMethod(EngineInterface::TScript &callback, EngineInterface::IBaluInstance* obj);
	void CallMethod(EngineInterface::TScript &callback, EngineInterface::TMouseEventArgs* e);
	void CallMethod(EngineInterface::TScript &callback, NVGcontext* context, EngineInterface::TCustomDrawCommand* command);
	void CallMethod(EngineInterface::TScript &callback, EngineInterface::IBaluPhysShapeInstance* obj_a, EngineInterface::IBaluInstance* obj_b);

	//std::string GetEventSignature(EngineInterface::TEventType event_type);

	std::string AddName(std::string format, std::string name)
	{
		size_t size = format.size() + name.size();
		std::unique_ptr<char> buf(new char[size]);
		sprintf_s(buf.get(), size*sizeof(char), format.c_str());
		return buf.get();
	}
};