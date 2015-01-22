#pragma once

#include "SkeletonAnimation.h"
#include "SkeletonInstance.h"

class TTrackInstance
{
private:
	TBoneInstance* bone;
	TTrack* source;
	//std::set<TTrackFrame, TFrameComparer> frames;
public:
	TTrackInstance(TBoneInstance* bone, TTrack* source);
	void Update(float time, float timeline_size);
};

class TTimeLineInstance
{
private:
	TTimeLine* source;

	std::vector<std::unique_ptr<TTrackInstance>> tracks;
	float current_time;
	//float alpha;
	float active_alpha;
	//bool smooth_stop_active;
	bool loop;
	bool is_active;
public:
	TTimeLineInstance(TSkeletonInstance* skeleton, TTimeLine* source);
	void SetAlpha();
	bool IsActive();
	void PlayOnce();
	void PlayLoop();
	void Stop();
	//void SmoothStop();
	void Step(float step);
	TTimeLine* GetSource();
};

class TSkeletonAnimationInstance: public EngineInterface::ISkeletonAnimationInstance
{
private:
	TSkeletonAnimation* source;
	TSkeletonInstance* skeleton;

	std::vector<std::unique_ptr<TTimeLineInstance>> animations;
public:
	TSkeletonAnimationInstance(TSkeletonInstance* skeleton, TSkeletonAnimation* source);
	void Update(float step);
	void PlayAnimation(std::string name, float alpha);
	void StopAnimation(std::string name);
};