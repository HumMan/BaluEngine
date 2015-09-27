
#ifndef BALU_ENGINE_DISABLE_PRAGMA_ONCE
#pragma once
#endif

#ifndef BALU_ENGINE_SCRIPT_CLASSES

#include "../../BaluLib/Source/Math/vec.h"
#include <vector>
#include <Interfaces\exportMacro.h>

namespace pugi
{
	class xml_node;
}

class TBaluWorld;
class TBaluSpritePolygon;
#endif

namespace EngineInterface
{

#ifndef BALU_ENGINE_SCRIPT_CLASSES
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
#endif

#ifdef BALU_ENGINE_SCRIPT_CLASSES
	BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, TFrame, "TFrame");
	MUnpackConstrA2(WrapInterface<TFrame>, Constr, WrapValue<TVec2>, WrapValue<TVec2>);
	MUnpackRA0(WrapValue<TVec2>, WrapInterface<TFrame>, GetLeftBottom);
	MUnpackRA0(WrapValue<TVec2>, WrapInterface<TFrame>, GetRightTop);
	BALU_ENGINE_SCRIPT_END_CLASS;
#endif

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	class TAnimDesc
	{
	public:
		virtual TFrame GetFrame(int index) = 0;

		virtual void Save(pugi::xml_node& parent_node, const int version)=0;
		virtual void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world)=0;
	};
#endif

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	typedef TAnimDesc*(*AnimDescClone)();
	class BALUENGINEDLL_API AnimDescFactory
	{
	public:
		static bool Register(const char* name, AnimDescClone clone);
		static TAnimDesc* Create(const char* name);
	};
#endif

#ifndef BALU_ENGINE_SCRIPT_CLASSES
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
#endif

#ifndef BALU_ENGINE_SCRIPT_CLASSES
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
#endif

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	class BALUENGINEDLL_API TFramesRange
	{
		int start;
		int end;
	public:
		TFramesRange(int start, int end);
		std::vector<int> ToFramesArray();
	};
#endif

#ifndef BALU_ENGINE_SCRIPT_CLASSES
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
#endif

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	class BALUENGINEDLL_API TAnimLine
	{
	public:
		std::string line_name;
		std::vector<TAnimationFrames> frames;

		void Save(pugi::xml_node& parent_node, const int version, TBaluSpritePolygon* sprite_polygon);
		void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world, TBaluSpritePolygon* sprite_polygon);
	};
#endif
}