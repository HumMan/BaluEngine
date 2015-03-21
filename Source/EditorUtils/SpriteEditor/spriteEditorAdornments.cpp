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
	IBaluWorld* world;
	IBaluSceneInstance* scene_instance;
};

TSpriteOBBAdornment::~TSpriteOBBAdornment()
{
	p->scene_instance->DestroyInstance(p->class_instance);
	p->world->DestroyClass("SpritePolygonOBBAdornment");
	p->world->DestroySprite("SpritePolygonOBBAdornment_custom_draw_sprite");
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
	dynamic_cast<IBaluWorldObject*>(adornment_class)->GetProperties()->SetBool("editor_temp_object", true);
	auto adornment_sprite = world->CreateSprite("SpritePolygonOBBAdornment_custom_draw_sprite");
	dynamic_cast<IBaluWorldObject*>(adornment_sprite)->GetProperties()->SetBool("editor_temp_object", true);
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
	friend void SpritePolygonAdornmentCustomDraw(TCallbackData* data, NVGcontext* vg, TCustomDrawCommand* params);
private:
	IBaluInstance* class_instance;
	bool visible;
	IBaluSprite* visual;
	TDrawingHelper* drawing_helper;
	IBaluWorld* world;
	IBaluSceneInstance* scene_instance;
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

void SpritePolygonAdornmentCustomDraw(TCallbackData* data, NVGcontext* vg, TCustomDrawCommand* params)
{
	auto state = (TSpritePolygonAdornmentPrivate*)data->GetUserData();
	if (state->visible)
	{
		auto sprite_poly = state->visual->GetPolygone();
		auto vertices = sprite_poly->GetPolygon();
		state->drawing_helper->RenderLinesLoop(vertices, sprite_poly->GetTransform(), sprite_poly->GetScale());
		for (auto& v : vertices)
			state->drawing_helper->RenderPointAdornment(v, sprite_poly->GetTransform(), sprite_poly->GetScale());
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
	friend void SpritePolygonAdornmentCustomDraw(TCallbackData* data, NVGcontext* vg, TCustomDrawCommand* params);
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