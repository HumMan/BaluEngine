#pragma once


#include <vector>
#include <memory>

#include <WorldDef/Objects/Material/IMaterial.h>
#include <WorldDef/Objects/Scene/IScene.h>
#include "../IMaterialInstance.h"
#include "../../Scene/ISceneInstance.h"

namespace EngineInterface
{

	class TDrawingHelper;

	class TMaterialEditorScene
	{
	private:

	public:
		IBaluMaterial* source_material;
		IBaluSceneInstance* editor_scene_instance;

		IBaluTransformedClassInstance* editor_scene_class_instance; //экземпляр редактируемого материала на сцене редактора

	public:
		void Initialize(IBaluWorld* world, IBaluMaterial* source_material, IBaluSceneInstance* source_scene_instance, TDrawingHelper* drawing_helper);
		void Deinitialize();
	};
}
