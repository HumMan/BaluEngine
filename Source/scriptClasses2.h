#pragma once

#include <map>

#include <baluScript.h>

#include <baluRender.h>
#include <Box2D.h>

class TBaluEngine;

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

class TBaluMaterial
{
public:
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
private:
	TAlphaTestFunc alpha_test_func;
	TBlendFunc blend_func;
	TBlendEquation blend_left, blend_right;
	TTexFilter texture_filter;
	TTexClamp texture_clamp;

	std::string material_name;
	std::string image_path;
	TVec4 color;
public:

};


class TBaluSpritePolygon
{
public:
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
private:
	TBaluMaterial* material;

	TAABB<float, 2> aabb;

	std::vector<TVec2> polygon_vertices;
	std::vector<TVec2> tex_coordinates;
	TPolygonMode polygone_mode;
	TPrimitive primitive;

	TBaluTransform sprite_polygon_transform;
public:
	TOBB<float, 2> GetOBB();
};

class TBaluPhysShape
{
protected:
	TBaluTransform phys_shape_transform;
public:
	std::string GetName()
	{
		return "PhysShape";
	}
	virtual ~TBaluPhysShape(){}
	virtual TOBB<float, 2> GetOBB() = 0;
	virtual b2Shape& GetB2Shape() = 0;
	virtual void BuildFixture(b2Body &body) = 0;
};


class TBaluPolygonShape : public TBaluPhysShape
{
private:
	b2PolygonShape b2shape;
public:
	std::string GetName()
	{
		return "PolygonShape";
	}
	TBaluPolygonShape()
	{
	}
	TOBB<float, 2> GetOBB();

	b2Shape& GetB2Shape(){ return b2shape; }
};


class TBaluSprite
{
private:
	std::string sprite_name;
	TBaluSpritePolygon sprite_polygon;
	
	std::unique_ptr<TBaluPhysShape> phys_shape;
	
public:
	std::string GetName()
	{
		return sprite_name;
	}
	TBaluSprite(){}
};

class TBaluSpriteInstance
{
public:
	std::string GetName()
	{
		return "SpriteInstance";
	}
	TBaluSprite* sprite;
	std::string tag;
	TBaluTransform transform;

	TOBB<float, 2> GetOBB();
};


class TBaluClass
{
private:
	std::string class_name;
	std::vector<std::unique_ptr<TBaluSpriteInstance>> sprites;
public:
	std::string GetName()
	{
		return class_name;
	}
	TBaluClass(){}
	TBaluClass(TBaluClass&& right)
	{
		class_name = std::move(right.class_name);
		sprites = std::move(right.sprites);
	}
	virtual ~TBaluClass();
	void BuildFixtures(b2Body& body);
};


class TBaluInstance
{
private:
	std::string name;
	TBaluClass* instance_class;
	TBaluTransform instance_transform;
public:
	void Build();
	TOBB<float, 2> GetOBB();
};


class TBaluScene
{
private:
	std::string scene_name;
	std::vector<std::unique_ptr<TBaluInstance>> instances;
public:
	std::string GetName()
	{
		return scene_name;
	}
	TBaluScene(){}
	TBaluScene(TBaluScene&& right)
	{
		scene_name = std::move(right.scene_name);
		instances = std::move(right.instances);
	}
};

class TBaluWorldDef
{
private:
	std::map<std::string, TBaluMaterial> materials;
	std::map<std::string, TBaluSprite> sprites;
	std::map<std::string, TBaluClass> classes;
	std::map<std::string, TBaluScene> scenes;
public:
	virtual ~TBaluWorldDef();
};