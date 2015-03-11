
#include "spriteEditorTools.h"

#include "spriteEditorScene.h"

#include "spriteEditorAdornments.h"

#include "../DrawingHelper.h"


class TModifySpritePolygonOBB : public IEditorTool, public TBoundaryBoxChangeListener
{
protected:
	TSpriteEditorScene* sprite_editor_scene;
public:
	TWorldObjectType NeedObjectSelect()
	{
		return TWorldObjectType::None;
	}
	void SetSelectedObject(IBaluWorldObject* obj)
	{
		assert(false);
	}
	TModifySpritePolygonOBB(TSpriteEditorScene* sprite_editor_scene)
	{
		this->sprite_editor_scene = sprite_editor_scene;
	}

	void BoxResize(TOBB<float, 2> old_box, TOBB<float, 2> new_box)
	{
		auto scale = new_box.GetLocalAABB().GetSize() / old_box.GetLocalAABB().GetSize();
		sprite_editor_scene->selected_instance->SetScale(
			sprite_editor_scene->selected_instance->GetScale().ComponentMul(scale));
	}
	void BoxMove(TVec2 old_pos, TVec2 new_pos)
	{
		auto trans = sprite_editor_scene->selected_instance->GetTransform();
		trans.position = new_pos;
		sprite_editor_scene->selected_instance->SetTransform(trans);
	}
	void BoxRotate(TOBB<float, 2> old_box, TOBB<float, 2> new_box)
	{
		auto trans = sprite_editor_scene->selected_instance->GetTransform();
		trans.angle = TRot(new_box);
		sprite_editor_scene->selected_instance->SetTransform(trans);
	}

	void OnMouseDown(TMouseEventArgs e)
	{
		if (sprite_editor_scene->boundary_box.enable)
		{
			sprite_editor_scene->boundary_box.OnMouseDown(e, sprite_editor_scene->drawing_helper->FromScreenPixelsToScene(e.location));
		}
		if (!sprite_editor_scene->boundary_box.IsCursorCaptured())
		{
			if (sprite_editor_scene->hightlighted_instance != nullptr)
			{
				sprite_editor_scene->selected_instance = sprite_editor_scene->hightlighted_instance;
				sprite_editor_scene->boundary_box.OnChange = this;
				sprite_editor_scene->boundary_box.enable = true;
				sprite_editor_scene->boundary_box.SetBoundary(sprite_editor_scene->selected_instance->GetOBB());
			}
			else
			{
				sprite_editor_scene->boundary_box.enable = false;
				sprite_editor_scene->selected_instance = nullptr;
			}
		}
	}
	void OnMouseMove(TMouseEventArgs e)
	{
		if (sprite_editor_scene->boundary_box.enable)
		{
			sprite_editor_scene->boundary_box.OnMouseMove(e, sprite_editor_scene->drawing_helper->FromScreenPixelsToScene(e.location));
		}
		if (!sprite_editor_scene->boundary_box.IsCursorCaptured())
		{
			auto world_cursor_location = sprite_editor_scene->drawing_helper->FromScreenPixelsToScene(TVec2i(e.location[0], e.location[1]));
			//IBaluInstance* instance_collision(nullptr);
			//if (sprite_editor_scene->source_sprite->PointCollide(world_cursor_location, instance_collision))
			//{
			//	sprite_editor_scene->boundary_box_contour->SetEnable(true);
			//	sprite_editor_scene->boundary_box_contour->SetBox(instance_collision->GetOBB());
			//	sprite_editor_scene->hightlighted_instance = instance_collision;
			//}
			//else
			//{
			//	sprite_editor_scene->boundary_box_contour->SetEnable(false);
			//	sprite_editor_scene->hightlighted_instance = nullptr;
			//}
		}

	}
	void OnMouseUp(TMouseEventArgs e)
	{
		if (sprite_editor_scene->boundary_box.enable)
		{
			sprite_editor_scene->boundary_box.OnMouseUp(e, sprite_editor_scene->drawing_helper->FromScreenPixelsToScene(e.location));
		}
		if (!sprite_editor_scene->boundary_box.IsCursorCaptured())
		{
		}
	}
	void CancelOperation()
	{

	}
};

TSpriteEditorToolsRegistry::TSpriteEditorToolsRegistry(TSpriteEditorScene* scene)
{
	this->scene = scene;
	tools.emplace_back(new TModifySpritePolygonOBB(scene), "Modify");
}

TSpriteEditorToolsRegistry::TSpriteEditorToolsRegistry(TSpriteEditorToolsRegistry&& o)
{
	tools = std::move(o.tools);
	scene = std::move(o.scene);
}
const std::vector<TToolWithDescription>& TSpriteEditorToolsRegistry::GetTools()
{
	return tools;
}
TSpriteEditorToolsRegistry::~TSpriteEditorToolsRegistry()
{

}