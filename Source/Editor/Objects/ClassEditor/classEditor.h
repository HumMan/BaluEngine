#pragma once

#include "../../IAbstractEditor.h"

#include "classEditorScene.h"
#include "classEditorTools.h"

namespace BaluEngine
{
	namespace WorldInstance
	{
		namespace Internal
		{
			class TClassEditor :public TAbstractEditor
			{

				TClassEditorScene scene;
				TClassEditorToolsRegistry tools_registry;
				std::unique_ptr<TDrawingHelper> drawing_helper;
			public:
				TClassEditor(TDrawingHelperContext drawing_context, WorldDef::IWorld* world, WorldDef::IClass* edited_class, WorldInstance::IWorld* world_instance);
				~TClassEditor();

				bool CanSetSelectedAsWork();
				void SetSelectedAsWork();

				bool CanEndSelectedAsWork();
				bool EndSelectedAsWork();
				WorldInstance::IScene* GetEditorSceneInstance();
				const std::vector<TToolWithDescription>& GetAvailableTools();
			};
		}
	}
}
