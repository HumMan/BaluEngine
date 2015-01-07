#pragma once

#include "Skeleton.h"

#include <set>

class TInterpolateCurve
{
	enum Type
	{
		Linear,
		Stepped,
		Curve
	};
	//std::vector<TCurveSegment> segments;
};



class TTrackFrame
{
public:
	//int index;
	float time;
	float rotation;
	TTrackFrame()
	{
		time = 0;
		rotation = 0;
	}
	TTrackFrame(float time)
	{
		this->time = time;
		this->rotation = 0;
	}
};

class TFrameComparer
{
public:
	bool operator() (const TTrackFrame& lhs, const TTrackFrame& rhs) const
	{
		//return lhs.index < rhs.index;
		return lhs.time < rhs.time;
	}
};

class TTrack
{
private:
	TBone* bone;
	std::set<TTrackFrame, TFrameComparer> frames;
public:
	TTrack(TBone* bone);
	const TTrackFrame* CreateFrame(float time, float rotation);
	void DestroyFrame(TTrackFrame* frame);
	TBone* GetBone();
	std::set<TTrackFrame, TFrameComparer>& GetFrames();
};

class TTimeLine
{
private:
	std::vector<std::unique_ptr<TTrack>> tracks;
	std::string name;
	float timeline_size;
public:
	TTimeLine(std::string name);
	TTrack* CreateTrack(TBone* bone);
	void DestroyTrack(TTrack* track);
	void SetTimelineSize(float size);
	float GetTimelineSize();
	std::string GetName();
	int GetTracksCount();
	TTrack* GetTrack(int index);
};

class TSkeletonAnimation
{
private:
	std::vector<std::unique_ptr<TTimeLine>> animations;
	TSkeleton* skeleton;
public:
	TSkeletonAnimation();
	TSkeletonAnimation(TSkeleton* skeleton);
	TTimeLine* CreateAnimation(std::string name);
	void DestroyAnimation(TTimeLine* animation);
	int GetAnimationsCount();
	TTimeLine* GetAnimation(int index);
};
