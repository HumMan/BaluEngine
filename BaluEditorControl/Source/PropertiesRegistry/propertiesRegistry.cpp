#include "propertiesRegistry.h"

namespace Editor
{

	ref class TSpriteProperties : public TPropertiesObject
	{
		TBaluSpriteDef* obj_def;
	public:
		property int TestProp;
	};

	TPropertiesObject^ TPropertiesRegistry::CreateProperties(TWorldObjectDef* obj_def)
	{
		return gcnew TSpriteProperties();
	}
}