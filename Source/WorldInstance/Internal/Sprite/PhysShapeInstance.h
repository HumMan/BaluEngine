#pragma once

#include "../../Interface.h"

#include "PhysShapeInstance.h"

class b2Body;
class b2Fixture;

namespace BaluEngine
{
	namespace WorldInstance
	{
		namespace Internal
		{
			class TPhysShapeInstance : public IPhysShapeInstance//, public IChangeListener
			{
			protected:
				WorldDef::IPhysShape * source;
				b2Fixture* fixture;
				b2Body* body;
				TPhysShapeUserData user_data;
			public:
				TPhysShapeInstance(WorldDef::IPhysShape* source, TPhysShapeUserData user_data);
				~TPhysShapeInstance();
				void BuildFixture(b2Body* body, WorldDef::TTransformWithScale class_transform);
				TPhysShapeUserData* GetUserData()
				{
					return &user_data;
				}
			};
		}
	}
}