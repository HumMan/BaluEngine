#pragma once

#include "SkeletonAnimation.h"
#include "SkeletonInstance.h"

class TTimeLineInstance
{
private:
	TTimeLine* source;

	float current_time;
	//float alpha;
	float active_alpha;
	//bool smooth_stop_active;
	bool loop;
public:
	TTimeLineInstance(TTimeLine* source);
	void SetAlpha();
	bool IsActive();
	void PlayOnce();
	void PlayLoop();
	//void SmoothStop();
};

class TSkeletonAnimationInstance
{
private:
	TSkeletonAnimation* source;
	TSkeletonInstance* skeleton;

	std::vector<std::unique_ptr<TTimeLineInstance>> active_animations;
public:
	TSkeletonAnimationInstance(TSkeletonInstance* skeleton, TSkeletonAnimation* source);
	void PlayAnimation(std::string name, float alpha);
	void StopAnimation(std::string name);
};