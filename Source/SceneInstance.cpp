#include "SceneInstance.h"

void TBaluSceneInstance::BeginContact(b2Contact* contact) 
{ 
	auto fixtureA = (TBaluPhysShapeInstance*) contact->GetFixtureA()->GetUserData();
	auto fixtureB = (TBaluPhysShapeInstance*)contact->GetFixtureB()->GetUserData();

	if (fixtureA->GetParent() != fixtureB->GetParent())
	{
		if (fixtureA->IsSensor())
			//collisions.push_back(TCollisionInfo(fixtureA, fixtureB));
			begin_contact.push_back(TCollisionInfo(fixtureA, fixtureB));
		else if (fixtureB->IsSensor())
			//collisions.push_back(TCollisionInfo(fixtureB, fixtureA));
			begin_contact.push_back(TCollisionInfo(fixtureB, fixtureA));
	}
}
void TBaluSceneInstance::EndContact(b2Contact* contact)
{
	auto fixtureA = (TBaluPhysShapeInstance*)contact->GetFixtureA()->GetUserData();
	auto fixtureB = (TBaluPhysShapeInstance*)contact->GetFixtureB()->GetUserData();

	if (fixtureA->GetParent() != fixtureB->GetParent())
	{
		if (fixtureA->IsSensor())
			//collisions.push_back(TCollisionInfo(fixtureA, fixtureB));
			end_contact.push_back(TCollisionInfo(fixtureA, fixtureB));
		else if (fixtureB->IsSensor())
			//collisions.push_back(TCollisionInfo(fixtureB, fixtureA));
			end_contact.push_back(TCollisionInfo(fixtureB, fixtureA));
		/*auto iter = std::find_if(collisions.begin(), collisions.end(),
			[&](TBaluSceneInstance::TCollisionInfo& p)
		{
			return (p.A == fixtureA && p.B == fixtureB) || (p.A == fixtureB && p.B == fixtureA);
		});
		if (iter != collisions.end())
			collisions.erase(iter);*/
	}
}
void TBaluSceneInstance::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
	B2_NOT_USED(contact);
	B2_NOT_USED(oldManifold);
}
void TBaluSceneInstance::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
	B2_NOT_USED(contact);
	B2_NOT_USED(impulse);
}

TViewport* TBaluSceneInstance::GetViewport(std::string name)
{
	return &viewports[name];
}

TBaluSceneInstance::TBaluSceneInstance(TBaluScene* source, TResources* resources)
{
	this->resources = resources;
	phys_world = std::make_unique<b2World>(b2Vec2(0, -1));

	phys_debug.Create();

	phys_world->SetDebugDraw(&phys_debug);
	phys_world->SetContactListener(this);

	for (int i = 0; i < source->GetInstancesCount(); i++)
	{
		auto source_instance = source->GetInstance(i);
		auto instance = CreateInstance(source_instance->balu_class, source->GetInstance(i)->transform);
		instance->SetTransform(source_instance->transform);
	}
}

TBaluSceneInstance::TBaluSceneInstance(TBaluSceneInstance&& right)
{
	phys_world = std::move(right.phys_world);
	instances = std::move(right.instances);
}

TBaluInstance* TBaluSceneInstance::CreateInstance(TBaluClass* use_class, TBaluTransform transform)
{
	instances.push_back(std::make_unique<TBaluInstance>(use_class, phys_world.get(), transform, resources));
	return instances.back().get();
}

TVec2 TBaluSceneInstance::WorldToScene(const TVec2& v)
{
	//TODO
	return TVec2();
}

TVec2 TBaluSceneInstance::SceneToWorld(const TVec2& v)
{
	//TODO
	return TVec2();
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
		if (polygons[i]->GetSpritePolygon()->IsCustomDraw())
		{
			
			polygons[i]->RenderCustom(custom_draw);
		}
		else
		{
			results.emplace_back();
			polygons[i]->Render(results.back());
		}
	}
}

void TBaluSceneInstance::OnPrePhysStep()
{
	for (int i = 0; i < instances.size(); i++)
		instances[i]->DoBeforePhysicsStep();
}
void TBaluSceneInstance::PhysStep(float step)
{
	//collisions.clear();
	begin_contact.clear();
	end_contact.clear();
	phys_world->Step(step*10, 3, 5);
}

void TBaluSceneInstance::OnProcessCollisions()
{
	//for (int i = 0; i < collisions.size(); i++)
	//{
	//	collisions[i].A->GetParent()->DoSensorCollide(collisions[i].A->GetParentSensor(), collisions[i].B->GetParent(), collisions[i].B);
	//}
	for (int i = 0; i < begin_contact.size(); i++)
	{
		begin_contact[i].A->GetParent()->DoBeginContact(begin_contact[i].A->GetParentSensor(), begin_contact[i].B->GetParent(), begin_contact[i].B);
	}
	for (int i = 0; i < end_contact.size(); i++)
	{
		end_contact[i].A->GetParent()->DoEndContact(end_contact[i].A->GetParentSensor(), end_contact[i].B->GetParent(), end_contact[i].B);
	}
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
		instances[i]->DoKeyDown(key);
}

void TBaluSceneInstance::UpdateTransform()
{
	for (int i = 0; i < instances.size(); i++)
	{
		instances[i]->UpdateTranform();
	}
}

void TBaluSceneInstance::DebugDraw()
{
	uint32 flags = 0;
	flags |= b2Draw::e_shapeBit;
	flags |= b2Draw::e_jointBit;
	//flags |= b2Draw::e_aabbBit;
	flags |= b2Draw::e_centerOfMassBit;
	phys_debug.SetFlags(flags);

	//phys_world->DrawDebugData();
	//phys_debug.Flush();
}