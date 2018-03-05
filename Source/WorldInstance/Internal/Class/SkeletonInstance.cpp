#include "ClassInstance.h"

#include "../Sprite/SpriteInstance.h"

using namespace BaluEngine;
using namespace BaluEngine::WorldInstance;
using namespace BaluEngine::WorldInstance::Internal;
using namespace BaluLib;

TBoneInstance::TBoneInstance(TBoneInstance* parent, WorldDef::IBone* source)
{
	this->parent = parent;
	this->source = source;

	current_rotation = 0;

	for (int i = 0; i < source->GetChildrenCount(); i++)
	{
		children.push_back(std::unique_ptr<TBoneInstance>(new TBoneInstance(this, source->GetChild(i))));
	}

}

int TBoneInstance::GetChildrenCount()
{
	return children.size();
}

TBoneInstance* TBoneInstance::GetChild(int index)
{
	return children[index].get();
}

void TBoneInstance::SetRotationAmount(float amount)
{
	current_rotation = amount;
}

WorldDef::IBone* TBoneInstance::GetSourceBone()
{
	return source;
}

WorldDef::TTransform FromLocalToGlobal(WorldDef::TTransform global, WorldDef::TTransform local)
{
	auto x_axis = global.angle.GetXAxis();
	auto y_axis = global.angle.GetYAxis();
	TMatrix2 global_orient(*(TVec2*)&x_axis, *(TVec2*)&y_axis);

	TVec2 result_pos = global_orient*local.position;

	return WorldDef::TTransform(result_pos, WorldDef::TRot(global.angle.GetAngle() + local.angle.GetAngle()));
}

void TBoneInstance::UpdateTranform(WorldDef::TTransform parent_transform)
{
	auto local = source->GetTransform();
	auto x_axis = parent_transform.angle.GetXAxis();
	auto y_axis = parent_transform.angle.GetYAxis();
	TMatrix2 global_orient(*(TVec2*)&x_axis, *(TVec2*)&y_axis);
	//global_orient.Transpose();

	global.position = parent_transform.position + global_orient*local.position;
	global.angle = WorldDef::TRot(parent_transform.angle.GetAngle() + local.angle.GetAngle() + current_rotation);

	for (int i = 0; i < children.size(); i++)
	{
		children[i]->UpdateTranform(global);
	}
}

WorldDef::TTransform TBoneInstance::GetGlobalTransform()
{
	return global;
}

TSkinInstance::TSkinInstance(WorldDef::ISkin* source, TResources* resources, ISceneObjectInstance* scene_object)
{
	sprites_of_bones.resize(source->GetBonesCount());
	for (int i = 0; i < sprites_of_bones.size(); i++)
	{
		auto& source_sprite_of_bones = source->IGetSpritesOfBone(i);
		for (int k = 0; k < source_sprite_of_bones.size(); k++)
		{
			sprites_of_bones[i].push_back(std::unique_ptr<ITransformedSpriteInstance>(new TTransformedSpriteInstance(source_sprite_of_bones[k], resources, scene_object)));
		}
	}
}

void TSkinInstance::QueryAABB(TAABB2 frustum, std::vector<ISpritePolygonInstance*>& results)
{
	for (int i = 0; i < sprites_of_bones.size(); i++)
	{
		for (int k = 0; k < sprites_of_bones[i].size(); k++)
		{
			if (dynamic_cast<TSpritePolygonInstance*>(sprites_of_bones[i][k]->GetPolygon())->IsEnable())
			{
				results.push_back(sprites_of_bones[i][k]->GetPolygon());
			}
		}
	}
}

void TSkinInstance::UpdateSpritesTransform(std::vector<TBoneInstance*> bones, WorldDef::TTransformWithScale class_transform)
{
	for (int i = 0; i < sprites_of_bones.size(); i++)
	{
		for (int k = 0; k < sprites_of_bones[i].size(); k++)
		{
			dynamic_cast<TTransformedSpriteInstance*>(sprites_of_bones[i][k].get())->UpdateTransform(class_transform.ToGlobal(WorldDef::TTransformWithScale(bones[i]->GetGlobalTransform(), TVec2(1, 1))));
		}
	}
}

void GatherBones(TBoneInstance* bone, std::vector<TBoneInstance*> &result)
{
	result.push_back(bone);
	for (int i = 0; i < bone->GetChildrenCount(); i++)
	{
		GatherBones(bone->GetChild(i), result);
	}
}

TSkeletonInstance::TSkeletonInstance(WorldDef::ISkeleton* source, TResources* resources, ISceneObjectInstance* scene_object)
{
	this->source = source;
	//source->AddChangesListener(this);
	if (source->GetRoot() == nullptr)
		return;

	root = std::unique_ptr<TBoneInstance>(new TBoneInstance(nullptr, source->GetRoot()));

	auto all_source_bones = source->GetAllBones();
	
	std::vector<TBoneInstance*> all_bones_unsorted;
	all_bones_unsorted.reserve(all_source_bones.size());

	GatherBones(root.get(), all_bones_unsorted);

	assert(all_bones_unsorted.size() == all_source_bones.size());

	std::vector<TBoneInstance*> all_bones_sorted;
	for (int i = 0; i < all_source_bones.size(); i++)
	{
		TBoneInstance* temp_bone(nullptr);
		for (int k = 0; k < all_bones_unsorted.size(); k++)
		{
			if (all_bones_unsorted[k]->GetSourceBone() == all_source_bones[i])
			{
				temp_bone = all_bones_unsorted[i];
				break;
			}
		}

		assert(temp_bone != nullptr);
		all_bones_sorted.push_back(temp_bone);
	}

	bones = all_bones_sorted;

	for (int i = 0; i < source->GetSkinsCount(); i++)
	{
		skins.push_back(std::unique_ptr<TSkinInstance>(new TSkinInstance(source->GetSkin(i), resources, scene_object)));
	}
}

TSkeletonInstance::~TSkeletonInstance()
{
	//source->RemoveChangesListener(this);
}

void TSkeletonInstance::UpdateTranform(WorldDef::TTransformWithScale class_transform)
{
	if (root != nullptr)
	{
		root->UpdateTranform(WorldDef::TTransform());
		for (int i = 0; i < skins.size(); i++)
		{
			skins[i]->UpdateSpritesTransform(bones, class_transform);
		}
	}
}

void TSkeletonInstance::QueryAABB(TAABB2 frustum, std::vector<ISpritePolygonInstance*>& results)
{
	for (int i = 0; i < skins.size(); i++)
	{
		skins[i]->QueryAABB(frustum, results);
	}
}

WorldDef::ISkeleton* TSkeletonInstance::GetSource()
{
	return source;
}

TBoneInstance* TSkeletonInstance::GetBone(int index)
{
	return bones[index];
}
