
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

	IBaluWorld* world = scene_instance->GetWorld()->GetSource();
	IBaluClass* adornment_class;
	if (!world->TryFind("SceneEditorOBBContour", adornment_class))
	{
		adornment_class = CreateClass(world, scene_instance->GetSource(), p.get());
	}

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
	auto adornment_sprite = world->CreateSprite("SceneEditorOBBContour_custom_draw_sprite");
	//adornment_sprite->GetPolygone()->SetEnable(false);
	adornment_sprite->GetPolygone()->OnCustomDraw(CallbackWithData<TCustomDrawCallback>(OBBContourCustomDraw, &world->GetCallbacksActiveType(), data, TCallbacksActiveType::EDITOR));
	adornment_class->AddSprite(adornment_sprite);

	return adornment_class;
}

TOBBContour::~TOBBContour()
{

}