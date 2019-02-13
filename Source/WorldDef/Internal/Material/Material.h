#pragma once

#include "../../Interface.h"

#include "../Common/Common.h"

namespace BaluEngine
{
	namespace WorldDef
	{
		namespace Internal
		{
			class TMaterial : public TWorldObject, public IMaterial
			{
			protected:
				void InitAllProperties()
				{
					InitProperty_BlendMode();
					InitProperty_AlfaTestLevel();
					InitProperty_AlfaTestFunc();
					InitProperty_BlendFunc();
					InitProperty_BlendLeft();
					InitProperty_BlendRight();
					InitProperty_TextureFilter();
					InitProperty_TextureClamp();
					InitProperty_ImagePath();
					InitProperty_Color();
				}
			public:

				BALU_ENGINE_REGISTER_PROPERTY(BlendMode,PropertyType::TransparentMode, TTransparentMode::TM_NONE)
				BALU_ENGINE_REGISTER_PROPERTY(AlfaTestLevel, PropertyType::Float, 0)
				BALU_ENGINE_REGISTER_PROPERTY(AlfaTestFunc, PropertyType::AlphaTestFunc, TAlphaTestFunc::AT_LESS)
				BALU_ENGINE_REGISTER_PROPERTY(BlendFunc, PropertyType::BlendFunc, TBlendFunc::BF_ADD)
				BALU_ENGINE_REGISTER_PROPERTY(BlendLeft, PropertyType::BlendEquation, TBlendEquation::BE_DST_ALPHA)
				BALU_ENGINE_REGISTER_PROPERTY(BlendRight, PropertyType::BlendEquation, TBlendEquation::BE_ONE_MINUS_SRC_ALPHA)
				BALU_ENGINE_REGISTER_PROPERTY(TextureFilter, PropertyType::TexFilter, TTexFilter::Nearest)
				BALU_ENGINE_REGISTER_PROPERTY(TextureClamp, PropertyType::TexClamp, TTexClamp::NONE)
				
				BALU_ENGINE_REGISTER_PROPERTY(ImagePath, PropertyType::String, "images/default.png")
				BALU_ENGINE_REGISTER_PROPERTY(Color, PropertyType::ColorWithAlpha, BaluLib::TVec4(1,1,1,1))

				static TWorldObjectType GetWorldObjectType()
				{
					return TWorldObjectType::Material;
				}

				TMaterial(std::string material_name, IWorld* world);

				void Save(pugi::xml_node& parent_node, const int version)const;
				void Load(const pugi::xml_node& instance_node, const int version, IWorld* world);
			};
		}
	}
}

