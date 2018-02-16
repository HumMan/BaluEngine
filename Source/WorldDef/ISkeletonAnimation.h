#pragma once


namespace BaluEngine
{
	namespace WorldDef
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


		class ITrack
		{
		public:
			virtual ITrackFrame* CreateFrame(float time, float rotation) = 0;
		};


		class ITimeLine
		{
		public:
			virtual ITrack* CreateTrack(IBone* bone) = 0;
			virtual void DestroyTrack(ITrack* track) = 0;
			virtual void SetTimelineSize(float size) = 0;
		};

		class ISkeletonAnimation
		{
		public:
			virtual ITimeLine* CreateAnimation(std::string name) = 0;
		};
	}
}