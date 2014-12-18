#pragma once

#include "PhysShape.h"

class TBaluPhysShapeInstance
{
protected:
	TBaluPhysShape* source;
	TBaluTransform global;
public:
	virtual ~TBaluPhysShapeInstance(){}
	virtual void BuildFixture(b2Body &body) = 0;
};


class TBaluPolygonShapeInstance : public TBaluPhysShapeInstance
{
private:
	TBaluPolygonShape* source;
	b2PolygonShape b2shape;
public:

	void BuildFixture(b2Body &body);
};
