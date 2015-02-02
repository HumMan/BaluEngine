#include "sceneEditorAdornments.h"

#include "../../EngineInterfaces/IClass.h"
#include "../../EngineInterfaces/IScene.h"
#include "../../EngineInterfaces/IWorld.h"

#include "../../EngineInterfaces/IClassInstance.h"
#include "../../EngineInterfaces/ISceneInstance.h"
#include "../../EngineInterfaces/IWorldInstance.h"

using namespace EngineInterface;

class TClassInstanceAdornmentPrivate
{
	friend class TClassInstanceAdornment;
	friend void ClassInstanceAdornmentCustomDraw(IBaluSpritePolygonInstance* instance, NVGcontext* vg, void* user_data);
private:
	IBaluInstance* class_instance;
	bool visible;
};

void ClassInstanceAdornmentCustomDraw(IBaluSpritePolygonInstance* instance, NVGcontext* vg, void* user_data)
{
	auto state = (TClassInstanceAdornmentPrivate*)user_data;
	if (state->visible)
	{

	}
}

EngineInterface::IBaluClass* TClassInstanceAdornment::CreateClass(IBaluWorld* world, IBaluScene* scene)
{
	auto adornment_class = world->CreateClass("SceneEditorAdornment");
	auto adornment_sprite = world->CreateSprite("SceneEditorAdornment_custom_draw_sprite");
	adornment_sprite->GetPolygone()->OnCustomDraw(ClassInstanceAdornmentCustomDraw);
	adornment_class->AddSprite(adornment_sprite);

	return adornment_class;
}

TClassInstanceAdornment::TClassInstanceAdornment(IBaluSceneInstance* scene_instance)
{
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