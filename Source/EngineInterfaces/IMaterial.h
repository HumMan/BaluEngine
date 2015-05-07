
#ifndef BALU_ENGINE_DISABLE_PRAGMA_ONCE
#pragma once
#endif


#ifndef BALU_ENGINE_SCRIPT_CLASSES
#include "../../../BaluLib/Source/Math/vec.h"
#include "../../../BaluLib/Source/Math/matrix.h"
#include "../../../BaluLib/Source/BVolumes/OBB.h"

#include <string>

#ifndef BALU_ENGINE_DISABLE_PRAGMA_ONCE
#include "IProperties.h"
#endif

namespace EngineInterface
{
	class TScreen;
	class TView;
}
#endif

namespace EngineInterface
{

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	struct TRot
	{
		TRot() {}
		TRot(float s, float c)
		{
			this->s = s;
			this->c = c;
		}
		explicit TRot(float angle)
		{
			Set(angle);
		}
		explicit TRot(const TOBB2& box)
		{
			c = box.orient[0][0];
			s = box.orient[0][1];
		}
		void Set(float angle)
		{
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
#endif

#ifdef BALU_ENGINE_SCRIPT_CLASSES	
	BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapValue, TRot, "TRot");
	MUnpackA1(TYPE, Set, WrapValue<float>);
	MUnpackA0(TYPE, SetIdentity);
	MUnpackCRA0(WrapValue<float>, TYPE, GetAngle);
	BALU_ENGINE_SCRIPT_END_CLASS;
#endif


#ifndef BALU_ENGINE_SCRIPT_CLASSES
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
		TVec2 ToGlobal(TVec2 p)
		{
			return GetOrientation()*p + position;
		}
		TVec2 ToLocal(TVec2 p)
		{
			return GetOrientation().TransMul((p - position));
		}

		TOBB2 ToGlobal(TOBB2 box)
		{
			//TODO
			return TOBB2(box.pos + position, GetOrientation()*box.orient, box.local);
		}
		TOBB2 ToGlobal(TAABB2 box)
		{
			//TODO
			return TOBB2(position, GetOrientation(), box);
		}
		TBaluTransform ToGlobal(TBaluTransform local)
		{
			TBaluTransform global;
			global.position = position + GetOrientation()*local.position;
			global.angle = TRot(angle.GetAngle() + local.angle.GetAngle());
			return global;
		}
		TVec2 Transform(TVec2 vertex, TVec2 scale)
		{
			return this->ToGlobal((vertex).ComponentMul(scale));
		}
	};
#endif

#ifdef BALU_ENGINE_SCRIPT_CLASSES	
	BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapValue, TBaluTransform, "TTransform");
	MUnpackRA2(WrapValue<TVec2>, TYPE, Transform, WrapValue<TVec2>, WrapValue<TVec2>);
	BALU_ENGINE_SCRIPT_END_CLASS;
#endif

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	//TODO
	class TBaluTransformWithScale
	{
	public:
		TBaluTransform transform;
		TVec2 scale;
		TBaluTransformWithScale()
		{
			scale = TVec2(1, 1);
		}
		TBaluTransformWithScale(TBaluTransform transform, TVec2 scale)
		{
			this->transform = transform;
			this->scale = scale;
		}
		//TVec2 ToGlobal(TVec2 p)
		//{
		//	return GetOrientation()*p + position;
		//}
		//TVec2 ToLocal(TVec2 p)
		//{
		//	return GetOrientation().TransMul((p - position));
		//}

		//TOBB2 ToGlobal(TOBB2 box)
		//{
		//	//TODO
		//	return TOBB2(box.pos + position, GetOrientation()*box.orient, box.local);
		//}
		//TOBB2 ToGlobal(TAABB2 box)
		//{
		//	//TODO
		//	return TOBB2(position, GetOrientation(), box);
		//}
		//TBaluTransform ToGlobal(TBaluTransform local)
		//{
		//	TBaluTransform global;
		//	global.position = position + GetOrientation()*local.position;
		//	global.angle = TRot(angle.GetAngle() + local.angle.GetAngle());
		//	return global;
		//}
		//TVec2 Transform(TVec2 vertex)
		//{
		//	return tranform.ToGlobal((vertex).ComponentMul(scale));
		//}
	};
#endif

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	class IViewport
	{
	public:
		virtual void SetTransform(TBaluTransform transform) = 0;
		virtual TBaluTransform GetTransform() = 0;
		virtual void SetAspectRatio(float aspect) = 0;
		virtual void SetWidth(float width) = 0;
		virtual TAABB2 GetAABB() = 0;
		virtual void SetSize(TVec2 size) = 0;
		virtual TVec2 GetSize() = 0;
	};
#endif

#ifdef BALU_ENGINE_SCRIPT_CLASSES	
	BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, IViewport, "IViewport");
	MUnpackA1(TYPE, SetSize, WrapValue<TVec2>);
	MUnpackRA0(WrapValue<TVec2>, TYPE, GetSize);
	BALU_ENGINE_SCRIPT_END_CLASS;
#endif

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	class IBaluMaterial
	{
	public:
		static std::string GetDefaultName()
		{
			return "material";
		}
		virtual std::string GetName() = 0;
		virtual void SetImagePath(std::string image_path) = 0;
		virtual std::string GetImagePath() = 0;
		virtual void SetColor(TVec4 color) = 0;
	};
#endif

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	struct TDrawingHelperContext
	{
		TScreen* screen;
		TView* view;
		EngineInterface::IViewport* viewport;
		TDrawingHelperContext()
		{
			screen = nullptr;
			view = nullptr;
			viewport = nullptr;
		}
	};
#endif

}

