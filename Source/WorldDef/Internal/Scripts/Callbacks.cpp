#include "Callbacks.h"

#include <pugixml.hpp>

using namespace BaluEngine::WorldDef;
using namespace BaluEngine::WorldDef::Internal;
using namespace pugi;

//TScript::TScript()
//{
//}
//
//TScript::TScript(std::string script_source)
//{
//	this->script_source = script_source;
//}
//
//std::string TScript::GetScriptSource()
//{
//	return script_source;
//}
//
//void TScript::SetScriptSource(const char* source)
//{
//	script_source = source;
//}
//
//void TScript::SaveToXML(pugi::xml_node& parent_node, const int version)
//{
//	xml_node new_node = parent_node.append_child("Script");
//
//	xml_node ndAvatarData = new_node.append_child(pugi::node_pcdata);
//	ndAvatarData.set_value(script_source.c_str());
//}
//
//void TScript::LoadFromXML(const pugi::xml_node& document_node, const int version)
//{
//	script_source = document_node.child_value();
//}
