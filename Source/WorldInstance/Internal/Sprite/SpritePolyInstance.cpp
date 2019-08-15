#include "SpritePolygonInstance.h"

using namespace BaluEngine;
using namespace BaluEngine::WorldInstance;
using namespace BaluEngine::WorldInstance::Internal;
using namespace BaluLib;

void TSpritePolygonInstance::UpdateGeometry()
{

}

WorldDef::ISpritePolygon* TSpritePolygonInstance::GetSpritePolygon()
{
	return source;
}

TSpritePolygonInstance::TSpritePolygonInstance(WorldDef::ISpritePolygon* source, TResources* resources)
	:material(source->GetMaterial(), resources)
{
	this->layer = source->GetLayer();
	enabled = source->GetEnabled();
	this->source = source;
	//source->AddChangesListener(this);
	tex_coords = source->GetTexCoords();

	animation_time_from_start = 0;
	auto animation_line_names = source->GetAnimationLineNames();
	if (animation_line_names.size()>0)
		active_animation_line = *animation_line_names.begin();
	active_frame_index = 0;
	active_desc_index = 0;
	UpdateAnimation();
}

TSpritePolygonInstance::~TSpritePolygonInstance()
{
	//source->RemoveChangesListener(this);
}

void TSpritePolygonInstance::Render(std::vector<TRenderCommand>& commands/*, TLayersManager& layers*/)
{
	if (enabled && vertices.size() > 0)
	{
		//if (layers.GetLayersCount() > 0)
		{
			//auto layer_desc = layers.GetLayer(layer);
			//if (layer_desc.IsVisible())
			{
				commands.emplace_back();

				auto& command = commands.back();

				command.draw_triangles_grid = source->GetDrawTrianglesGrid();
				command.material_id = &material;
				command.vertices = &vertices[0];
				command.vertices_count = vertices.size();
				assert(tex_coords.size() != 0);
				command.tex_coords = &tex_coords[0];
				/*command.layer_order = layer_desc.GetOrder();
				command.alpha = layer_desc.GetAlpha();*/
				command.layer_order = 0;
				command.alpha = 1.0f;
			}
		}
	}
}

void TSpritePolygonInstance::NextFrame()
{
	if (active_frame_index == source->GetAnimationLine(active_animation_line)->GetFrames(active_desc_index)->GetFrames().size() - 1)
	{
		active_frame_index = 0;
		

		if (active_desc_index == source->GetAnimationLine(active_animation_line)->GetFramesCount() - 1)
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

void TSpritePolygonInstance::UpdateAnimation()
{
	if (source->GetAnimationLineNames().size() > 0)
	{
		float time_on_frame = 0.3;
		float step = 0.05;

		if ((int)((animation_time_from_start + step) / time_on_frame) > (int)(animation_time_from_start / time_on_frame))
		{
			NextFrame();
		}
		animation_time_from_start += step;

		auto active_frame = source->GetAnimationLine(active_animation_line)->GetFrames(active_desc_index);
		auto frame = active_frame->GetDesc()->GetFrame(active_frame->GetFrames()[active_frame_index]);

		source->SetTexCoordsFromVerticesByRegion(frame.left_bottom, frame.right_top);
		tex_coords = source->GetTexCoords();
	}
}

void TSpritePolygonInstance::UpdateTransform(WorldDef::TTransformWithScale global)
{
	if (source->GetAnimationLineNames().size() > 0)
		UpdateAnimation();

	vertices = source->GetTriangulatedVertices();
	tex_coords = source->GetTexCoords();
	auto polygon_transform = WorldDef::TTransformWithScale(source->GetTransform(), source->GetScale());
	auto local = source->GetTransform();
	for (int i = 0; i < vertices.size(); i++)
	{
		//vertices[i] = parent.ToGlobal(class_transform.ToGlobal(sprite_transform.ToGlobal(polygon_transform.ToGlobal(vertices[i]))));
		//vertices[i] = class_transform.ToGlobal(sprite_transform.ToGlobal((parent.ToGlobal(polygon_transform)).ToGlobal(vertices[i])));
		//vertices[i] = (parent.ToGlobal(polygon_transform)).ToGlobal(vertices[i]);

		vertices[i] = global.ToGlobal(polygon_transform).ToGlobal(vertices[i]);
	}
}

void TSpritePolygonInstance::SetActiveAnimation(const std::string& name)
{
	if (active_animation_line != name)
	{
		active_animation_line = name;
		active_frame_index = 0;
		active_desc_index = 0;
	}
}