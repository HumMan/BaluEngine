#pragma once

#include "baluEditorDefs.h"
#include "baluEngineApi.h"

class BALUENGINEDLL_API TBaluEditorDefsSerializer
{
public:
	void Save(TBaluWorldDef& use_world, pugi::xml_node& parent_node, const int version);
//	void Load(const pugi::xml_node& node, const int version);
};