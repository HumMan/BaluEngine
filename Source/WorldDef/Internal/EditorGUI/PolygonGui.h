
#pragma once

#include "../../Interface.h"

#include "../../Internal/Common/Common.h"

namespace BaluEngine
{
	namespace WorldDef
	{
		namespace Internal
		{
			class TSpritePolygonAdornment : public TGui
			{
			private:
				bool visible;

				bool show_add_point_control;
				int line_start_point_index;
				BaluLib::TVec2 point_to_add;

				bool show_point_hightlight;
				std::vector<int> hightlight_poly_point_index;

				bool show_selection_box;
				BaluLib::TOBB2 selection_box;
				ISpritePolygon* visual;
			public:
				TSpritePolygonAdornment();
				void SetVisual(ISpritePolygon* visual);
				~TSpritePolygonAdornment() {}

				void SetVisible(bool visible);
				void ShowAddPointControl(bool show);
				void SetAddPointControlData(int line_start_point_index, BaluLib::TVec2 point_to_add);
				void ShowPointHightLinght(bool show);
				void SetShowPointHightlightData(std::vector<int> poly_point_index);
				void ShowSelectionBox(bool visible);
				void SetSelectionBox(BaluLib::TOBB2 box);

				static const char* FactoryName()
				{
					return "SpritePolygonAdornment";
				}

				static ISceneObject* Clone()
				{
					return new TSpritePolygonAdornment();
				}

				const char* GetFactoryName()
				{
					return FactoryName();
				}

				void Save(pugi::xml_node& parent_node, const int version)const;
				void Load(const pugi::xml_node& instance_node, const int version, IWorld* world);
			};

			REGISTER_FACTORY_CLASS(SceneObjectFactory, TSpritePolygonAdornment)
		}
	}
}
