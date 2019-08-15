#pragma once

namespace BaluEngine
{
	namespace WorldDef
	{
		

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
			virtual IScene* GetScene() {
				return nullptr;
			}
			virtual const char* GetFactoryName() = 0;
			virtual void SetTransform(TTransform transform) = 0;
			virtual void SetScale(BaluLib::TVec2 scale) = 0;
			virtual TTransform GetTransform() = 0;
			virtual BaluLib::TVec2 GetScale() = 0;
			virtual TTransformWithScale GetTransformWithScale() = 0;
			virtual ~ISceneObject() {};
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
                                const char* values[] =
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

		



		class IWorldObject:public ISerializable, public virtual IProperties
		{
		public:
			virtual std::string GetName()const = 0;
			virtual IWorld* GetWorld() = 0;
			virtual IRuntimeProperties* GetProperties()const = 0;
			//virtual IAbstractEditor* CreateEditor(TDrawingHelperContext drawing_context, IWorldInstance* world_instance) = 0;
			virtual ~IWorldObject() {}
			//virtual TWorldObjectType GetWorldObjectType() = 0;
		};
	}

}

