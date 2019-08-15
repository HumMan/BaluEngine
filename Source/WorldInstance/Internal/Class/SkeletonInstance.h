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
				std::weak_ptr < TBoneInstance> parent;
				std::vector<std::shared_ptr<TBoneInstance>> children;

				WorldDef::IBone* source;

				//float rotation_amount;

				//TVec2 current_position;
				float current_rotation;

				WorldDef::TTransform global;
			public:
				TBoneInstance();
				void Init(std::weak_ptr < TBoneInstance> parent, WorldDef::IBone* source, std::weak_ptr < TBoneInstance> this_ptr);
				int GetChildrenCount();
				std::shared_ptr < TBoneInstance> GetChild(int index);

				void SetRotationAmount(float amount);

				WorldDef::IBone* GetSourceBone();

				void UpdateTranform(WorldDef::TTransform parent);
				WorldDef::TTransform GetGlobalTransform();
			};

			class TSkinInstance
			{
			private:
				std::vector<std::vector<std::shared_ptr<ITransformedSpriteInstance>>> sprites_of_bones;
			public:
				TSkinInstance(WorldDef::ISkin* source, TResources* resources, std::weak_ptr < ISceneObjectInstance> scene_object);
				void QueryAABB(BaluLib::TAABB2 frustum, std::vector< std::shared_ptr<ISpritePolygonInstance>>& results);
				void UpdateSpritesTransform(std::vector< std::shared_ptr<TBoneInstance>> bones, WorldDef::TTransformWithScale class_transform);
			};

			class TSkeletonInstance : public ISkeletonInstance //public IChangeListener
			{
			private:
				std::shared_ptr<TBoneInstance> root;
				std::vector< std::shared_ptr<TBoneInstance>> bones;
				std::vector<std::shared_ptr<TSkinInstance>> skins;

				WorldDef::ISkeleton* source;
			public:
				TSkeletonInstance(WorldDef::ISkeleton* source, TResources* resources, std::weak_ptr < ISceneObjectInstance> scene_object);
				~TSkeletonInstance();
				void UpdateTranform(WorldDef::TTransformWithScale class_transform);
				void QueryAABB(BaluLib::TAABB2 frustum, std::vector< std::shared_ptr<ISpritePolygonInstance>>& results);
				WorldDef::ISkeleton* GetSource();
				std::shared_ptr < TBoneInstance> GetBone(int index);
			};
		}
	}
}