#pragma once


namespace BaluEngine
{
	namespace WorldDef
	{	

#define BALU_ENGINE_VPROPERTY(property_name, value_type)\
	virtual void Set##property_name(const value_type& value)=0;\
	virtual value_type Get##property_name()const=0;
		
		enum class RuntimePropertyType
		{
			Bool,
			Int,
			Float,
			String,
			Vec2,
			Vec3,
			Vec4,			
			TransformWithScale,
			Transform,
			Rotation,			
		};

		class ISerializable
		{
		public:
			virtual void Save(pugi::xml_node& parent_node, const int version)const = 0;
			virtual void Load(const pugi::xml_node& instance_node, const int version, IWorld* world) = 0;
		};

		class IRuntimeProperties : public ISerializable
		{
		public:
			virtual bool HasProperty(const std::string& name, RuntimePropertyType& type) = 0;
			virtual void SetBool(const std::string& name, bool value) = 0;
			virtual bool GetBool(const std::string& name) = 0;
		};
	}
}
