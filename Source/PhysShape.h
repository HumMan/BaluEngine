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


class TBaluCircleShape : public TBaluPhysShape
{
private:
	b2PolygonShape b2shape;
public:
	TBaluCircleShape(float radius);
	TBaluCircleShape(float radius, TVec2 pos);
	void BuildFixture(b2Body &body);
};

class TBaluBoxShape : public TBaluPhysShape
{
private:
	b2PolygonShape b2shape;
public:
	TBaluBoxShape(float width, float height);
	void BuildFixture(b2Body &body);
};
