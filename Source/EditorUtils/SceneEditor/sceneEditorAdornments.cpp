#include "sceneEditorAdornments.h"

#include "../../EngineInterfaces/IClass.h"
#include "../../EngineInterfaces/IScene.h"
#include "../../EngineInterfaces/IWorld.h"

#include "../../EngineInterfaces/IClassInstance.h"
#include "../../EngineInterfaces/ISceneInstance.h"
#include "../../EngineInterfaces/IWorldInstance.h"

using namespace EngineInterface;

#include "nanovg.h"

class TClassInstanceAdornmentPrivate
{
	friend class TClassInstanceAdornment;
	friend void ClassInstanceAdornmentCustomDraw(NVGcontext* vg, TCustomDrawCommand* params);
private:
	IBaluInstance* class_instance;
	bool visible;
};

IBaluInstance* TClassInstanceAdornment::GetInstance()
{
	return p->class_instance;
}

TClassInstanceAdornment::~TClassInstanceAdornment()
{

}

void ClassInstanceAdornmentCustomDraw(NVGcontext* vg, TCustomDrawCommand* params)
{
	auto state = (TClassInstanceAdornmentPrivate*)params->command.user_data;
	//if (state->visible)
	{
		//auto transform = params->poly->GetGlobalTransform();
		auto transform = TBaluTransform(TVec2(200,200), TRot(0));

		float cornerRadius = 3.0f;
		NVGpaint shadowPaint;
		NVGpaint headerPaint;

		nvgBeginPath(vg);
		//TODO from scene space to screen
		//nvgCircle(vg, transform.position[0], transform.position[1], 4.0f);
		nvgCircle(vg, transform.position[0], transform.position[1], 5.0f);
		nvgFillColor(vg, nvgRGBA(0, 160, 192, 255));
		nvgFill(vg);

		nvgBeginPath(vg);
		nvgCircle(vg, transform.position[0], transform.position[1], 3.0f);
		nvgFillColor(vg, nvgRGBA(220, 220, 220, 255));
		nvgFill(vg);
	}
}

EngineInterface::IBaluClass* TClassInstanceAdornment::CreateClass(IBaluWorld* world, IBaluScene* scene)
{
	auto adornment_class = world->CreateClass("SceneEditorAdornment");
	auto adornment_sprite = world->CreateSprite("SceneEditorAdornment_custom_draw_sprite");
	//adornment_sprite->GetPolygone()->SetEnable(false);
	adornment_sprite->GetPolygone()->OnCustomDraw(ClassInstanceAdornmentCustomDraw);
	adornment_class->AddSprite(adornment_sprite);

	return adornment_class;
}

TClassInstanceAdornment::TClassInstanceAdornment(IBaluSceneInstance* scene_instance)
{
	p = std::make_unique<TClassInstanceAdornmentPrivate>();

	IBaluWorld* world = scene_instance->GetWorld()->GetSource();
	IBaluClass* adornment_class;
	if (!world->TryFindClass("SceneEditorAdornment", adornment_class))
	{
		adornment_class = CreateClass(world, scene_instance->GetSource());
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