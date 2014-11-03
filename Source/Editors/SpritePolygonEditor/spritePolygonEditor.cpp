#include "spritePolygonEditor.h"

#include "../abstractEditor.h"

TSpritePolygonEditor::TSpritePolygonEditor()
{
	//this->world = world;
	curr_state = CurrState::None;
}

void TSpritePolygonEditor::Initialize(TWorldObjectDef* obj, TVec2 editor_global_pos)
{
	this->editor_global_pos = editor_global_pos;
	Initialize(dynamic_cast<TBaluSpritePolygonDef*>(obj));
}

void TSpritePolygonEditor::Initialize(TBaluSpritePolygonDef* obj)
{
	this->sprite = obj;
}

bool TSpritePolygonEditor::CanSetSelectedAsWork()
{
	return false;
}
void TSpritePolygonEditor::SetSelectedAsWork()
{

}

bool TSpritePolygonEditor::CanEndSelectedAsWork()
{
	return parent_editors.size()>0;
}
bool TSpritePolygonEditor::EndSelectedAsWork()
{
	return true;
}

void TSpritePolygonEditor::OnMouseDown(TMouseEventArgs e, TVec2 world_cursor_location)
{
	world_cursor_location -= editor_global_pos;

	if (curr_state == CurrState::CanSubdivide)
	{
		if (nearest_line != -1)
		{
			sprite->polygon_vertices.insert(sprite->polygon_vertices.begin() + nearest_line + 1, 1, cursor_pos);
		}
	}
	else if (curr_state == CurrState::CanMoveSelected)
	{
		if (nearest_point != -1)
		{
			selected_points.clear();
			selected_points.push_back(nearest_point);
			old_cursor_pos = cursor_pos;
			curr_state = CurrState::MovingSelected;
		}
	}
}
void TSpritePolygonEditor::OnMouseMove(TMouseEventArgs e, TVec2 world_cursor_location)
{
	world_cursor_location -= editor_global_pos;

	TVec2 new_pos = world_cursor_location;
	cursor_pos = new_pos;
	if (curr_state == CurrState::MovingSelected)
	{
		for (int i : selected_points)
			sprite->polygon_vertices[i] += new_pos - old_cursor_pos;
		old_cursor_pos = new_pos;
		sprite->tex_coordinates = sprite->polygon_vertices;
	}
	else
	{

		int size = sprite->polygon_vertices.size();
		nearest_point = -1;
		nearest_point_dist = 0;
		for (int i = 0; i < size; i++)
		{
			float dist = sprite->polygon_vertices[i].Distance(new_pos);
			if (nearest_point == -1 || nearest_point_dist > dist)
			{
				nearest_point = i;
				nearest_point_dist = dist;
			}
		}
		nearest_line = -1;
		nearest_line_dist = 0;
		for (int i = 0; i < size + 1; i++)
		{
			float t;
			TVec2 p;
			float dist = DistanceBetweenLinePoint(new_pos, sprite->polygon_vertices[i%size], sprite->polygon_vertices[(i + 1) % size], t, p);
			if (t>0 && t < 1)
			{
				if (nearest_line == -1 || dist < nearest_line_dist)
				{
					nearest_line = i;
					nearest_line_dist = dist;
				}
			}
		}
		if (nearest_point_dist < 0.3)
		{
			curr_state = CurrState::CanMoveSelected;
		}
		else if (nearest_line != -1 && nearest_line_dist < nearest_point_dist)
		{
			curr_state = CurrState::CanSubdivide;
		}
	}
}
void TSpritePolygonEditor::OnMouseUp(TMouseEventArgs e, TVec2 world_cursor_location)
{
	world_cursor_location -= editor_global_pos;

	if (curr_state == CurrState::MovingSelected)
	{
		selected_points.clear();
		curr_state = CurrState::None;
	}
}

const std::vector<TToolWithDescription>& TSpritePolygonEditor::GetAvailableTools()
{
	return tools;
}
void TSpritePolygonEditor::SetActiveTool(TEditorTool* tool)
{

}

void TSpritePolygonEditor::SetAsBox(TVec2 size)
{
	sprite->polygon_vertices.resize(4);
	sprite->polygon_vertices[0] = TVec2(-1, 1);
	sprite->polygon_vertices[1] = TVec2(1, 1);
	sprite->polygon_vertices[2] = TVec2(1, -1);
	sprite->polygon_vertices[3] = TVec2(-1, -1);
	sprite->tex_coordinates = sprite->polygon_vertices;
}

bool isConvex(TVec2 p2, TVec2 p1, TVec2 p0)
{
	return (p1-p0).GetNormalized().Cross()*(p2-p1)<0;
}

//обход по часовой стрелке
bool isConvex(std::vector<TVec2> v)
{
	int size = v.size();
	if (size >= 3)
	{
		for (int i = 0; i < v.size(); i++)
		{
			if (!isConvex(v[(i + 2) % size], v[(i + 1) % size], v[(i + 0) % size]))
				return false;
		}
	}
	else
		return false;
	return true;
}

void TSpritePolygonEditor::Render(TDrawingHelper* drawing_helper)
{
	//
	//if (world->materials.find(sprite->material_name) != world->materials.end())
	///ActivateMaterial(render, &world->materials[sprite->material_name]);

	//drawing_helper->ActivateMaterial(sprite->material);
	
	if (isConvex(sprite->polygon_vertices))
		drawing_helper->SetSelectedBoundaryColor();
	drawing_helper->DrawSpritePolygon(sprite);

	drawing_helper->SetTransform(editor_global_pos);
	//if (world->materials.find(sprite->material_name) != world->materials.end())
	//	DeactivateMaterial(render, &world->materials[sprite->material_name]);

	//drawing_helper->DeactivateMaterial(sprite->material);
	
	drawing_helper->DrawSpritePolygonContour(sprite);
	
	//render->Texture.Enable(true);

	if (curr_state == CurrState::CanSubdivide)
	{
		if (nearest_line != -1)
		{
			drawing_helper->SetSelectedPointColor();
			int size = sprite->polygon_vertices.size();
			drawing_helper->DrawLine(cursor_pos, sprite->polygon_vertices[nearest_line]);
			drawing_helper->DrawLine(cursor_pos, sprite->polygon_vertices[(nearest_line + 1) % size]);
		}
	}
	else if (curr_state == CurrState::CanMoveSelected)
	{
		if (nearest_point != -1)
		{
			drawing_helper->DrawPoint(sprite->polygon_vertices[nearest_point]);
		}
	}
	drawing_helper->UnsetColor();
	drawing_helper->PopTransform();
}