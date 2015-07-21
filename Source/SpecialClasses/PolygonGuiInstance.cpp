#include "PolygonGuiInstance.h"

#include "..\EditorUtils\DrawingHelper.h"
#include "..\SceneInstance.h"

TSpritePolygonAdornment::TSpritePolygonAdornment()
{
	this->visible = false;
	this->show_add_point_control = false;
	this->show_point_hightlight = false;
	this->show_selection_box = false;
	this->visual = nullptr;
	this->line_start_point_index = -1;
}

void TSpritePolygonAdornment::SetVisual(EngineInterface::IBaluSpritePolygon* visual)
{
	this->visual = visual;
}

void TSpritePolygonAdornment::SetVisible(bool visible)
{
	this->visible = visible;
}

void TSpritePolygonAdornment::ShowAddPointControl(bool show)
{
	this->show_add_point_control = show;
}
void TSpritePolygonAdornment::SetAddPointControlData(int line_start_point_index, TVec2 point_to_add)
{
	this->line_start_point_index = line_start_point_index;
	this->point_to_add = point_to_add;
}

void TSpritePolygonAdornment::ShowPointHightLinght(bool show)
{
	this->show_point_hightlight = show;
}

void TSpritePolygonAdornment::SetShowPointHightlightData(std::vector<int> poly_point_index)
{
	this->hightlight_poly_point_index = poly_point_index;
}

void TSpritePolygonAdornment::ShowSelectionBox(bool visible)
{
	this->show_selection_box = visible;
}
void TSpritePolygonAdornment::SetSelectionBox(TOBB2 box)
{
	this->selection_box = box;
}

TSpritePolygonAdornmentInstance::TSpritePolygonAdornmentInstance(TBaluSceneInstance* scene)
{
	scene->AddInstance(this);
}

void TSpritePolygonAdornmentInstance::Render(TDrawingHelper* drawing_helper)const
{
	if (visible)
	{
		auto sprite_poly_trans = visual->GetTransformWithScale();
		auto vertices = visual->GetPolygon();
		drawing_helper->RenderLinesLoop(vertices, sprite_poly_trans);
		for (auto& v : vertices)
			drawing_helper->RenderPointAdornment(v, sprite_poly_trans);

		if (show_add_point_control && line_start_point_index != -1)
		{
			TVec2 left, right;
			left = sprite_poly_trans.ToGlobal(vertices[line_start_point_index]);
			right = sprite_poly_trans.ToGlobal(vertices[(line_start_point_index + 1) % vertices.size()]);
			drawing_helper->RenderPointAdornment(point_to_add, sprite_poly_trans);

			drawing_helper->RenderLine(left, sprite_poly_trans.ToGlobal(point_to_add));
			drawing_helper->RenderLine(right, sprite_poly_trans.ToGlobal(point_to_add));
		}
		if (show_selection_box)
		{
			drawing_helper->RenderSelectionBox(selection_box);
		}
		if (show_point_hightlight)
		{
			for (auto& v : hightlight_poly_point_index)
			{
				drawing_helper->RenderPointHighlightAdornment(vertices[v], sprite_poly_trans);
			}
		}
	}
}