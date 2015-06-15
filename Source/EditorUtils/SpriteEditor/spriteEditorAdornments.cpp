#include "spriteEditorAdornments.h"

#include "../../EngineInterfaces/ISprite.h"
#include "../../EngineInterfaces/IScene.h"
#include "../../EngineInterfaces/IWorld.h"

#include "../../EngineInterfaces/ISpriteInstance.h"
#include "../../EngineInterfaces/ISceneInstance.h"
#include "../../EngineInterfaces/IWorldInstance.h"

using namespace EngineInterface;

#include "../EditorControlsModel.h"
#include "../DrawingHelper.h"

class TSpritePolygonOBBAdornmentPrivate
{
	friend class TSpriteOBBAdornment;
	friend void SpritePolygonOBBAdornmentCustomDraw(void* user_data, NVGcontext* vg, TCustomDrawCommand* params);
private:
	IBaluInstance* class_instance;
	bool visible;
	IVisualAdornment* visual;
	TDrawingHelper* drawing_helper;
	IBaluWorld* world;
	IBaluSceneInstance* scene_instance;
};

TSpriteOBBAdornment::~TSpriteOBBAdornment()
{
	p->scene_instance->DestroyInstance(p->class_instance);
	p->world->DestroyClass("SpritePolygonOBBAdornment");
	p->world->DestroySprite("SpritePolygonOBBAdornment_custom_draw_sprite");
}

void SpritePolygonOBBAdornmentCustomDraw(void* user_data, NVGcontext* vg, TCustomDrawCommand* params)
{
	auto state = (TSpritePolygonOBBAdornmentPrivate*)user_data;
	//if (state->visible)
	{
		auto items = state->visual->Render();
		for (auto& v : items)
			v->Render(state->drawing_helper);
	}
}

EngineInterface::IBaluClass* TSpriteOBBAdornment::CreateClass(IBaluWorld* world, IBaluScene* scene, TSpritePolygonOBBAdornmentPrivate* data)
{
	auto adornment_class = world->CreateClass("SpritePolygonOBBAdornment");
	dynamic_cast<IBaluWorldObject*>(adornment_class)->GetProperties()->SetBool("editor_temp_object", true);
	auto adornment_sprite = world->CreateSprite("SpritePolygonOBBAdornment_custom_draw_sprite");
	dynamic_cast<IBaluWorldObject*>(adornment_sprite)->GetProperties()->SetBool("editor_temp_object", true);
	//adornment_sprite->GetPolygon()->SetEnable(false);
//	adornment_sprite->GetPolygon()->AddOnCustomDraw(TSpecialCallback<TCustomDrawCallback>(SpritePolygonOBBAdornmentCustomDraw, &world->GetCallbacksActiveType(), data, TCallbacksActiveType::EDITOR));
	adornment_class->AddSprite(adornment_sprite);

	return adornment_class;
}

TSpriteOBBAdornment::TSpriteOBBAdornment(IBaluSceneInstance* scene_instance, IVisualAdornment* visual, TDrawingHelper* drawing_helper)
{
	p = std::make_unique<TSpritePolygonOBBAdornmentPrivate>();

	p->visual = visual;
	p->drawing_helper = drawing_helper;

	p->scene_instance = scene_instance;

	IBaluWorld* world = scene_instance->GetWorld()->GetSource();
	p->world = world;

	IBaluClass* adornment_class;
	if (world->TryFind("SpritePolygonOBBAdornment", adornment_class))
	{
		assert(false);
	}
	adornment_class = CreateClass(world, scene_instance->GetSource(), p.get());

	p->class_instance = scene_instance->CreateInstance(adornment_class, TBaluTransform(TVec2(0, 0), TRot(0)), TVec2(1, 1));
}

class TSpritePolygonAdornmentPrivate
{
	friend class TSpritePolygonAdornment;
	friend void SpritePolygonAdornmentCustomDraw(void* user_data, NVGcontext* vg, TCustomDrawCommand* params);
private:
	IBaluInstance* class_instance;
	bool visible;
	IBaluSprite* visual;
	TDrawingHelper* drawing_helper;
	IBaluWorld* world;
	IBaluSceneInstance* scene_instance;

	bool show_add_point_control;
	int line_start_point_index;
	TVec2 point_to_add;

	bool show_point_hightlight;
	std::vector<int> hightlight_poly_point_index;

	bool show_selection_box;
	TOBB2 selection_box;
};

TSpritePolygonAdornment::~TSpritePolygonAdornment()
{
	p->scene_instance->DestroyInstance(p->class_instance);
	p->world->DestroyClass("SpritePolygonAdornment");
	p->world->DestroySprite("SpritePolygonAdornment_custom_draw_sprite");
}

void TSpritePolygonAdornment::SetVisible(bool visible)
{
	p->visible = visible;
}

void TSpritePolygonAdornment::ShowAddPointControl(bool show)
{
	p->show_add_point_control = show;
}
void TSpritePolygonAdornment::SetAddPointControlData(int line_start_point_index, TVec2 point_to_add)
{
	p->line_start_point_index = line_start_point_index;
	p->point_to_add = point_to_add;
}

void TSpritePolygonAdornment::ShowPointHightLinght(bool show)
{
	p->show_point_hightlight = show;
}

void TSpritePolygonAdornment::SetShowPointHightlightData(std::vector<int> poly_point_index)
{
	p->hightlight_poly_point_index = poly_point_index;
}

void TSpritePolygonAdornment::ShowSelectionBox(bool visible)
{
	p->show_selection_box = visible;
}
void TSpritePolygonAdornment::SetSelectionBox(TOBB2 box)
{
	p->selection_box = box;
}

void SpritePolygonAdornmentCustomDraw(void* user_data, NVGcontext* vg, TCustomDrawCommand* params)
{
	auto state = (TSpritePolygonAdornmentPrivate*)user_data;
	if (state->visible)
	{
		auto sprite_poly = state->visual->GetPolygon();
		auto sprite_poly_trans = sprite_poly->GetTransformWithScale();
		auto vertices = sprite_poly->GetPolygon();
		state->drawing_helper->RenderLinesLoop(vertices, sprite_poly_trans);
		for (auto& v : vertices)
			state->drawing_helper->RenderPointAdornment(v, sprite_poly_trans);

		if (state->show_add_point_control && state->line_start_point_index!=-1)
		{
			TVec2 left, right;
			left = sprite_poly_trans.ToGlobal(vertices[state->line_start_point_index]);
			right = sprite_poly_trans.ToGlobal(vertices[(state->line_start_point_index + 1) % vertices.size()]);
			state->drawing_helper->RenderPointAdornment(state->point_to_add, sprite_poly_trans);

			state->drawing_helper->RenderLine(left, sprite_poly_trans.ToGlobal(state->point_to_add));
			state->drawing_helper->RenderLine(right, sprite_poly_trans.ToGlobal(state->point_to_add));
		}
		if (state->show_selection_box)
		{
			state->drawing_helper->RenderSelectionBox(state->selection_box);
		}
		if (state->show_point_hightlight)
		{
			for (auto& v : state->hightlight_poly_point_index)
			{
				state->drawing_helper->RenderPointHighlightAdornment(vertices[v], sprite_poly_trans);
			}
		}
	}
}

EngineInterface::IBaluClass* TSpritePolygonAdornment::CreateClass(IBaluWorld* world, IBaluScene* scene, TSpritePolygonAdornmentPrivate* data)
{
	auto adornment_class = world->CreateClass("SpritePolygonAdornment");
	dynamic_cast<IBaluWorldObject*>(adornment_class)->GetProperties()->SetBool("editor_temp_object", true);
	auto adornment_sprite = world->CreateSprite("SpritePolygonAdornment_custom_draw_sprite");
	dynamic_cast<IBaluWorldObject*>(adornment_sprite)->GetProperties()->SetBool("editor_temp_object", true);
	//adornment_sprite->GetPolygon()->SetEnable(false);
//	adornment_sprite->GetPolygon()->AddOnCustomDraw(TSpecialCallback<TCustomDrawCallback>(SpritePolygonAdornmentCustomDraw, &world->GetCallbacksActiveType(), data, TCallbacksActiveType::EDITOR));
	adornment_class->AddSprite(adornment_sprite);

	return adornment_class;
}

TSpritePolygonAdornment::TSpritePolygonAdornment(IBaluSceneInstance* scene_instance, IBaluSprite* visual, TDrawingHelper* drawing_helper)
{
	p = std::make_unique<TSpritePolygonAdornmentPrivate>();

	p->visual = visual;
	p->drawing_helper = drawing_helper;

	p->scene_instance = scene_instance;

	IBaluWorld* world = scene_instance->GetWorld()->GetSource();
	p->world = world;
	IBaluClass* adornment_class;
	if (world->TryFind("SpritePolygonAdornment", adornment_class))
	{
		assert(false);
	}
	adornment_class = CreateClass(world, scene_instance->GetSource(), p.get());
	p->class_instance = scene_instance->CreateInstance(adornment_class, TBaluTransform(TVec2(0, 0), TRot(0)), TVec2(1, 1));
}


class TSpriteAdornmentPrivate
{
	friend class TSpriteAdornment;
	friend void SpritePolygonAdornmentCustomDraw(void* user_data, NVGcontext* vg, TCustomDrawCommand* params);
private:
	IBaluInstance* class_instance;
	bool visible;
	IBaluSprite* visual;
	TDrawingHelper* drawing_helper;
	IBaluWorld* world;
	IBaluSceneInstance* scene_instance;
};

TSpriteAdornment::~TSpriteAdornment()
{
	p->scene_instance->DestroyInstance(p->class_instance);
	p->world->DestroyClass("SpriteAdornment");
}

EngineInterface::IBaluClass* TSpriteAdornment::CreateClass(IBaluWorld* world, IBaluScene* scene, TSpriteAdornmentPrivate* data)
{
	auto adornment_class = world->CreateClass("SpriteAdornment");
	auto adornment_sprite = adornment_class->AddSprite(data->visual);

	return adornment_class;
}

TSpriteAdornment::TSpriteAdornment(IBaluSceneInstance* scene_instance, IBaluSprite* visual, TDrawingHelper* drawing_helper)
{
	p = std::make_unique<TSpriteAdornmentPrivate>();
	
	p->visual = visual;
	p->drawing_helper = drawing_helper;
	p->scene_instance = scene_instance;

	IBaluWorld* world = scene_instance->GetWorld()->GetSource();
	p->world = world;

	IBaluClass* adornment_class;
	if (world->TryFind("SpriteAdornment", adornment_class))
	{
		assert(false);
	}

	adornment_class = CreateClass(world, scene_instance->GetSource(), p.get());

	p->class_instance = scene_instance->CreateInstance(adornment_class, TBaluTransform(TVec2(0, 0), TRot(0)), TVec2(1, 1));
	p->class_instance->UpdateTranform();
}

IBaluInstance* TSpriteAdornment::GetInstance()
{
	return p->class_instance;
}