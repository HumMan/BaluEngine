#pragma once

#include <string>

#include "exportMacro.h"

namespace EngineInterface
{
	enum PropertyType
	{
		Bool,
		Int,
		Float,
		String,
	};

	class IProperties
	{
	public:
		virtual void SetBool(std::string name, bool value)=0;
		virtual bool GetBool(std::string name) = 0;
	};

	class IBaluMaterial
	{
	public:
	};

	class IBaluSprite
	{
	public:
		virtual std::string GetName() = 0;
		virtual void SetName(std::string name) = 0;
	};	

	class IBaluClassSprite
	{
	public:
	};

	class ISkeletonAnimation
	{
	public:
	};

	class IBaluClass
	{
	public:
		virtual int GetSpritesCount()=0;
		virtual IBaluClassSprite* GetSprite(int index) = 0;
		virtual ISkeletonAnimation* GetSkeletonAnimation()=0;
	};

	class IBaluScene
	{
	public:
	};

	class IBaluWorld
	{
	public:
		virtual IBaluMaterial* CreateMaterial(char* mat_name) = 0;
		virtual IBaluSprite* CreateSprite(char* sprite_name) = 0;
		virtual IBaluClass* CreateClass(char* class_name) = 0;
		virtual IBaluScene* CreateScene(char* scene_name) = 0;

		virtual IBaluScene* GetScene(char* scene_name) = 0;
	};
}

BALUENGINEDLL_API EngineInterface::IBaluWorld* CreateWorld();
BALUENGINEDLL_API void DestroyWorld(EngineInterface::IBaluWorld* world);


namespace EngineInterface
{
	class TBaluPhysShapeInstance
	{

	};

	class IBaluSpriteInstance
	{
	public:
		//virtual void SetTransform(TBaluTransform local)=0;
		//virtual TBaluTransform GetTransform() = 0;
		virtual IBaluSprite* GetSourceSprite() = 0;
	};

	class IBaluMaterialInstance
	{
	public:
	};

	class ISensorInstance
	{

	};

	class IBaluClassPhysBodyIntance
	{
	public:
		virtual TVec2 GetLinearVelocity()=0;
		virtual void SetLinearVelocity(TVec2 velocity)=0;
	};

	class IBaluInstance
	{
	public:
		virtual int GetSpritesCount() = 0;
		virtual IBaluSpriteInstance* GetSprite(int index) = 0;
		virtual IProperties* GetProperties() = 0;
		virtual IBaluClassPhysBodyIntance* GetPhysBody() = 0;
	};

	class IBaluSceneInstance
	{
	public:
	};

	class IBaluWorldInstance
	{
	public:
	};
}