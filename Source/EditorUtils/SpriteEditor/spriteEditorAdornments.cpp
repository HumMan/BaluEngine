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
	friend void SpritePolygonOBBAdornmentCustomDraw(TCallbackData* data, NVGcontext* vg, TCustomDrawCommand* params);
private:
	IBaluInstance* class_instance;
	bool visible;
	IVisualAdornment* visual;
	TDrawingHelper* drawing_helper;
};

TSpriteOBBAdornment::~TSpriteOBBAdornment()
{

}

void SpritePolygonOBBAdornmentCustomDraw(TCallbackData* data, NVGcontext* vg, TCustomDrawCommand* params)
{
	auto state = (TSpritePolygonOBBAdornmentPrivate*)data->GetUserData();
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
	auto adornment_sprite = world->CreateSprite("SpritePolygonOBBAdornment_custom_draw_sprite");
	//adornment_sprite->GetPolygone()->SetEnable(false);
	adornment_sprite->GetPolygone()->OnCustomDraw(CallbackWithData<TCustomDrawCallback>(SpritePolygonOBBAdornmentCustomDraw, &world->GetCallbacksActiveType(), data, TCallbacksActiveType::EDITOR));
	adornment_class->AddSprite(adornment_sprite);

	return adornment_class;
}

TSpriteOBBAdornment::TSpriteOBBAdornment(IBaluSceneInstance* scene_instance, IVisualAdornment* visual, TDrawingHelper* drawing_helper)
{
	p = std::make_unique<TSpritePolygonOBBAdornmentPrivate>();

	p->visual = visual;
	p->drawing_helper = drawing_helper;

	IBaluWorld* world = scene_instance->GetWorld()->GetSource();
	IBaluClass* adornment_class;
	if (!world->TryFind("SceneEditorAdornment", adornment_class))
	{
		adornment_class = CreateClass(world, scene_instance->GetSource(), p.get());
	}

	p->class_instance = scene_instance->CreateInstance(adornment_class, TBaluTransform(TVec2(0, 0), TRot(0)), TVec2(1, 1));
}

class TSpritePolygonAdornmentPrivate
{
	friend class TSpritePolygonAdornment;
	friend void SpritePolygonAdornmentCustomDraw(TCallbackData* data, NVGcontext* vg, TCustomDrawCommand* params);
private:
	IBaluInstance* class_instance;
	bool visible;
	IBaluSprite* visual;
	TDrawingHelper* drawing_helper;
};

TSpritePolygonAdornment::~TSpritePolygonAdornment()
{

}

void SpritePolygonAdornmentCustomDraw(TCallbackData* data, NVGcontext* vg, TCustomDrawCommand* params)
{
	auto state = (TSpritePolygonAdornmentPrivate*)data->GetUserData();
	//if (state->visible)
	{
		//auto items = state->visual->Render();
		//for (auto& v : items)
		//	v->Render(state->drawing_helper);
	}
}

EngineInterface::IBaluClass* TSpritePolygonAdornment::CreateClass(IBaluWorld* world, IBaluScene* scene, TSpritePolygonAdornmentPrivate* data)
{
	auto adornment_class = world->CreateClass("SpritePolygonAdornment");
	auto adornment_sprite = world->CreateSprite("SpritePolygonAdornment_custom_draw_sprite");
	//adornment_sprite->GetPolygone()->SetEnable(false);
	adornment_sprite->GetPolygone()->OnCustomDraw(CallbackWithData<TCustomDrawCallback>(SpritePolygonAdornmentCustomDraw, &world->GetCallbacksActiveType(), data, TCallbacksActiveType::EDITOR));
	adornment_class->AddSprite(adornment_sprite);

	return adornment_class;
}

TSpritePolygonAdornment::TSpritePolygonAdornment(IBaluSceneInstance* scene_instance, IBaluSprite* visual, TDrawingHelper* drawing_helper)
{
	p = std::make_unique<TSpritePolygonAdornmentPrivate>();

	p->visual = visual;
	p->drawing_helper = drawing_helper;

	IBaluWorld* world = scene_instance->GetWorld()->GetSource();
	IBaluClass* adornment_class;
	if (!world->TryFind("SpritePolygonAdornment", adornment_class))
	{
		adornment_class = CreateClass(world, scene_instance->GetSource(), p.get());
	}

	p->class_instance = scene_instance->CreateInstance(adornment_class, TBaluTransform(TVec2(0, 0), TRot(0)), TVec2(1, 1));
}