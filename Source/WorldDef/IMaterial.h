#pragma once

namespace BaluEngine
{
	namespace WorldDef
	{
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

		class IMaterial : public virtual IWorldObject
		{
		public:
			static std::string GetDefaultName()
			{
				return "material";
			}

			BALU_ENGINE_VPROPERTY(BlendMode, TTransparentMode)
			BALU_ENGINE_VPROPERTY(AlfaTestLevel, float)
			BALU_ENGINE_VPROPERTY(AlfaTestFunc, TAlphaTestFunc)
			BALU_ENGINE_VPROPERTY(BlendFunc, TBlendFunc)
			BALU_ENGINE_VPROPERTY(BlendLeft, TBlendEquation)
			BALU_ENGINE_VPROPERTY(BlendRight, TBlendEquation)
			BALU_ENGINE_VPROPERTY(TextureFilter, TTexFilter)
			BALU_ENGINE_VPROPERTY(TextureClamp, TTexClamp)

			BALU_ENGINE_VPROPERTY(ImagePath, std::string)
			BALU_ENGINE_VPROPERTY(Color, BaluLib::TVec4)

		};
	}
}

