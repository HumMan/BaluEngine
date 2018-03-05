#pragma once

#include "../../Interface.h"


namespace BaluEngine
{
	namespace WorldInstance
	{
		namespace Internal
		{

			class TBoneInstance
			{
			private:
				TBoneInstance * parent;
				std::vector<std::unique_ptr<TBoneInstance>> children;

				WorldDef::IBone* source;

				//float rotation_amount;

				//TVec2 current_position;
				float current_rotation;

				WorldDef::TTransform global;
			public:
				TBoneInstance(TBoneInstance* parent, WorldDef::IBone* source);
				int GetChildrenCount();
				TBoneInstance* GetChild(int index);

				void SetRotationAmount(float amount);

				WorldDef::IBone* GetSourceBone();

				void UpdateTranform(WorldDef::TTransform parent);
				WorldDef::TTransform GetGlobalTransform();
			};

			class TSkinInstance
			{
			private:
				std::vector<std::vector<std::unique_ptr<ITransformedSpriteInstance>>> sprites_of_bones;
			public:
				TSkinInstance(WorldDef::ISkin* source, TResources* resources, ISceneObjectInstance* scene_object);
				void QueryAABB(BaluLib::TAABB2 frustum, std::vector<ISpritePolygonInstance*>& results);
				void UpdateSpritesTransform(std::vector<TBoneInstance*> bones, WorldDef::TTransformWithScale class_transform);
			};

			class TSkeletonInstance : public ISkeletonInstance //public IChangeListener
			{
			private:
				std::unique_ptr<TBoneInstance> root;
				std::vector<TBoneInstance*> bones;
				std::vector<std::unique_ptr<TSkinInstance>> skins;

				WorldDef::ISkeleton* source;
			public:
				TSkeletonInstance(WorldDef::ISkeleton* source, TResources* resources, ISceneObjectInstance* scene_object);
				~TSkeletonInstance();
				void UpdateTranform(WorldDef::TTransformWithScale class_transform);
				void QueryAABB(BaluLib::TAABB2 frustum, std::vector<ISpritePolygonInstance*>& results);
				WorldDef::ISkeleton* GetSource();
				TBoneInstance* GetBone(int index);
			};
		}
	}
}