#pragma once

#include "ISprite.h"
#include "IPhysShapeInstance.h"
#include "ISpritePolygonInstance.h"

namespace EngineInterface
{
	class TSceneObjectInstance;

	class IBaluTransformedSpriteInstance
	{
	public:
		//virtual void SetTransform(TBaluTransform local)=0;
		//virtual TBaluTransform GetTransform() = 0;
		virtual IBaluTransformedSprite* GetSource()=0;
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

#ifdef BALUENGINEDLL_EXPORTS

	class TBaluTransformedSpriteInstance : public IBaluTransformedSpriteInstance
	{
	private:
		TBaluTransformedSprite* source;

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

		TBaluTransformedSpriteInstance(TBaluTransformedSprite* source, TResources* resources, TSceneObjectInstance* scene_object);

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
		TBaluTransformedSprite* GetSource();

		TOBB2 GetOBB();

		IBaluPhysShapeInstance* GetPhysShape();

		TBaluSpritePolygonInstance* GetPolygon();

		void PlayAnimation(std::string animation_name, bool loop);
		void PauseAnimation(bool pause);
		void StopAnimation();

		void UpdateTranform(TBaluTransformWithScale global);
};
#endif

}