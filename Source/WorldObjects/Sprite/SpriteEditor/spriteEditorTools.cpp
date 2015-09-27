
#include "spriteEditorTools.h"

#include "spriteEditorScene.h"

#include "spriteEditorAdornments.h"

#include <EditorUtils/DrawingHelper.h>


class TModifySpritePolygonOBB : public IEditorTool, public TBoundaryBoxChangeListener
{
protected:
	TSpriteEditorScene* sprite_editor_scene;
public:
	void Activate()
	{
 		sprite_editor_scene->boundary_box->SetBoundary(sprite_editor_scene->source_sprite->GetPolygon()->GetBoundingBox());
		sprite_editor_scene->boundary_box->enable = true;
		sprite_editor_scene->boundary_box->OnChange = this;
	}
	void Deactivate()
	{
		sprite_editor_scene->boundary_box->enable = false;
		sprite_editor_scene->boundary_box->OnChange = nullptr;
	}
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

	void BoxResize(TOBB<float, 2> old_box, TOBB<float, 2> new_box, TVec2 scale)
	{
		sprite_editor_scene->source_sprite->GetPolygon()->SetScale(
			sprite_editor_scene->source_sprite->GetPolygon()->GetScale().ComponentMul(scale));
		//sprite_editor_scene->sprite_adornment->GetInstance()->UpdateTranform();
	}
	void BoxMove(TVec2 old_pos, TVec2 new_pos)
	{
		auto trans = sprite_editor_scene->source_sprite->GetPolygon()->GetTransform();
		trans.position = new_pos;
		sprite_editor_scene->source_sprite->GetPolygon()->SetTransform(trans);
		//sprite_editor_scene->sprite_adornment->GetInstance()->UpdateTranform();
	}
	void BoxRotate(TOBB<float, 2> old_box, TOBB<float, 2> new_box)
	{
		auto trans = sprite_editor_scene->source_sprite->GetPolygon()->GetTransform();
		trans.angle = TRot(new_box);
		sprite_editor_scene->source_sprite->GetPolygon()->SetTransform(trans);
		//sprite_editor_scene->sprite_adornment->GetInstance()->UpdateTranform();
	}

	void OnMouseDown(TMouseEventArgs e)
	{
		if (sprite_editor_scene->boundary_box->enable)
		{
			sprite_editor_scene->boundary_box->OnMouseDown(e, sprite_editor_scene->drawing_helper->GetContext().FromScreenPixelsToScene(e.location));
		}
		if (!sprite_editor_scene->boundary_box->IsCursorCaptured())
		{
			//if (sprite_editor_scene->hightlighted_instance != nullptr)
			//{
			//	sprite_editor_scene->selected_instance = sprite_editor_scene->hightlighted_instance;
			//	sprite_editor_scene->boundary_box->OnChange = this;
			//	sprite_editor_scene->boundary_box->enable = true;
			//	sprite_editor_scene->boundary_box->SetBoundary(sprite_editor_scene->selected_instance->GetOBB());
			//}
			//else
			//{
			//	sprite_editor_scene->boundary_box->enable = false;
			//	sprite_editor_scene->selected_instance = nullptr;
			//}
		}
	}
	void OnMouseMove(TMouseEventArgs e)
	{
		if (sprite_editor_scene->boundary_box->enable)
		{
			sprite_editor_scene->boundary_box->OnMouseMove(e, sprite_editor_scene->drawing_helper->GetContext().FromScreenPixelsToScene(e.location));
		}
		if (!sprite_editor_scene->boundary_box->IsCursorCaptured())
		{
			auto world_cursor_location = sprite_editor_scene->drawing_helper->GetContext().FromScreenPixelsToScene(TVec2i(e.location[0], e.location[1]));
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
		if (sprite_editor_scene->boundary_box->enable)
		{
			sprite_editor_scene->boundary_box->OnMouseUp(e, sprite_editor_scene->drawing_helper->GetContext().FromScreenPixelsToScene(e.location));
		}
		if (!sprite_editor_scene->boundary_box->IsCursorCaptured())
		{
		}
	}
	void CancelOperation()
	{
		sprite_editor_scene->boundary_box->enable = false;
	}
};
//
//
//class TModifySpritePhysShapeOBB : public IEditorTool, public TBoundaryBoxChangeListener
//{
//protected:
//	TSpriteEditorScene* sprite_editor_scene;
//public:
//	void Activate()
//	{
//		//sprite_editor_scene->sprite_polygon_adornment->SetVisible(true);
//	}
//	void Deactivate()
//	{
//		//sprite_editor_scene->sprite_polygon_adornment->SetVisible(false);
//	}
//	TWorldObjectType NeedObjectSelect()
//	{
//		return TWorldObjectType::None;
//	}
//	void SetSelectedObject(IBaluWorldObject* obj)
//	{
//		assert(false);
//	}
//	TModifySpritePolygonOBB(TSpriteEditorScene* sprite_editor_scene)
//	{
//		this->sprite_editor_scene = sprite_editor_scene;
//	}
//
//	void BoxResize(TOBB<float, 2> old_box, TOBB<float, 2> new_box)
//	{
//		auto scale = new_box.GetLocalAABB().GetSize() / old_box.GetLocalAABB().GetSize();
//		sprite_editor_scene->selected_instance->SetScale(
//			sprite_editor_scene->selected_instance->GetScale().ComponentMul(scale));
//	}
//	void BoxMove(TVec2 old_pos, TVec2 new_pos)
//	{
//		auto trans = sprite_editor_scene->selected_instance->GetTransform();
//		trans.position = new_pos;
//		sprite_editor_scene->selected_instance->SetTransform(trans);
//	}
//	void BoxRotate(TOBB<float, 2> old_box, TOBB<float, 2> new_box)
//	{
//		auto trans = sprite_editor_scene->selected_instance->GetTransform();
//		trans.angle = TRot(new_box);
//		sprite_editor_scene->selected_instance->SetTransform(trans);
//	}
//
//	void OnMouseDown(TMouseEventArgs e)
//	{
//		if (sprite_editor_scene->boundary_box->enable)
//		{
//			sprite_editor_scene->boundary_box->OnMouseDown(e, sprite_editor_scene->drawing_helper->FromScreenPixelsToScene(e.location));
//		}
//		if (!sprite_editor_scene->boundary_box->IsCursorCaptured())
//		{
//		}
//	}
//	void OnMouseMove(TMouseEventArgs e)
//	{
//		if (sprite_editor_scene->boundary_box->enable)
//		{
//			sprite_editor_scene->boundary_box->OnMouseMove(e, sprite_editor_scene->drawing_helper->FromScreenPixelsToScene(e.location));
//		}
//		if (!sprite_editor_scene->boundary_box->IsCursorCaptured())
//		{
//			auto world_cursor_location = sprite_editor_scene->drawing_helper->FromScreenPixelsToScene(TVec2i(e.location[0], e.location[1]));
//		}
//
//	}
//	void OnMouseUp(TMouseEventArgs e)
//	{
//		if (sprite_editor_scene->boundary_box->enable)
//		{
//			sprite_editor_scene->boundary_box->OnMouseUp(e, sprite_editor_scene->drawing_helper->FromScreenPixelsToScene(e.location));
//		}
//		if (!sprite_editor_scene->boundary_box->IsCursorCaptured())
//		{
//		}
//	}
//	void CancelOperation()
//	{
//
//	}
//};

class TEditSpritePolygon : public IEditorTool
{
protected:
	TSpriteEditorScene* sprite_editor_scene;
	std::string active_state;

	bool mouse_down;
	TVec2 mouse_down_pos;
	std::vector<TVec2> mouse_down_polygon;

	int nearest_point;
	int nearest_line;
	float nearest_point_dist;

	enum class CurrEditState
	{
		SelectionBox,
		MovingSelected,
		None
	} curr_edit_state;

	std::vector<int> selected_points;
	
	int point_under_cursor;
public:
	TEditSpritePolygon(TSpriteEditorScene* sprite_editor_scene)
	{
		this->sprite_editor_scene = sprite_editor_scene;
		this->active_state = GetAvailableStates()[0];
		this->mouse_down = false;
		this->curr_edit_state = CurrEditState::None;
		this->nearest_point = -1;
		this->nearest_line = -1;
	}
	void Activate()
	{
		sprite_editor_scene->sprite_polygon_adornment->SetVisual(sprite_editor_scene->source_sprite->GetPolygon());
		sprite_editor_scene->sprite_polygon_adornment->SetVisible(true);
	}
	void Deactivate()
	{
		sprite_editor_scene->sprite_polygon_adornment->SetVisible(false);
	}
	TWorldObjectType NeedObjectSelect()
	{
		return TWorldObjectType::None;
	}
	std::vector<std::string> GetAvailableStates()
	{
		return std::vector<std::string>()=
		{
			"edit", "create", "delete"
		};
	}
	void SetActiveState(std::string active_state)
	{
		this->active_state = active_state;

		sprite_editor_scene->sprite_polygon_adornment->ShowAddPointControl(false);
		sprite_editor_scene->sprite_polygon_adornment->ShowPointHightLinght(false);

		if (active_state == "edit")
		{

		}
		else if (active_state == "create")
		{
			sprite_editor_scene->sprite_polygon_adornment->ShowAddPointControl(true);
			sprite_editor_scene->sprite_polygon_adornment->SetAddPointControlData(-1, TVec2());
		}
		else if (active_state == "delete")
		{

		}
	}
	void SetSelectedObject(IBaluWorldObject* obj)
	{
		assert(false);
	}
	

	void UpdateOldPolygon()
	{
		mouse_down_polygon = sprite_editor_scene->source_sprite->GetPolygon()->GetPolygon();
	}

	void OnMouseDown(TMouseEventArgs e)
	{
		if (e.button != TMouseButton::Left) return;
		mouse_down = true;
		auto poly_trans = sprite_editor_scene->source_sprite->GetPolygon()->GetTransformWithScale();
		mouse_down_pos = poly_trans.ToLocal(sprite_editor_scene->drawing_helper->GetContext().FromScreenPixelsToScene(e.location));
		UpdateOldPolygon();
		if (active_state == "edit")
		{
			if (curr_edit_state == CurrEditState::MovingSelected)
			{
				if (nearest_point != -1)
				{
					if (std::find(selected_points.begin(), selected_points.end(), nearest_point) == selected_points.end())
					{
						selected_points.clear();
						selected_points.push_back(nearest_point);
					}
				}
			}
		}
		else if (active_state == "create")
		{
			if (nearest_line != -1)
			{
				auto poly_vertices = sprite_editor_scene->source_sprite->GetPolygon()->GetPolygon();
				poly_vertices.insert(poly_vertices.begin() + nearest_line + 1, mouse_down_pos);
				sprite_editor_scene->source_sprite->GetPolygon()->SetVertices(poly_vertices);
			}
			else
			{
				auto poly_vertices = sprite_editor_scene->source_sprite->GetPolygon()->GetPolygon();
				poly_vertices.push_back(mouse_down_pos);
				sprite_editor_scene->source_sprite->GetPolygon()->SetVertices(poly_vertices);
			}
		}
		else if (active_state == "delete")
		{
			if (curr_edit_state == CurrEditState::MovingSelected)
			{
				if (nearest_point != -1)
				{
					auto poly_vertices = sprite_editor_scene->source_sprite->GetPolygon()->GetPolygon();
					poly_vertices.erase(poly_vertices.begin() + nearest_point);
					sprite_editor_scene->source_sprite->GetPolygon()->SetVertices(poly_vertices);
					selected_points.clear();
					sprite_editor_scene->sprite_polygon_adornment->SetShowPointHightlightData(selected_points);
				}
			}
		}
	}
	void FindNearestPoint(TVec2 new_pos)
	{
		auto poly_vertices = sprite_editor_scene->source_sprite->GetPolygon()->GetPolygon();
		int size = poly_vertices.size();

		nearest_point = -1;
		nearest_point_dist = 0;
		for (int i = 0; i < size; i++)
		{
			float dist = poly_vertices[i].Distance(new_pos);
			if (nearest_point == -1 || nearest_point_dist > dist)
			{
				nearest_point = i;
				nearest_point_dist = dist;
			}
		}
	}
	void OnMouseMove(TMouseEventArgs e)
	{
		auto poly_trans = sprite_editor_scene->source_sprite->GetPolygon()->GetTransformWithScale();
		TVec2 new_pos = poly_trans.ToLocal(sprite_editor_scene->drawing_helper->GetContext().FromScreenPixelsToScene(e.location));

		if (active_state == "edit")
		{
			if (mouse_down)
			{
				if (curr_edit_state == CurrEditState::SelectionBox)
				{
					sprite_editor_scene->sprite_polygon_adornment->ShowPointHightLinght(true);
					TOBB2 selection_box = TOBB2(
						(poly_trans.ToGlobal(new_pos) + poly_trans.ToGlobal(mouse_down_pos))*0.5,
						TMatrix2::GetIdentity(), 
						TAABB2(TVec2(0, 0), (poly_trans.ToGlobal(new_pos) - poly_trans.ToGlobal(mouse_down_pos)).GetAbs()*0.5));
					sprite_editor_scene->sprite_polygon_adornment->ShowSelectionBox(true);
					sprite_editor_scene->sprite_polygon_adornment->SetSelectionBox(selection_box);
					selected_points.clear();
					for (int i = 0; i < mouse_down_polygon.size();i++)
					{
						if (selection_box.PointCollide(poly_trans.ToGlobal(mouse_down_polygon[i])))
						{
							selected_points.push_back(i);
						}
					}
					sprite_editor_scene->sprite_polygon_adornment->SetShowPointHightlightData(selected_points);
				}
				else if (curr_edit_state == CurrEditState::MovingSelected)
				{
					if (selected_points.size() > 0)
					{
						auto vertices = sprite_editor_scene->source_sprite->GetPolygon()->GetPolygon();
						for (auto& v : selected_points)
							vertices[v] = mouse_down_polygon[v] + new_pos - mouse_down_pos;
						sprite_editor_scene->source_sprite->GetPolygon()->SetVertices(vertices);
					}
				}
			}
			else
			{
				sprite_editor_scene->sprite_polygon_adornment->ShowSelectionBox(false);
				sprite_editor_scene->sprite_polygon_adornment->ShowPointHightLinght(true);
				FindNearestPoint(new_pos);
				if (nearest_point!=-1&&nearest_point_dist < 0.3)
				{
					curr_edit_state = CurrEditState::MovingSelected;
					std::vector<int> v;
					v.push_back(nearest_point);
					sprite_editor_scene->sprite_polygon_adornment->SetShowPointHightlightData(v);
				}
				else
				{
					curr_edit_state = CurrEditState::SelectionBox;
					std::vector<int> v;
					sprite_editor_scene->sprite_polygon_adornment->SetShowPointHightlightData(v);
				}
			}
		}
		else if (active_state == "create")
		{
			auto poly_vertices = sprite_editor_scene->source_sprite->GetPolygon()->GetPolygon();
			int size = poly_vertices.size();
			
			nearest_line = -1;
			float nearest_line_dist = 0;
			if (size > 0)
			{
				for (int i = 0; i < size + 1; i++)
				{
					float t;
					TVec2 p;
					float dist = DistanceBetweenPointSegment(new_pos, TSegment<float, 2>(poly_vertices[i%size], poly_vertices[(i + 1) % size]), t, p);
					//if (t>0 && t < 1)
					{
						if (nearest_line == -1 || dist < nearest_line_dist)
						{
							nearest_line = i;
							nearest_line_dist = dist;
						}
					}
				}
			}
			sprite_editor_scene->sprite_polygon_adornment->SetAddPointControlData(nearest_line, new_pos);
		}
		else if (active_state == "delete")
		{
			sprite_editor_scene->sprite_polygon_adornment->ShowSelectionBox(false);
			sprite_editor_scene->sprite_polygon_adornment->ShowPointHightLinght(true);
			FindNearestPoint(new_pos);
			if (nearest_point!=-1&&nearest_point_dist < 0.3)
			{
				curr_edit_state = CurrEditState::MovingSelected;
				selected_points.clear();
				selected_points.push_back(nearest_point);
				sprite_editor_scene->sprite_polygon_adornment->SetShowPointHightlightData(selected_points);
			}
			else
			{
				curr_edit_state = CurrEditState::None;
				selected_points.clear();
				sprite_editor_scene->sprite_polygon_adornment->SetShowPointHightlightData(selected_points);
			}
		}
	}
	void OnMouseUp(TMouseEventArgs e)
	{
		if (e.button != TMouseButton::Left) return;
		mouse_down = false;
		if (active_state == "edit")
		{

		}
		else if (active_state == "create")
		{
			//sprite_editor_scene->sprite_polygon_adornment->SetAddPointControlData();
		}
		else if (active_state == "delete")
		{

		}
	}
	void CancelOperation()
	{

	}
};

//
//class TEditPhysShapePolygon : public IEditorTool, public TBoundaryBoxChangeListener
//{
//protected:
//	TSpriteEditorScene* sprite_editor_scene;
//public:
//	void Activate()
//	{
//		//sprite_editor_scene->sprite_polygon_adornment->SetVisible(true);
//	}
//	void Deactivate()
//	{
//		//sprite_editor_scene->sprite_polygon_adornment->SetVisible(false);
//	}
//	TWorldObjectType NeedObjectSelect()
//	{
//		return TWorldObjectType::None;
//	}
//	void SetSelectedObject(IBaluWorldObject* obj)
//	{
//		assert(false);
//	}
//	TModifySpritePolygonOBB(TSpriteEditorScene* sprite_editor_scene)
//	{
//		this->sprite_editor_scene = sprite_editor_scene;
//	}
//
//	void BoxResize(TOBB<float, 2> old_box, TOBB<float, 2> new_box)
//	{
//		auto scale = new_box.GetLocalAABB().GetSize() / old_box.GetLocalAABB().GetSize();
//		sprite_editor_scene->selected_instance->SetScale(
//			sprite_editor_scene->selected_instance->GetScale().ComponentMul(scale));
//	}
//	void BoxMove(TVec2 old_pos, TVec2 new_pos)
//	{
//		auto trans = sprite_editor_scene->selected_instance->GetTransform();
//		trans.position = new_pos;
//		sprite_editor_scene->selected_instance->SetTransform(trans);
//	}
//	void BoxRotate(TOBB<float, 2> old_box, TOBB<float, 2> new_box)
//	{
//		auto trans = sprite_editor_scene->selected_instance->GetTransform();
//		trans.angle = TRot(new_box);
//		sprite_editor_scene->selected_instance->SetTransform(trans);
//	}
//
//	void OnMouseDown(TMouseEventArgs e)
//	{
//		if (sprite_editor_scene->boundary_box->enable)
//		{
//			sprite_editor_scene->boundary_box->OnMouseDown(e, sprite_editor_scene->drawing_helper->FromScreenPixelsToScene(e.location));
//		}
//		if (!sprite_editor_scene->boundary_box->IsCursorCaptured())
//		{
//		}
//	}
//	void OnMouseMove(TMouseEventArgs e)
//	{
//		if (sprite_editor_scene->boundary_box->enable)
//		{
//			sprite_editor_scene->boundary_box->OnMouseMove(e, sprite_editor_scene->drawing_helper->FromScreenPixelsToScene(e.location));
//		}
//		if (!sprite_editor_scene->boundary_box->IsCursorCaptured())
//		{
//			auto world_cursor_location = sprite_editor_scene->drawing_helper->FromScreenPixelsToScene(TVec2i(e.location[0], e.location[1]));
//		}
//
//	}
//	void OnMouseUp(TMouseEventArgs e)
//	{
//		if (sprite_editor_scene->boundary_box->enable)
//		{
//			sprite_editor_scene->boundary_box->OnMouseUp(e, sprite_editor_scene->drawing_helper->FromScreenPixelsToScene(e.location));
//		}
//		if (!sprite_editor_scene->boundary_box->IsCursorCaptured())
//		{
//		}
//	}
//	void CancelOperation()
//	{
//
//	}
//};

TSpriteEditorToolsRegistry::TSpriteEditorToolsRegistry(TSpriteEditorScene* scene)
{
	this->scene = scene;
	tools.emplace_back(new TModifySpritePolygonOBB(scene), "Move sprite");
	//tools.emplace_back(new TModifySpritePolygonOBB(scene), "Move phys shape");
	tools.emplace_back(new TEditSpritePolygon(scene), "Edit sprite");
	//tools.emplace_back(new TModifySpritePolygonOBB(scene), "Edit phys");
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