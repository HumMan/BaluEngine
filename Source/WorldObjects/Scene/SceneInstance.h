#pragma once

#include "Scene.h"
#include "ClassInstance.h"

#include "Utils/DebugDraw.h"

#include "EngineInterfaces\ISceneInstance.h"

class TBaluWorldInstance;

struct TCollisionInfo
{
	b2Fixture *A, *B;
	TCollisionInfo(){}
	TCollisionInfo(b2Fixture* A, b2Fixture* B)
	{
		this->A = A;
		this->B = B;
	}
	bool operator==(const TCollisionInfo& r)const
	{
		return (A == r.A && B == r.B) || (A == r.B && B == r.A);
	}
};

class TContactsHolder : public b2ContactListener
{
public:
	std::vector<TCollisionInfo> contacts;
	std::vector<TCollisionInfo> in_step_contacts;

	void AddContact(TCollisionInfo collision)
	{
		auto it = std::find(contacts.begin(), contacts.end(), collision);
		if (it == contacts.end())
		{
			contacts.push_back(collision);
		}
	}
	void RemoveContact(TCollisionInfo collision)
	{
		auto it = std::find(contacts.begin(), contacts.end(), collision);
		if (it != contacts.end())
		{
			contacts.erase(it);
		}
	}
	void AddInStepContact(TCollisionInfo collision)
	{
		auto it = std::find(in_step_contacts.begin(), in_step_contacts.end(), collision);
		if (it == in_step_contacts.end())
		{
			in_step_contacts.push_back(collision);
		}
	}
	void RemoveInStepContact(TCollisionInfo collision)
	{
		auto it = std::find(in_step_contacts.begin(), in_step_contacts.end(), collision);
		if (it != in_step_contacts.end())
		{
			in_step_contacts.erase(it);
		}
	}

	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);

	void BeforePhysStep()
	{
		in_step_contacts.clear();
	}
	void OnProcessCollisions();
};

class TBaluSceneInstance : public EngineInterface::IBaluSceneInstance
{
private:
	TResources* resources;

	std::unique_ptr<b2World> phys_world;

	DebugDraw phys_debug;

	TBaluScene* source;
	std::vector<std::unique_ptr<EngineInterface::TSceneObjectInstance>> instances;

	std::map<std::string, TViewport> viewports;

	std::unique_ptr<TLayersManagerInstance> layers;

	//struct TCollisionInfo
	//{
	//	TBaluPhysShapeInstance *A, *B;
	//	TCollisionInfo(){}
	//	TCollisionInfo(TBaluPhysShapeInstance* A, TBaluPhysShapeInstance* B)
	//	{
	//		this->A = A;
	//		this->B = B;
	//	}
	//};
	//std::vector<TCollisionInfo> begin_contact, end_contact;

	TBaluWorldInstance* world;

	TContactsHolder contact_listener;
public:
	TLayersManagerInstance* GetLayers()
	{
		return layers.get();
	}
	TResources* GetResources()
	{
		return resources;
	}
	b2World* GetPhysWorld()
	{
		return phys_world.get();
	}
	bool PointCollide(TVec2 scene_space_point, EngineInterface::TSceneObjectInstance* &result);

	TBaluScene* GetSource();
	EngineInterface::IBaluWorldInstance* GetWorld();

	TViewport* GetViewport(std::string name);

	TBaluSceneInstance(TBaluWorldInstance* world, TBaluScene* source, TResources* resources);
	TBaluSceneInstance(TBaluWorldInstance* world, TResources* resources, TLayersManager* layers=nullptr);
	//TBaluSceneInstance(TBaluSceneInstance&& right);
	~TBaluSceneInstance();

	//TSceneObjectInstance* CreateInstance(TSceneObject* use_class, TBaluTransform transform, TVec2 scale);
	//EngineInterface::IBaluInstance* CreateInstance(EngineInterface::TSceneObject* use_class, TBaluTransform transform, TVec2 scale);
	void AddInstance(EngineInterface::TSceneObjectInstance*);
	void DestroyInstance(EngineInterface::TSceneObjectInstance*);

	void QueryAABB(TAABB2 frustum, std::vector<TBaluSpritePolygonInstance*>& results);
	void QueryAABB(TAABB2 frustum, std::vector<TRenderCommand>& results, std::vector<IGUIVisual*>& gui);

	void OnPrePhysStep();
	void PhysStep(float step);

	void OnProcessCollisions();
	void OnStep(float step);

	void OnKeyDown(TKey key);

	void OnMouseUp(EngineInterface::TMouseEventArgs e, TVec2 scene_cursor_location);
	void OnMouseDown(EngineInterface::TMouseEventArgs e, TVec2 scene_cursor_location);
	void OnMouseMove(EngineInterface::TMouseEventArgs e, TVec2 scene_cursor_location);

	void UpdateTransform();

	void DebugDraw(TDrawingHelperContext drawing_context);
};
