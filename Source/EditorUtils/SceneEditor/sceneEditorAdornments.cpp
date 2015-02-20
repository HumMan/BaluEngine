#include "sceneEditorAdornments.h"

#include "../../EngineInterfaces/IClass.h"
#include "../../EngineInterfaces/IScene.h"
#include "../../EngineInterfaces/IWorld.h"

#include "../../EngineInterfaces/IClassInstance.h"
#include "../../EngineInterfaces/ISceneInstance.h"
#include "../../EngineInterfaces/IWorldInstance.h"

using namespace EngineInterface;

#include "../EditorControlsModel.h"
#include "../DrawingHelper.h"

class TClassInstanceAdornmentPrivate
{
	friend class TClassInstanceAdornment;
	friend void ClassInstanceAdornmentCustomDraw(TCallbackData* data, NVGcontext* vg, TCustomDrawCommand* params);
private:
	IBaluInstance* class_instance;
	bool visible;
	IVisualAdornment* visual;
	TDrawingHelper* drawing_helper;
};

//IBaluInstance* TClassInstanceAdornment::GetInstance()
//{
//	return p->class_instance;
//}

TClassInstanceAdornment::~TClassInstanceAdornment()
{

}

void ClassInstanceAdornmentCustomDraw(TCallbackData* data, NVGcontext* vg, TCustomDrawCommand* params)
{
	auto state = (TClassInstanceAdornmentPrivate*)data->GetUserData();
	//if (state->visible)
	{
		auto items = state->visual->Render();
		for (auto& v : items)
			v->Render(state->drawing_helper);
	}
}

EngineInterface::IBaluClass* TClassInstanceAdornment::CreateClass(IBaluWorld* world, IBaluScene* scene, TClassInstanceAdornmentPrivate* data)
{
	auto adornment_class = world->CreateClass("SceneEditorAdornment");
	auto adornment_sprite = world->CreateSprite("SceneEditorAdornment_custom_draw_sprite");
	//adornment_sprite->GetPolygone()->SetEnable(false);
	adornment_sprite->GetPolygone()->OnCustomDraw(CallbackWithData<TCustomDrawCallback>(ClassInstanceAdornmentCustomDraw, &world->GetCallbacksActiveType(), data, TCallbacksActiveType::EDITOR));
	adornment_class->AddSprite(adornment_sprite);

	return adornment_class;
}

TClassInstanceAdornment::TClassInstanceAdornment(IBaluSceneInstance* scene_instance, IVisualAdornment* visual, TDrawingHelper* drawing_helper)
{
	p = std::make_unique<TClassInstanceAdornmentPrivate>();

	p->visual = visual;
	p->drawing_helper = drawing_helper;

	IBaluWorld* world = scene_instance->GetWorld()->GetSource();
	IBaluClass* adornment_class;
	if (!world->TryFindClass("SceneEditorAdornment", adornment_class))
	{
		adornment_class = CreateClass(world, scene_instance->GetSource(), p.get());
	}
		
	p->class_instance = scene_instance->CreateInstance(adornment_class, TBaluTransform(TVec2(0,0), TRot(0)));
}

//void TClassInstanceAdornment::Render(TDrawingHelper* drawing_helper)
//{
//	TBoundaryBoxAdornment::Render(drawing_helper);
//	drawing_helper->SetTransform(class_instance->instance_transform.position);
//	drawing_helper->DrawClass(class_instance->instance_class);
//	drawing_helper->PopTransform();
//}

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
	//if (state->visible)
	{
		state->drawing_helper->RenderBoxCountour(state->box);
	}
}

TOBBContour::TOBBContour(IBaluSceneInstance* scene_instance, TDrawingHelper* drawing_helper)
{
	p = std::make_unique<TOBBContourPrivate>();

	p->drawing_helper = drawing_helper;

	IBaluWorld* world = scene_instance->GetWorld()->GetSource();
	IBaluClass* adornment_class;
	if (!world->TryFindClass("SceneEditorOBBContour", adornment_class))
	{
		adornment_class = CreateClass(world, scene_instance->GetSource(), p.get());
	}

	p->class_instance = scene_instance->CreateInstance(adornment_class, TBaluTransform(TVec2(0, 0), TRot(0)));
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