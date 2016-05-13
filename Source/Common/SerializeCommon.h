#pragma once

#include <pugixml.hpp>

using namespace pugi;

#include <baluLib.h>

#include <Common/ICommon.h>

using namespace EngineInterface;
using namespace BaluLib;

void SaveColor(pugi::xml_node& parent, TVec4 color);
TVec4 LoadColor(const pugi::xml_node& node);

void SaveCoord(pugi::xml_node& parent_node, std::string name, TVec2 coord);
TVec2 LoadCoord(const pugi::xml_node& node);

void SaveTransform(pugi::xml_node& parent_node, std::string name, TBaluTransform transform);
TBaluTransform LoadTransform(const pugi::xml_node& node);

void SaveTransformWithScale(pugi::xml_node& parent_node, std::string name, TBaluTransformWithScale transform);
TBaluTransformWithScale LoadTransformWithScale(const pugi::xml_node& node);
