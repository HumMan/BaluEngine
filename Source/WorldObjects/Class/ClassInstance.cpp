#include "IClassInstance.h"
#include "IClass.h"

#include <World/IWorldInstance.h>

using namespace EngineInterface;

TBaluClassInstance* TBaluInstance::GetClass()
{
	return instance_class;
}

bool TBaluInstance::PointCollide(TVec2 scene_space_point)
{
	TVec2 p = instance_transform.ToLocal(scene_space_point);
	return instance_class->GetClass()->PointCollide(p);
}

TOBB2 TBaluInstance::GetOBB()
{
	auto aabb = GetClass()->GetClass()->GetAABB();
	return instance_transform.ToGlobal(aabb);
}

TBaluInstance::TBaluInstance(TBaluSceneClassInstance* source, TBaluSceneInstance* scene)
	:skeleton(source->GetClass()->GetSkeleton(), this, scene->GetResources()), skeleton_animation(&skeleton, source->GetClass()->GetSkeletonAnimation())
{
	tag = nullptr;
	this->instance_class = dynamic_cast<TBaluWorldInstance*>(scene->GetWorld())->GetClassInstance(source->GetClass());
	instance_transform = source->GetTransformWithScale();
	this->scene = scene;
	skeleton_animation.Init();

	for (int i = 0; i < source->GetClass()->GetSpritesCount(); i++)
	{
		sprites.push_back(std::make_unique<TBaluClassInstanceSpriteInstance>(source->GetClass()->GetSprite(i), this, scene->GetResources()));
	}

	phys_body = std::make_unique<TBaluClassPhysBodyIntance>(scene->GetPhysWorld(), source->GetClass()->GetPhysBody(), this);

	scene->AddInstance(this);
}

TBaluInstance::TBaluInstance(TBaluClass* source, TBaluTransform transform, TVec2 scale, TBaluSceneInstance* scene)
	: skeleton(source->GetSkeleton(), this, scene->GetResources()), skeleton_animation(&skeleton, source->GetSkeletonAnimation())
{
	tag = nullptr;
	this->scene = scene;
	skeleton_animation.Init();
	instance_transform = TBaluTransformWithScale(transform, scale);
	this->instance_class = dynamic_cast<TBaluWorldInstance*>(scene->GetWorld())->GetClassInstance(source);

	for (int i = 0; i < source->GetSpritesCount(); i++)
	{
		sprites.push_back(std::make_unique<TBaluClassInstanceSpriteInstance>(source->GetSprite(i), this, scene->GetResources()));
	}

	phys_body = std::make_unique<TBaluClassPhysBodyIntance>(scene->GetPhysWorld(), source->GetPhysBody(), this);

	scene->AddInstance(this);
}

void TBaluInstance::SetTransform(TBaluTransform transform)
{
	this->instance_transform.transform = transform;
	if (phys_body->IsEnable())
	{
		phys_body->SetTransform(transform);
	}
}

TBaluTransform TBaluInstance::GetTransform()
{
	return instance_transform.transform;
}
TVec2 TBaluInstance::GetScale()
{
	return this->instance_transform.scale;
}
void TBaluInstance::SetScale(TVec2 scale)
{
	this->instance_transform.scale = scale;
	if (phys_body->IsEnable())
	{
		phys_body->BuildAllFixtures();
	}
}
TProperties* TBaluInstance::GetProperties()
{
	return &properties;
}

TBaluClassPhysBodyIntance* TBaluInstance::GetPhysBody()
{
	return phys_body.get();
}

int TBaluInstance::GetSpritesCount()
{
	return sprites.size();
}

TSceneObjectInstance* TBaluInstance::Clone(TSceneObject* source, TBaluSceneInstance* scene)
{
	return new TBaluInstance(dynamic_cast<TBaluSceneClassInstance*>(source), scene);
}

//TODO uncomment
//TBaluClassInstanceSpriteInstance* TBaluInstance::GetSprite(int index)
//{
//	return sprites[index].get();
//}
//
//TBaluClassInstanceSpriteInstance* TBaluInstance::AddSprite(IBaluClassSpriteInstance* _source)
//{
//	TBaluClassSpriteInstance* source = dynamic_cast<TBaluClassSpriteInstance*>(_source);
//	sprites.push_back(std::make_unique<TBaluClassInstanceSpriteInstance>(source, this, scene->GetResources()));
//	return sprites.back().get();
//}

TAABB2 TBaluInstance::GetAABB()
{
	//TODO
	return TAABB2();
}

TSkeletonAnimationInstance* TBaluInstance::GetSkeletonAnimation()
{
	return &skeleton_animation;
}

bool TBaluInstance::PointCollide(TVec2 class_space_point, EngineInterface::IBaluClassInstanceSpriteInstance* &result)
{
	for (int i = 0; i < sprites.size(); i++)
	{
		bool collide = sprites[i]->GetSource()->PointCollide(class_space_point);
		if (collide)
		{
			result = sprites[i].get();
			return true;
		}
	}
	return false;
}

void TBaluInstance::QueryAABB(TAABB2 frustum, std::vector<TBaluSpritePolygonInstance*>& results)
{
	for (int i = 0; i < sprites.size(); i++)
	{
		if (sprites[i]->GetPolygon()->IsEnable())
		{
			//if (sprites[i]->GetAABB().CollideWith(frustum))
			results.push_back(sprites[i]->GetPolygon());
		}
	}
	skeleton.QueryAABB(frustum, results);
}

void TBaluInstance::UpdateTransform()
{
	if (phys_body->IsEnable())
	{
		instance_transform.transform = phys_body->GetTransform();
	}
	for (int i = 0; i < sprites.size(); i++)
	{
		sprites[i]->UpdateTranform(instance_transform);
	}
	skeleton.UpdateTranform(instance_transform);
}

bool TBaluClassPhysBodyIntance::IsEnable()
{
	return is_enable;
}

void TBaluClassPhysBodyIntance::BuildAllFixtures()
{
	for (int i = 0; i < parent->GetSpritesCount(); i++)
	{
		auto sensor_source = parent->GetSprite(i);
		
		//TODO uncomment
		//sensor_source->GetPhysShape()->BuildFixture(phys_body, TBaluTransformWithScale( sensor_source->GetTransform(), sensor_source->GetScale()));
	}
}

TBaluClassPhysBodyIntance::TBaluClassPhysBodyIntance(b2World* phys_world, TBaluClassPhysBody* source, TBaluInstance* parent)
{
	is_enable = source->IsEnable();
	if (source->IsEnable())
	{
		this->source = source;
		this->phys_world = phys_world;

		auto body_def = source->GetBodyDef();
		auto instance_transform = parent->GetTransform();
		this->parent = parent;
		body_def.position = *(b2Vec2*)&instance_transform.position;
		body_def.angle = instance_transform.angle.GetAngle();
		body_def.linearDamping = 0.1;
		//body_def.angularDamping = 0.1;
		//body_def.fixedRotation = false;
		//if (body_def.type == b2BodyType::b2_dynamicBody)
		//	body_def.angularVelocity = 10;

		phys_body = phys_world->CreateBody(&body_def);

		BuildAllFixtures();
	}
}

void TBaluClassPhysBodyIntance::SetFixedRotation(bool fixed)
{
	if (phys_body->GetType() == b2BodyType::b2_staticBody)
		throw std::invalid_argument("Недоступно для данного типа тела");
	phys_body->SetFixedRotation(fixed);
}

TVec2 TBaluClassPhysBodyIntance::GetLinearVelocity()
{
	if (phys_body->GetType() == b2BodyType::b2_staticBody)
		throw std::invalid_argument("Недоступно для данного типа тела");
	return *(TVec2*)&(phys_body->GetLinearVelocity());
}

void TBaluClassPhysBodyIntance::SetLinearVelocity(TVec2 velocity)
{
	if (phys_body->GetType() == b2BodyType::b2_staticBody)
		throw std::invalid_argument("Недоступно для данного типа тела");
	phys_body->SetLinearVelocity(*(b2Vec2*)&velocity);
}

float TBaluClassPhysBodyIntance::GetAngularVelocity()
{
	if (phys_body->GetType() == b2BodyType::b2_staticBody)
		throw std::invalid_argument("Недоступно для данного типа тела");
	return phys_body->GetAngularVelocity();
}

void TBaluClassPhysBodyIntance::SetAngularVelocity(float velocity)
{
	if (phys_body->GetType() == b2BodyType::b2_staticBody)
		throw std::invalid_argument("Недоступно для данного типа тела");
	phys_body->SetAngularVelocity(velocity);
}

TBaluTransform TBaluClassPhysBodyIntance::GetTransform()
{
	return *(TBaluTransform*)&phys_body->GetTransform();
}

void TBaluClassPhysBodyIntance::SetTransform(TBaluTransform transform)
{
	phys_body->SetTransform(*(b2Vec2*)&transform.position, transform.angle.GetAngle());
}

void TBaluClassInstance::DoKeyDown(TKey key, TBaluInstance* instance)
{
	for (auto& v : on_key_down_callbacks)
	{
		if (v.first == key)
		{
			world_instance->GetScriptEngine()->CallInstanceEvent(v.second, instance);
		}
	}
}

void TBaluClassInstance::DoKeyUp(TKey key, TBaluInstance* instance)
{
	for (auto& v : on_key_up_callbacks)
	{
		if (v.first == key)
		{
			world_instance->GetScriptEngine()->CallInstanceEvent(v.second, instance);
		}
	}
}

void TBaluClassInstance::DoBeforePhysicsStep(TBaluInstance* instance)
{
	for (auto& i : before_physics_callbacks)
	{
		world_instance->GetScriptEngine()->CallInstanceEvent(i, instance);
	}
}

void TBaluClassInstance::DoCollide(TBaluPhysShapeInstance* obj_a, TBaluInstance* obstancle)
{
	for (auto& i : on_collide_callbacks)
	{
		if (i.sprite == obj_a->GetSpriteInstance()->GetSprite() && i.with_class == obstancle->GetClass()->GetClass())
			world_instance->GetScriptEngine()->CallCollide(i.script, obj_a, obstancle);
	}
}

TBaluClassInstance::TBaluClassInstance(TBaluWorldInstance* world_instance, TBaluClass* source)
{
	this->world_instance = world_instance;
	this->source = source;
}

void TBaluClassInstance::CompileScripts()
{
	TBaluScriptInstance& script_engine = *world_instance->GetScriptEngine();
	for (auto& v : source->GetOnBeforePhysicsStep())
	{
		auto method_body = v.GetScriptSource();
		std::string method = std::string("func static BeforePhys(IInstance object)\n{\n") + method_body + "\n}\n";
		before_physics_callbacks.push_back(script_engine.CompileMethod(&v, method.c_str()));
	}
	for (auto& s : source->GetOnKeyDown())
	{
		for (auto& v : s.second)
		{
			auto method_body = v.GetScriptSource();
			std::string method = std::string("func static KeyDown(IInstance object)\n{\n") + method_body + "\n}\n";
			on_key_down_callbacks.push_back(std::pair<TKey, TScriptInstance>(s.first, script_engine.CompileMethod(&v, method.c_str())));
		}
	}
	for (auto& s : source->GetOnKeyUp())
	{
		for (auto& v : s.second)
		{
			auto method_body = v.GetScriptSource();
			std::string method = std::string("func static KeyUp(IInstance object)\n{\n") + method_body + "\n}\n";
			on_key_up_callbacks.push_back(std::pair<TKey, TScriptInstance>(s.first, script_engine.CompileMethod(&v, method.c_str())));
		}
	}
	for (auto& v : source->GetOnCollide())
	{
		auto method_body = v.script.GetScriptSource();
		std::string method = std::string("func static Collide(IPhysShapeInstance source, IInstance obstancle)\n{\n") + method_body + "\n}\n";
		on_collide_callbacks.push_back(TSpriteWithClassCollideInstance(v.sprite, v.with_class, script_engine.CompileMethod(&v.script, method.c_str())));
	}
}


void TBaluClassInstance::CheckScriptErrors(TBaluClass* source, TBaluScriptInstance* script_engine, std::vector<std::string>& errors_list)
{
	for (auto& v : source->GetOnBeforePhysicsStep())
	{
		auto method_body = v.GetScriptSource();
		std::string method = std::string("func static BeforePhys(IInstance object)\n{\n") + method_body + "\n}\n";
		script_engine->CompileMethod(&v, method.c_str());
	}
	for (auto& s : source->GetOnKeyDown())
	{
		for (auto& v : s.second)
		{
			auto method_body = v.GetScriptSource();
			std::string method = std::string("func static KeyDown(IInstance object)\n{\n") + method_body + "\n}\n";
			script_engine->CompileMethod(&v, method.c_str());
		}
	}
	for (auto& s : source->GetOnKeyUp())
	{
		for (auto& v : s.second)
		{
			auto method_body = v.GetScriptSource();
			std::string method = std::string("func static KeyUp(IInstance object)\n{\n") + method_body + "\n}\n";
			script_engine->CompileMethod(&v, method.c_str());
		}
	}
	for (auto& v : source->GetOnCollide())
	{
		auto method_body = v.script.GetScriptSource();
		std::string method = std::string("func static Collide(IPhysShapeInstance source, IInstance obstancle)\n{\n") + method_body + "\n}\n";
		script_engine->CompileMethod(&v.script, method.c_str());
	}
}