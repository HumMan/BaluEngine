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

class TBaluTransform
{
public:
	TVec2 position;
	b2Rot angle;
};

inline b2Vec2 ToB2Vec(TVec2 vec)
{
	return *(b2Vec2*)&vec;
}

inline TVec2 FromB2Vec(b2Vec2 vec)
{
	return *(TVec2*)&vec;
}

class TWorldObjectDef
{
public:
	virtual std::string GetName() = 0;
	virtual ~TWorldObjectDef(){}
};

class BALUENGINEDLL_API TBaluMaterialDef : public TWorldObjectDef
{
public:
	std::string GetName()
	{
		return material_name;
	}
	//extureId text_id; //временно, только для прототипа редактора
	TBaluMaterialDef()
	{
		color = TVec4(1, 1, 1, 1);
		blend_mode = TTransparentMode::TM_NONE;
		alpha_test_value = 0.5;
		texture_filter = TTexFilter::Bilinear;
		texture_clamp = TTexClamp::NONE;
	}

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
	enum class TPolygonMode
	{
		Point,
		Line,
		Fill
	};

	enum class TBlendFunc
	{
		BF_ADD,
		BF_SUBTRACT
	};
	enum class TBlendEquation
	{
		BE_SRC_COLOR,
		BE_ONE_MINUS_SRC_COLOR,
		BE_SRC_ALPHA,
		BE_ONE_MINUS_SRC_ALPHA,
		BE_DST_COLOR,
		BE_ONE_MINUS_DST_COLOR,
		BE_DST_ALPHA,
		BE_ONE_MINUS_DST_ALPHA,
		BE_CONSTANT_COLOR,
		BE_ONE_MINUS_CONSTANT_COLOR,
		BE_CONSTANT_ALPHA,
		BE_ONE_MINUS_CONSTANT_ALPHA
	};

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
	enum class TTexFilter
	{
		Nearest,
		Linear,
		Bilinear,
		Trilinear,
		BilinearAniso,
		TrilinearAniso
	};

	enum class TTexClamp
	{
		NONE = 0,
		S = 1,
		T = 2,
		R = 4,
		ST = 1 | 2,
		STR = 1 | 2 | 4
	};
	TAlphaTestFunc alpha_test_func;

	TBlendFunc blend_func;

	TBlendEquation blend_left, blend_right;

	TTexFilter texture_filter;

	TTexClamp texture_clamp;

	void Save(pugi::xml_node& parent_node, const int version);
	void Load(const pugi::xml_node& node, const int version);
};

class TBaluSpritePolygonDef : public TWorldObjectDef
{
public:
	std::string GetName()
	{
		return "SpritePolygon";
	}

	TBaluMaterialDef* material;

	TAABB<float, 2> aabb;
	TBaluTransform transform;//TODO все трансформации применять не к объекту, а хранить отдельно

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

	TOBB<float, 2> GetOBB();

	void Save(pugi::xml_node& parent_node, const int version);
	void Load(const pugi::xml_node& node, const int version);
};

class TBaluSpriteDef : public TWorldObjectDef
{
public:
	std::string GetName()
	{
		return sprite_name;
	}
	std::string sprite_name;
	
	std::vector<std::unique_ptr<TBaluSpritePolygonDef>> polygons;

	void Save(pugi::xml_node& parent_node, const int version);
	void Load(const pugi::xml_node& node, const int version);
};

class TBaluShapeDef : public TWorldObjectDef
{
protected:
	 
public:
	std::string GetName()
	{
		return "PhysShape";
	}
	virtual ~TBaluShapeDef(){}
	virtual void Save(pugi::xml_node& parent_node, const int version)=0;
	virtual TOBB<float, 2> GetOBB() = 0;
	virtual b2Shape& GetB2Shape() = 0;
};

class TBaluPolygonShapeDef : public TBaluShapeDef
{
public:
	std::string GetName()
	{
		return "PolygonShape";
	}
	TBaluPolygonShapeDef()
	{
		aabb = TAABB<float, 2>(TVec2(0, 0), TVec2(0, 0));
		transform.position = TVec2(0, 0);
		transform.angle.Set(0);
	}
	TAABB<float, 2> aabb;

	TBaluTransform transform;//TODO все трансформации применять не к объекту, а хранить отдельно

	b2PolygonShape b2shape;
	//b2FixtureDef b2fixture_def;
	void Save(pugi::xml_node& parent_node, const int version);

	TOBB<float, 2> GetOBB();

	b2Shape& GetB2Shape(){ return b2shape; }
};

class TBaluCircleShapeDef : public TBaluShapeDef
{
public:
	std::string GetName()
	{
		return "CircleShape";
	}
	TBaluTransform transform;
	b2CircleShape b2shape;

	void Save(pugi::xml_node& parent_node, const int version);

	TOBB<float, 2> GetOBB();

	b2Shape& GetB2Shape(){ return b2shape; }
};

class TBaluPhysBodyDef : public TWorldObjectDef
{
public:
	std::string GetName()
	{
		return phys_body_name;
	}
	std::string phys_body_name;
	std::vector<std::unique_ptr<TBaluShapeDef>> fixtures;
	b2BodyDef b2body_def;

	void Save(pugi::xml_node& parent_node, const int version);
	virtual ~TBaluPhysBodyDef();
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
	std::string GetName()
	{
		return "PrismaticJoint";
	}
	b2PrismaticJointDef b2joint_def;
	void Save(pugi::xml_node& parent_node, const int version);
};

class TBaluSpriteInstanceDef: public TWorldObjectDef
{
public:
	std::string GetName()
	{
		return "SpriteInstance";
	}
	TBaluSpriteDef* sprite;
	std::string tag;
	TBaluTransform transform;

	TOBB<float, 2> GetOBB();

	void Save(pugi::xml_node& parent_node, const int version);
};

class TBaluBodyInstanceDef : public TWorldObjectDef
{
public:
	std::string GetName()
	{
		return "BodyInstance";
	}
	TBaluPhysBodyDef* body;
	std::string tag;
	TBaluTransform transform;

	TOBB<float, 2> GetOBB();

	void Save(pugi::xml_node& parent_node, const int version);
};

class TBaluClass : public TWorldObjectDef
{
public:
	std::string GetName()
	{
		return class_name;
	}
	std::string class_name;
	
	std::vector<std::unique_ptr<TBaluSpriteInstanceDef>> sprites;
	std::vector<std::unique_ptr<TBaluBodyInstanceDef>> bodies;

	std::vector<std::unique_ptr<TBaluJointDef>> joints;

	void Save(pugi::xml_node& parent_node, const int version);
	virtual ~TBaluClass();
};

class TBaluInstanceDef : public TWorldObjectDef
{
public:
	std::string GetName()
	{
		return "ClassInstance";
	}
	std::string name;
	std::string class_name;
	TBaluTransform instance_transform;
	void Save(pugi::xml_node& parent_node, const int version);
};

class TBaluSceneDef : public TWorldObjectDef
{
public:
	std::string GetName()
	{
		return scene_name;
	}
	std::string scene_name;
	std::vector<TBaluInstanceDef> instances;
	std::vector<std::unique_ptr<TBaluJointDef>> scene_joints;
	void Save(pugi::xml_node& parent_node, const int version);
	virtual ~TBaluSceneDef();
};

class TBaluWorldDef
{
public:
	std::map<std::string, TBaluMaterialDef> materials;
	std::map<std::string, TBaluSpriteDef> sprites;
	std::map<std::string, TBaluPhysBodyDef> phys_bodies;
	std::map<std::string, TBaluClass> classes;
	std::map<std::string, TBaluSceneDef> scenes;

	void Save(pugi::xml_node& parent_node, const int version);
	void Load(const pugi::xml_node& node, const int version);
	virtual ~TBaluWorldDef();
};