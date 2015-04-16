#include "SkeletonAnimationInstance.h"

TTrackInstance::TTrackInstance(TBoneInstance* bone, TTrack* source)
{
	this->bone = bone;
	this->source = source;
}

float Blend(float time0, float value0, float time1, float value1, float time)
{
	assert(time1 >= time0);
	float length = time1 - time0;
	float t = time - time0;
	float alpha = t / length;
	return value0*(1 - alpha) + value1*alpha;
}

void TTrackInstance::Update(float time, float timeline_size)
{
	auto& frames = source->GetFrames();
	if (frames.size() > 1)
	{
		auto lower_it = frames.lower_bound(TTrackFrame(time));
		float amount;

		if (lower_it == frames.end())
		{
			auto t0 = std::prev(frames.end());
			auto t1 = frames.begin();
			amount = Blend(t0->time, t0->rotation, timeline_size, t1->rotation, time);
		}
		else if (lower_it == frames.begin())
		{
			amount = lower_it->rotation;
		}
		else
		{
			auto t0 = std::prev(lower_it);
			auto t1 = lower_it;
			amount = Blend(t0->time, t0->rotation, t1->time, t1->rotation, time);
		}
		bone->SetRotationAmount(amount);
	}
	else if (frames.size() == 1)
	{
		bone->SetRotationAmount(frames.begin()->rotation);
	}
}

TTimeLineInstance::TTimeLineInstance(TSkeletonInstance* skeleton, TTimeLine* source)
{
	this->source = source;
	is_active = false;

	for (int i = 0; i < source->GetTracksCount(); i++)
	{
		auto source_track = source->GetTrack(i);
		int bone_index = skeleton->GetSource()->GetBoneIndex(source_track->GetBone());
		tracks.push_back(std::make_unique<TTrackInstance>(skeleton->GetBone(bone_index), source_track));
	}
}
void TTimeLineInstance::SetAlpha()
{

}
bool TTimeLineInstance::IsActive()
{
	return is_active;
}
void TTimeLineInstance::PlayOnce()
{

}
void TTimeLineInstance::PlayLoop()
{
	if (is_active)
	{
		current_time = 0;
	}
	else
	{
		current_time = 0;
		is_active = true;
	}
}

void TTimeLineInstance::Stop()
{
	if (is_active)
	{
		current_time = 0;
		is_active = false;
	}
	else
	{
		current_time = 0;
	}
}

void TTimeLineInstance::Step(float step)
{
	current_time += step;

	auto temp = source->GetTimelineSize() * (int)(current_time / source->GetTimelineSize());
	current_time -= temp;

	for (int i = 0; i < tracks.size(); i++)
	{
		tracks[i]->Update(current_time, source->GetTimelineSize());
	}
}

TTimeLine* TTimeLineInstance::GetSource()
{
	return source;
}

TSkeletonAnimationInstance::TSkeletonAnimationInstance(TSkeletonInstance* skeleton, TSkeletonAnimation* source)
{
	this->skeleton = skeleton;
	this->source = source;

	
}

void TSkeletonAnimationInstance::Init()
{
	for (int i = 0; i < source->GetAnimationsCount(); i++)
	{
		animations.push_back(std::make_unique<TTimeLineInstance>(skeleton, source->GetAnimation(i)));
	}
}

void TSkeletonAnimationInstance::Update(float step)
{
	for (int i = 0; i < animations.size(); i++)
	{
			if (animations[i]->IsActive())
			{
				animations[i]->Step(step);
			}
	}
}

void TSkeletonAnimationInstance::PlayAnimation(std::string name, float alpha)
{
	for (int i = 0; i < animations.size(); i++)
	{
		if (animations[i]->GetSource()->GetName() == name)
		{
			if (!animations[i]->IsActive())
			{
				animations[i]->PlayLoop();
			}
		}
	}
}

void TSkeletonAnimationInstance::StopAnimation(std::string name)
{
	for (int i = 0; i < animations.size(); i++)
	{
		if (animations[i]->GetSource()->GetName() == name)
		{
			if (animations[i]->IsActive())
			{
				animations[i]->Stop();
			}
		}
	}
}