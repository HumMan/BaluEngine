#pragma once

#include "../../Interface.h"

namespace BaluEngine
{
	namespace WorldDef
	{
		namespace Internal
		{
			namespace SerializeCommon
			{
				void SaveColor(pugi::xml_node& parent, BaluLib::TVec3 color);
				BaluLib::TVec3 LoadColor(const pugi::xml_node& node);

				void SaveColorWithAlpha(pugi::xml_node& parent, BaluLib::TVec4 color);
				BaluLib::TVec4 LoadColorWithAlpha(const pugi::xml_node& node);

				void SaveCoord(pugi::xml_node& parent_node, std::string name, BaluLib::TVec2 coord);
				BaluLib::TVec2 LoadCoord(const pugi::xml_node& node);

				void SaveRotation(pugi::xml_node& parent_node, std::string name, TRot coord);
				TRot LoadRotation(const pugi::xml_node& node);

				void SaveTransform(pugi::xml_node& parent_node, std::string name, TTransform transform);
				TTransform LoadTransform(const pugi::xml_node& node);

				void SaveTransformWithScale(pugi::xml_node& parent_node, std::string name, TTransformWithScale transform);
				TTransformWithScale LoadTransformWithScale(const pugi::xml_node& node);
			}

			struct xml_string_writer : pugi::xml_writer
			{
				std::string result;

				virtual void write(const void* data, size_t size)
				{
					result.append(static_cast<const char*>(data), size);
				}
			};
		}
	}
}