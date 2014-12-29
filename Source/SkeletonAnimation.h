class TInterpolateCurve
{
	enum Type
	{
		Linear,
		Stepped,
		Curve
	};
	//std::vector<TCurveSegment> segments;
}

class TFrameComparer
{
	
}

class TFrame
{
	int index;
	float time;
	float rotation;
}

class TTrack
{
	TSkeletonBone* bone;
	std::set<TFrame, TFrameComparer> frames;
}

class TTimeLine
{
	std::vector<TTrack> tracks; //по треку на каждый объект (кость)
}

class TSkeletonAnimation
{
}

