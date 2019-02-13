#pragma once


namespace BaluEngine
{
	namespace WorldDef
	{	
		enum class PropertyType
		{
			Bool,
			Int,
			Number,
			Float,
			String,
			Color,
			ColorWithAlpha,
			TransparentMode,
			AlphaTestFunc,
			BlendFunc,
			BlendEquation,
			TexFilter,
			TexClamp,
			Size,
			TransformWithScale,
			Transform,
			Scale,
			Pos,
			Rotation,
			PhysBodyType,
			PhysShapeType,//возможно просто PhysSHape
			ImagePath,

			//TODO что за свойства такие???
			Material,
			Layer,
			Properties,
		};

		enum class TTransparentMode
		{
			TM_NONE,
			TM_ALPHA_BLEND,
			TM_ALPHA_TEST,
		};

		enum class TPolygonMode
		{
			Point,
			Line,
			Fill
		};

		enum class TBlendFunc
		{
			BF_ADD,
			BF_SUBTRACT
		};
		enum class TBlendEquation
		{
			BE_SRC_COLOR,
			BE_ONE_MINUS_SRC_COLOR,
			BE_SRC_ALPHA,
			BE_ONE_MINUS_SRC_ALPHA,
			BE_DST_COLOR,
			BE_ONE_MINUS_DST_COLOR,
			BE_DST_ALPHA,
			BE_ONE_MINUS_DST_ALPHA,
			BE_CONSTANT_COLOR,
			BE_ONE_MINUS_CONSTANT_COLOR,
			BE_CONSTANT_ALPHA,
			BE_ONE_MINUS_CONSTANT_ALPHA
		};

		enum class TAlphaTestFunc
		{
			AT_ALWAYS,
			AT_NEVER,
			AT_LEQUAL,
			AT_LESS,
			AT_EQUAL,
			AT_NOTEQUAL,
			AT_GEQUAL,
			AT_GREATER
		};
		enum class TTexFilter
		{
			Nearest,
			Linear,
			Bilinear,
			Trilinear,
			BilinearAniso,
			TrilinearAniso
		};

		enum class TTexClamp
		{
			NONE = 0,
			S = 1,
			T = 2,
			R = 4,
			ST = 1 | 2,
			STR = 1 | 2 | 4
		};

		enum class TMouseButton
		{
			Left,
			Right,
			Middle
		};


		enum TPhysBodyType
		{
			Static,
			Kinematic,
			Dynamic,
		};

		class TMouseEventArgs
		{
		public:
			TMouseButton button;
			BaluLib::TVec2i location;
			TMouseEventArgs() {}
			TMouseEventArgs(TMouseButton button, BaluLib::TVec2i location)
			{
				this->button = button;
				this->location = location;
			}
		};

		struct TRot
		{
			TRot() {}
			TRot(float s, float c)
			{
				this->s = s;
				this->c = c;
			}
			explicit TRot(float angle)
			{
				Set(angle);
			}
			explicit TRot(const BaluLib::TOBB2& box)
			{
				c = box.orient[0][0];
				s = box.orient[0][1];
			}
			void Set(float angle)
			{
				s = sinf(angle);
				c = cosf(angle);
			}
			void SetIdentity()
			{
				s = 0.0f;
				c = 1.0f;
			}
			float GetAngle() const
			{
				return atan2(s, c);
			}
			BaluLib::TVec2 GetXAxis() const
			{
				return BaluLib::TVec2(c, s);
			}
			BaluLib::TVec2 GetYAxis() const
			{
				return BaluLib::TVec2(-s, c);
			}
			float s, c;
		};

		class TTransform
		{
		public:
			BaluLib::TVec2 position;
			TRot angle;
			TTransform()
			{
				position = BaluLib::TVec2(0, 0);
				angle = TRot(0);
			}
			TTransform(BaluLib::TVec2 position, TRot angle)
			{
				this->position = position;
				this->angle = angle;
			}
			BaluLib::TMatrix2 GetOrientation()
			{
				return BaluLib::TMatrix2(angle.GetXAxis(), angle.GetYAxis());
			}
			BaluLib::TVec2 ToGlobal(BaluLib::TVec2 p)
			{
				return GetOrientation()*p + position;
			}
			BaluLib::TVec2 ToLocal(BaluLib::TVec2 p)
			{
				return GetOrientation().TransMul((p - position));
			}

			BaluLib::TOBB2 ToGlobal(BaluLib::TOBB2 box)
			{
				return BaluLib::TOBB2(box.pos + position, GetOrientation()*box.orient, box.local);
			}
			BaluLib::TOBB2 ToGlobal(BaluLib::TAABB2 box)
			{
				return BaluLib::TOBB2(position, GetOrientation(), box);
			}
			TTransform ToGlobal(TTransform local)
			{
				TTransform global;
				global.position = position + GetOrientation()*local.position;
				global.angle = TRot(angle.GetAngle() + local.angle.GetAngle());
				return global;
			}
			BaluLib::TVec2 Transform(BaluLib::TVec2 vertex, BaluLib::TVec2 scale)
			{
				return this->ToGlobal((vertex).ComponentMul(scale));
			}
		};

		class TTransformWithScale
		{
		public:
			TTransform transform;
			BaluLib::TVec2 scale;
			TTransformWithScale()
			{
				scale = BaluLib::TVec2(1, 1);
				transform = TTransform(BaluLib::TVec2(0, 0), TRot(0));
			}
			TTransformWithScale(TTransform transform, BaluLib::TVec2 scale)
			{
				this->transform = transform;
				this->scale = scale;
			}
			BaluLib::TVec2 ToLocal(BaluLib::TVec2 point)
			{
				BaluLib::TVec2 p = transform.ToLocal(point);
				p /= scale;
				return p;
			}
			BaluLib::TVec2 ToGlobal(BaluLib::TVec2 p)
			{
				return transform.ToGlobal(p.ComponentMul(scale));
			}
			TTransformWithScale ToGlobal(TTransformWithScale local)
			{
				TTransformWithScale global;
				global.transform.position = transform.position + transform.GetOrientation()*(local.transform.position.ComponentMul(scale));
				global.transform.angle = TRot(transform.angle.GetAngle() + local.transform.angle.GetAngle());
				global.scale = scale.ComponentMul(local.scale);
				return global;
			}
			BaluLib::TOBB2 ToGlobal(BaluLib::TAABB2 box)
			{
				box.border[0] *= scale;
				box.border[1] *= scale;
				return transform.ToGlobal(box);
			}
			BaluLib::TOBB2 ToGlobal(BaluLib::TOBB2 box)
			{
				box.local.border[0] *= scale;
				box.local.border[1] *= scale;
				return transform.ToGlobal(box);
			}
		};

		template<int T>
		class PropertyToTypeMap {};

#define BALU_ENGINE_REGISTER_PROPERTY_TO_TYPE_MAP(prop, result)\
			template<>\
			class PropertyToTypeMap<(int)prop>\
			{\
			public:\
				typedef result Result;\
			};

		BALU_ENGINE_REGISTER_PROPERTY_TO_TYPE_MAP(PropertyType::Bool, bool)
			BALU_ENGINE_REGISTER_PROPERTY_TO_TYPE_MAP(PropertyType::Int, int)
			BALU_ENGINE_REGISTER_PROPERTY_TO_TYPE_MAP(PropertyType::Number, unsigned int)
			BALU_ENGINE_REGISTER_PROPERTY_TO_TYPE_MAP(PropertyType::Float, float)
			BALU_ENGINE_REGISTER_PROPERTY_TO_TYPE_MAP(PropertyType::String, std::string)
			BALU_ENGINE_REGISTER_PROPERTY_TO_TYPE_MAP(PropertyType::Color, BaluLib::TVec3)
			BALU_ENGINE_REGISTER_PROPERTY_TO_TYPE_MAP(PropertyType::ColorWithAlpha, BaluLib::TVec4)
			BALU_ENGINE_REGISTER_PROPERTY_TO_TYPE_MAP(PropertyType::TransparentMode, TTransparentMode)
			BALU_ENGINE_REGISTER_PROPERTY_TO_TYPE_MAP(PropertyType::AlphaTestFunc, TAlphaTestFunc)
			BALU_ENGINE_REGISTER_PROPERTY_TO_TYPE_MAP(PropertyType::BlendFunc, TBlendFunc)
			BALU_ENGINE_REGISTER_PROPERTY_TO_TYPE_MAP(PropertyType::BlendEquation, TBlendEquation)
			BALU_ENGINE_REGISTER_PROPERTY_TO_TYPE_MAP(PropertyType::TexFilter, TTexFilter)
			BALU_ENGINE_REGISTER_PROPERTY_TO_TYPE_MAP(PropertyType::TexClamp, TTexClamp)
			BALU_ENGINE_REGISTER_PROPERTY_TO_TYPE_MAP(PropertyType::Size, BaluLib::TVec2)
			BALU_ENGINE_REGISTER_PROPERTY_TO_TYPE_MAP(PropertyType::TransformWithScale, TTransformWithScale)
			BALU_ENGINE_REGISTER_PROPERTY_TO_TYPE_MAP(PropertyType::Transform, TTransform)
			BALU_ENGINE_REGISTER_PROPERTY_TO_TYPE_MAP(PropertyType::Scale, BaluLib::TVec2)
			BALU_ENGINE_REGISTER_PROPERTY_TO_TYPE_MAP(PropertyType::Pos, BaluLib::TVec2)
			BALU_ENGINE_REGISTER_PROPERTY_TO_TYPE_MAP(PropertyType::Rotation, TRot)
			BALU_ENGINE_REGISTER_PROPERTY_TO_TYPE_MAP(PropertyType::PhysBodyType, TPhysBodyType)
			//BALU_ENGINE_REGISTER_PROPERTY_TO_TYPE_MAP(PropertyType::PhysShapeType, TPhysShapeType TODO)
			BALU_ENGINE_REGISTER_PROPERTY_TO_TYPE_MAP(PropertyType::ImagePath, std::string)

#undef BALU_ENGINE_REGISTER_PROPERTY_TO_TYPE_MAP




		class IProperty
		{
		public:
			virtual PropertyType GetType()const = 0;
			virtual void Save(pugi::xml_node& parent_node, const int version)const = 0;
			virtual void Load(const pugi::xml_node& instance_node, const int version) = 0;
			virtual std::string SerializeValue()const=0;
			virtual void DeserializeValue(const std::string& value)=0;

#define BALU_ENGINE_PROPERTY_SETGET(property_type)\
				virtual void SetAs##property_type(const PropertyToTypeMap<(int)PropertyType::##property_type>::Result& value)=0;\
				virtual PropertyToTypeMap<(int)PropertyType::##property_type>::Result GetAs##property_type()const=0;\

			BALU_ENGINE_PROPERTY_SETGET(Bool)
				BALU_ENGINE_PROPERTY_SETGET(Int)
				BALU_ENGINE_PROPERTY_SETGET(Number)
				BALU_ENGINE_PROPERTY_SETGET(Float)
				BALU_ENGINE_PROPERTY_SETGET(String)
				BALU_ENGINE_PROPERTY_SETGET(Color)
				BALU_ENGINE_PROPERTY_SETGET(ColorWithAlpha)
				BALU_ENGINE_PROPERTY_SETGET(TransparentMode)
				BALU_ENGINE_PROPERTY_SETGET(AlphaTestFunc)
				BALU_ENGINE_PROPERTY_SETGET(BlendFunc)
				BALU_ENGINE_PROPERTY_SETGET(BlendEquation)
				BALU_ENGINE_PROPERTY_SETGET(TexFilter)
				BALU_ENGINE_PROPERTY_SETGET(TexClamp)
				BALU_ENGINE_PROPERTY_SETGET(Size)
				BALU_ENGINE_PROPERTY_SETGET(TransformWithScale)
				BALU_ENGINE_PROPERTY_SETGET(Transform)
				BALU_ENGINE_PROPERTY_SETGET(Scale)
				BALU_ENGINE_PROPERTY_SETGET(Pos)
				BALU_ENGINE_PROPERTY_SETGET(Rotation)
				BALU_ENGINE_PROPERTY_SETGET(PhysBodyType)
				BALU_ENGINE_PROPERTY_SETGET(ImagePath)

#undef BALU_ENGINE_PROPERTY_SETGET
		};

		class IProperties
		{
		public:
			virtual IProperty * GetProperty(const std::string& name)const = 0;
			virtual bool HasProperty(const std::string& name, PropertyType& type)const = 0;
			virtual std::vector<std::string> GetPropertyNames() = 0;
			virtual void SaveProperties(pugi::xml_node& parent_node, const int version)const = 0;
			virtual void LoadProperties(const pugi::xml_node& instance_node, const int version) = 0;
		};

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
