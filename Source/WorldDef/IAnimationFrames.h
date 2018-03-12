#pragma once

#include "../Interfaces/ExportMacro.h"

namespace BaluEngine
{
	namespace WorldDef
	{
		class TFrame//: public ISerializable
		{
		public:
			BaluLib::TVec2 left_bottom;
			BaluLib::TVec2 right_top;
			TFrame(BaluLib::TVec2 left_bottom, BaluLib::TVec2 right_top)
			{
				this->left_bottom = left_bottom;
				this->right_top = right_top;
			}
			BaluLib::TVec2 GetLeftBottom()
			{
				return left_bottom;
			}
			BaluLib::TVec2 GetRightTop()
			{
				return right_top;
			}

			//void Save(pugi::xml_node& parent_node, const int version)const;
			//void Load(const pugi::xml_node& instance_node, const int version, IWorld* world);
		};

		class IAnimDesc : public ISerializable
		{
		public:
			virtual TFrame GetFrame(int index) = 0;
			BALUENGINEDLL_API static IAnimDesc* Create_TGridFrames(BaluLib::TVec2 left_bottom, BaluLib::TVec2 width_height, int cell_count_x, int cell_count_y);
		};

		class IAnimationFrames
		{
		public:
			virtual IAnimDesc * GetDesc()const = 0;
			virtual std::vector<int> GetFrames()const = 0;

			virtual void Save(pugi::xml_node& parent_node, const int version, const ISpritePolygon* sprite_polygon)const=0;
			virtual void Load(const pugi::xml_node& instance_node, const int version, IWorld* world, ISpritePolygon* sprite_polygon)=0;
			virtual ~IAnimationFrames() {};
		};

		class TFramesRange
		{
		private:
			int start;
			int end;
		public:
			TFramesRange(int start, int end)
			{
				this->start = start;
				this->end = end;
			}

			std::vector<int> ToFramesArray()
			{
				if (end < start)
					throw std::invalid_argument("end должен быть больше start");
				std::vector<int> result;
				int length = end - start + 1;
				result.reserve(length);
				result.resize(length);
				for (int i = start; i <= end; i++)
				{
					result[i - start] = i;
				}
				return result;
			}
		};

		class IAnimationLine
		{
		public:
			virtual int GetFramesCount()const = 0;
			virtual IAnimationFrames* GetFrames(int index)const = 0;
		};
	}
}
