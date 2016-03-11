#pragma once

#include <World/ICommon.h>

namespace EngineInterface
{
	

	class IBaluMaterial: public virtual IBaluWorldObject
	{
	public:
		static std::string GetDefaultName()
		{
			return "material";
		}
		virtual void SetImagePath(std::string image_path) = 0;
		virtual std::string GetImagePath() = 0;
		virtual void SetColor(TVec4 color) = 0;
	};

#ifdef BALUENGINEDLL_EXPORTS
	class TBaluMaterial : public TBaluWorldObject, public IBaluMaterial, public TChangeListenerArray
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

	public:
		static TWorldObjectType GetWorldObjectType()
		{
			return TWorldObjectType::Material;
		}
		IBaluWorld* GetWorld()
		{
			return world;
		}

		TBaluMaterial(std::string material_name, TBaluWorld* world);
		void SetBlendMode(TTransparentMode mode);
		void SetAlphaTestValue(float alpha_test_value);

		void SetImagePath(std::string image_path);
		std::string GetImagePath();

		void SetColor(TVec4 color);

		IProperties* GetProperties();

		void Save(pugi::xml_node& parent_node, const int version);
		void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world);

		IAbstractEditor* CreateEditor(TDrawingHelperContext drawing_context, IBaluWorldInstance* world_instance);
	};
#endif

}

