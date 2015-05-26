#pragma once


#include <vector>
#include <memory>

#include "../../EngineInterfaces/IMaterial.h"
#include "../../EngineInterfaces/IScene.h"
#include "../../EngineInterfaces/IMaterialInstance.h"
#include "../../EngineInterfaces/ISceneInstance.h"
#include "../../EngineInterfaces/IWorld.h"

using namespace EngineInterface;

#include "MaterialEditorAdornments.h"

class TDrawingHelper;

class TMaterialEditorScene
{
private:
	std::unique_ptr<TMaterialInstanceAdornment> adornment_instance;

public:
	IBaluMaterial* source_material;
	IBaluSceneInstance* editor_scene_instance;

	IBaluInstance* editor_scene_class_instance; //экземпляр редактируемого материала на сцене редактора

public:
	void Initialize(IBaluWorld* world, IBaluMaterial* source_material, IBaluSceneInstance* source_scene_instance, TDrawingHelper* drawing_helper);
	void Deinitialize();
};