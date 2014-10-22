
#pragma once

#include "../baluEditorDefs.h"

class TBaluRender;
class TEditorResourses;

class TDrawingHelper
{
	TBaluRender* render;
	TEditorResourses* resources;
	bool use_global_alpha;
	float global_alpha;
public:
	TDrawingHelper(TBaluRender* render, TEditorResourses* resources);
	void DrawSpritePolygon(TBaluSpritePolygonDef* sprite);
	void DrawPolygon(TBaluPolygonShapeDef* polygon);
	void DrawCircle(TBaluCircleShapeDef* circle);
	void DrawLine( TVec2 p0, TVec2 p1);
	void DrawPoint( TVec2 p);
	void DrawSpritePolygonContour(TBaluSpritePolygonDef* sprite);
	void ActivateMaterial( TBaluMaterialDef* material);
	void DeactivateMaterial( TBaluMaterialDef* material);
	void DrawBoundary(TOBB<float, 2> boundary,bool fill);

	void SetSelectedPointColor();
	void SetSelectedBoundaryColor();
	void UnsetColor();
	void SetGlobalAlpha(float alpha);
	void UnsetGlobalAlpha();
	void SetGlobalAlphaColor();
};