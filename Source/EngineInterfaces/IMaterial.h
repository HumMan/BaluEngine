#pragma once

#include "../../BaluLib/Source/Math/vec.h"
#include "../../BaluLib/Source/Math/matrix.h"

#include <string>

struct TRot
{
	TRot() {}
	explicit TRot(float angle)
	{
		/// TODO_ERIN optimize
		s = sinf(angle);
		c = cosf(angle);
	}
	void Set(float angle)
	{
		/// TODO_ERIN optimize
		s = sinf(angle);
		c = cosf(angle);
	}
	void SetIdentity()
	{
		s = 0.0f;
		c = 1.0f;
	}
	float GetAngle() const
	{
		return atan2(s, c);
	}
	TVec2 GetXAxis() const
	{
		return TVec2(c, s);
	}
	TVec2 GetYAxis() const
	{
		return TVec2(-s, c);
	}
	float s, c;
};

class TBaluTransform
{
public:
	TVec2 position;
	TRot angle;
	TBaluTransform()
	{
		position = TVec2(0, 0);
		angle = TRot(0);
	}
	TBaluTransform(TVec2 position, TRot angle)
	{
		this->position = position;
		this->angle = angle;
	}
	TMatrix2 GetOrientation()
	{
		return TMatrix2(angle.GetXAxis(), angle.GetYAxis());
	}
};


namespace EngineInterface
{
	class IBaluMaterial
	{
	public:
		virtual void SetImagePath(std::string image_path) = 0;
		virtual std::string GetImagePath() = 0;
		virtual void SetColor(TVec4 color) = 0;
	};
}