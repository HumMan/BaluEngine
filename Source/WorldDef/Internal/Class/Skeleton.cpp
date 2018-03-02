#include "Skeleton.h"

#include "../Sprite/Sprite.h"

using namespace BaluEngine::WorldDef;
using namespace BaluEngine::WorldDef::Internal;
using namespace BaluLib;

TBone::TBone(TBone* parent)
{
	this->parent = parent;
}

void TBone::SetTransform(TTransform local)
{
	this->local = local;
}

TTransform TBone::GetTransform()
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
	return dynamic_cast<TBone*>(children[index]);
}

TSkin::TSkin(int bones_count)
{
	sprites_of_bones.resize(bones_count);
}

void TSkin::SetBoneSprite(int bone_index, TSprite* sprite, TTransform global)
{
	sprites_of_bones[bone_index].push_back(TTransformedSprite(sprite));
	sprites_of_bones[bone_index].back().SetTransform(global);
}

void TSkin::SetBoneSprite(int bone_index, ISprite* sprite, TTransform global)
{
	SetBoneSprite(bone_index, dynamic_cast<TSprite*>(sprite), global);
}

int TSkin::GetBonesCount()
{
	return sprites_of_bones.size();
}

std::vector<TTransformedSprite>& TSkin::GetSpritesOfBone(int bone_index)
{
	return sprites_of_bones[bone_index];
}

ISkin* TSkeleton::CreateSkin()
{
	skins.push_back(std::unique_ptr<TSkin>(new TSkin(bones.size())));
	return skins.back().get();
}

void TSkeleton::DestroySkin(ISkin* skin)
{
	DestroySkin(dynamic_cast<TSkin*>(skin));
}
int TSkeleton::GetSkinsCount()const
{
	return skins.size();
}
ISkin* TSkeleton::GetSkin(int index)const
{
	return skins[index].get();
}
IBone* TSkeleton::CreateBone(IBone* _parent)
{
	auto parent = dynamic_cast<TBone*>(_parent);
	if (parent == nullptr)
	{
		root = 0;
		bones.push_back(std::unique_ptr<TBone>(new TBone(nullptr)));
	}
	else
	{
		auto new_bone = std::unique_ptr<TBone>(new TBone(parent));
		parent->AddChild(new_bone.get());
		bones.push_back(std::move(new_bone));
	}

	return bones.back().get();
}

void TSkeleton::DestroyBone(IBone* bone)
{
	DestroyBone(dynamic_cast<TBone*>(bone));
}

int TSkeleton::GetBoneIndex(const IBone* bone)const
{
	for (int i = 0; i < bones.size(); i++)
	{
		if (bones[i].get() == bone)
			return i;
	}
	throw std::invalid_argument("Данная кость отсутсвует в скелете!");
}

IBone* TSkeleton::GetRoot()const
{
	if (root == -1)
		return nullptr;
	return bones[root].get();
}

std::vector<IBone*> TSkeleton::GetAllBones()const
{
	std::vector<IBone*> result;
	result.reserve(bones.size());
	for (auto& v : bones)
		result.push_back(v.get());
	return result;
}
