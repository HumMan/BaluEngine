#pragma once

#include "Skeleton.h"

class TBoneInstance
{
private:
	TBoneInstance* parent;
	std::vector<std::unique_ptr<TBoneInstance>> children;

	TBone* source;

	float rotation_amount;

	TVec2 current_position;
	float current_rotation;
public:
	TBoneInstance(TBoneInstance* parent, TBone* source);
	void AddChild(TBoneInstance* bone);
	int GetChildrenCount();
	TBoneInstance* GetChild(int index);

	void SetRotationAmount(float amount);
};


class TSkeletonInstance
{
private:
	std::unique_ptr<TBoneInstance> root;
	std::vector<TBoneInstance*> bones;

	TSkeleton* source;
public:
	void UpdateTranform();
};