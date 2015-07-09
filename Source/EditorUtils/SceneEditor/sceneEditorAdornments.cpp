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
	//friend void ClassInstanceAdornmentCustomDraw(void* user_data, NVGcontext* vg, TCustomDrawCommand* params);
private:
	IBaluInstance* class_instance;
	bool visible;
	IVisualAdornment* visual;
	TDrawingHelper* drawing_helper;
	IBaluWorld* world;
	IBaluSceneInstance* scene_instance;
};

//IBaluInstance* TClassInstanceAdornment::GetInstance()
//{
//	return p->class_instance;
//}

TClassInstanceAdornment::~TClassInstanceAdornment()
{
	p->scene_instance->DestroyInstance(dynamic_cast<TSceneObjectInstance*>(p->class_instance));
	p->world->DestroyClass("SceneEditorAdornment");
	p->world->DestroySprite("SceneEditorAdornment_custom_draw_sprite");
}

//void ClassInstanceAdornmentCustomDraw(void* user_data, NVGcontext* vg, TCustomDrawCommand* params)
//{
//	auto state = (TClassInstanceAdornmentPrivate*)user_data;
//	//if (state->visible)
//	{
//		auto items = state->visual->Render();
//		for (auto& v : items)
//			v->Render(state->drawing_helper);
//	}
//}

EngineInterface::IBaluClass* TClassInstanceAdornment::CreateClass(IBaluWorld* world, IBaluScene* scene, TClassInstanceAdornmentPrivate* data)
{
	auto adornment_class = world->CreateClass("SceneEditorAdornment");
	dynamic_cast<IBaluWorldObject*>(adornment_class)->GetProperties()->SetBool("editor_temp_object", true);
	auto adornment_sprite = world->CreateSprite("SceneEditorAdornment_custom_draw_sprite");
	dynamic_cast<IBaluWorldObject*>(adornment_sprite)->GetProperties()->SetBool("editor_temp_object", true);
	//adornment_sprite->GetPolygon()->SetEnable(false);
//	adornment_sprite->GetPolygon()->AddOnCustomDraw(TSpecialCallback<TCustomDrawCallback>(ClassInstanceAdornmentCustomDraw, &world->GetCallbacksActiveType(), data, TCallbacksActiveType::EDITOR));
	adornment_class->AddSprite(adornment_sprite);

	return adornment_class;
}

TClassInstanceAdornment::TClassInstanceAdornment(IBaluSceneInstance* scene_instance, IVisualAdornment* visual, TDrawingHelper* drawing_helper)
{
	p = std::make_unique<TClassInstanceAdornmentPrivate>();

	p->visual = visual;
	p->drawing_helper = drawing_helper;
	p->scene_instance = scene_instance;

	IBaluWorld* world = scene_instance->GetWorld()->GetSource();
	p->world = world;
	IBaluClass* adornment_class;
	if (world->TryFind("SceneEditorAdornment", adornment_class))
	{
		assert(false);
	}
	adornment_class = CreateClass(world, scene_instance->GetSource(), p.get());
		
	p->class_instance = dynamic_cast<IBaluInstance*>(scene_instance->CreateInstance(dynamic_cast<TSceneObject*>(adornment_class), TBaluTransform(TVec2(0, 0), TRot(0)), TVec2(1, 1)));
}

//void TClassInstanceAdornment::Render(TDrawingHelper* drawing_helper)
//{
//	TBoundaryBoxAdornment::Render(drawing_helper);
//	drawing_helper->SetTransform(class_instance->instance_transform.position);
//	drawing_helper->DrawClass(class_instance->instance_class);
//	drawing_helper->PopTransform();
//}
