#pragma once

#include <WorldDef/Objects/Sprite/ISprite.h>
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
	class TSpriteInstance: public IChangeListener
	{
	private:
		TSprite* source;
		std::unique_ptr<TBaluPhysShapeInstance> phys_shape;
		TSpritePolygonInstance polygon;

		TProperties properties;
	public:
		TSprite* GetSource();
		TSpriteInstance(TSprite* source, TResources* resources, TSceneObjectInstance* scene_object, TBaluTransformedSpriteInstance* parent);
		~TSpriteInstance();
		TOBB2 GetOBB();

		IBaluPhysShapeInstance* GetPhysShape();

		TSpritePolygonInstance* GetPolygon();

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

		TSpriteInstance sprite_instance;
	public:
		IProperties* GetProperties()
		{
			return sprite_instance.GetProperties();
		}
		TSpriteInstance* GetSprite();
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

		TSpritePolygonInstance* GetPolygon();

		void PlayAnimation(std::string animation_name, bool loop);
		void PauseAnimation(bool pause);
		void StopAnimation();

		void UpdateTransform(TBaluTransformWithScale global);
};
#endif

}