
#ifndef BALU_ENGINE_DISABLE_PRAGMA_ONCE
#pragma once
#endif


#ifndef BALU_ENGINE_SCRIPT_CLASSES

#ifndef BALU_ENGINE_DISABLE_PRAGMA_ONCE
#include "ISprite.h"
#include "IPhysShapeInstance.h"
#include "ISpritePolygonInstance.h"
#endif

#endif

namespace EngineInterface
{

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	class IBaluClassInstanceSpriteInstance
	{
	public:
		//virtual void SetTransform(TBaluTransform local)=0;
		//virtual TBaluTransform GetTransform() = 0;
		virtual IBaluClassSpriteInstance* GetSource()=0;
		virtual IBaluPhysShapeInstance* GetPhysShape() = 0;
		virtual TVec2 GetScale() = 0;
		virtual TOBB2 GetOBB() = 0;
		virtual void SetScale(TVec2 scale) = 0;
		virtual void SetTransform(TBaluTransform local) = 0;
		virtual TBaluTransform GetTransform() = 0;
		virtual IBaluSpritePolygonInstance* GetPolygon() = 0;
		virtual IProperties* GetProperties() = 0;
		virtual void SetTag(void* tag)=0;
		virtual void* GetTag()=0;
	};

	class TBaluPhysShapeInstance;
	class TBaluInstance;

	class TBaluClassInstanceSpriteInstance : public IBaluClassInstanceSpriteInstance
	{
	private:
		TBaluClassSpriteInstance* source;

		TBaluTransformWithScale local;

		std::unique_ptr<TBaluPhysShapeInstance> phys_shape;
		TBaluSpritePolygonInstance polygon;

		TProperties properties;
		void* tag;
	public:
		void SetTag(void* tag)
		{
			this->tag = tag;
		}
		void* GetTag()
		{
			return tag;
		}

		IProperties* GetProperties()
		{
			return &properties;
		}

		TBaluClassInstanceSpriteInstance(TBaluClassSpriteInstance* source, TBaluInstance* parent, TResources* resources);

		void SetTransform(TBaluTransform local)
		{
			this->local.transform = local;
		}
		TBaluTransform GetTransform()
		{
			return local.transform;
		}
		TVec2 GetScale()
		{
			return local.scale;
		}
		void SetScale(TVec2 scale)
		{
			local.scale = scale;
		}
		TBaluClassSpriteInstance* GetSource();

		TOBB2 GetOBB();

		IBaluPhysShapeInstance* GetPhysShape();

		TBaluSpritePolygonInstance* GetPolygon();

		void PlayAnimation(std::string animation_name, bool loop);
		void PauseAnimation(bool pause);
		void StopAnimation();

		void UpdateTranform(TBaluTransformWithScale global);
};
#endif

#ifdef BALU_ENGINE_SCRIPT_CLASSES
	BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, IBaluClassInstanceSpriteInstance, "IClassInstanceSpriteInstance");
	MUnpackRA0(WrapPointer<IBaluClassSpriteInstance>,	TYPE, GetSource);
	MUnpackRA0(WrapPointer<IBaluPhysShapeInstance>,		TYPE, GetPhysShape);
	MUnpackRA0(WrapValue<TVec2>,						TYPE, GetScale);
	MUnpackRA0(WrapPointer<IBaluSpritePolygonInstance>,	TYPE, GetPolygon);
	BALU_ENGINE_SCRIPT_END_CLASS;
#endif

}