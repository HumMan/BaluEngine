#pragma once

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
		};

		class IAnimationFrames
		{
		public:
			virtual IAnimDesc * GetDesc()const = 0;
			virtual std::vector<int> GetFrames()const = 0;

			virtual void Save(pugi::xml_node& parent_node, const int version, const ISpritePolygon* sprite_polygon)const=0;
			virtual void Load(const pugi::xml_node& instance_node, const int version, IWorld* world, ISpritePolygon* sprite_polygon)=0;
		};

		class IAnimationLine
		{
		public:
			virtual int GetFramesCount()const = 0;
			virtual IAnimationFrames* GetFrames(int index)const = 0;
		};
	}
}
