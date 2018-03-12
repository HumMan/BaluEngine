#pragma once

namespace BaluEngine
{
	namespace WorldInstance
	{
		class ITransformedSpriteInstance
		{
		public:
			virtual WorldDef::ITransformedSprite* GetSource() = 0;
			virtual IPhysShapeInstance* GetPhysShape() = 0;
			virtual BaluLib::TVec2 GetScale() = 0;
			virtual BaluLib::TOBB2 GetOBB() = 0;
			virtual void SetScale(BaluLib::TVec2 scale) = 0;
			virtual void SetTransform(WorldDef::TTransform local) = 0;
			virtual WorldDef::TTransform GetTransform() = 0;
			virtual ISpritePolygonInstance* GetPolygon() = 0;
			//virtual IProperties* GetProperties() = 0;

			virtual ~ITransformedSpriteInstance() {}
		};
	}
}