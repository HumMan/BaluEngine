
#include "classEditorTools.h"

#include "classEditorScene.h"

#include "../DrawingHelper.h"

class TCreateClassSpriteTool : public IEditorTool
{
protected:
	TClassEditorScene* class_editor_scene;
	IBaluSprite* active_tool_sprite;
public:
	TWorldObjectType NeedObjectSelect()
	{
		return TWorldObjectType::Sprite;
	}
	void SetSelectedObject(IBaluWorldObject* obj)
	{
		active_tool_sprite = dynamic_cast<IBaluSprite*>(obj);
	}
	TCreateClassSpriteTool(TClassEditorScene* class_editor_scene)
	{
		this->class_editor_scene = class_editor_scene;
		active_tool_sprite = nullptr;
	}
	void OnMouseDown(TMouseEventArgs e)
	{
		if (active_tool_sprite != nullptr)
		{
			//трансформируем позицию курсора в координаты сцены
			auto transform = TBaluTransform(class_editor_scene->drawing_helper->GetContext().FromScreenPixelsToScene(e.location), TRot(0));

			//создаем в редактируемом классе новый спрайт
			auto new_sprite_instance = class_editor_scene->source_class->AddSprite(active_tool_sprite);
			new_sprite_instance->SetTransform(transform);

			////создаем в сцене редактора класса новый инстанс отвечающий за новый спрайт
			//auto new_class_instance = class_editor_scene->editor_scene_instance->CreateInstance(active_tool_class, transform, TVec2(1, 1));
			auto class_sprite_instance = class_editor_scene->source_class->AddSprite(active_tool_sprite);
			class_sprite_instance->SetTransform(transform);
			auto class_instance_sprite_instance = class_editor_scene->editor_scene_class_instance->AddSprite(class_sprite_instance);

			class_editor_scene->selected_instance_source = new_sprite_instance;
			class_editor_scene->selected_instance = class_instance_sprite_instance;

			//записываем в экземл€р спрайта указатель на исходный экземпл€р спрайта в редактируемом классе - дл€ использовани€ в других инструментах (перемещение и т.д.)
			class_instance_sprite_instance->SetTag(new_sprite_instance);
			class_editor_scene->boundary_box->SetBoundary(TOBB2(transform.position, transform.GetOrientation(), TAABB2(TVec2(0, 0), TVec2(1, 1))));
		}
	}
	void OnMouseMove(TMouseEventArgs e)
	{
	}
	void OnMouseUp(TMouseEventArgs e)
	{
	}
	void CancelOperation()
	{
	}
};


class TModifyClassSpriteTool : public IEditorTool, public TBoundaryBoxChangeListener
{
protected:
	TClassEditorScene* class_editor_scene;
	IBaluSprite* active_tool_sprite;
public:
	TWorldObjectType NeedObjectSelect()
	{
		return TWorldObjectType::None;
	}
	void SetSelectedObject(IBaluWorldObject* obj)
	{
		active_tool_sprite = dynamic_cast<IBaluSprite*>(obj);
	}
	TModifyClassSpriteTool(TClassEditorScene* class_editor_scene)
	{
		this->class_editor_scene = class_editor_scene;
	}

	void BoxResize(TOBB<float, 2> old_box, TOBB<float, 2> new_box, TVec2 scale)
	{
		//auto scale = new_box.GetLocalAABB().GetSize() / old_box.GetLocalAABB().GetSize();
		auto new_scale = class_editor_scene->selected_instance->GetScale().ComponentMul(scale);
		class_editor_scene->selected_instance->SetScale(new_scale);
		((IBaluClassSpriteInstance*)(class_editor_scene->selected_instance->GetTag()))->SetScale(new_scale);
	}
	void BoxMove(TVec2 old_pos, TVec2 new_pos)
	{
		auto trans = class_editor_scene->selected_instance->GetTransform();
		trans.position = new_pos;
		class_editor_scene->selected_instance->SetTransform(trans);
		((IBaluClassSpriteInstance*)(class_editor_scene->selected_instance->GetTag()))->SetTransform(trans);
	}
	void BoxRotate(TOBB<float, 2> old_box, TOBB<float, 2> new_box)
	{
		auto trans = class_editor_scene->selected_instance->GetTransform();
		trans.angle = TRot(new_box);
		class_editor_scene->selected_instance->SetTransform(trans);
		((IBaluClassSpriteInstance*)(class_editor_scene->selected_instance->GetTag()))->SetTransform(trans);
	}

	void OnMouseDown(TMouseEventArgs e)
	{
		if (class_editor_scene->boundary_box->enable)
		{
			class_editor_scene->boundary_box->OnMouseDown(e, class_editor_scene->drawing_helper->GetContext().FromScreenPixelsToScene(e.location));
		}
		if (!class_editor_scene->boundary_box->IsCursorCaptured())
		{
			if (class_editor_scene->hightlighted_instance != nullptr)
			{
				class_editor_scene->selected_instance = class_editor_scene->hightlighted_instance;
				class_editor_scene->boundary_box->OnChange = this;
				class_editor_scene->boundary_box->enable = true;
				class_editor_scene->boundary_box->SetBoundary(class_editor_scene->selected_instance->GetOBB());
			}
			else
			{
				class_editor_scene->boundary_box->enable = false;
				class_editor_scene->selected_instance = nullptr;
			}
		}
	}
	void OnMouseMove(TMouseEventArgs e)
	{
		if (class_editor_scene->boundary_box->enable)
		{
			class_editor_scene->boundary_box->OnMouseMove(e, class_editor_scene->drawing_helper->GetContext().FromScreenPixelsToScene(e.location));
		}
		if (!class_editor_scene->boundary_box->IsCursorCaptured())
		{
			auto world_cursor_location = class_editor_scene->drawing_helper->GetContext().FromScreenPixelsToScene(TVec2i(e.location[0], e.location[1]));
			IBaluClassInstanceSpriteInstance* instance_collision(nullptr);
			if (class_editor_scene->editor_scene_class_instance->PointCollide(world_cursor_location, instance_collision))
			{
				class_editor_scene->boundary_box_contour->SetEnable(true);
				class_editor_scene->boundary_box_contour->SetBox(instance_collision->GetOBB());
				class_editor_scene->hightlighted_instance = instance_collision;
			}
			else
			{
				class_editor_scene->boundary_box_contour->SetEnable(false);
				class_editor_scene->hightlighted_instance = nullptr;
			}
		}

	}
	void OnMouseUp(TMouseEventArgs e)
	{
		if (class_editor_scene->boundary_box->enable)
		{
			class_editor_scene->boundary_box->OnMouseUp(e, class_editor_scene->drawing_helper->GetContext().FromScreenPixelsToScene(e.location));
		}
		if (!class_editor_scene->boundary_box->IsCursorCaptured())
		{
		}
	}
	void CancelOperation()
	{

	}
};

TClassEditorToolsRegistry::TClassEditorToolsRegistry(TClassEditorScene* scene)
{
	this->scene = scene;
	tools.emplace_back(new TCreateClassSpriteTool(scene), "Sprite");
	tools.emplace_back(new TModifyClassSpriteTool(scene), "Modify");
}
TClassEditorToolsRegistry::TClassEditorToolsRegistry(TClassEditorToolsRegistry&& o)
{
	tools = std::move(o.tools);
	scene = std::move(o.scene);
}
const std::vector<TToolWithDescription>& TClassEditorToolsRegistry::GetTools()
{
	return tools;
}
TClassEditorToolsRegistry::~TClassEditorToolsRegistry()
{

}