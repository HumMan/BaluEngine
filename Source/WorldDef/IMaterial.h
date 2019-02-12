#pragma once

namespace BaluEngine
{
	namespace WorldDef
	{
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

