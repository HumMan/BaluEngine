#include "PolygonGui.h"

using namespace BaluEngine::WorldDef;
using namespace BaluEngine::WorldDef::Internal;
using namespace BaluLib;

TSpritePolygonAdornment::TSpritePolygonAdornment()
{
	this->visible = false;
	this->show_add_point_control = false;
	this->show_point_hightlight = false;
	this->show_selection_box = false;
	this->visual = nullptr;
	this->line_start_point_index = -1;
}

void TSpritePolygonAdornment::SetVisual(ISpritePolygon* visual)
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

void TSpritePolygonAdornment::Save(pugi::xml_node & parent_node, const int version) const
{
}

void TSpritePolygonAdornment::Load(const pugi::xml_node & instance_node, const int version, IWorld * world)
{
}
