#pragma once

#include <map>

#include <baluScript.h>

#include <baluRender.h>
#include <Box2D.h>

#include "exportMacro.h"

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

	//compiled geometry
	std::vector<int> indices;
	std::vector<TVec2> vertices;
public:
	TOBB<float, 2> GetOBB();
};

class TBaluPhysShape
{
protected:
	TBaluTransform phys_shape_transform;
public:
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

	TOBB<float, 2> GetOBB();

	b2Shape& GetB2Shape(){ return b2shape; }
};


class TBaluSprite
{
private:
	std::string sprite_name;
	TBaluSpritePolygon sprite_polygon;
	
	std::unique_ptr<TBaluPhysShape> phys_shape;
	
	int layer;

	
public:
	TBaluSprite(){}

	void SetPhysShape(TBaluPhysShape* shape);
};

class TBaluSpriteInstance
{
public:
	TBaluSprite* sprite;
	std::string tag;
	TBaluTransform transform;

	TOBB<float, 2> GetOBB();

	void GetSpriteGeometry(std::vector<int> index, std::vector<TVec2> vertex);
	void GetSpriteGeometrySize(int& indices, int& vertices);
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
	void ConstructPhysBody(b2Body& body);

	TBaluSpriteInstance* AddSprite(TBaluSprite* sprite);
	void RemoveSprite(TBaluSprite* sprite);
};


class TBaluInstance
{
private:
	int uid;
	TBaluClass* instance_class;
	TBaluTransform instance_transform;

	//TCustomMembersValues custom_values;

	//runtime
	//b2Body* phys_body
	//sprite_geometry_indices, vertices
	//
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

	TBaluInstance* CreateInstance(char* class_name);

	TVec2 WorldToScene(const TVec2& v);
	TVec2 SceneToWorld(const TVec2& v);
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

	TBaluMaterial* CreateMaterial(char* mat_name, char* tex_path, TVec4 use_color);
	TBaluSprite* CreateSprite(char* sprite_name, char* mat_name, TVec2 use_size, float use_local_angle, TVec2 use_local_pos, float use_z_bias);
	TBaluClass* CreateClass(char* class_name);
	TBaluScene* CreateScene(char* scene_name);

	TVec2 ScreenToWorld(const TVec2& v);
	TVec2 WorldToScreen(const TVec2& v);

	void SetAcitveScene();
};

class TBaluEngineInternal;

BALUENGINEDLL_API int Init();

class BALUENGINEDLL_API  TBaluEngine
{
private:
	std::unique_ptr<TBaluEngineInternal> p;
public:

	//void CallEvent(TBaluEvent use_event, int par0);
public:
	TBaluEngine(int hWnd, TVec2i use_size);
	~TBaluEngine();
	void Start();
	void Step(float step, double time);
	void SetViewport(TVec2i use_size);

	void OnMouseLeftUp();
	void OnMouseLeftDown();
	void OnMouseRightUp();
	void OnMouseRightDown();
	void OnMouseMiddleUp();
	void OnMouseMiddleDown();
	void OnMouseMove(TVec2i use_client_mouse_pos);
	void OnMouseScroll(float delta);
	void UpdateKeyStates(unsigned char new_keystates[]);
	void UpdateMouseState(bool lpressed, bool mpressed, bool rpressed, TVec2i use_client_mouse_pos);
};
