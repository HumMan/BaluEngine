#include "ISceneInstance.h"

#include <World/IWorldInstance.h>

bool TBaluSceneInstance::PointCollide(TVec2 scene_space_point, EngineInterface::TSceneObjectInstance* &result)
{
	for (int i = 0; i < instances.size(); i++)
	{
		bool collide = instances[i]->PointCollide(scene_space_point);
		if (collide)
		{
			result = instances[i].get();
			return true;
		}
	}
	return false;
}

TBaluScene* TBaluSceneInstance::GetSource()
{
	return source;
}

EngineInterface::IBaluWorldInstance* TBaluSceneInstance::GetWorld()
{
	return dynamic_cast<EngineInterface::IBaluWorldInstance*>(world);
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

		auto instance_a = dynamic_cast<TBaluTransformedClassInstance*>(user_data_a->GetSceneObject());
		auto instance_b = dynamic_cast<TBaluTransformedClassInstance*>(user_data_b->GetSceneObject());

		//auto class_a = instance_a!=nullptr?dynamic_cast<TBaluClassCompiledScripts*>(instance_a->GetClass()->GetScripts()):nullptr;
		//auto class_b = instance_b!=nullptr?dynamic_cast<TBaluClassCompiledScripts*>(instance_b->GetClass()->GetScripts()):nullptr;

		//if (class_a != nullptr && class_b != nullptr)
		//{
		//	//TODO взаимодействие не только с TBaluTransformedClassInstance
		//	class_a->DoCollide(instance_a, sprite_a, dynamic_cast<TBaluTransformedClassInstance*>(instance_b));
		//	class_b->DoCollide(instance_b, sprite_b, dynamic_cast<TBaluTransformedClassInstance*>(instance_a));
		//}
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

TViewport* TBaluSceneInstance::GetViewport(std::string name)
{
	return &viewports[name];
}

TBaluSceneInstance::TBaluSceneInstance(TBaluWorldInstance* world, TBaluScene* source, TResources* resources)
{
	this->source = source;
	this->world = world;
	this->resources = resources;
	phys_world = std::make_unique<b2World>(b2Vec2(0, -1));

	phys_debug.Create();

	phys_world->SetDebugDraw(&phys_debug);
	phys_world->SetContactListener(&contact_listener);

	for (int i = 0; i < source->GetInstancesCount(); i++)
	{
		auto source_instance = source->GetInstance(i);
		auto instance = SceneObjectInstanceFactory::Create(source_instance->GetFactoryName(), source_instance, this);
	}

	source->AddChangesListener(this);
}


TBaluSceneInstance::TBaluSceneInstance(TBaluWorldInstance* world, TResources* resources, TLayersManager* layers)
{
	this->source = nullptr;
	this->world = world;
	this->resources = resources;
	phys_world = std::make_unique<b2World>(b2Vec2(0, -1));

	phys_debug.Create();

	phys_world->SetDebugDraw(&phys_debug);
	phys_world->SetContactListener(&contact_listener);
}

TBaluSceneInstance::~TBaluSceneInstance()
{
	phys_debug.Destroy();
	if (source != nullptr)
		source->RemoveChangesListener(this);
}

void TBaluSceneInstance::AddInstance(EngineInterface::TSceneObjectInstance* instance)
{
	for (auto& v : instances)
		if (v.get() == instance)
			assert(false);
	instances.push_back(std::unique_ptr<TSceneObjectInstance>(instance));
}

void TBaluSceneInstance::DestroyInstance(EngineInterface::TSceneObjectInstance* instance)
{
	for (int i = 0; i < instances.size(); i++)
	{
		if (dynamic_cast<TSceneObjectInstance*>(instances[i].get()) == instance)
		{
			instances[i].reset();
		}
	}
}

void TBaluSceneInstance::QueryAABB(TAABB2 frustum, std::vector<TBaluSpritePolygonInstance*>& results)
{
	for (int i = 0; i < instances.size(); i++)
	{
		instances[i]->QueryAABB(frustum, results);
	}
}

void TBaluSceneInstance::QueryAABB(TAABB2 frustum, std::vector<TRenderCommand>& results, std::vector<IGUIVisual*>& gui)
{
	std::vector<TBaluSpritePolygonInstance*> polygons;
	QueryAABB(frustum, polygons);

	
	if (this->source != nullptr)
	{
		TLayersManager* layers = this->source->GetLayers();
		{
			for (int i = 0; i < polygons.size(); i++)
			{
				polygons[i]->Render(results, *layers);
			}
		}
	}
	else
	{
		TLayersManager without_layers(nullptr);	
		without_layers.AddLayer(TLayer(), -1);
		for (int i = 0; i < polygons.size(); i++)
		{
			polygons[i]->Render(results, without_layers);
		}
	}

	for (auto& v : instances)
	{
		auto visual = dynamic_cast<IGUIVisual*>(v.get());
		if (visual != nullptr)
			gui.push_back(visual);
	}
}


void TBaluSceneInstance::PhysStep(float step)
{
	contact_listener.BeforePhysStep();
	phys_world->Step(step*10, 3, 5);
}

void TBaluSceneInstance::OnProcessCollisions()
{
	contact_listener.OnProcessCollisions();
}

void TBaluSceneInstance::OnStep(float step)
{
	for (int i = 0; i < instances.size(); i++)
	{
		auto class_instance = dynamic_cast<TBaluTransformedClassInstance*>(instances[i].get());
		if (class_instance != nullptr)
			class_instance->GetSkeletonAnimation()->Update(step);
	}
}


void TBaluSceneInstance::UpdateTransform()
{
	for (int i = 0; i < instances.size(); i++)
	{
		instances[i]->UpdateTransform();
	}
}

void TBaluSceneInstance::DebugDraw(TDrawingHelperContext drawing_context)
{
	uint32 flags = 0;
	flags |= b2Draw::e_shapeBit;
	flags |= b2Draw::e_jointBit;
	//flags |= b2Draw::e_aabbBit;
	flags |= b2Draw::e_centerOfMassBit;
	phys_debug.SetFlags(flags);
	g_camera.drawing_context = drawing_context;
	phys_world->DrawDebugData();
	phys_debug.Flush();
}