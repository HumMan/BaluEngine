
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

	TVec2 active_transform;
	TMatrix4 last_transform;
public:
	TDrawingHelper(TBaluRender* render, TEditorResourses* resources);
	void DrawClass(TBaluClass* balu_class);
	void DrawPhysBody(TBaluPhysBodyDef* body);
	void DrawSprite(TBaluSpriteDef* sprite);

	void DrawSpritePolygon(TBaluSpritePolygonDef* sprite_poly);
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

	void PushTransform();
	void PopTransform();
	void SetTransform(TVec2 transform);
};