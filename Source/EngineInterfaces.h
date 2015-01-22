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

	class IBaluPhysShape
	{
	public:
	};

	class IBaluPolygonShape
	{
	public:
	};

	class IBaluCircleShape
	{
	public:
	};

	class IBaluBoxShape
	{
	public:
	};

	class IBaluPhysShapeFactory
	{
	public:
		virtual IBaluPolygonShape* CreatePolygonShape() = 0;
		virtual IBaluCircleShape* CreateCircleShape() = 0;
		virtual IBaluBoxShape* CreateBoxShape() = 0;
	};

	class IBaluSpritePolygon
	{
	public:
		virtual void AddAnimDesc(TAnimDesc* desc)=0;
		virtual void CreateAnimationLine(std::string line_name, std::vector<TAnimationFrames> frames)=0;
		virtual void CreateAnimationLine(std::string line_name, TAnimDesc* desc, std::vector<int> frames)=0;

		virtual IBaluMaterial* GetMaterial() = 0;
		virtual void SetMaterial(IBaluMaterial* material) = 0;
		virtual void SetPolygonVertices(std::vector<TVec2> polygon_vertices) = 0;
		virtual void SetAsBox(float width, float height) = 0;

		virtual void SetVertices(std::vector<TVec2> vertices) = 0;
		virtual std::vector<TVec2> GetVertices() = 0;

		virtual std::vector<TVec2> GetTexCoords() = 0;

		virtual int GetVerticesCount() = 0;
		virtual void SetVertex(int id, TVec2 pos) = 0;
		virtual TVec2 GetPolygonVertex(int id) = 0;
		virtual TVec2 GetVertex(int id) = 0;

		virtual void SetTexCoordsFromVertices(TVec2 origin, TVec2 scale) = 0;
		virtual void SetTexCoordsFromVerticesByRegion(TVec2 left_bottom, TVec2 right_top) = 0;
	};

	class IBaluSprite
	{
	public:
		virtual std::string GetName() = 0;
		virtual void SetName(std::string name) = 0;
		virtual void SetPhysShape(IBaluPhysShape* shape)=0;
		virtual IBaluPhysShape* GetPhysShape()=0;
		virtual void SetPhysShapeFromGeometry()=0;
		virtual IBaluSpritePolygon* GetPolygone()=0;
	};	

	class IBaluClassSprite
	{
	public:
	};

	class ISkeletonAnimation
	{
	public:
	};

	class ISensor
	{
	public:

	};

	class IBaluClassPhysBody
	{
	public:
		virtual int GetSensorsCount()=0;
		virtual ISensor* GetSensor(int index) = 0;
		virtual void SetFixedRotation(bool fixed) = 0;
		virtual void SetPhysBodyType(TPhysBodyType type) = 0;
		virtual void Enable(bool enable) = 0;
		virtual bool IsEnable() = 0;
		virtual b2BodyDef GetBodyDef() = 0;
		virtual ISensor* CreateSensor(IBaluPhysShape* shape) = 0;
	};

	class IBaluClass
	{
	public:
		virtual int GetSpritesCount()=0;
		virtual IBaluClassSprite* GetSprite(int index) = 0;
		virtual ISkeletonAnimation* GetSkeletonAnimation()=0;
		virtual IBaluClassPhysBody* GetPhysBody();
	};

	class IViewport
	{
	public:
		virtual void SetTransform(TBaluTransform transform) = 0;
		virtual void SetAspectRatio(float aspect) = 0;
		virtual void SetWidth(float width) = 0;
		virtual TAABB2 GetAABB() = 0;
	};

	class IBaluSceneClassInstance
	{
	public:
	};

	class IBaluScene
	{
	public:
		virtual IViewport* CreateViewport(std::string name);

		virtual std::string GetName();
		virtual void SetName(std::string name);

		virtual int GetInstancesCount();
		virtual IBaluSceneClassInstance* GetInstance(int index);

		virtual IBaluSceneClassInstance* CreateInstance(IBaluClass* balu_class);
		virtual void DestroyIntance(IBaluSceneClassInstance*);
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
	class IBaluPhysShapeInstance
	{
	public:
	};

	class IBaluSpritePolygonInstance
	{
	public:
		virtual void SetSpritePolygon(std::string name)=0;
		virtual IBaluSpritePolygon* GetSpritePolygon()=0;

		virtual void SetActiveAnimation(std::string)=0;
	};

	class IBaluSpriteInstance
	{
	public:
		//virtual void SetTransform(TBaluTransform local)=0;
		//virtual TBaluTransform GetTransform() = 0;
		virtual IBaluSprite* GetSourceSprite() = 0;
		virtual IBaluPhysShapeInstance* GetPhysShape()=0;

		virtual IBaluSpritePolygonInstance* GetPolygon()=0;
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

	class ISkeletonAnimationInstance
	{
	public:
		virtual void Update(float step)=0;
		virtual void PlayAnimation(std::string name, float alpha)=0;
		virtual void StopAnimation(std::string name)=0;
	};

	class IBaluInstance
	{
	public:
		virtual int GetSpritesCount() = 0;
		virtual IBaluSpriteInstance* GetSprite(int index) = 0;
		virtual IProperties* GetProperties() = 0;
		virtual IBaluClassPhysBodyIntance* GetPhysBody() = 0;
		virtual ISkeletonAnimationInstance* GetSkeletonAnimation() = 0;
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