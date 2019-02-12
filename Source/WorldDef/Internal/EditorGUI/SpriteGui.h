
#pragma once

#include "../../Interface.h"

#include "../../Internal/Common/Common.h"

namespace BaluEngine
{
	namespace WorldDef
	{
		namespace Internal
		{
			class TSimpleSprite: TGui
			{
			protected:
				bool visible;
				ISprite* visual;
			public:
				ISprite* GetSprite();
				static const char* FactoryName()
				{
					return "SimpleSprite";
				}

				static ISceneObject* Clone(TScene*)
				{
					return new TSimpleSprite();
				}

				const char* GetFactoryName()
				{
					return FactoryName();
				}

				void Save(pugi::xml_node& parent_node, const int version)const;
				void Load(const pugi::xml_node& instance_node, const int version, IWorld* world);
			};

			REGISTER_FACTORY_CLASS(SceneObjectFactory, TSimpleSprite)

		}
	}
}