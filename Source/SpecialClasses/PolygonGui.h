#pragma once

#include "..\EngineInterfaces\IMaterial.h"
#include "..\EngineInterfaces\ISpritePolygon.h"

class TSpritePolygonAdornment : public EngineInterface::TSceneObject
{
	friend class TSpritePolygonAdornmentInstance;
private:
	bool visible;

	bool show_add_point_control;
	int line_start_point_index;
	TVec2 point_to_add;

	bool show_point_hightlight;
	std::vector<int> hightlight_poly_point_index;

	bool show_selection_box;
	TOBB2 selection_box;
	EngineInterface::IBaluSpritePolygon* visual;
public:
	TSpritePolygonAdornment(EngineInterface::IBaluSpritePolygon* visual);

	~TSpritePolygonAdornment();

	void SetVisible(bool visible);
	void ShowAddPointControl(bool show);
	void SetAddPointControlData(int line_start_point_index, TVec2 point_to_add);
	void ShowPointHightLinght(bool show);
	void SetShowPointHightlightData(std::vector<int> poly_point_index);
	void ShowSelectionBox(bool visible);
	void SetSelectionBox(TOBB2 box);
};