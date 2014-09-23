#include "propertiesRegistry.h"

namespace Editor
{
	using namespace System::ComponentModel;

	value class TVecProperties
	{
	private:
		TVec2* vec;
	public:
		TVecProperties(TVec2* vec)
		{
			this->vec = vec;
		}
		property float X {float get(){ return (*vec)[0]; } void set(float value) { (*vec)[0] = value; }}
		property float Y {float get(){ return (*vec)[1]; } void set(float value) { (*vec)[1] = value; }}
	};

	value class TOBBProperites
	{
	private:
		TOBB<float, 2>* box;
	public:
		TOBBProperites(TOBB<float, 2>* box)
		{
			this->box = box;
		}
		property float X {float get(){ return box->GetPos()[0]; }}
		property float Y {float get(){ return box->GetPos()[1]; }}
	};

	ref class TSpriteProperties : public TPropertiesObject
	{
		TBaluSpriteDef* obj_def;
	public:
		TSpriteProperties(TBaluSpriteDef* obj_def){ this->obj_def = obj_def; }
		property int TestProp;
	};

	ref class TBaluPhysShapeProperties : public TPropertiesObject
	{
		TBaluShapeDef* obj_def;
	public:
		TBaluPhysShapeProperties(TBaluShapeDef* obj_def)
		{
			this->obj_def = obj_def;
			
		}
		//[CategoryAttribute("SubInfo")]
		//[DisplayNameAttribute("Name")]
		[TypeConverter(ExpandableObjectConverter::typeid)]
		property TOBBProperites^ OBB
		{
			TOBBProperites^ get()
			{
				return gcnew TOBBProperites(&obj_def->GetOBB());
			}
		}
	};

	ref class TBaluPolygonShapeProperties : public TBaluPhysShapeProperties
	{
		TBaluPolygonShapeDef* obj_def;
	public:
		TBaluPolygonShapeProperties(TBaluPolygonShapeDef* obj_def) :TBaluPhysShapeProperties(obj_def)
		{
			this->obj_def = obj_def; 
		}
		property int testprop;
	};

	TPropertiesObject^ TPropertiesRegistry::CreateProperties(TWorldObjectDef* obj_def)
	{
		if ((dynamic_cast<TBaluSpriteDef*>(obj_def)) != nullptr)
			return gcnew TSpriteProperties(dynamic_cast<TBaluSpriteDef*>(obj_def));

		if ((dynamic_cast<TBaluPolygonShapeDef*>(obj_def)) != nullptr)
			return gcnew TBaluPolygonShapeProperties(dynamic_cast<TBaluPolygonShapeDef*>(obj_def));
	}
}