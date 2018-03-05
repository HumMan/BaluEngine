#pragma once


namespace BaluEngine
{
	namespace WorldDef
	{	

#define BALU_ENGINE_VPROPERTY(property_name, value_type)\
	virtual void Set##property_name(const value_type& value)=0;\
	virtual value_type Get##property_name()const=0;
		
	}
}
