#pragma once

#include "baluEditorDefs.h"

#include <string>
#include <map>
#include <vector>

#include <baluLib.h>
#include <baluRender.h>

#include <Box2D.h>

class TBaluMaterial
{
	TBaluMaterialDef material_def;
	TTextureId texture_id;
public:
};

class TBaluSprite
{
	TBaluMaterial* material;
	TBaluSpriteDef sprite_def;
};

class TBaluShape
{
	virtual ~TBaluShape();
};

class TBaluPolygonShape : public TBaluShape
{
	TBaluPolygonShapeDef shape_def;
	b2Fixture* b2fixture;
	b2Body* parent_b2body;
};

class TBaluPhysBody
{
	TBaluPhysBodyDef phys_body_def;
	std::vector<std::unique_ptr<TBaluShape>> fixtures;
	b2Body* b2body;
};

class TBaluJoint
{
	virtual ~TBaluJoint();
};

class TBaluPrismaticJoint :public TBaluJoint
{
	TBaluPrismaticJointDef joint_def;
	b2PrismaticJoint* b2joint;
	TBaluPhysBody *bodyA;
	TBaluPhysBody *bodyB;
};

class TBaluInstance
{
	TBaluInstanceDef instance_def;

	std::vector<TBaluSprite*> sprites;
	std::vector<TTransform> sprites_transform;

	std::vector<TBaluPhysBody> bodies;

	std::vector<std::unique_ptr<TBaluJoint>> instance_joints;

public:

	void AddSprite(TBaluSprite* sprite, TTransform sprite_transform);
	void RemoveSprite(TBaluSprite* sprite);

	TBaluPhysBody* CreatePhysBody(TBaluPhysBodyDef phys_body_def);
	void DestroyPhysBody(TBaluPhysBody* balu_class);

	TBaluJoint* CreateJoint(TBaluPrismaticJointDef joint_def);
	void DestroyJoint(TBaluJoint* balu_joint);
};

class TBaluScene
{
	std::vector<TBaluInstance> instances;
	std::vector<std::unique_ptr<TBaluJoint>> scene_joints;
public:
	TBaluInstance* CreateInstance(TBaluInstanceDef instance_def);
	void DestroyInstance(TBaluInstance* balu_instance);

	TBaluJoint* CreateJoint(TBaluPrismaticJointDef joint_def);
	void DestroyJoint(TBaluJoint* balu_joint);
};

class TBaluWorld
{
	//shared
	std::map<std::string, TBaluMaterial> materials;
	std::map<std::string, TBaluSprite> sprites;

	//instances
	//std::vector<TBaluPhysBody> phys_bodies;
	std::vector<TBaluScene> scenes;
	//std::vector<TBaluJoint> joints;

public:
	TBaluMaterial* CreateMaterial(TBaluMaterialDef material_def);
	void DestroyMaterial(TBaluMaterial* balu_material);

	TBaluSprite* CreateSprite(TBaluSpriteDef sprite_def);
	void DestroySprite(TBaluSprite* balu_sprite);

	TBaluScene* CreateScene(TBaluSceneDef scene_def);
	void DestroyScene(TBaluScene* balu_scene);
};