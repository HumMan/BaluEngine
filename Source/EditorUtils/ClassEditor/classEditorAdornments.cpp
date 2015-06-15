#include "classEditorAdornments.h"

#include "../../EngineInterfaces/IClass.h"
#include "../../EngineInterfaces/IScene.h"
#include "../../EngineInterfaces/IWorld.h"

#include "../../EngineInterfaces/IClassInstance.h"
#include "../../EngineInterfaces/ISceneInstance.h"
#include "../../EngineInterfaces/IWorldInstance.h"

using namespace EngineInterface;

#include "../EditorControlsModel.h"
#include "../DrawingHelper.h"

class TSpriteInstanceAdornmentPrivate
{
	friend class TClassSpriteAdornment;
	friend void SpriteInstanceAdornmentCustomDraw(void* user_data, NVGcontext* vg, TCustomDrawCommand* params);
private:
	IBaluInstance* class_instance;
	bool visible;
	IVisualAdornment* visual;
	TDrawingHelper* drawing_helper;
	IBaluWorld* world;
	IBaluSceneInstance* scene_instance;
};


TClassSpriteAdornment::~TClassSpriteAdornment()
{
	p->scene_instance->DestroyInstance(p->class_instance);
	p->world->DestroyClass("ClassEditorSpriteAdornment");
	p->world->DestroySprite("ClassEditorAdornment_custom_draw_sprite");
}

void SpriteInstanceAdornmentCustomDraw(void* user_data, NVGcontext* vg, TCustomDrawCommand* params)
{
	auto state = (TSpriteInstanceAdornmentPrivate*)user_data;
	//if (state->visible)
	{
		auto items = state->visual->Render();
		for (auto& v : items)
			v->Render(state->drawing_helper);
	}
}

EngineInterface::IBaluClass* TClassSpriteAdornment::CreateClass(IBaluWorld* world, IBaluScene* scene, TSpriteInstanceAdornmentPrivate* data)
{
	auto adornment_class = world->CreateClass("ClassEditorSpriteAdornment");
	dynamic_cast<IBaluWorldObject*>(adornment_class)->GetProperties()->SetBool("editor_temp_object", true);
	auto adornment_sprite = world->CreateSprite("ClassEditorAdornment_custom_draw_sprite");
	dynamic_cast<IBaluWorldObject*>(adornment_sprite)->GetProperties()->SetBool("editor_temp_object", true);
	//adornment_sprite->GetPolygon()->SetEnable(false);
	//adornment_sprite->GetPolygon()->AddOnCustomDraw(TSpecialCallback<TCustomDrawCallback>(SpriteInstanceAdornmentCustomDraw, &world->GetCallbacksActiveType(), data, TCallbacksActiveType::EDITOR));
	adornment_class->AddSprite(adornment_sprite);

	return adornment_class;
}

TClassSpriteAdornment::TClassSpriteAdornment(IBaluSceneInstance* scene_instance, IVisualAdornment* visual, TDrawingHelper* drawing_helper)
{
	p = std::make_unique<TSpriteInstanceAdornmentPrivate>();

	p->visual = visual;
	p->drawing_helper = drawing_helper;
	p->scene_instance = scene_instance;

	IBaluWorld* world = scene_instance->GetWorld()->GetSource();
	p->world = world;
	IBaluClass* adornment_class;
	if (world->TryFind("ClassEditorSpriteAdornment", adornment_class))
	{
		assert(false);
	}
	adornment_class = CreateClass(world, scene_instance->GetSource(), p.get());

	p->class_instance = scene_instance->CreateInstance(adornment_class, TBaluTransform(TVec2(0, 0), TRot(0)), TVec2(1, 1));
}
