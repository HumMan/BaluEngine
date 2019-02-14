#pragma once

#include "../../Interface.h"

#include "SpritePolygon.h"

#include "../Common/Common.h"

#include "PhysShape.h"

namespace BaluEngine
{
	namespace WorldDef
	{
		namespace Internal
		{
			class TSprite : public ISprite, public TWorldObject
			{
			private:
				TSpritePolygon sprite_polygon;
				std::unique_ptr<TPhysShape> phys_shape;
			protected:
				void InitAllProperties()
				{
				}
			public:

				TSprite(const char* name, IWorld* world);

				void SetPhysShape(IPhysShape* shape);

				TPhysShape* GetPhysShape();
				void SetPhysShapeFromGeometry();

				TSpritePolygon* GetPolygon();

				void Save(pugi::xml_node& parent_node, const int version)const;
				void Load(const pugi::xml_node& instance_node, const int version, IWorld* world);
			};

			class TTransformedSprite : public ITransformedSprite
			{
				TSprite* sprite;
				TTransformWithScale local;
			public:
				static TWorldObjectType GetWorldObjectType()
				{
					return TWorldObjectType::Sprite;
				}
				TSprite* GetSprite()
				{
					return sprite;
				}
				TTransformedSprite()
				{
					this->sprite = nullptr;
				}
				TTransformedSprite(TSprite* sprite)
				{
					this->sprite = sprite;
				}
				void SetTransform(TTransform transform)
				{
					this->local.transform = transform;
				}
				void SetScale(BaluLib::TVec2 scale)
				{
					this->local.scale = scale;
				}
				TTransformWithScale GetTransformWithScale()
				{
					return local;
				}
				TTransform GetTransform()
				{
					return local.transform;
				}
				BaluLib::TVec2 GetScale()
				{
					return local.scale;
				}
				bool PointCollide(BaluLib::TVec2 class_space_point)
				{
					BaluLib::TVec2 p = local.ToLocal(class_space_point);
					bool is_in_sprite = GetSprite()->GetPolygon()->PointCollide(p);
					return (is_in_sprite);
				}
				void Save(pugi::xml_node& parent_node, const int version)const;
				void Load(const pugi::xml_node& instance_node, const int version, IWorld* world);
			};
		}
	}
}
