#pragma once

#include "../../Interface.h"

namespace BaluEngine
{
	namespace WorldDef
	{
		namespace Internal
		{
			class TWorld;
			class TSpritePolygon;

			class TFrame: public ISerializable
			{
			public:
				BaluLib::TVec2 left_bottom;
				BaluLib::TVec2 right_top;
				TFrame(BaluLib::TVec2 left_bottom, BaluLib::TVec2 right_top);
				BaluLib::TVec2 GetLeftBottom()
				{
					return left_bottom;
				}
				BaluLib::TVec2 GetRightTop()
				{
					return right_top;
				}

				void Save(pugi::xml_node& parent_node, const int version)const;
				void Load(const pugi::xml_node& instance_node, const int version, IWorld* world);
			};

			typedef IAnimDesc*(*AnimDescClone)();
			class AnimDescFactory
			{
			public:
				static bool Register(const char* name, AnimDescClone clone);
				static IAnimDesc* Create(const char* name);
				static void UnregisterAll();
			};

			class TSpecificFrame : public IAnimDesc
			{
				BaluLib::TVec2 left_bottom;
				BaluLib::TVec2 right_top;
			public:
				TSpecificFrame()
				{
				}
				static IAnimDesc* Clone()
				{
					return new TSpecificFrame();
				}
				TSpecificFrame(BaluLib::TVec2 left_bottom, BaluLib::TVec2 right_top);
				IFrame* GetFrame(int index);

				void Save(pugi::xml_node& parent_node, const int version)const;
				void Load(const pugi::xml_node& instance_node, const int version, IWorld* world);
			};
			static bool TSpecificFrame_registered = AnimDescFactory::Register("SpecificFrame", TSpecificFrame::Clone);

			class TGridFrames : public IAnimDesc
			{
				BaluLib::TVec2 left_bottom;
				BaluLib::TVec2 width_height;
				int cell_count_x;
				int cell_count_y;
			public:
				TGridFrames()
				{
				}
				static IAnimDesc* Clone()
				{
					return new TGridFrames();
				}
				TGridFrames(BaluLib::TVec2 left_bottom, BaluLib::TVec2 width_height, int cell_count_x, int cell_count_y);
				IFrame* GetFrame(int index);

				void Save(pugi::xml_node& parent_node, const int version)const;
				void Load(const pugi::xml_node& instance_node, const int version, IWorld* world);
			};
			static bool TGridFrames_registered = AnimDescFactory::Register("GridFrames", TGridFrames::Clone);

			class TFramesRange
			{
				int start;
				int end;
			public:
				TFramesRange(int start, int end);
				std::vector<int> ToFramesArray();
			};

			class TAnimationFrames
			{
			public:
				TAnimationFrames()
				{
				}
				IAnimDesc* desc;
				std::vector<int> frames;
				TAnimationFrames(IAnimDesc* desc, std::vector<int> frames);
				TAnimationFrames(IAnimDesc* desc, int frame);

				void Save(pugi::xml_node& parent_node, const int version, const TSpritePolygon* sprite_polygon)const;
				void Load(const pugi::xml_node& instance_node, const int version, IWorld* world, TSpritePolygon* sprite_polygon);
			};

			class TAnimLine
			{
			public:
				std::string line_name;
				std::vector<TAnimationFrames> frames;

				void Save(pugi::xml_node& parent_node, const int version, const TSpritePolygon* sprite_polygon)const;
				void Load(const pugi::xml_node& instance_node, const int version, IWorld* world, TSpritePolygon* sprite_polygon);
			};

		}
	}
}