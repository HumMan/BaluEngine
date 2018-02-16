#pragma once

#include "../../Interface.h"

#include "../Common/Common.h"

namespace BaluEngine
{
	namespace WorldDef
	{
		namespace Internal
		{

			class TBaluMaterial : public TWorldObject, public IMaterial, public TChangeListenerArray
			{
			public:
				
			private:
				TTransparentMode blend_mode;
				float alpha_test_value;
				TAlphaTestFunc alpha_test_func;
				TBlendFunc blend_func;
				TBlendEquation blend_left, blend_right;
				TTexFilter texture_filter;
				TTexClamp texture_clamp;
				std::string image_path;
				BaluLib::TVec4 color;

			public:
				static TWorldObjectType GetWorldObjectType()
				{
					return TWorldObjectType::Material;
				}
				IWorld* GetWorld()
				{
					return world;
				}

				TBaluMaterial(std::string material_name, IWorld* world);
				void SetBlendMode(TTransparentMode mode);
				void SetAlphaTestValue(float alpha_test_value);

				void SetImagePath(std::string image_path);
				std::string GetImagePath();

				void SetColor(BaluLib::TVec4 color);

				IProperties* GetProperties();

				void Save(pugi::xml_node& parent_node, const int version)const;
				void Load(const pugi::xml_node& instance_node, const int version, IWorld* world);
			};
		}
	}
}

