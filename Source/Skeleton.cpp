#include "Skeleton.h"


TBone::TBone(TBone* parent)
{
	this->parent = parent;
}

void TBone::SetTransform(TBaluTransform local)
{
	this->local = local;
}

TBaluTransform TBone::GetTransform()
{
	return local;
}

void TBone::AddChild(TBone* bone)
{
	children.push_back(bone);
}
int TBone::GetChildrenCount()
{
	return children.size();
}
TBone* TBone::GetChild(int index)
{
	return children[index];
}

TSkin::TBaluSpriteInstance::TBaluSpriteInstance(TBaluSprite* sprite)
{
	this->sprite = sprite;
}
void TSkin::TBaluSpriteInstance::SetTransform(TBaluTransform global)
{
	transform = global;
}
TBaluTransform TSkin::TBaluSpriteInstance::GetTransform()
{
	return transform;
}

TBaluSprite* TSkin::TBaluSpriteInstance::GetSprite()
{
	return sprite;
}

TSkin::TSkin(int bones_count)
{
	sprites_of_bones.resize(bones_count);
}

void TSkin::SetBoneSprite(int bone_index, TBaluSprite* sprite, TBaluTransform global)
{
	sprites_of_bones[bone_index].push_back(TBaluSpriteInstance(sprite));
	sprites_of_bones[bone_index].back().SetTransform(global);
}

void TSkin::SetBoneSprite(int bone_index, EngineInterface::IBaluSprite* sprite, TBaluTransform global)
{
	SetBoneSprite(bone_index, dynamic_cast<TBaluSprite*>(sprite), global);
}

int TSkin::GetBonesCount()
{
	return sprites_of_bones.size();
}

std::vector<TSkin::TBaluSpriteInstance>& TSkin::GetSpritesOfBone(int bone_index)
{
	return sprites_of_bones[bone_index];
}

TSkeleton::TSkeleton(TSkeleton&& right)
	:root(std::move(right.root))
	, bones(std::move(right.bones))
	, skins(std::move(right.skins))
{
	
}

TSkin* TSkeleton::CreateSkin()
{
	skins.push_back(std::make_unique<TSkin>(bones.size()));
	return skins.back().get();
}
void TSkeleton::DestroySkin(TSkin* skin)
{
	
}
void TSkeleton::DestroySkin(EngineInterface::ISkin* skin)
{
	DestroySkin(dynamic_cast<TSkin*>(skin));
}
int TSkeleton::GetSkinsCount()
{
	return skins.size();
}
TSkin* TSkeleton::GetSkin(int index)
{
	return skins[index].get();
}
TBone* TSkeleton::CreateBone(TBone* parent)
{
	if (parent == nullptr)
	{
		root = 0;
		bones.push_back(std::make_unique<TBone>(nullptr));
	}
	else
	{
		auto new_bone = std::make_unique<TBone>(parent);
		parent->AddChild(new_bone.get());
		bones.push_back(std::move(new_bone));
	}

	return bones.back().get();
}

EngineInterface::IBone* TSkeleton::CreateBone(EngineInterface::IBone* parent)
{
	return CreateBone(dynamic_cast<TBone*>(parent));
}

void TSkeleton::DestroyBone(TBone* bone)
{

}

void TSkeleton::DestroyBone(EngineInterface::IBone* bone)
{
	DestroyBone(dynamic_cast<TBone*>(bone));
}

int TSkeleton::GetBoneIndex(TBone* bone)
{
	for (int i = 0; i < bones.size(); i++)
	{
		if (bones[i].get() == bone)
			return i;
	}
	throw std::invalid_argument("Данная кость отсутсвует в скелете!");
}

int TSkeleton::GetBoneIndex(EngineInterface::IBone* bone)
{
	return GetBoneIndex(dynamic_cast<TBone*>(bone));
}

TBone* TSkeleton::GetRoot()
{
	if (root == -1)
		return nullptr;
	return bones[root].get();
}

std::vector<TBone*> TSkeleton::GetAllBones()
{
	std::vector<TBone*> result;
	result.reserve(bones.size());
	for (auto& v : bones)
		result.push_back(v.get());
	return result;
}
