#pragma once

#include <map>
#include <set>

#include <WorldObjects/Sprite/ISprite.h>

#include "ISkeleton.h"

namespace EngineInterface
{

	class ITrackFrame
	{
	public:
	};

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

#ifdef BALUENGINEDLL_EXPORTS
	class TTrackFrame : public ITrackFrame
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
		void Save(pugi::xml_node& parent_node, const int version) const;
		void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world);
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
#endif

	class ITrack
	{
	public:
		virtual ITrackFrame* CreateFrame(float time, float rotation) = 0;
	};

#ifdef BALUENGINEDLL_EXPORTS
	class TTrack : public ITrack
	{
	private:
		TBone* bone;
		std::set<TTrackFrame, TFrameComparer> frames;
	public:
		TTrack()
		{
			bone = nullptr;
		}
		TTrack(TBone* bone);
		TTrackFrame* CreateFrame(float time, float rotation);
		void DestroyFrame(TTrackFrame* frame);
		TBone* GetBone();
		std::set<TTrackFrame, TFrameComparer>& GetFrames();
		void Save(pugi::xml_node& parent_node, const int version, TSkeleton* skeleton);
		void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world, TSkeleton* skeleton);
	};
#endif

	class ITimeLine
	{
	public:
		virtual ITrack* CreateTrack(IBone* bone) = 0;
		virtual void DestroyTrack(ITrack* track) = 0;
		virtual void SetTimelineSize(float size) = 0;
	};

#ifdef BALUENGINEDLL_EXPORTS
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
		TTrack* CreateTrack(TBone* bone);
		ITrack* CreateTrack(IBone* bone);
		void DestroyTrack(TTrack* track);
		void DestroyTrack(ITrack* track);
		void SetTimelineSize(float size);
		float GetTimelineSize();
		std::string GetName();
		int GetTracksCount();
		TTrack* GetTrack(int index);
		void Save(pugi::xml_node& parent_node, const int version, TSkeleton* skeleton);
		void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world, TSkeleton* skeleton);
	};
#endif

	class ISkeletonAnimation
	{
	public:
		virtual ITimeLine* CreateAnimation(std::string name) = 0;
	};

#ifdef BALUENGINEDLL_EXPORTS
	class TSkeletonAnimation : public ISkeletonAnimation
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

		void Save(pugi::xml_node& parent_node, const int version);
		void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world);
	};
#endif
}