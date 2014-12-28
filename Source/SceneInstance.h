#pragma once

#include "Scene.h"
#include "ClassInstance.h"

#include "Utils/DebugDraw.h"

class TBaluSceneInstance : public b2ContactListener
{
private:
	TResourses* resources;

	std::unique_ptr<b2World> phys_world;

	DebugDraw phys_debug;

	TBaluScene* source;
	std::vector<std::unique_ptr<TBaluInstance>> instances;

	std::map<std::string, TViewport> viewports;

	struct TCollisionInfo
	{
		TBaluPhysShapeInstance *A, *B;
		TCollisionInfo(){}
		TCollisionInfo(TBaluPhysShapeInstance* A, TBaluPhysShapeInstance* B)
		{
			this->A = A;
			this->B = B;
		}
	};
	std::vector<TCollisionInfo> begin_contact, end_contact;
public:

	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);

	TViewport* GetViewport(std::string name);

	TBaluSceneInstance(TBaluScene* source, TResourses* resources);
	TBaluSceneInstance(TBaluSceneInstance&& right);

	TBaluInstance* CreateInstance(TBaluClass* use_class, TBaluTransform transform);

	TVec2 WorldToScene(const TVec2& v);
	TVec2 SceneToWorld(const TVec2& v);
	
	void QueryAABB(TAABB2 frustum, std::vector<TBaluSpritePolygonInstance*>& results);

	void OnPrePhysStep();
	void PhysStep(float step);

	void OnProcessCollisions();
	void OnStep(float step);

	void OnKeyDown(TKey key);

	void UpdateTransform();

	void DebugDraw();
};
