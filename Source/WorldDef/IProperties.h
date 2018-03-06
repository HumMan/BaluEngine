#pragma once


namespace BaluEngine
{
	namespace WorldDef
	{	

#define BALU_ENGINE_VPROPERTY(property_name, value_type)\
	virtual void Set##property_name(const value_type& value)=0;\
	virtual value_type Get##property_name()const=0;
		
		class ISerializable
		{
		public:
			virtual void Save(pugi::xml_node& parent_node, const int version)const = 0;
			virtual void Load(const pugi::xml_node& instance_node, const int version, IWorld* world) = 0;
		};
	}
}
