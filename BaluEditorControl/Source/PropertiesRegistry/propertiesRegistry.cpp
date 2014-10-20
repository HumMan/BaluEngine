#include "propertiesRegistry.h"

#include <msclr/marshal_cppstd.h>



namespace Editor
{
	using namespace System::ComponentModel;
	using namespace System;

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

	/*ref class DrinkDosesConverter :EnumConverter
	{
	private:
		System::Type^ _enumType;
		/// <summary />Initializing instance</summary />
		/// <param name=""type"" />type Enum</param />
		/// this is only one function, that you must
		/// change. All another functions for enums
		/// you can use by Ctrl+C/Ctrl+V
	public:
		DrinkDosesConverter(Type type)
			: base(type)
		{
			_enumType = type;
		}

		bool CanConvertTo(ITypeDescriptorContext context,
			Type destType)
		{
			return destType == typeof(string);
		}

		System::Object^ ConvertTo(ITypeDescriptorContext context,
			CultureInfo culture,
			object value, Type destType)
		{
			FieldInfo fi = _enumType.GetField(Enum.GetName(_enumType, value));
			DescriptionAttribute dna =
				(DescriptionAttribute)Attribute.GetCustomAttribute(
				fi, typeof(DescriptionAttribute));

			if (dna != null)
				return dna.Description;
			else
				return value.ToString();
		}

		bool CanConvertFrom(ITypeDescriptorContext context,
			Type srcType)
		{
			return srcType == typeof(string);
		}

		System::Object ConvertFrom(ITypeDescriptorContext context,
			CultureInfo culture,
			object value)
		{
			foreach(FieldInfo fi in _enumType.GetFields())
			{
				DescriptionAttribute dna =
					(DescriptionAttribute)Attribute.GetCustomAttribute(
					fi, typeof(DescriptionAttribute));

				if ((dna != null) && ((string)value == dna.Description))
					return Enum.Parse(_enumType, fi.Name);
			}
			return Enum.Parse(_enumType, (string)value);
		}
	};*/

	ref class TMaterialProperties : public TPropertiesObject
	{
		TBaluMaterialDef* obj_def;
	public:
		TMaterialProperties(TBaluMaterialDef* obj_def)
		{
			this->obj_def = obj_def;
		}
		property String^ Name {
			String^ get()
			{
				return gcnew String(obj_def->material_name.c_str());
			}
			
		};
		property String^ Image
		{
			String^ get()
			{
				return gcnew String(obj_def->image_path.c_str());
			}
			void set(String^ value)
			{
				obj_def->image_path = msclr::interop::marshal_as< std::string >(value);
			}
		};
		enum class TTransparentMode : int
		{//TODO тестирование и смешивание может работать одновременно
			TM_NONE,
			TM_ALPHA_BLEND,
			TM_ALPHA_TEST,
		};
		property TTransparentMode BlendMode
		{
			TTransparentMode get()
			{
				return (TTransparentMode)obj_def->blend_mode;
			}
			void set(TTransparentMode value)
			{
				obj_def->blend_mode = (TBaluMaterialDef::TTransparentMode)value;
			}
		};

		property TBaluMaterialDef::TTexFilter TextureFilter
		{
			TBaluMaterialDef::TTexFilter get()
			{
				return (TBaluMaterialDef::TTexFilter)obj_def->blend_mode;
			}
			void set(TBaluMaterialDef::TTexFilter value)
			{
				obj_def->texture_filter = (TBaluMaterialDef::TTexFilter)value;
			}
		};
	};

	ref class TSpriteProperties : public TPropertiesObject
	{
		TBaluSpriteDef* obj_def;
	public:
		TSpriteProperties(TBaluSpriteDef* obj_def){ this->obj_def = obj_def; }
		property String^ Name {String^ get() { return gcnew String(obj_def->sprite_name.c_str()); } };
		//property String^ Material {String^ get() { return gcnew String(obj_def->material_name.c_str()); } };
		//property TBaluSpriteDef::TPolygonMode PolygonMode {TBaluSpriteDef::TPolygonMode get() { return obj_def->polygone_mode; } };
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
		property int polygon_testprop;
	};

	ref class TBaluPhysBodyProperties : public TPropertiesObject
	{
		TBaluPhysBodyDef* obj_def;
	public:
		TBaluPhysBodyProperties(TBaluPhysBodyDef* obj_def)
		{
			this->obj_def = obj_def;
		}
		property int phys_body_testprop;
	};

	TPropertiesObject^ TPropertiesRegistry::CreateProperties(TWorldObjectDef* obj_def)
	{
		if ((dynamic_cast<TBaluMaterialDef*>(obj_def)) != nullptr)
			return gcnew TMaterialProperties(dynamic_cast<TBaluMaterialDef*>(obj_def));

		if ((dynamic_cast<TBaluSpriteDef*>(obj_def)) != nullptr)
			return gcnew TSpriteProperties(dynamic_cast<TBaluSpriteDef*>(obj_def));

		if ((dynamic_cast<TBaluPhysBodyDef*>(obj_def)) != nullptr)
			return gcnew TBaluPhysBodyProperties(dynamic_cast<TBaluPhysBodyDef*>(obj_def));

		return gcnew TPropertiesObject();
	}
}