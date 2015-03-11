#pragma once

#include "exportMacro.h"

#include "EngineInterfaces\IWorld.h"
#include "EngineInterfaces\IWorldInstance.h"

#include <memory>
#include <vector>

enum class TWorldObjectType
{
	Material,
	Sprite,
	PhysBody,
	Class,
	None
};

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

		virtual void CancelOperation() = 0;

		//virtual void Render(TDrawingHelper* drawing_helper) = 0;
		virtual ~IEditorTool() = 0;
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


	class IEditorSelectionChangedListener
	{
	public:
		void SelectionChanged(IProperties* old_selection, IProperties* new_selection);
	};
	

	class IAbstractEditor
	{
	public:
		IEditorSelectionChangedListener* OnSelectionChanged;

		virtual bool CanSetSelectedAsWork() = 0;
		virtual void SetSelectedAsWork() = 0;

		virtual bool CanEndSelectedAsWork() = 0;
		virtual bool EndSelectedAsWork() = 0;

		//std::map<std::string, TAbstractEditorObject*> CanCreateObjects();

		virtual const std::vector<TToolWithDescription>& GetAvailableTools() = 0;
		virtual void SetActiveTool(IEditorTool* tool)=0;
		virtual IEditorTool* GetActiveTool() =0;
		virtual ~IAbstractEditor() = 0;
	};
	inline IAbstractEditor::~IAbstractEditor() { }
}

BALUENGINEDLL_API EngineInterface::IAbstractEditor* CreateSceneEditor(TDrawingHelperContext drawing_context, EngineInterface::IBaluWorld* world, EngineInterface::IBaluScene* edited_scene, EngineInterface::IBaluSceneInstance* editor_scene_instance);
BALUENGINEDLL_API void DestroySceneEditor(EngineInterface::IAbstractEditor*);

BALUENGINEDLL_API EngineInterface::IAbstractEditor* CreateSpriteEditor(TDrawingHelperContext drawing_context, EngineInterface::IBaluWorld* world, EngineInterface::IBaluSprite* edited_sprite, EngineInterface::IBaluSceneInstance* editor_scene_instance);
BALUENGINEDLL_API void DestroySpriteEditor(EngineInterface::IAbstractEditor*);