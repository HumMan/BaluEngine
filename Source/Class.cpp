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

TBaluClass::TBaluClass()
{
}
TBaluClass::TBaluClass(TBaluClass&& right)
{
	class_name = std::move(right.class_name);
	sprites = std::move(right.sprites);
}
TBaluClass::~TBaluClass()
{

}

void TBaluClass::OnMouseMove(TMouseMoveCallback)
{

}

TBaluClassPhysBody& TBaluClass::GetPhysBody()
{
	return phys_body;
}

TSensor* TBaluClassPhysBody::CreateSensor(TBaluPhysShape* shape)
{
	sensors.push_back(std::make_unique<TSensor>(shape));
	return sensors.back().get();
}


TBaluClass::TBaluSpriteInstance* TBaluClass::AddSprite(TBaluSprite* sprite)
{
	sprites.push_back(std::make_unique<TBaluClass::TBaluSpriteInstance>(sprite));
	return sprites.back().get();
}

void TBaluClass::RemoveSprite(TBaluSprite* sprite)
{

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

void TBaluClass::OnKeyDown(TKey key, KeyDownCallback callback)
{

}

void TBaluClass::OnBeforePhysicsStep(BeforePhysicsCallback callback)
{

}

void TBaluClass::OnSensorCollide(TSensor* sensor, SensorCollideCallback callback)
{

}