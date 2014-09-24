#include "spriteEditor.h"

#include "abstractEditor.h"

//#include <boost/signals2.hpp>

TSpriteEditor::TSpriteEditor(TBaluWorldDef* world)
{
	this->world = world;
	curr_state = CurrState::None;

	//boost::signals2::signal<void(int)> s;
}

void TSpriteEditor::StartEdit(TBaluSpriteDef* use_sprite)
{
	sprite = use_sprite;
	if (use_sprite->polygon_vertices.size() == 0)
	{
		SetAsBox(TVec2(1, 1));
	}
}

void TSpriteEditor::EndEdit()
{
	sprite = NULL;
}

void TSpriteEditor::MouseMove(TVec2 new_pos)
{
	cursor_pos = new_pos;
	if (curr_state == CurrState::MovingSelected)
	{
		for (int i : selected_points)
			sprite->polygon_vertices[i] += new_pos - old_cursor_pos;
		old_cursor_pos = new_pos;
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

void TSpriteEditor::MouseDown()
{
	if (curr_state == CurrState::CanSubdivide)
	{
		if (nearest_line != -1)
		{
			sprite->polygon_vertices.insert(sprite->polygon_vertices.begin()+nearest_line+1, 1, cursor_pos);
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

void TSpriteEditor::MouseUp()
{
	if (curr_state == CurrState::MovingSelected)
	{
		selected_points.clear();
		curr_state = CurrState::None;
	}
}

void TSpriteEditor::SetAsBox(TVec2 size)
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


//void ConvexDecompose(std::vector<TVec2> v)
//{
//	int i = 0;
//	int j = v.size();
//	if (isConvex(i+2,i+1,i)
//}

void TSpriteEditor::Render(TDrawingHelper* drawing_helper)
{
	//if (world->materials.find(sprite->material_name) != world->materials.end())
	//	ActivateMaterial(render, &world->materials[sprite->material_name]);
	
	if (isConvex(sprite->polygon_vertices))
		drawing_helper->SetSelectedBoundaryColor();
	drawing_helper->DrawSprite(sprite);
	//if (world->materials.find(sprite->material_name) != world->materials.end())
	//	DeactivateMaterial(render, &world->materials[sprite->material_name]);

	
	drawing_helper->DrawSpriteContour(sprite);
	
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
}