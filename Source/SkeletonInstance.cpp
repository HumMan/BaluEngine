#include "SkeletonInstance.h"

TBoneInstance::TBoneInstance(TBoneInstance* parent, TBone* source)
{
	this->parent = parent;
	this->source = source;

	current_rotation = 0;

	for (int i = 0; i < source->GetChildrenCount(); i++)
	{
		children.push_back(std::make_unique<TBoneInstance>(this, source->GetChild(i)));
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
	TMatrix2 global_orient(*(TVec2*)&global.angle.GetXAxis(), *(TVec2*)&global.angle.GetYAxis());
	//TMatrix2 local_orient(*(TVec2*)&local.angle.GetXAxis(), *(TVec2*)&local.angle.GetYAxis());

	TVec2 result_pos = global_orient*local.position;

	return TBaluTransform(result_pos, TRot(global.angle.GetAngle() + local.angle.GetAngle()));
}

void TBoneInstance::UpdateTranform(TBaluTransform parent_transform)
{
	auto local = source->GetTransform();

	TMatrix2 global_orient(*(TVec2*)&parent_transform.angle.GetXAxis(), *(TVec2*)&parent_transform.angle.GetYAxis());
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

TSkinInstance::TSkinInstance(TSkin* source, TBaluInstance* parent, TResources* resources)
{
	sprites_of_bones.resize(source->GetBonesCount());
	for (int i = 0; i < sprites_of_bones.size(); i++)
	{
		auto& source_sprite_of_bones = source->GetSpritesOfBone(i);
		for (int k = 0; k < source_sprite_of_bones.size(); k++)
		{
			TBaluSprite* source(source_sprite_of_bones[k].GetSprite());
			TBaluTransform local(source_sprite_of_bones[k].GetTransform());

			sprites_of_bones[i].push_back(std::make_unique<TBaluSpriteInstance>(source, local, parent, resources));
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

void TSkinInstance::UpdateSpritesTransform(std::vector<TBoneInstance*> bones, TVec2 class_scale, TBaluTransform class_transform)
{
	for (int i = 0; i < sprites_of_bones.size(); i++)
	{
		for (int k = 0; k < sprites_of_bones[i].size(); k++)
		{
			sprites_of_bones[i][k]->UpdateTranform(bones[i]->GetGlobalTransform(), class_scale, class_transform);
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

TSkeletonInstance::TSkeletonInstance(TSkeleton* source,TBaluInstance* parent, TResources* resources)
{
	this->source = source;

	if (source->GetRoot() == nullptr)
		return;

	root = std::make_unique<TBoneInstance>(nullptr, source->GetRoot());

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
		skins.push_back(std::make_unique<TSkinInstance>(source->GetSkin(i), parent, resources));
	}
}

void TSkeletonInstance::UpdateTranform(TBaluTransform parent, TVec2 class_scale, TBaluTransform class_transform)
{
	if (root != nullptr)
	{
		root->UpdateTranform(parent);
		for (int i = 0; i < skins.size(); i++)
		{
			skins[i]->UpdateSpritesTransform(bones, class_scale, class_transform);
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