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
	children.push_back(std::unique_ptr<TBone>(bone));
}
int TBone::GetChildrenCount()
{
	return children.size();
}
TBone* TBone::GetChild(int index)
{
	return children[index].get();
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

int TSkin::GetBonesCount()
{
	return sprites_of_bones.size();
}

std::vector<TSkin::TBaluSpriteInstance>& TSkin::GetSpritesOfBone(int bone_index)
{
	return sprites_of_bones[bone_index];
}

TSkin* TSkeleton::CreateSkin()
{
	skins.push_back(std::make_unique<TSkin>(bones.size()));
	return skins.back().get();
}
void TSkeleton::DestroySkin(TSkin* skin)
{
	
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
		root = std::make_unique<TBone>(nullptr);
		bones.push_back(root.get());
	}
	else
	{
		auto new_bone = new TBone(parent);
		parent->AddChild(new_bone);
		bones.push_back(new_bone);
	}

	return bones.back();
}
void TSkeleton::DestroyBone(TBone* bone)
{

}

int TSkeleton::GetBoneIndex(TBone* bone)
{
	for (int i = 0; i < bones.size(); i++)
	{
		if (bones[i] == bone)
			return i;
	}
	throw std::invalid_argument("Данная кость отсутсвует в скелете!");
}

TBone* TSkeleton::GetRoot()
{
	return root.get();
}

std::vector<TBone*> TSkeleton::GetAllBones()
{
	return bones;
}