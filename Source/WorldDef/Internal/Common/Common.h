#pragma once

#include "../../Interface.h"

#include "Properties.h"
#include "RuntimeProperties.h"

namespace BaluEngine
{
	namespace WorldDef
	{
		namespace Internal
		{
			typedef ISceneObject*(*SceneObjectClone)(IScene*);
			class SceneObjectFactory
			{
			public:
				static bool Register(const char* name, SceneObjectClone clone);
				static ISceneObject* Create(const char* name, IScene* scene);
				static void UnregisterAll();
			};

			class TGui : public ISceneObject
			{
			public:
				void SetTransform(TTransform transform) {}
				void SetScale(BaluLib::TVec2 scale) {}
				TTransform GetTransform() { return TTransform(); }
				BaluLib::TVec2 GetScale() { return BaluLib::TVec2(1, 1); }
				TTransformWithScale GetTransformWithScale() { return TTransformWithScale(); }
			};			

			class TWorldObject : public TProperties, public virtual IWorldObject
			{
			protected:
				IWorld * world;

				std::unique_ptr<TRuntimeProperties> runtime_properties;

				void InitAllProperties()
				{
					InitProperty_Name();
				}

			public:

				BALU_ENGINE_REGISTER_PROPERTY(Name, PropertyType::String, "")

				TWorldObject(IWorld* world, std::string name);
				IWorld* GetWorld();

				IRuntimeProperties* GetProperties()const
				{
					return runtime_properties.get();
				}
			};
		}
	}
}

