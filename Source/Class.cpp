#include "Class.h"


TBaluClassPhysBody::TBaluClassPhysBody()
{
	enable = false;
}

int TBaluClassPhysBody::GetSensorsCount()
{
	return sensors.size();
}
TSensor* TBaluClassPhysBody::GetSensor(int index)
{
	return sensors[index].get();
}

void TBaluClassPhysBody::SetFixedRotation(bool fixed)
{
	body_def.fixedRotation = fixed;
}
void TBaluClassPhysBody::SetPhysBodyType(TPhysBodyType type)
{
	switch (type)
	{
	case Static:
		body_def.type = b2BodyType::b2_staticBody;
		break;
	case Dynamic:
		body_def.type = b2BodyType::b2_dynamicBody;
		break;
	case Kinematic:
		body_def.type = b2BodyType::b2_kinematicBody;
		break;
	default:
		assert(false);
		break;
	}
}
void TBaluClassPhysBody::Enable(bool enable)
{
	this->enable = enable;
}

bool TBaluClassPhysBody::IsEnable()
{
	return this->enable;
}

b2BodyDef TBaluClassPhysBody::GetBodyDef()
{
	return body_def;
}

std::string TBaluClass::GetName()
{
	return class_name;
}

void TBaluClass::SetName(std::string name)
{
	class_name = name;
}

TBaluClass::TBaluClass() :skeleton_animation(&skeleton)
{
}
TBaluClass::TBaluClass(TBaluClass&& right)
{
	//skeleton = std::move(right.skeleton);
	//skeleton_animation = std::move(right.skeleton_animation);
	class_name = std::move(right.class_name);
	sprites = std::move(right.sprites);
}
TBaluClass::~TBaluClass()
{

}

void TBaluClass::OnMouseMove(TMouseMoveCallback)
{

}

TBaluClassPhysBody* TBaluClass::GetPhysBody()
{
	return &phys_body;
}

TSkeletonAnimation* TBaluClass::GetSkeletonAnimation()
{
	return &skeleton_animation;
}

TSkeleton* TBaluClass::GetSkeleton()
{
	return &skeleton;
}

TSensor* TBaluClassPhysBody::CreateSensor(TBaluPhysShape* shape)
{
	sensors.push_back(std::make_unique<TSensor>(shape));
	return sensors.back().get();
}

EngineInterface::ISensor* TBaluClassPhysBody::CreateSensor(EngineInterface::IBaluPhysShape* shape)
{
	sensors.push_back(std::make_unique<TSensor>(static_cast<TBaluPhysShape*>(shape)));
	return sensors.back().get();
}


TBaluClass::TBaluSpriteInstance* TBaluClass::AddSprite(TBaluSprite* sprite)
{
	sprites.push_back(std::make_unique<TBaluClass::TBaluSpriteInstance>(sprite));
	return sprites.back().get();
}

EngineInterface::IBaluClassSprite* TBaluClass::AddSprite(EngineInterface::IBaluSprite* sprite)
{
	return AddSprite(dynamic_cast<TBaluSprite*>(sprite));
}

void TBaluClass::RemoveSprite(TBaluSprite* sprite)
{

}

int TBaluClass::GetSpritesCount()
{
	return sprites.size();
}

TBaluClass::TBaluSpriteInstance* TBaluClass::GetSprite(int index)
{
	return sprites[index].get();
}

void TBaluClass::CreateBone()
{

}
void TBaluClass::AttachSpriteToBone()
{

}
void TBaluClass::CreateAnimationLine()
{

}
void TBaluClass::SetBoneTransform()
{

}
void TBaluClass::CreateKeyFrame()
{

}
void TBaluClass::SetAnimationTime()
{

}

void TBaluClass::OnKeyDown(TKey key, CallbackWithData<KeyUpDownCallback> callback)
{
	on_key_down_callbacks[key].push_back(callback);
}

void TBaluClass::OnKeyUp(TKey key, CallbackWithData<KeyUpDownCallback> callback)
{
	on_key_up_callbacks[key].push_back(callback);
}


void TBaluClass::OnBeforePhysicsStep(BeforePhysicsCallback callback)
{
	before_physics_callbacks.push_back(callback);
}

//void TBaluClass::OnSensorCollide(TSensor* sensor, SensorCollideCallback callback)
//{
//	sensor->on_sensor_collide_callbacks.push_back(callback);
//}

void TBaluClass::OnBeginContact(TSensor* sensor, SensorCollideCallback callback)
{
	sensor->on_begin_contact.push_back(callback);
}

void TBaluClass::OnBeginContact(EngineInterface::ISensor* sensor, SensorCollideCallback callback)
{
	dynamic_cast<TSensor*>(sensor)->on_begin_contact.push_back(callback);
}

void TBaluClass::OnEndContact(TSensor* sensor, SensorCollideCallback callback)
{
	sensor->on_end_contact.push_back(callback);
}

void TBaluClass::OnEndContact(EngineInterface::ISensor* sensor, SensorCollideCallback callback)
{
	dynamic_cast<TSensor*>(sensor)->on_end_contact.push_back(callback);
}