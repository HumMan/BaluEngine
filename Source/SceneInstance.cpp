#include "SceneInstance.h"

#include "WorldInstance.h"

bool TBaluSceneInstance::PointCollide(TVec2 scene_space_point, EngineInterface::IBaluInstance* &result)
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
		auto shape_a = (TBaluPhysShapeInstance*)v.A->GetUserData();
		auto shape_b = (TBaluPhysShapeInstance*) v.B->GetUserData();

		auto instance_a = shape_a->GetParent();
		auto instance_b = shape_b->GetParent();

		auto class_a = dynamic_cast<TBaluClassInstance*>(instance_a->GetClass());
		auto class_b = dynamic_cast<TBaluClassInstance*>(instance_b->GetClass());


		auto sprite_a = shape_a->GetSpriteInstance();
		auto sprite_b = shape_b->GetSpriteInstance();

		class_a->DoCollide(shape_a, dynamic_cast<TBaluInstance*>(instance_b));
		class_b->DoCollide(shape_b, dynamic_cast<TBaluInstance*>(instance_a));

		//auto c = (dynamic_cast<TBaluClassSpriteInstance*>(sprite_a))->GetSprite()->GetOnCollide(dynamic_cast<TBaluClass*>(class_b));
		//if (c != nullptr)
		//{
		//	//c->Execute(dynamic_cast<IBaluPhysShapeInstance*>(shape_a), instance_b);
		//}
		//c = (dynamic_cast<TBaluClassSpriteInstance*>(sprite_b))->GetSprite()->GetOnCollide(dynamic_cast<TBaluClass*>(class_a));
		//if (c != nullptr)
		//{
		//	//c->Execute(dynamic_cast<IBaluPhysShapeInstance*>(shape_b), instance_a);
		//}

		//auto c = (dynamic_cast<TBaluInstance*>(class_a))->GetClass()->GetOnCollide(dynamic_cast<TBaluClass*>(class_b));
		//if (c != nullptr)
		//{
		//	c->Execute(instance_a, instance_b);
		//}
		//c = (dynamic_cast<TBaluInstance*>(class_b))->GetClass()->GetOnCollide(dynamic_cast<TBaluClass*>(class_a));
		//if (c != nullptr)
		//{
		//	c->Execute(instance_b, instance_a);
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
		auto instance = CreateInstance(source_instance->GetClass(), source->GetInstance(i)->GetTransform(), source->GetInstance(i)->GetScale());
		instance->SetTransform(source_instance->GetTransform());
		instance->UpdateTranform();
	}
}

TBaluSceneInstance::~TBaluSceneInstance()
{
	phys_debug.Destroy();
}

//TBaluSceneInstance::TBaluSceneInstance(TBaluSceneInstance&& right)
//{
//	phys_world = std::move(right.phys_world);
//	instances = std::move(right.instances);
//}

TBaluInstance* TBaluSceneInstance::CreateInstance(TBaluClass* use_class, TBaluTransform transform, TVec2 scale)
{
	auto class_instance = world->GetClassInstance(use_class);
	instances.push_back(std::make_unique<TBaluInstance>(class_instance, phys_world.get(), transform, scale, resources));
	return instances.back().get();
}

EngineInterface::IBaluInstance* TBaluSceneInstance::CreateInstance(EngineInterface::IBaluClass* use_class, TBaluTransform transform, TVec2 scale)
{
	return dynamic_cast<EngineInterface::IBaluInstance*>(CreateInstance(dynamic_cast<TBaluClass*>(use_class), transform, scale));
}

void TBaluSceneInstance::DestroyInstance(EngineInterface::IBaluInstance* instance)
{
	for (int i = 0; i < instances.size();i++)
		if (instances[i].get() == instance)
		{
			instances[i].reset();
		}
}

void TBaluSceneInstance::QueryAABB(TAABB2 frustum, std::vector<TBaluSpritePolygonInstance*>& results)
{
	for (int i = 0; i < instances.size(); i++)
	{
		instances[i]->QueryAABB(frustum, results);
	}
}

void TBaluSceneInstance::QueryAABB(TAABB2 frustum, std::vector<TRenderCommand>& results, std::vector<TCustomDrawCommand>& custom_draw)
{
	std::vector<TBaluSpritePolygonInstance*> polygons;
	QueryAABB(frustum, polygons);
	//results.resize(polygons.size());

	for (int i = 0; i < polygons.size(); i++)
	{
		//if (polygons[i]->GetSpritePolygon()->IsCustomDraw())
		//{
		//	
		//	polygons[i]->RenderCustom(custom_draw);
		//}
		//else
		{
			results.emplace_back();
			polygons[i]->Render(results.back());
		}
	}
}

void TBaluSceneInstance::OnPrePhysStep()
{
	for (int i = 0; i < instances.size(); i++)
		instances[i]->GetClass()->DoBeforePhysicsStep(instances[i].get());
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
		instances[i]->GetSkeletonAnimation()->Update(step);
	}
}

void TBaluSceneInstance::OnKeyDown(TKey key)
{
	for (int i = 0; i < instances.size(); i++)
		instances[i]->GetClass()->DoKeyDown(key, instances[i].get());
}

void TBaluSceneInstance::UpdateTransform()
{
	for (int i = 0; i < instances.size(); i++)
	{
		instances[i]->UpdateTranform();
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