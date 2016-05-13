
#include "abstractEditor.h"

#include <WorldObjects/Scene/SceneEditor/sceneEditor.h>
#include <WorldObjects/Class/ClassEditor/classEditor.h>
#include <WorldObjects/Sprite/SpriteEditor/spriteEditor.h>
#include <WorldObjects/Material/MaterialEditor/materialEditor.h>

#include <easylogging++.h>

#include <ctime>

#include <pugixml.hpp>

#if defined(WIN32)||defined(_WIN32)
#else
void ctime_s(char* dt,int buf_size, time_t* now)
{
	char* temp = ctime(now);
	strcpy(temp, dt);
}
void localtime_s(tm* timeinfo, time_t* time)
{
	tm* temp = localtime(time);
	*timeinfo = *temp;
}
#endif

namespace EngineInterface
{
	void DestroyEditor(EngineInterface::IAbstractEditor* editor)
	{
		delete editor;
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
