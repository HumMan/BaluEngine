#include "materialEditorAdornments.h"

#include "../../EngineInterfaces/IMaterial.h"
#include "../../EngineInterfaces/IWorld.h"

#include "../../EngineInterfaces/IMaterialInstance.h"
#include "../../EngineInterfaces/IWorldInstance.h"

using namespace EngineInterface;

#include "../DrawingHelper.h"


class TMaterialInstanceAdornmentPrivate
{
	friend class TMaterialInstanceAdornment;
private:
	IBaluInstance* class_instance;
	IBaluWorld* world;
	IBaluSceneInstance* scene_instance;
};

TMaterialInstanceAdornment::TMaterialInstanceAdornment(EngineInterface::IBaluWorld* world, EngineInterface::IBaluSceneInstance* scene_instance, EngineInterface::IBaluMaterial* material)
{
	p = std::make_unique<TMaterialInstanceAdornmentPrivate>();

	p->scene_instance = scene_instance;

	p->world = world;
	IBaluClass* adornment_class;
	if (world->TryFind("MaterialEditorAdornmentClass", adornment_class))
	{
		assert(false);
	}

	adornment_class = world->CreateClass("MaterialEditorAdornmentClass");
	dynamic_cast<IBaluWorldObject*>(adornment_class)->GetProperties()->SetBool("editor_temp_object", true);
	auto adornment_sprite = world->CreateSprite("MaterialEditorAdornmentSprite");
	dynamic_cast<IBaluWorldObject*>(adornment_sprite)->GetProperties()->SetBool("editor_temp_object", true);
	adornment_sprite->GetPolygon()->SetMaterial(material);
	adornment_sprite->GetPolygon()->SetAsBox(1, 1);
	adornment_sprite->GetPolygon()->SetTexCoordsFromVertices(TVec2(-0.5, -0.5), TVec2(1, 1));
	adornment_class->AddSprite(adornment_sprite);

	p->class_instance = scene_instance->CreateInstance(adornment_class, TBaluTransform(TVec2(0, 0), TRot(0)), TVec2(1, 1));
}

TMaterialInstanceAdornment::~TMaterialInstanceAdornment()
{
	p->scene_instance->DestroyInstance(p->class_instance);
	p->world->DestroyClass("MaterialEditorAdornmentClass");
	p->world->DestroySprite("MaterialEditorAdornmentSprite");
}