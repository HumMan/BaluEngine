#pragma once

class TBaluPhysShape
{
protected:
	TBaluTransform phys_shape_transform;
public:
	virtual ~TBaluPhysShape(){}
	virtual void BuildFixture(b2Body &body) = 0;
};

class TBaluPolygonShape : public TBaluPhysShape
{
private:
	b2PolygonShape b2shape;
public:

	void BuildFixture(b2Body &body);
};
