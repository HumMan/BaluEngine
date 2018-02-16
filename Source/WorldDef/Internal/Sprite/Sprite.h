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

			class TBaluSprite :public ISprite, public TWorldObject, public TChangeListenerArray
			{
			private:
				std::string sprite_name;

				TSpritePolygon sprite_polygon;
				std::unique_ptr<TPhysShape> phys_shape;

				int layer;
				TProperties properties;


			public:
				TBaluSprite(const char* name, IWorld* world);

				IProperties* GetProperties();

				void SetPhysShape(IPhysShape* shape);

				TPhysShape* GetPhysShape();
				void SetPhysShapeFromGeometry();

				TSpritePolygon* GetPolygon();

				void Save(pugi::xml_node& parent_node, const int version)const;
				void Load(const pugi::xml_node& instance_node, const int version, IWorld* world);
			};

			class TTransformedSprite : public ITransformedSprite, public TChangeListenerArray
			{
				//TObjLocator<TBaluSprite> sprite;
				TBaluSprite* sprite;
				TTransformWithScale local;
			public:
				static TWorldObjectType GetWorldObjectType()
				{
					return TWorldObjectType::Sprite;
				}
				TBaluSprite* GetSprite()
				{
					//return sprite.Get();
					return sprite;
				}
				TTransformedSprite()
					//:sprite(world, sprite->GetName())
				{
					this->sprite = nullptr;
				}
				TTransformedSprite(TBaluSprite* sprite)
					//:sprite(world, sprite->GetName())
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
