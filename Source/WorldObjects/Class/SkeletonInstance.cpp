#include "IClass.h"
#include "IClassInstance.h"

using namespace EngineInterface;

TBoneInstance::TBoneInstance(TBoneInstance* parent, TBone* source)
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

TBone* TBoneInstance::GetSourceBone()
{
	return source;
}

TBaluTransform FromLocalToGlobal(TBaluTransform global, TBaluTransform local)
{
	auto x_axis = global.angle.GetXAxis();
	auto y_axis = global.angle.GetYAxis();
	TMatrix2 global_orient(*(TVec2*)&x_axis, *(TVec2*)&y_axis);

	TVec2 result_pos = global_orient*local.position;

	return TBaluTransform(result_pos, TRot(global.angle.GetAngle() + local.angle.GetAngle()));
}

void TBoneInstance::UpdateTranform(TBaluTransform parent_transform)
{
	auto local = source->GetTransform();
	auto x_axis = parent_transform.angle.GetXAxis();
	auto y_axis = parent_transform.angle.GetYAxis();
	TMatrix2 global_orient(*(TVec2*)&x_axis, *(TVec2*)&y_axis);
	//global_orient.Transpose();

	global.position = parent_transform.position + global_orient*local.position;
	global.angle = TRot(parent_transform.angle.GetAngle() + local.angle.GetAngle() + current_rotation);

	for (int i = 0; i < children.size(); i++)
	{
		children[i]->UpdateTranform(global);
	}
}

TBaluTransform TBoneInstance::GetGlobalTransform()
{
	return global;
}

TSkinInstance::TSkinInstance(TSkin* source, TResources* resources, TSceneObjectInstance* scene_object)
{
	sprites_of_bones.resize(source->GetBonesCount());
	for (int i = 0; i < sprites_of_bones.size(); i++)
	{
		auto& source_sprite_of_bones = source->GetSpritesOfBone(i);
		for (int k = 0; k < source_sprite_of_bones.size(); k++)
		{
			sprites_of_bones[i].push_back(std::unique_ptr<TBaluTransformedSpriteInstance>(new TBaluTransformedSpriteInstance(&source_sprite_of_bones[k], resources, scene_object)));
		}
	}
}

void TSkinInstance::QueryAABB(TAABB2 frustum, std::vector<TBaluSpritePolygonInstance*>& results)
{
	for (int i = 0; i < sprites_of_bones.size(); i++)
	{
		for (int k = 0; k < sprites_of_bones[i].size(); k++)
		{
			if (sprites_of_bones[i][k]->GetPolygon()->IsEnable())
			{
				results.push_back(sprites_of_bones[i][k]->GetPolygon());
			}
		}
	}
}

void TSkinInstance::UpdateSpritesTransform(std::vector<TBoneInstance*> bones, TBaluTransformWithScale class_transform)
{
	for (int i = 0; i < sprites_of_bones.size(); i++)
	{
		for (int k = 0; k < sprites_of_bones[i].size(); k++)
		{
			sprites_of_bones[i][k]->UpdateTransform(class_transform.ToGlobal(TBaluTransformWithScale(bones[i]->GetGlobalTransform(), TVec2(1, 1))));
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

TSkeletonInstance::TSkeletonInstance(TSkeleton* source, TResources* resources, TSceneObjectInstance* scene_object)
{
	this->source = source;
	source->AddChangesListener(this);
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
		skins.push_back(std::unique_ptr<TSkinInstance>(new TSkinInstance(source->GetSkin(i), resources,scene_object)));
	}
}

TSkeletonInstance::~TSkeletonInstance()
{
	source->RemoveChangesListener(this);
}

void TSkeletonInstance::UpdateTranform(TBaluTransformWithScale class_transform)
{
	if (root != nullptr)
	{
		root->UpdateTranform(TBaluTransform());
		for (int i = 0; i < skins.size(); i++)
		{
			skins[i]->UpdateSpritesTransform(bones, class_transform);
		}
	}
}

void TSkeletonInstance::QueryAABB(TAABB2 frustum, std::vector<TBaluSpritePolygonInstance*>& results)
{
	for (int i = 0; i < skins.size(); i++)
	{
		skins[i]->QueryAABB(frustum, results);
	}
}

TSkeleton* TSkeletonInstance::GetSource()
{
	return source;
}

TBoneInstance* TSkeletonInstance::GetBone(int index)
{
	return bones[index];
}
