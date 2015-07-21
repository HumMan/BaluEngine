#include "SpritePolyInstance.h"

void TBaluSpritePolygonInstance::UpdateGeometry()
{

}

TBaluSpritePolygon* TBaluSpritePolygonInstance::GetSpritePolygon()
{
	return source;
}

TBaluSpritePolygonInstance::TBaluSpritePolygonInstance(TBaluSpritePolygon* source, TResources* resources)
	:material(source->GetMaterial(), resources)
{
	enable = source->enable;
	this->source = source;
	tex_coords = source->GetTexCoords();

	animation_time_from_start = 0;
	if (source->animation_lines.size()>0)
		active_animation_line = source->animation_lines.begin()->second.line_name;
	active_frame_index = 0;
	active_desc_index = 0;
	UpdateAnimation();
}

void TBaluSpritePolygonInstance::Render(TRenderCommand& command)
{
	if (enable)
	{
		//TODO убрать резервирование места если здесь ничего не добавляется
		if (vertices.size() > 0)
		{
			command.draw_triangles_grid = source->draw_triangles_grid;
			command.material_id = &material;
			command.vertices = &vertices[0];
			command.vertices_count = vertices.size();
			assert(tex_coords.size() != 0);
			command.tex_coords = &tex_coords[0];
		}else
			command.vertices_count = 0;
	}
}

void TBaluSpritePolygonInstance::NextFrame()
{
	if (active_frame_index == source->animation_lines[active_animation_line].frames[active_desc_index].frames.size() - 1)
	{
		active_frame_index = 0;
		

		if (active_desc_index == source->animation_lines[active_animation_line].frames.size() - 1)
		{
			active_frame_index = 0;
			active_desc_index = 0;
		}
		else
		{
			active_desc_index += 1;
		}
	}
	else
	{
		active_frame_index += 1;
	}
}

void TBaluSpritePolygonInstance::UpdateAnimation()
{
	if (source->animation_lines.size() > 0)
	{
		float time_on_frame = 0.3;
		float step = 0.05;

		if ((int)((animation_time_from_start + step) / time_on_frame) > (int)(animation_time_from_start / time_on_frame))
		{
			NextFrame();
		}
		animation_time_from_start += step;

		auto& active_frame = source->animation_lines[active_animation_line].frames[active_desc_index];
		auto frame = active_frame.desc->GetFrame(active_frame.frames[active_frame_index]);

		source->SetTexCoordsFromVerticesByRegion(frame.left_bottom, frame.right_top);
		tex_coords = source->GetTexCoords();
	}
}

void TBaluSpritePolygonInstance::UpdateTransform(TBaluTransformWithScale parent, TBaluTransformWithScale class_transform, TBaluTransformWithScale sprite_transform)
{
	if (source->animation_lines.size()>0)
		UpdateAnimation();

	vertices = source->GetTriangulatedVertices();
	tex_coords = source->GetTexCoords();
	auto polygon_transform = TBaluTransformWithScale(source->GetTransform(), source->GetScale());
	auto local = source->GetTransform();
	for (int i = 0; i < vertices.size(); i++)
	{
		//vertices[i] = parent.ToGlobal(class_transform.ToGlobal(sprite_transform.ToGlobal(polygon_transform.ToGlobal(vertices[i]))));
		vertices[i] = class_transform.ToGlobal(sprite_transform.ToGlobal((parent.ToGlobal(polygon_transform)).ToGlobal(vertices[i])));
		//vertices[i] = (parent.ToGlobal(polygon_transform)).ToGlobal(vertices[i]);
	}
}

void TBaluSpritePolygonInstance::SetActiveAnimation(std::string name)
{
	if (active_animation_line != name)
	{
		active_animation_line = name;
		active_frame_index = 0;
		active_desc_index = 0;
	}
}