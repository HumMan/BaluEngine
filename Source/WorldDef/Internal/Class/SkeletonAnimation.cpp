#include "SkeletonAnimation.h"

#include "../Sprite/Sprite.h"

using namespace BaluEngine::WorldDef;
using namespace BaluEngine::WorldDef::Internal;
using namespace BaluLib;

TTrack::TTrack(IBone* bone)
{
	this->bone = bone;
}

TTrackFrame* TTrack::CreateFrame(float time, float rotation)
{
	TTrackFrame temp;
	//temp.index = 0;
	temp.time = time;
	temp.rotation = rotation;
	auto it = frames.insert(temp);
	return (TTrackFrame*) &(*(it.first));
}

void TTrack::DestroyFrame(TTrackFrame* frame)
{

}

IBone* TTrack::GetBone()
{
	return bone;
}

std::set<TTrackFrame, TFrameComparer>& TTrack::GetFrames()
{
	return frames;
}

TTimeLine::TTimeLine(std::string name)
{
	this->name = name;
}

TTrack* TTimeLine::CreateTrack(IBone* bone)
{
	tracks.push_back(std::unique_ptr<TTrack>(new TTrack(bone)));
	return tracks.back().get();
}


void TTimeLine::DestroyTrack(TTrack* track)
{

}

void TTimeLine::DestroyTrack(ITrack* track)
{
	DestroyTrack(dynamic_cast<TTrack*>(track));
}

void TTimeLine::SetTimelineSize(float size)
{
	this->timeline_size = size;
}

float TTimeLine::GetTimelineSize()
{
	return timeline_size;
}

std::string TTimeLine::GetName()
{
	return name;
}

int TTimeLine::GetTracksCount()
{
	return tracks.size();
}

TTrack* TTimeLine::GetTrack(int index)
{
	return tracks[index].get();
}

TSkeletonAnimation::TSkeletonAnimation()
{
	skeleton = nullptr;
}
TSkeletonAnimation::TSkeletonAnimation(ISkeleton* skeleton)
{
	this->skeleton = skeleton;
}
TTimeLine* TSkeletonAnimation::CreateAnimation(std::string name)
{
	animations.push_back(std::unique_ptr<TTimeLine>(new TTimeLine(name)));
	return animations.back().get();
}
void TSkeletonAnimation::DestroyAnimation(TTimeLine* animation)
{

}

int TSkeletonAnimation::GetAnimationsCount()
{
	return animations.size();
}

TTimeLine* TSkeletonAnimation::GetAnimation(int index)
{
	return animations[index].get();
}
