#pragma once

#include "WorldInstance/Interface.h"

#include "../Render/DrawingHelper.h"

namespace BaluEngine
{
	namespace WorldInstance
	{

		class IEditorTool
		{
		public:
			virtual WorldDef::TWorldObjectType NeedObjectSelect() = 0;
			virtual void SetSelectedObject(WorldDef::IWorldObject* obj) = 0;
			virtual void OnMouseDown(WorldDef::TMouseEventArgs e) = 0;
			virtual void OnMouseMove(WorldDef::TMouseEventArgs e) = 0;
			virtual void OnMouseUp(WorldDef::TMouseEventArgs e) = 0;

			virtual void Activate() {}
			virtual void Deactivate() {}

			virtual void CancelOperation() = 0;

			//virtual void Render(TDrawingHelper* drawing_helper) = 0;
			virtual ~IEditorTool() = 0;

			virtual std::vector<std::string> GetAvailableStates() { return std::vector<std::string>(); }
			virtual void SetActiveState(std::string) {}
		};

		inline IEditorTool::~IEditorTool() { }

		class TToolWithDescription
		{
		public:
			std::unique_ptr<IEditorTool> tool;
			std::string name, image, tooltip;
			TToolWithDescription(IEditorTool* tool, std::string name)
			{
				this->tool.reset(tool);
				this->name = name;
			}
			TToolWithDescription(TToolWithDescription&& o)
			{
				tool = std::move(o.tool);
				name = std::move(o.name);
			}
			~TToolWithDescription()
			{}
		};

		class ISelectionChangeListener
		{
		public:
			virtual void OnSelectionChange(WorldDef::IProperties* new_selection) = 0;
		};

		class TSelectionChangeListeners
		{
		private:
			std::vector<ISelectionChangeListener*> selection_listeners;
		public:
			void AddSelectionChangeListener(ISelectionChangeListener* listener);
			void RemoveSelectionChangeListener(ISelectionChangeListener* listener);

			void EmitOnSelectionChange(WorldDef::IProperties* new_selection);
		};


		class IEditorSelectionChangedListener
		{
		public:
			void SelectionChanged(WorldDef::IProperties* old_selection, WorldDef::IProperties* new_selection);
		};


		class IAbstractEditor
		{
		public:
			//IEditorSelectionChangedListener* OnSelectionChanged;

			virtual bool CanSetSelectedAsWork() = 0;
			virtual void SetSelectedAsWork() = 0;

			virtual bool CanEndSelectedAsWork() = 0;
			virtual bool EndSelectedAsWork() = 0;
			virtual WorldInstance::IScene* GetEditorSceneInstance() = 0;
			//std::map<std::string, TAbstractEditorObject*> CanCreateObjects();

			virtual const std::vector<TToolWithDescription>& GetAvailableTools() = 0;
			virtual void SetActiveTool(IEditorTool* tool) = 0;
			virtual IEditorTool* GetActiveTool() = 0;
			virtual ~IAbstractEditor() = 0;
		};
		inline IAbstractEditor::~IAbstractEditor() { }

		BALUENGINEDLL_API IAbstractEditor* CreateEditor(WorldDef::IWorldObject*,
			WorldInstance::TDrawingHelperContext drawing_context, WorldInstance::IWorld* world_instance);
		BALUENGINEDLL_API void DestroyEditor(IAbstractEditor*);

		BALUENGINEDLL_API void ConfigureLogging();
		BALUENGINEDLL_API void WriteInfoToLog(char* message);

		BALUENGINEDLL_API std::wstring as_wide(std::string utf_8_string);
		BALUENGINEDLL_API std::string as_utf8(std::wstring wide_string);
	}
}

