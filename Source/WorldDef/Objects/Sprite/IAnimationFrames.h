#pragma once

#include <baluLib.h>
using namespace BaluLib;
#include <vector>

#include <Interfaces/ExportMacro.h>

namespace pugi
{
	class xml_node;
}

namespace EngineInterface
{
	class TBaluWorld;
	class TBaluSpritePolygon;

	class BALUENGINEDLL_API TFrame
	{
	public:
		TVec2 left_bottom;
		TVec2 right_top;
		TFrame(TVec2 left_bottom, TVec2 right_top);
		TVec2 GetLeftBottom()
		{
			return left_bottom;
		}
		TVec2 GetRightTop()
		{
			return right_top;
		}

		void Save(pugi::xml_node& parent_node, const int version);
		void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world);
	};

	class TAnimDesc
	{
	public:
		virtual TFrame GetFrame(int index) = 0;

		virtual void Save(pugi::xml_node& parent_node, const int version)=0;
		virtual void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world)=0;
	};

	typedef TAnimDesc*(*AnimDescClone)();
	class BALUENGINEDLL_API AnimDescFactory
	{
	public:
		static bool Register(const char* name, AnimDescClone clone);
		static TAnimDesc* Create(const char* name);
		static void UnregisterAll();
	};

	class BALUENGINEDLL_API TSpecificFrame : public TAnimDesc
	{
		TVec2 left_bottom;
		TVec2 right_top;
	public:
		TSpecificFrame()
		{
		}
		static TAnimDesc* Clone()
		{
			return new TSpecificFrame();
		}
		TSpecificFrame(TVec2 left_bottom, TVec2 right_top);
		TFrame GetFrame(int index);

		void Save(pugi::xml_node& parent_node, const int version);
		void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world);
	};
	static bool TSpecificFrame_registered = AnimDescFactory::Register("SpecificFrame", TSpecificFrame::Clone);

	class BALUENGINEDLL_API TGridFrames : public TAnimDesc
	{
		TVec2 left_bottom;
		TVec2 width_height;
		int cell_count_x;
		int cell_count_y;
	public:
		TGridFrames()
		{
		}
		static TAnimDesc* Clone()
		{
			return new TGridFrames();
		}
		TGridFrames(TVec2 left_bottom, TVec2 width_height, int cell_count_x, int cell_count_y);
		TFrame GetFrame(int index);

		void Save(pugi::xml_node& parent_node, const int version);
		void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world);
	};
	static bool TGridFrames_registered = AnimDescFactory::Register("GridFrames", TGridFrames::Clone);

	class BALUENGINEDLL_API TFramesRange
	{
		int start;
		int end;
	public:
		TFramesRange(int start, int end);
		std::vector<int> ToFramesArray();
	};

	class BALUENGINEDLL_API TAnimationFrames
	{
	public:
		TAnimationFrames()
		{
		}
		TAnimDesc* desc;
		std::vector<int> frames;
		TAnimationFrames(TAnimDesc* desc, std::vector<int> frames);
		TAnimationFrames(TAnimDesc* desc, int frame);

		void Save(pugi::xml_node& parent_node, const int version, TBaluSpritePolygon* sprite_polygon);
		void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world, TBaluSpritePolygon* sprite_polygon);
	};

	class BALUENGINEDLL_API TAnimLine
	{
	public:
		std::string line_name;
		std::vector<TAnimationFrames> frames;

		void Save(pugi::xml_node& parent_node, const int version, TBaluSpritePolygon* sprite_polygon);
		void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world, TBaluSpritePolygon* sprite_polygon);
	};

}
