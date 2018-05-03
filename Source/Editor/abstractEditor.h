#pragma once

#include "IAbstractEditor.h"

namespace BaluEngine
{
	namespace WorldInstance
	{
		namespace Internal
		{
			class TAbstractEditor :
				public IAbstractEditor,
				public IMouseEventListener,
				public TSelectionChangeListeners
			{
			private:
				WorldInstance::IWorld* world_instance;

			protected:
				std::vector<TAbstractEditor*> parent_editors;
				TAbstractEditor* current_local_editor;
				IEditorTool* active_tool;
				BaluLib::TVec2 editor_global_pos;

				void OnMouseMove(WorldDef::TMouseEventArgs e);
				void OnMouseDown(WorldDef::TMouseEventArgs e);
				void OnMouseUp(WorldDef::TMouseEventArgs e);

			public:

				TAbstractEditor(WorldInstance::IWorld* world_instance);
				virtual ~TAbstractEditor();

				virtual void SetActiveTool(IEditorTool* tool);
				IEditorTool* GetActiveTool()
				{
					return active_tool;
				}
			};
		}
	}
}


