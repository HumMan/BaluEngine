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
		IBaluMaterial* obj_def;
	public:
		TMaterialProperties(IBaluMaterial* obj_def)
		{
			this->obj_def = obj_def;
		}
		property String^ Name {
			String^ get()
			{
				return gcnew String(obj_def->GetName().c_str());
			}
			
		};
		property String^ Image
		{
			String^ get()
			{
				return gcnew String(obj_def->GetImagePath().c_str());
			}
			void set(String^ value)
			{
				obj_def->SetImagePath(msclr::interop::marshal_as< std::string >(value));
			}
		};
		//enum class TTransparentMode : int
		//{//TODO тестирование и смешивание может работать одновременно
		//	TM_NONE,
		//	TM_ALPHA_BLEND,
		//	TM_ALPHA_TEST,
		//};
		//property TTransparentMode BlendMode
		//{
		//	TTransparentMode get()
		//	{
		//		return (TTransparentMode)obj_def->blend_mode;
		//	}
		//	void set(TTransparentMode value)
		//	{
		//		obj_def->blend_mode = (TBaluMaterialDef::TTransparentMode)value;
		//	}
		//};

		//property TBaluMaterialDef::TTexFilter TextureFilter
		//{
		//	TBaluMaterialDef::TTexFilter get()
		//	{
		//		return (TBaluMaterialDef::TTexFilter)obj_def->blend_mode;
		//	}
		//	void set(TBaluMaterialDef::TTexFilter value)
		//	{
		//		obj_def->texture_filter = (TBaluMaterialDef::TTexFilter)value;
		//	}
		//};
	};

	ref class TSpritePolygonProperties : public TPropertiesObject
	{
		IBaluSpritePolygon* obj_def;
		IBaluWorld* world;
	public:
		TSpritePolygonProperties(IBaluWorld* world, IBaluSpritePolygon* obj_def)
		{
			this->world = world;
			this->obj_def = obj_def; 
		}
		property String^ Material
		{
			String^ get() 
			{
				if (obj_def->GetMaterial()!=nullptr)
					return gcnew String(obj_def->GetMaterial()->GetName().c_str());
				else return "";
			}
			void set(String^ value)
			{
				auto mat_name = msclr::interop::marshal_as<std::string>(value);
				IBaluMaterial* result;
				auto mat_found = world->TryFind(mat_name.c_str(), result);
				if (mat_found)
					obj_def->SetMaterial(result);
			}
		};
		//property TBaluSpriteDef::TPolygonMode PolygonMode {TBaluSpriteDef::TPolygonMode get() { return obj_def->polygone_mode; } };
	};

	ref class TSpriteProperties : public TPropertiesObject
	{
		IBaluSprite* obj_def;
	public:
		TSpriteProperties(IBaluSprite* obj_def){ this->obj_def = obj_def; }
		property String^ Name 
		{
			String^ get()
			{
				return gcnew String(obj_def->GetName().c_str());
			}
		};
		//property String^ Material {String^ get() { return gcnew String(obj_def->material_name.c_str()); } };
		//property TBaluSpriteDef::TPolygonMode PolygonMode {TBaluSpriteDef::TPolygonMode get() { return obj_def->polygone_mode; } };
	};

	//ref class TBaluPhysShapeProperties : public TPropertiesObject
	//{
	//	IBaluPhysShape* obj_def;
	//public:
	//	TBaluPhysShapeProperties(IBaluPhysShape* obj_def)
	//	{
	//		this->obj_def = obj_def;
	//		
	//	}
	//	//[CategoryAttribute("SubInfo")]
	//	//[DisplayNameAttribute("Name")]
	//	[TypeConverter(ExpandableObjectConverter::typeid)]
	//	property TOBBProperites^ OBB
	//	{
	//		TOBBProperites^ get()
	//		{
	//			return gcnew TOBBProperites(&obj_def->GetOBB());
	//		}
	//	}
	//};

	//ref class TBaluPolygonShapeProperties : public TBaluPhysShapeProperties
	//{
	//	IBaluSpritePolygon* obj_def;
	//public:
	//	TBaluPolygonShapeProperties(IBaluSpritePolygon* obj_def) :TBaluPhysShapeProperties(obj_def)
	//	{
	//		this->obj_def = obj_def; 
	//	}
	//	property int polygon_testprop;
	//};

	ref class TBaluClassProperties : public TPropertiesObject
	{
		IBaluClass* obj_def;
	public:
		TBaluClassProperties(IBaluClass* obj_def)
		{
			this->obj_def = obj_def;
		}
		property int TBaluClass_testprop;
	};

	ref class TBaluSpriteInstanceProperties : public TPropertiesObject
	{
		IBaluClassSpriteInstance* obj_def;
	public:
		TBaluSpriteInstanceProperties(IBaluClassSpriteInstance* obj_def)
		{
			this->obj_def = obj_def;
		}
		property int TTBaluSpriteInstanceDef_testprop;
	};

	ref class TBaluInstanceDefProperties : public TPropertiesObject
	{
		IBaluInstance* obj_def;
	public:
		TBaluInstanceDefProperties(IBaluInstance* obj_def)
		{
			this->obj_def = obj_def;
		}
		property int TBaluInstanceDef_testprop;
	};

	ref class TBaluSceneProperties : public TPropertiesObject
	{
		IBaluScene* obj_def;
	public:
		TBaluSceneProperties(IBaluScene* obj_def)
		{
			this->obj_def = obj_def;
		}
		property int TBaluSceneDef_testprop;
	};

	TPropertiesObject^ TPropertiesRegistry::CreateProperties(IBaluWorld* world, IBaluWorldObject* obj_def)
	{
		//return gcnew TPropertiesObject();

		if ((dynamic_cast<IBaluMaterial*>(obj_def)) != nullptr)
			return gcnew TMaterialProperties(dynamic_cast<IBaluMaterial*>(obj_def));

		if ((dynamic_cast<IBaluSpritePolygon*>(obj_def)) != nullptr)
			return gcnew TSpritePolygonProperties(world, dynamic_cast<IBaluSpritePolygon*>(obj_def));

		if ((dynamic_cast<IBaluSprite*>(obj_def)) != nullptr)
			return gcnew TSpriteProperties(dynamic_cast<IBaluSprite*>(obj_def));

		//if ((dynamic_cast<TBaluPhysBodyDef*>(obj_def)) != nullptr)
		//	return gcnew TBaluPhysBodyProperties(dynamic_cast<TBaluPhysBodyDef*>(obj_def));

		//if ((dynamic_cast<TBaluBodyInstanceDef*>(obj_def)) != nullptr)
		//	return gcnew TBaluBodyInstanceProperties(dynamic_cast<TBaluBodyInstanceDef*>(obj_def));

		if ((dynamic_cast<IBaluClassSpriteInstance*>(obj_def)) != nullptr)
			return gcnew TBaluSpriteInstanceProperties(dynamic_cast<IBaluClassSpriteInstance*>(obj_def));

		if ((dynamic_cast<IBaluClass*>(obj_def)) != nullptr)
			return gcnew TBaluClassProperties(dynamic_cast<IBaluClass*>(obj_def));

		if ((dynamic_cast<IBaluInstance*>(obj_def)) != nullptr)
			return gcnew TBaluInstanceDefProperties(dynamic_cast<IBaluInstance*>(obj_def));

		if ((dynamic_cast<IBaluScene*>(obj_def)) != nullptr)
			return gcnew TBaluSceneProperties(dynamic_cast<IBaluScene*>(obj_def));

		assert(false);

		return gcnew TPropertiesObject();
	}
}