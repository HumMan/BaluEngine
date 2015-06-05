#pragma once

#include <vector>
#include "../../BaluLib/Source/Math/vec.h"
#include "../../BaluLib/Source/Math/matrix.h"

#include <box2D.h>

#include "EngineInterfaces\IMaterial.h"

namespace pugi
{
	class xml_node;
}

class TBaluWorld;

class TBaluMaterial: public EngineInterface::IBaluMaterial, public EngineInterface::IBaluWorldObject
{
public:
	enum class TTransparentMode
	{
		TM_NONE,
		TM_ALPHA_BLEND,
		TM_ALPHA_TEST,
	};
	
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
	TTransparentMode blend_mode;
	float alpha_test_value;
	TAlphaTestFunc alpha_test_func;
	TBlendFunc blend_func;
	TBlendEquation blend_left, blend_right;
	TTexFilter texture_filter;
	TTexClamp texture_clamp;
	std::string image_path;
	TVec4 color;

#ifdef BALUENGINE_DESIGN_TIME
	TBaluWorld* world;
#endif

public:
	TBaluMaterial();

#ifdef BALUENGINE_DESIGN_TIME
	TBaluMaterial(TBaluWorld* world);	
#endif

	void SetBlendMode(TTransparentMode mode);
	void SetAlphaTestValue(float alpha_test_value);
	
	void SetName(std::string name);
	std::string GetName();

	void SetImagePath(std::string image_path);
	std::string GetImagePath();

	void SetColor(TVec4 color);

	EngineInterface::IProperties* GetProperties();

	void Save(pugi::xml_node& parent_node, const int version);
	void Load(const pugi::xml_node& instance_node, const int version);
};