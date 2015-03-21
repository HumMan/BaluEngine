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

	

	//vertices = source->GetTriangulatedVertices();
	tex_coords = source->GetTexCoords();

	animation_time_from_start = 0;
	if (source->animation_lines.size()>0)
		active_animation_line = source->animation_lines.begin()->second.line_name;
	active_frame_index = 0;
	active_desc_index = 0;
	UpdateAnimation();
}

//void TBaluSpritePolygonInstance::QueryAABB(TAABB2 frustum, std::vector<TBaluSpritePolygonInstance>& results)
//{
//
//}

void TBaluSpritePolygonInstance::Render(TRenderCommand& command)
{
	if (enable)
	{
		//TODO убрать резервирование места если здесь ничего не добавляется
		if (vertices.size() > 0)
		{
			command.material_id = &material;
			command.vertices = &vertices[0];
			command.vertices_count = vertices.size();
			assert(tex_coords.size() != 0);
			command.tex_coords = &tex_coords[0];
		}
	}
}

void TBaluSpritePolygonInstance::RenderCustom(std::vector<TCustomDrawCommand>& commands)
{
	for (auto& v : source->custom_draw_callbacks)
	{
		commands.emplace_back();
		commands.back().command = v;
		commands.back().poly = dynamic_cast<IBaluSpritePolygonInstance*>(this);
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

void TBaluSpritePolygonInstance::UpdateTransform(TBaluTransform parent, TVec2 class_scale, TBaluTransform class_transform, TVec2 sprite_scale, TBaluTransform sprite_transform)
{
	if (source->animation_lines.size()>0)
		UpdateAnimation();

	vertices = source->GetTriangulatedVertices();
	auto local = source->GetTransform();
	auto scale = source->GetScale();

	for (int i = 0; i < vertices.size(); i++)
	{
		vertices[i] = Transform(Transform(Transform(vertices[i], scale, parent.ToGlobal(local)), sprite_scale, sprite_transform), class_scale, class_transform);
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