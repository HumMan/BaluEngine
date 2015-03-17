
#include "OBBContour.h"

#include "DrawingHelper.h"

class TOBBContourPrivate
{
	friend class TOBBContour;
	friend void OBBContourCustomDraw(TCallbackData* data, NVGcontext* vg, TCustomDrawCommand* params);
private:
	IBaluInstance* class_instance;
	bool enable;
	TDrawingHelper* drawing_helper;
	TOBB2 box;
	IBaluWorld* world;
	IBaluSceneInstance* scene_instance;
};

void OBBContourCustomDraw(TCallbackData* data, NVGcontext* vg, TCustomDrawCommand* params)
{
	auto state = (TOBBContourPrivate*)data->GetUserData();
	if (state->enable)
	{
		state->drawing_helper->RenderBoxCountour(state->box, 1);
	}
}

TOBBContour::TOBBContour(IBaluSceneInstance* scene_instance, TDrawingHelper* drawing_helper)
{
	p = std::make_unique<TOBBContourPrivate>();

	p->drawing_helper = drawing_helper;
	p->scene_instance = scene_instance;
	p->world = scene_instance->GetWorld()->GetSource();
	IBaluClass* adornment_class;
	if (p->world->TryFind("SceneEditorOBBContour", adornment_class))
	{
		assert(false);
	}
	adornment_class = CreateClass(p->world, scene_instance->GetSource(), p.get());

	p->class_instance = scene_instance->CreateInstance(adornment_class, TBaluTransform(TVec2(0, 0), TRot(0)), TVec2(1, 1));
}

void TOBBContour::SetBox(TOBB2 box)
{
	p->box = box;
}

void TOBBContour::SetEnable(bool enable)
{
	p->enable = enable;
}

EngineInterface::IBaluClass* TOBBContour::CreateClass(EngineInterface::IBaluWorld* world, EngineInterface::IBaluScene* scene, TOBBContourPrivate* data)
{
	auto adornment_class = world->CreateClass("SceneEditorOBBContour");
	dynamic_cast<IBaluWorldObject*>(adornment_class)->GetProperties()->SetBool("editor_temp_object", true);
	auto adornment_sprite = world->CreateSprite("SceneEditorOBBContour_custom_draw_sprite");
	dynamic_cast<IBaluWorldObject*>(adornment_sprite)->GetProperties()->SetBool("editor_temp_object", true);
	//adornment_sprite->GetPolygone()->SetEnable(false);
	adornment_sprite->GetPolygone()->OnCustomDraw(CallbackWithData<TCustomDrawCallback>(OBBContourCustomDraw, &world->GetCallbacksActiveType(), data, TCallbacksActiveType::EDITOR));
	adornment_class->AddSprite(adornment_sprite);

	return adornment_class;
}

TOBBContour::~TOBBContour()
{
	p->scene_instance->DestroyInstance(p->class_instance);
	p->world->DestroyClass("SceneEditorOBBContour");
	p->world->DestroySprite("SceneEditorOBBContour_custom_draw_sprite");
}