#pragma once

#include "../../Interface.h"


namespace BaluEngine
{
	namespace WorldInstance
	{
		namespace Internal
		{

			class TTrackInstance
			{
			private:
				TBoneInstance * bone;
				WorldDef::ITrack* source;
				//std::set<TTrackFrame, TFrameComparer> frames;
			public:
				TTrackInstance(TBoneInstance* bone, WorldDef::ITrack* source);
				void Update(float time, float timeline_size);
			};

			class TTimeLineInstance
			{
			private:
				WorldDef::ITimeLine * source;

				std::vector<std::unique_ptr<TTrackInstance>> tracks;
				float current_time;
				//float alpha;
				float active_alpha;
				//bool smooth_stop_active;
				bool loop;
				bool is_active;
			public:
				TTimeLineInstance(TSkeletonInstance* skeleton, WorldDef::ITimeLine* source);
				void SetAlpha();
				bool IsActive();
				void PlayOnce();
				void PlayLoop();
				void Stop();
				//void SmoothStop();
				void Step(float step);
				WorldDef::ITimeLine* GetSource();
			};

			class TSkeletonAnimationInstance : public ISkeletonAnimationInstance//, public IChangeListener
			{
			private:
				WorldDef::ISkeletonAnimation * source;
				TSkeletonInstance* skeleton;

				std::vector<std::unique_ptr<TTimeLineInstance>> animations;

				void Init();
			public:
				TSkeletonAnimationInstance(TSkeletonInstance* skeleton, WorldDef::ISkeletonAnimation* source);
				~TSkeletonAnimationInstance();

				void Update(float step);
				void PlayAnimation(const std::string& name, float alpha);
				void StopAnimation(const std::string& name);
			};
		}
	}
}