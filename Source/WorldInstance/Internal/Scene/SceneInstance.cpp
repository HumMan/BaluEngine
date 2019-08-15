#include "SceneInstance.h"

#include "WorldInstance/IWorldInstance.h"

#include <algorithm>

#include <Box2D.h>

#include "../../../Utils/DebugDraw.h"

#include "../Sprite/PhysShapeInstance.h"
#include "../Sprite/SpriteInstance.h"
#include "../Class/ClassInstance.h"

using namespace BaluEngine;
using namespace BaluEngine::WorldInstance;
using namespace BaluEngine::WorldInstance::Internal;
using namespace BaluLib;

class TSceneObjectInstance::TPrivate
{
public:
	std::weak_ptr<IScene> scene;
	std::shared_ptr<WorldDef::Internal::TRuntimeProperties> properties;
};

typedef std::vector < std::pair<const char*, SceneObjectInstanceClone>> scene_object_instance_registry_type;
scene_object_instance_registry_type *scene_object_instance_registry = nullptr;

bool SceneObjectInstanceFactory::Register(const char* name, SceneObjectInstanceClone clone)
{
	if (scene_object_instance_registry == nullptr)
		scene_object_instance_registry = new scene_object_instance_registry_type();
	scene_object_instance_registry->push_back(std::pair<const char*, SceneObjectInstanceClone>(name, clone));
	return true;
}

void SceneObjectInstanceFactory::UnregisterAll()
{
	delete scene_object_instance_registry;
}

std::shared_ptr<ISceneObjectInstance> SceneObjectInstanceFactory::Create(const char* name, WorldDef::ISceneObject* param, std::shared_ptr<IScene> scene)
{
	for (int i = 0; i < scene_object_instance_registry->size(); i++)
		if (strcmp((*scene_object_instance_registry)[i].first, name) == 0)
			return (*scene_object_instance_registry)[i].second(param, scene);
	throw std::invalid_argument("��� �� ���������������");
}

struct TCollisionInfo
{
	b2Fixture *A, *B;
	TCollisionInfo() {}
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

	ISceneContactListener* events_listener;

	TContactsHolder()
	{
		events_listener = nullptr;
	}

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

class TScene::TPrivate
{
public:
	TResources * resources;

	std::unique_ptr<b2World> phys_world;

	DebugDraw phys_debug;

	WorldDef::IScene* source;
	std::vector<std::shared_ptr<ISceneObjectInstance>> instances;

	//std::vector<std::unique_ptr<ITransformedClassInstance>> class_instances;
	//std::vector<std::unique_ptr<IGUIVisual>> editor_gui_instances;
	//tiles;
	//particle systems;

	std::map<std::string, std::unique_ptr<WorldDef::IViewport>> viewports;

	struct TCollisionInfo
	{
		TPhysShapeInstance *A, *B;
		TCollisionInfo(){}
		TCollisionInfo(TPhysShapeInstance* A, TPhysShapeInstance* B)
		{
			this->A = A;
			this->B = B;
		}
	};
	std::vector<TCollisionInfo> begin_contact, end_contact;

	std::weak_ptr < IWorld> world;

	TContactsHolder contact_listener;
};

TSceneObjectInstance::~TSceneObjectInstance()
{
	p.reset(new TPrivate());
}

std::shared_ptr<WorldDef::IRuntimeProperties> TSceneObjectInstance::GetProperties()
{
	return p->properties;
}

std::shared_ptr<IScene> TSceneObjectInstance::GetScene()
{
	return p->scene.lock();
}
TSceneObjectInstance::TSceneObjectInstance(std::shared_ptr<IScene> scene)
{
	p.reset(new TPrivate());
	p->properties = std::make_shared<WorldDef::Internal::TRuntimeProperties>();
	p->scene = scene;
}

bool TScene::PointCollide(TVec2 scene_space_point, std::shared_ptr < ISceneObjectInstance> &result)
{
	for (int i = 0; i < p->instances.size(); i++)
	{
		bool collide = dynamic_cast<TSceneObjectInstance*>(p->instances[i].get())->PointCollide(scene_space_point);
		if (collide)
		{
			result = p->instances[i];
			return true;
		}
	}
	return false;
}

WorldDef::IScene* TScene::GetSource()
{
	return p->source;
}

std::shared_ptr < IWorld> TScene::GetWorld()
{
	return p->world.lock();
}

void TContactsHolder::BeginContact(b2Contact* contact)
{ 
	TCollisionInfo collision(contact->GetFixtureA(), contact->GetFixtureB());

	RemoveInStepContact(collision);
	AddContact(collision);
}
void TContactsHolder::EndContact(b2Contact* contact)
{
	TCollisionInfo collision(contact->GetFixtureA(), contact->GetFixtureB());

	AddInStepContact(collision);
	RemoveContact(collision);
}

void TContactsHolder::OnProcessCollisions()
{
	for (auto& v : contacts)
	{
		auto user_data_a = (TPhysShapeUserData*)v.A->GetUserData();
		auto user_data_b = (TPhysShapeUserData*)v.B->GetUserData();

		auto sprite_a = user_data_a->GetSprite();
		auto sprite_b = user_data_b->GetSprite();

		auto instance_a = std::dynamic_pointer_cast<TTransformedClassInstance>(user_data_a->GetSceneObject());
		auto instance_b = std::dynamic_pointer_cast<TTransformedClassInstance>(user_data_b->GetSceneObject());
		if (events_listener != nullptr)
		{
			events_listener->ProcessCollision(instance_a, sprite_a, instance_b);
			events_listener->ProcessCollision(instance_b, sprite_b, instance_a);
		}
	}
}

void TContactsHolder::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
	B2_NOT_USED(contact);
	B2_NOT_USED(oldManifold);
}
void TContactsHolder::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
	B2_NOT_USED(contact);
	B2_NOT_USED(impulse);
}

WorldDef::IViewport* TScene::GetViewport(std::string name)
{
	return p->viewports[name].get();
}

void TScene::SetCollideListener(ISceneContactListener* contacts_listener)
{
	p->contact_listener.events_listener = contacts_listener;
}

TScene::TScene(std::weak_ptr < IWorld> world, WorldDef::IScene* source, TResources* resources)
{
	p.reset(new TPrivate());
	p->source = source;
	p->world = world;
	p->resources = resources;
	p->phys_world = std::unique_ptr<b2World>(new b2World(b2Vec2(0, -1)));

	p->phys_debug.Create();

	p->phys_world->SetDebugDraw(&p->phys_debug);
	p->phys_world->SetContactListener(&p->contact_listener);
}

void TScene::InitInstances(std::shared_ptr<IScene> this_ptr)
{
	for (int i = 0; i < p->source->GetInstancesCount(); i++)
	{
		auto source_instance = p->source->GetInstance(i);
		auto instance = SceneObjectInstanceFactory::Create(source_instance->GetFactoryName(), source_instance, this_ptr);
		p->instances.push_back(instance);
		auto class_instance = dynamic_cast<ITransformedClassInstance*>(instance.get());
		//if (class_instance != nullptr)
		//	p->world.lock()->GetEventsEditor()->OnCreate(class_instance);
	}

	//source->AddChangesListener(this);
}

TScene::~TScene()
{
	p->phys_debug.Destroy();
	//if (source != nullptr)
	//	source->RemoveChangesListener(this);
}

//void TScene::AddInstance(ISceneObjectInstance* instance)
//{
//	for (auto& v : p->instances)
//		if (v.get() == instance)
//			assert(false);
//	p->instances.push_back(std::unique_ptr<ISceneObjectInstance>(instance));
//	//auto class_instance = dynamic_cast<ITransformedClassInstance*>(instance);
//	//if (class_instance != nullptr)
//	//	p->world->GetEventsEditor()->OnCreate(class_instance);
//}

//void TScene::DestroyInstance(ISceneObjectInstance* instance)
//{
//	for (int i = 0; i < p->instances.size(); i++)
//	{
//		if (p->instances[i].get() == instance)
//		{
//			p->instances[i].reset();
//		}
//	}
//}

void TScene::QueryAABB(TAABB2 frustum, std::vector< std::shared_ptr<ISpritePolygonInstance>>& results)
{
	for (int i = 0; i < p->instances.size(); i++)
	{
		dynamic_cast<TSceneObjectInstance*>(p->instances[i].get())->QueryAABB(frustum, results);
	}
}

void TScene::QueryAABB(TAABB2 frustum, std::vector<TRenderCommand>& results, std::vector<IGUIVisual*>& gui)
{
	std::vector< std::shared_ptr<ISpritePolygonInstance>> polygons;
	QueryAABB(frustum, polygons);

	
	if (p->source != nullptr)
	{
		{
			for (int i = 0; i < polygons.size(); i++)
			{
				dynamic_cast<TSpritePolygonInstance*>(polygons[i].get())->Render(results);
			}
		}
	}
	else
	{
		for (int i = 0; i < polygons.size(); i++)
		{
			dynamic_cast<TSpritePolygonInstance*>(polygons[i].get())->Render(results);
		}
	}

	for (auto& v : p->instances)
	{
		auto visual = dynamic_cast<IGUIVisual*>(v.get());
		if (visual != nullptr)
			gui.push_back(visual);
	}
}

size_t TScene::GetInstancesCount()
{
	return p->instances.size();
}
std::shared_ptr < ISceneObjectInstance> TScene::GetInstance(size_t index)
{
	return p->instances[index];
}

void TScene::PhysStep(float step)
{
	p->contact_listener.BeforePhysStep();
	p->phys_world->Step(step*10, 3, 5);
}

void TScene::OnProcessCollisions()
{
	p->contact_listener.OnProcessCollisions();
}

void TScene::OnStep(float step)
{
	for (int i = 0; i < p->instances.size(); i++)
	{
		auto class_instance = dynamic_cast<ITransformedClassInstance*>(p->instances[i].get());
		if (class_instance != nullptr)
			class_instance->GetSkeletonAnimation()->Update(step);
	}
}


void TScene::UpdateTransform()
{
	for (int i = 0; i < p->instances.size(); i++)
	{
		dynamic_cast<TSceneObjectInstance*>(p->instances[i].get())->UpdateTransform();
	}
}

void TScene::DoDebugDraw(TDrawingHelperContext drawing_context)
{
	uint32 flags = 0;
	flags |= b2Draw::e_shapeBit;
	flags |= b2Draw::e_jointBit;
	//flags |= b2Draw::e_aabbBit;
	flags |= b2Draw::e_centerOfMassBit;
	p->phys_debug.SetFlags(flags);
	g_camera.drawing_context = drawing_context;
	p->phys_world->DrawDebugData();
	p->phys_debug.Flush();
}

TResources * TScene::GetResources()
{
	return p->resources;
}
b2World* TScene::GetPhysWorld()
{
	return p->phys_world.get();
}
