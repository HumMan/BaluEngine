#include "IMaterial.h"

#include <memory>

namespace BaluEngineWrapper
{

	public value class TVecCs
	{
	internal:
		float x, y;
		TVec2 Unpack()
		{
			return TVec2(x, y);
		}
		void Pack(TVec2 value)
		{
			x = value[0];
			y = value[1];
		}
	};

	public ref class TAABBCs
	{
	internal:
		TAABB2* value;
	public:
		TAABBCs()
		{
			value = new TAABB2();
		}
		~TAABBCs()
		{
			delete value;
		}
	};

	public ref class TOBBCs
	{
	internal:
		TOBB2* value;
	public:
		TOBBCs()
		{
			value = new TOBB2();
		}
		~TOBBCs()
		{
			delete value;
		}
	};

	public value class TRotCs
	{
	internal:
		float s, c;
		TRot Unpack()
		{
			return TRot(s, c);
		}
		void Pack(TRot value)
		{
			s = value.s;
			c = value.c;
		}
	public:
		TRotCs(float angle)
		{
			Pack(TRot(angle));
		}
		TRotCs(TOBBCs box)
		{
			Pack(TRot(*box.value));
		}
	};

	public ref class TBaluTransformCs
	{
	internal:
		TBaluTransform* value;
		TBaluTransformCs(TBaluTransform v)
		{
			value = new TBaluTransform(v);
		}
	public:
		TBaluTransformCs()
		{
			value = new TBaluTransform();
		}
		~TBaluTransformCs()
		{
			delete value;
		}
	};

	public ref class IViewportCs
	{
	internal:
		EngineInterface::IViewport* value;
		IViewportCs(EngineInterface::IViewport* value)
		{
			this->value = value;
		}
	public:
		void SetTransform(TBaluTransformCs transform)
		{
			value->SetTransform(*transform.value);
		}
		TBaluTransformCs^ GetTransform()
		{
			return gcnew TBaluTransformCs(value->GetTransform());
		}
		void SetAspectRatio(float aspect)
		{
			value->SetAspectRatio(aspect);
		}
		void SetWidth(float width)
		{
			value->SetWidth(width);
		}
	};

	public ref class IBaluMaterialCs
	{
	internal:
		EngineInterface::IBaluMaterial* value;
		IBaluMaterialCs(EngineInterface::IBaluMaterial* value)
		{
			this->value = value;
		}
	public:
	};
}