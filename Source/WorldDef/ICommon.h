#pragma once

namespace BaluEngine
{
	namespace WorldDef
	{
		enum class TMouseButton
		{
			Left,
			Right,
			Middle
		};

		class ISerializable
		{
		public:
			virtual void Save(pugi::xml_node& parent_node, const int version)const=0;
			virtual void Load(const pugi::xml_node& instance_node, const int version, IWorld* world)=0;
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

		class IViewport: public ISerializable
		{
		public:
			virtual void SetTransform(TTransform transform) = 0;
			virtual TTransform GetTransform() = 0;
			virtual void SetAspectRatio(float aspect) = 0;
			virtual void SetWidth(float width) = 0;
			virtual BaluLib::TAABB2 GetAABB() = 0;
			virtual void SetSize(BaluLib::TVec2 size) = 0;
			virtual BaluLib::TVec2 GetSize() = 0;
		};

		class ISceneObject: public ISerializable
		{
		public:
			virtual const char* GetFactoryName() = 0;
			//virtual void SetTransform(TTransform transform) = 0;
			//virtual void SetScale(BaluLib::TVec2 scale) = 0;
			//virtual TTransform GetTransform() = 0;
			//virtual BaluLib::TVec2 GetScale() = 0;
			//virtual TTransformWithScale GetTransformWithScale() = 0;
			virtual ~ISceneObject(){}
		};

		enum class TWorldObjectType
		{
			Material,
			Sprite,
			Class,
			Scene,
			None
		};

		enum class TWorldObjectSubType
		{
			//SpritePolygon,
			//SpritePhysShape,
			ClassSpriteInstance,
			SceneClassInstance
		};

		class TWorldObjectTypeString
		{
		public:
			static inline const char* Get(TWorldObjectType index)
			{
				char* values[] =
				{
					"Material",
					"Sprite",
					"Class",
					"Scene",
					"None",
				};
				return values[(int)index];
			}
		};

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



		class IProperty
		{
		public:
			virtual PropertyType GetType()const = 0;
			virtual void SetAsBool(bool value) = 0;
			virtual bool GetAsBool()const = 0;
			virtual void Set(const void const* new_value) = 0;
			virtual void Save(pugi::xml_node& parent_node, const int version)const = 0;
			virtual void Load(const pugi::xml_node& instance_node, const int version) = 0;
		};

		class IProperties
		{
		public:
			virtual IProperty * GetProperty(const std::string& name)const = 0;
			virtual bool HasProperty(const std::string& name, PropertyType& type)const = 0;
			virtual void SaveProperties(pugi::xml_node& parent_node, const int version)const=0;
			virtual void LoadProperties(const pugi::xml_node& instance_node, const int version)=0;
		};

		class IWorldObject:public ISerializable, public virtual IProperties
		{
		public:
			virtual IWorld* GetWorld() = 0;
			//virtual IAbstractEditor* CreateEditor(TDrawingHelperContext drawing_context, IWorldInstance* world_instance) = 0;
			virtual ~IWorldObject() {}
			//virtual TWorldObjectType GetWorldObjectType() = 0;
		};

		class IChangeListener
		{
		public:
			virtual void SourceChanged() {}
			virtual void ElementToSourceAdded(TWorldObjectSubType type) {}
			virtual void ElementFromSourceRemoved(TWorldObjectSubType type) {}
			virtual void BeforeDeleteSource() {}
		};

		class IChangeListenerArray
		{
		public:
			virtual void AddChangesListener(IChangeListener* listener) = 0;
			virtual void RemoveChangesListener(IChangeListener* listener) = 0;
			virtual void OnChanged() = 0;
			virtual void OnElementAdded(TWorldObjectSubType type) = 0;
			virtual void OnElementRemoved(TWorldObjectSubType type) = 0;
			virtual void OnBeforeDelete() = 0;
		};

		class TWorldChangeListener
		{
		public:
			virtual void OnObjectCreate(TWorldObjectType type, const std::string& name) = 0;
			virtual void OnObjectDestroy(TWorldObjectType type, const std::string& name) {}
			virtual void OnObjectRename(TWorldObjectType type, const std::string& old_name, const std::string& new_name) {}
		};
	}

}

