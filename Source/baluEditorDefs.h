#pragma once

#include <string>
#include <map>
#include <vector>

#include "exportMacro.h"

#include <baluLib.h>

#include <Box2D.h>

namespace pugi
{
	class xml_node;
}

class TWorldObjectDef
{
public:
	virtual ~TWorldObjectDef(){}
};

class BALUENGINEDLL_API TBaluMaterialDef : public TWorldObjectDef
{
public:
	//extureId text_id; //временно, только для прототипа редактора

	std::string material_name;
	std::string image_path;
	TVec4 color;
	enum class TTransparentMode
	{
		TM_NONE,
		TM_ALPHA_BLEND,
		TM_ALPHA_TEST,
	};
	TTransparentMode blend_mode;

	float alpha_test_value;

	enum class TAlphaTestFunc
	{
		AT_ALWAYS,
		AT_NEVER,
		AT_LEQUAL,
		AT_LESS,
		AT_EQUAL,
		AT_NOTEQUAL,
		AT_GEQUAL,
		AT_GREATER
	};
	TAlphaTestFunc alpha_test_func;
	enum class TBlendFunc
	{
		BF_ADD,
		BF_SUBTRACT
	};
	TBlendFunc blend_func;
	enum TBlendEquation
	{
		BE_SRC_COLOR,
		BE_SRC_ALPHA,
		BE_DST_COLOR,
		BE_DST_ALPHA,
		BE_CONSTANT_COLOR,
		BE_CONSTANT_ALPHA
	};
	TBlendEquation blend_left, blend_right;
	enum class TTexFilter
	{
		Nearest,
		Linear,
		Bilinear,
		Trilinear,
		BilinearAniso,
		TrilinearAniso
	};
	TTexFilter texture_filter;
	enum class TTexClamp
	{
		NONE = 0,
		S = 1,
		T = 2,
		R = 4,
		ST = 1 | 2,
		STR = 1 | 2 | 4
	};
	TTexClamp texture_clamp;

	void Save(pugi::xml_node& parent_node, const int version);
	void Load(const pugi::xml_node& node, const int version);
};

class TBaluSpriteDef : public TWorldObjectDef
{
public:
	std::string sprite_name;
	std::string material_name;

	std::vector<TVec2> polygon_vertices;
	std::vector<TVec2> tex_coordinates;

	enum class TPolygonMode
		{
			Points,
			Lines,
			LineLoop,
			LineStrip,
			Triangles,
			TriangleStrip,
			TriangleFan,
			Quads,
			QuadStrip
		};
	TPolygonMode polygone_mode;
	enum class TPrimitive
	{
		Points,
		Lines,
		LineLoop,
		LineStrip,
		Triangles,
		TriangleStrip,
		TriangleFan,
		Quads,
		QuadStrip
	};
	TPrimitive primitive;

	void Save(pugi::xml_node& parent_node, const int version);
	void Load(const pugi::xml_node& node, const int version);
};

class TBaluShapeDef : public TWorldObjectDef
{
protected:
	 
public:
	virtual ~TBaluShapeDef(){}
	virtual void Save(pugi::xml_node& parent_node, const int version)=0;
	virtual TOBB<float, 2> GetOBB() = 0;
	virtual b2Shape& GetB2Shape() = 0;
};

class TBaluPolygonShapeDef : public TBaluShapeDef
{
public:
	TAABB<float, 2> aabb;

	TVec2 pos;
	b2Rot angle;

	b2PolygonShape b2shape;
	//b2FixtureDef b2fixture_def;
	void Save(pugi::xml_node& parent_node, const int version);

	TOBB<float, 2> GetOBB();

	b2Shape& GetB2Shape(){ return b2shape; }
};

class TBaluCircleShapeDef : public TBaluShapeDef
{
public:
	TVec2 pos;
	b2Rot angle;
	b2CircleShape b2shape;

	void Save(pugi::xml_node& parent_node, const int version);

	TOBB<float, 2> GetOBB();

	b2Shape& GetB2Shape(){ return b2shape; }
};

class TBaluPhysBodyDef : public TWorldObjectDef
{
public:
	std::string phys_body_name;
	std::vector<std::unique_ptr<TBaluShapeDef>> fixtures;
	b2BodyDef b2body_def;

	void Save(pugi::xml_node& parent_node, const int version);
	~TBaluPhysBodyDef();
};

class TBaluJointDef
{
public:
	virtual ~TBaluJointDef()=0;

	std::string bodyA;
	std::string bodyB;

	bool is_interinstance_joint;
	std::string instanceA;
	std::string instanceB;

	virtual void Save(pugi::xml_node& parent_node, const int version);
};

class TBaluPrismaticJointDef :public TBaluJointDef
{
public:
	b2PrismaticJointDef b2joint_def;
	void Save(pugi::xml_node& parent_node, const int version);
};

class TTransform
{
public:
	TVec2 offset;
	b2Rot rotation;
};

class TBaluClass : public TWorldObjectDef
{
public:
	std::string class_name;
	std::vector<std::string> sprites;
	std::vector<std::string> sprites_tags;
	std::vector<TTransform> sprites_transform;

	std::vector<std::string> bodies;
	std::vector<std::string> bodies_tags;
	std::vector<TTransform> bodies_transform;

	std::vector<std::unique_ptr<TBaluJointDef>> joints;

	void Save(pugi::xml_node& parent_node, const int version);
};

class TBaluInstanceDef : public TWorldObjectDef
{
public:
	std::string name;
	std::string class_name;
	TTransform instance_transform;
	void Save(pugi::xml_node& parent_node, const int version);
};

class TBaluSceneDef : public TWorldObjectDef
{
public:
	std::string name;
	std::vector<TBaluInstanceDef> instances;
	std::vector<std::unique_ptr<TBaluJointDef>> scene_joints;
	void Save(pugi::xml_node& parent_node, const int version);
};

class TBaluWorldDef
{
public:
	std::map<std::string, TBaluMaterialDef> materials;
	std::map<std::string, TBaluSpriteDef> sprites;
	std::map<std::string, TBaluPhysBodyDef> phys_bodies;
	std::map<std::string, TBaluClass> classes;
	std::vector<TBaluSceneDef> scenes;

	void Save(pugi::xml_node& parent_node, const int version);
	void Load(const pugi::xml_node& node, const int version);
};