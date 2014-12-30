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
	int index;
	float time;
	float rotation;
};

class TFrameComparer
{
public:
	bool operator() (const TTrackFrame& lhs, const TTrackFrame& rhs) const
	{
		return lhs.index < rhs.index;
	}
};

class TTrack
{
private:
	TBone* bone;
	std::set<TTrackFrame, TFrameComparer> frames;
public:
	TTrack(TBone* bone);
	TTrackFrame* CreateFrame(float time, float rotation);
	void DestroyFrame(TTrackFrame* frame);
};

class TTimeLine
{
private:
	std::vector<TTrack> tracks;
public:
	TTimeLine(std::string name);
	TTrack* CreateTrack(TBone* bone);
	void DestroyTrack(TTrack* track);
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
};

