#pragma once


namespace BaluEngine
{
	namespace WorldDef
	{

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
			//void Save(pugi::xml_node& parent_node, const int version) const;
			//void Load(const pugi::xml_node& instance_node, const int version, IWorld* world);
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


		class ITrack
		{
		public:
			virtual TTrackFrame CreateFrame(float time, float rotation) = 0;
			virtual std::set<TTrackFrame, TFrameComparer>& GetFrames()=0;
			virtual IBone* GetBone()=0;
		};


		class ITimeLine
		{
		public:
			virtual ITrack* CreateTrack(IBone* bone) = 0;
			virtual void DestroyTrack(ITrack* track) = 0;
			virtual void SetTimelineSize(float size) = 0;
			virtual float GetTimelineSize()=0;
			virtual std::string GetName() = 0;
			virtual int GetTracksCount()=0;
			virtual ITrack* GetTrack(int index)=0;
		};

		class ISkeletonAnimation
		{
		public:
			virtual ITimeLine* CreateAnimation(std::string name) = 0;
			virtual ITimeLine* GetAnimation(int index)=0;
			virtual int GetAnimationsCount()=0;
		};
	}
}