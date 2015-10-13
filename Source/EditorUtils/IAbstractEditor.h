#pragma once

#if !defined(BALU_ENGINE_SCRIPT_CLASSES)  && !defined(BALU_ENGINE_DISABLE_PRAGMA_ONCE)
#include <Interfaces\ExportMacro.h>

#include <World\ICommon.h>
#include <World\IWorld.h>
#include <World\IWorldInstance.h>

#include <memory>
#include <vector>
#endif

namespace EngineInterface
{
	
	class IEditorTool
	{
	public:
		virtual TWorldObjectType NeedObjectSelect() = 0;
		virtual void SetSelectedObject(IBaluWorldObject* obj) = 0;
		virtual void OnMouseDown(TMouseEventArgs e) = 0;
		virtual void OnMouseMove(TMouseEventArgs e) = 0;
		virtual void OnMouseUp(TMouseEventArgs e) = 0;

		virtual void Activate(){}
		virtual void Deactivate(){}

		virtual void CancelOperation() = 0;

		//virtual void Render(TDrawingHelper* drawing_helper) = 0;
		virtual ~IEditorTool() = 0;

		virtual std::vector<std::string> GetAvailableStates(){ return std::vector<std::string>(); }
		virtual void SetActiveState(std::string){}
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
		virtual void OnSelectionChange(IProperties* new_selection) = 0;
	};

	class BALUENGINEDLL_API TSelectionChangeListeners
	{
	private:
		std::vector<ISelectionChangeListener*> selection_listeners;
	public:
		void AddSelectionChangeListener(ISelectionChangeListener* listener);
		void RemoveSelectionChangeListener(ISelectionChangeListener* listener);

		void EmitOnSelectionChange(IProperties* new_selection);
	};


	class IEditorSelectionChangedListener
	{
	public:
		void SelectionChanged(IProperties* old_selection, IProperties* new_selection);
	};
	

	class IAbstractEditor
	{
	public:
		//IEditorSelectionChangedListener* OnSelectionChanged;

		virtual bool CanSetSelectedAsWork() = 0;
		virtual void SetSelectedAsWork() = 0;

		virtual bool CanEndSelectedAsWork() = 0;
		virtual bool EndSelectedAsWork() = 0;
		virtual IBaluSceneInstance* GetEditorSceneInstance() = 0;
		//std::map<std::string, TAbstractEditorObject*> CanCreateObjects();

		virtual const std::vector<TToolWithDescription>& GetAvailableTools() = 0;
		virtual void SetActiveTool(IEditorTool* tool)=0;
		virtual IEditorTool* GetActiveTool() =0;
		virtual ~IAbstractEditor() = 0;
	};
	inline IAbstractEditor::~IAbstractEditor() { }

	BALUENGINEDLL_API void DestroyEditor(IAbstractEditor*);

	BALUENGINEDLL_API void ConfigureLogging();
	BALUENGINEDLL_API void WriteInfoToLog(char* message);

	BALUENGINEDLL_API std::wstring as_wide(std::string utf_8_string);
	BALUENGINEDLL_API std::string as_utf8(std::wstring wide_string);
}

