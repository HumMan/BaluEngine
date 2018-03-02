
#pragma once

#include "../../Interface.h"

#include "../../Internal/Common/Common.h"

namespace BaluEngine
{
	namespace WorldDef
	{
		namespace Internal
		{
			class TEditableOBBGui : public TGui
			{
			public:
				BaluLib::TOBB2 boundary;

				static const char* FactoryName()
				{
					return "EditableOBBGui";
				}

				static ISceneObject* Clone()
				{
					return new TEditableOBBGui();
				}

				const char* GetFactoryName()
				{
					return FactoryName();
				}

				void Save(pugi::xml_node& parent_node, const int version)const;
				void Load(const pugi::xml_node& instance_node, const int version, IWorld* world);
			};

			REGISTER_FACTORY_CLASS(SceneObjectFactory, TEditableOBBGui)
		}
	}
}
