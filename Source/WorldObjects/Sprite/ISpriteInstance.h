#pragma once

#include "ISprite.h"
#include "IPhysShapeInstance.h"
#include "ISpritePolygonInstance.h"

namespace EngineInterface
{
	class TBaluTransformedSpriteInstance;

	class IBaluSpriteInstance
	{
	public:
	};

#ifdef BALUENGINEDLL_EXPORTS
	class TBaluSpriteInstance: public IChangeListener
	{
	private:
		TBaluSprite* source;
		std::unique_ptr<TBaluPhysShapeInstance> phys_shape;
		TBaluSpritePolygonInstance polygon;

		TProperties properties;
	public:
		TBaluSprite* GetSource();
		TBaluSpriteInstance(TBaluSprite* source, TResources* resources, TSceneObjectInstance* scene_object, TBaluTransformedSpriteInstance* parent);
		~TBaluSpriteInstance();
		TOBB2 GetOBB();

		IBaluPhysShapeInstance* GetPhysShape();

		TBaluSpritePolygonInstance* GetPolygon();

		void PlayAnimation(std::string animation_name, bool loop);
		void PauseAnimation(bool pause);
		void StopAnimation();

		void UpdateTransform(TBaluTransformWithScale global);
		TProperties* GetProperties()
		{
			return &properties;
		}
	};
#endif

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
	};

#ifdef BALUENGINEDLL_EXPORTS

	class TBaluTransformedSpriteInstance : public IBaluTransformedSpriteInstance, public IChangeListener
	{
	private:
		TBaluTransformedSprite* source;

		TBaluTransformWithScale transform;

		TBaluSpriteInstance sprite_instance;
	public:
		IProperties* GetProperties()
		{
			return sprite_instance.GetProperties();
		}
		TBaluSpriteInstance* GetSprite();
		TBaluTransformedSpriteInstance(TBaluTransformedSprite* source, TResources* resources, TSceneObjectInstance* scene_object);

		void SetTransform(TBaluTransform local)
		{
			this->transform.transform = local;
		}
		TBaluTransform GetTransform()
		{
			return transform.transform;
		}
		TVec2 GetScale()
		{
			return transform.scale;
		}
		void SetScale(TVec2 scale)
		{
			transform.scale = scale;
		}
		TBaluTransformedSprite* GetSource();

		TOBB2 GetOBB();

		IBaluPhysShapeInstance* GetPhysShape();

		TBaluSpritePolygonInstance* GetPolygon();

		void PlayAnimation(std::string animation_name, bool loop);
		void PauseAnimation(bool pause);
		void StopAnimation();

		void UpdateTransform(TBaluTransformWithScale global);
};
#endif

}