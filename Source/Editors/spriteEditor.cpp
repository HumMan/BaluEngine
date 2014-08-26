#include "spriteEditor.h"

TSpriteEditor::TSpriteEditor()
{
	curr_state = CurrState::None;
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

void DrawSpriteContour(TBaluRender* render, TBaluSpriteDef* sprite)
{
	TStreamsDesc desc;
	desc.Clear();
	desc.AddStream(TStream::Vertex, TDataType::Float, 2, &*sprite->polygon_vertices.begin());
	desc.AddStream(TStream::TexCoord, TDataType::Float, 2, &*sprite->tex_coordinates.begin());
	render->Draw(desc, TPrimitive::LineLoop, sprite->polygon_vertices.size());
}

void DrawSprite(TBaluRender* render, TBaluSpriteDef* sprite)
{
	std::vector<TVec2> pos, tex;
	pos.push_back(TVec2(0, 0));
	pos.insert(pos.end(), sprite->polygon_vertices.begin(), sprite->polygon_vertices.end());
	pos.insert(pos.end(), sprite->polygon_vertices[0]);
	tex = pos;
	TStreamsDesc desc;
	desc.AddStream(TStream::Vertex, TDataType::Float, 2, &*pos.begin());
	desc.AddStream(TStream::TexCoord, TDataType::Float, 2, &*tex.begin());
	render->Draw(desc, TPrimitive::TriangleFan, sprite->polygon_vertices.size() + 2);
}

void DrawLine(TBaluRender* render, TVec2 p0, TVec2 p1)
{
	TVec2 v[2] = { p0, p1 };
	TStreamsDesc desc;
	desc.AddStream(TStream::Vertex, TDataType::Float, 2, &v[0]);
	render->Draw(desc, TPrimitive::Lines, 2);
}

void DrawPoint(TBaluRender* render, TVec2 p)
{
	TVec2 v[1] = { p};
	TStreamsDesc desc;
	desc.AddStream(TStream::Vertex, TDataType::Float, 2, &v[0]);

	render->Set.PointSize(5);

	render->Draw(desc, TPrimitive::Points, 1);

	render->Set.PointSize(1);
}

void TSpriteEditor::Render(TBaluRender* render)
{
	DrawSprite(render, sprite);
	
	//render->Texture.Enable(false);
	render->Set.Color(0, 1, 0);
	DrawSpriteContour(render, sprite);
	//render->Texture.Enable(true);

	if (curr_state == CurrState::CanSubdivide)
	{
		if (nearest_line != -1)
		{
			int size = sprite->polygon_vertices.size();
			DrawLine(render, cursor_pos, sprite->polygon_vertices[nearest_line]);
			DrawLine(render, cursor_pos, sprite->polygon_vertices[(nearest_line+1)%size]);
		}
	}
	else if (curr_state == CurrState::CanMoveSelected)
	{
		if (nearest_point != -1)
		{
			DrawPoint(render, sprite->polygon_vertices[nearest_point]);
		}
	}
}