#pragma once

#include <string>
#include <map>
#include <vector>

#include <baluLib.h>
#include <baluRender.h>

#include <Box2D.h>

class Archive;

class TBaluMaterialDef
{
public:
	std::string material_name;
	std::string image_path;
	TVec4 color;
	enum TTransparentMode
	{
		TM_NONE,
		TM_ALPHA_BLEND,
		TM_ALPHA_TEST,
	};
	TTextureId texture;
	TTransparentMode blend_mode;

	float alpha_test_value;
	TBaluRender::TAlphaTest::TAlphaTestFunc alpha_test_func;

	TBaluRender::TBlend::TBlendFunc blend_func;
	TBaluRender::TBlend::TBlendEquation blend_left, blend_right;
	TTexFilter::Enum texture_filter;
	TTexClamp::Enum texture_clamp;

	void Serialize(Archive ar, const int version);
};

class TBaluMaterial
{
	TBaluMaterialDef material_def;
	TTextureId texture_id;
public:
};

class TBaluSpriteDef
{
	std::string sprite_name;
	std::vector<TVec2> polygon_vertices;
	std::vector<TVec2> tex_coordinates;
	TPolygonMode::Enum polygone_mode;
	TPrimitive::Enum primitive;
};

class TBaluSprite
{
	TBaluMaterial* material;
	TBaluSpriteDef sprite_def;
};

class TBaluShapeDef
{
	virtual ~TBaluShapeDef();
};

class TBaluPolygonShapeDef : public TBaluShapeDef
{
	b2PolygonShape b2shape;
	b2FixtureDef b2fixture_def;
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

class TBaluPhysBodyDef
{
	std::string phys_body_name;
	std::vector<std::unique_ptr<TBaluShapeDef>> fixtures;
	b2BodyDef b2body_def;
};

class TBaluPhysBody
{
	TBaluPhysBodyDef phys_body_def;
	std::vector<std::unique_ptr<TBaluShape>> fixtures;
	b2Body* b2body;
};

class TBaluJointDef
{
	virtual ~TBaluJointDef();

	std::string bodyA;
	std::string bodyB;

	bool is_interinstance_joint;
	std::string instanceA;
	std::string instanceB;
};

class TBaluPrismaticJointDef :public TBaluJointDef
{
	b2PrismaticJointDef b2joint_def;
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

class TTransform
{
public:
	//TVec2 offset;
	b2Rot rotation;
};

class TBaluClass
{
	std::string class_name;
	std::vector<std::string> sprites;
	std::vector<std::string> sprites_tags;
	std::vector<TTransform> sprites_transform;

	std::vector<std::string> bodies;
	std::vector<std::string> bodies_tags;
	std::vector<TTransform> bodies_transform;

	std::vector<std::unique_ptr<TBaluJoint>> joints;
};

class TBaluInstanceDef
{
	std::string name;
	std::string class_name;
	TTransform instance_transform;
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

	TBaluJoint* CreateJoint(TBaluJointDef joint_def);
	void DestroyJoint(TBaluJoint* balu_joint);
};

class TBaluSceneDef
{
	std::vector<TBaluInstanceDef> instances;
	std::vector<std::unique_ptr<TBaluJointDef>> scene_joints;
};

class TBaluScene
{
	std::vector<TBaluInstance> instances;
	std::vector<std::unique_ptr<TBaluJoint>> scene_joints;
public:
	TBaluInstance* CreateInstance(TBaluInstanceDef instance_def);
	void DestroyInstance(TBaluInstance* balu_instance);

	TBaluJoint* CreateJoint(TBaluJointDef joint_def);
	void DestroyJoint(TBaluJoint* balu_joint);
};

class TBaluWorldDef
{
	std::map<std::string, TBaluMaterialDef> materials;
	std::map<std::string, TBaluSpriteDef> sprites;
	std::map<std::string, TBaluPhysBodyDef> phys_bodies;
	std::map<std::string, TBaluClass> classes;
	std::vector<TBaluSceneDef> scenes;

public:
	void Serialize(Archive ar, const int version);
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