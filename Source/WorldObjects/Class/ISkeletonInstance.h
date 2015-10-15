#pragma once

#include "../Sprite/ISpriteInstance.h"

namespace EngineInterface
{
	class TBaluTransformedClassInstance;


#ifdef BALUENGINEDLL_EXPORTS
	class TBoneInstance
	{
	private:
		TBoneInstance* parent;
		std::vector<std::unique_ptr<TBoneInstance>> children;

		TBone* source;

		//float rotation_amount;

		//TVec2 current_position;
		float current_rotation;

		TBaluTransform global;
	public:
		TBoneInstance(TBoneInstance* parent, TBone* source);
		int GetChildrenCount();
		TBoneInstance* GetChild(int index);

		void SetRotationAmount(float amount);

		TBone* GetSourceBone();

		void UpdateTranform(TBaluTransform parent);
		TBaluTransform GetGlobalTransform();
	};

	class TBaluTransformedSpriteInstance;
	class TResources;

	class TSkinInstance
	{
	private:
		std::vector<std::vector<std::unique_ptr<TBaluTransformedSpriteInstance>>> sprites_of_bones;
	public:
		TSkinInstance(TSkin* source, TResources* resources);
		void QueryAABB(TAABB2 frustum, std::vector<TBaluSpritePolygonInstance*>& results);
		void UpdateSpritesTransform(std::vector<TBoneInstance*> bones, TBaluTransformWithScale class_transform);
	};

	class TSkeletonInstance
	{
	private:
		std::unique_ptr<TBoneInstance> root;
		std::vector<TBoneInstance*> bones;
		std::vector<std::unique_ptr<TSkinInstance>> skins;

		TSkeleton* source;
	public:
		TSkeletonInstance(TSkeleton* source, TResources* resources);
		void UpdateTranform(TBaluTransformWithScale class_transform);
		void QueryAABB(TAABB2 frustum, std::vector<TBaluSpritePolygonInstance*>& results);
		TSkeleton* GetSource();
		TBoneInstance* GetBone(int index);
	};
#endif

}