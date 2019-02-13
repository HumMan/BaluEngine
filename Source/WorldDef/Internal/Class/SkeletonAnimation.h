#pragma once

#include "../../Interface.h"

#include "Skeleton.h"

namespace BaluEngine
{
	namespace WorldDef
	{
		namespace Internal
		{

			

			class TTrack : public ITrack
			{
			private:
				IBone * bone;
				std::set<TTrackFrame, TFrameComparer> frames;
			public:
				TTrack()
				{
					bone = nullptr;
				}
				TTrack(IBone* bone);
				TTrackFrame CreateFrame(float time, float rotation);
				void DestroyFrame(TTrackFrame* frame);
				IBone* GetBone();
				std::set<TTrackFrame, TFrameComparer>& GetFrames();
				void Save(pugi::xml_node& parent_node, const int version, ISkeleton* skeleton);
				void Load(const pugi::xml_node& instance_node, const int version, IWorld* world, ISkeleton* skeleton);
			};

			class TTimeLine : public ITimeLine
			{
			private:
				std::vector<std::unique_ptr<TTrack>> tracks;
				std::string name;
				float timeline_size;
			public:
				TTimeLine()
				{
				}
				TTimeLine(std::string name);
				TTrack* CreateTrack(IBone* bone);
				void DestroyTrack(TTrack* track);
				void DestroyTrack(ITrack* track);
				void SetTimelineSize(float size);
				float GetTimelineSize();
				std::string GetName();
				int GetTracksCount();
				TTrack* GetTrack(int index);
				void Save(pugi::xml_node& parent_node, const int version, ISkeleton* skeleton);
				void Load(const pugi::xml_node& instance_node, const int version, IWorld* world, ISkeleton* skeleton);
			};

			class TSkeletonAnimation : public ISkeletonAnimation, public ISerializable
			{
			private:
				std::vector<std::unique_ptr<TTimeLine>> animations;
				ISkeleton* skeleton;
			public:
				TSkeletonAnimation();
				TSkeletonAnimation(ISkeleton* skeleton);
				TTimeLine* CreateAnimation(std::string name);
				void DestroyAnimation(TTimeLine* animation);
				int GetAnimationsCount();
				TTimeLine* GetAnimation(int index);

				void Save(pugi::xml_node& parent_node, const int version)const;
				void Load(const pugi::xml_node& instance_node, const int version, IWorld* world);
			};
		}
	}
}