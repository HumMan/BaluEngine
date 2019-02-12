#pragma once

#include "../../abstractEditor.h"

#include "../../../WorldDef/Internal/EditorGUI/BoxGui.h"
#include "../../../WorldDef/Internal/EditorGUI/OBBGui.h"
#include "../../../WorldDef/Internal/EditorGUI/PolygonGui.h"
#include "../../../WorldDef/Internal/EditorGUI/SpriteGui.h"

namespace BaluEngine
{
	namespace WorldInstance
	{
		namespace Internal
		{
			class TSceneEditorScene
			{
			public:
				WorldDef::IScene* source_scene;

				WorldInstance::IScene* editor_scene_instance;
				WorldDef::ISceneObject* selected;

				TDrawingHelper* drawing_helper;

				//tools controls
				WorldDef::Internal::TEditableOBBGui* boundary_box;
				WorldDef::Internal::TBoxGui* boundary_box_contour;

				WorldDef::ISceneObject* hightlighted_instance;

				TSelectionChangeListeners* selection_listeners;

				void Initialize(WorldDef::IWorld* world, WorldDef::IScene* source_scene,
					TDrawingHelper* drawing_helper, TSelectionChangeListeners* selection_listeners);
				void Deinitialize();
			};
		}
	}
}
