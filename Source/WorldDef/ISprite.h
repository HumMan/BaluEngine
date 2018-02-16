#pragma once

namespace BaluEngine
{
	namespace WorldDef
	{

		class ISprite : public virtual IWorldObject
		{
		public:
			static std::string GetDefaultName()
			{
				return "sprite";
			}
			virtual void SetPhysShape(IPhysShape* shape) = 0;
			virtual IPhysShape* GetPhysShape() = 0;
			virtual void SetPhysShapeFromGeometry() = 0;
			virtual ISpritePolygon* GetPolygon() = 0;
		};

		class ITransformedSprite
		{
		public:
			virtual ISprite* GetSprite() = 0;
			virtual void SetTransform(TTransform transform) = 0;
			virtual void SetScale(BaluLib::TVec2 scale) = 0;
			virtual TTransform GetTransform() = 0;
			virtual BaluLib::TVec2 GetScale() = 0;
		};
	}
}
