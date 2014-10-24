#pragma once

class TWorldObjectDef;
class TCallbackManagedBridge;
class TBaluWorldDef;

namespace Editor
{
	using namespace System;
	using namespace System::Diagnostics;
	using namespace System::ComponentModel;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;
	using namespace System::Threading;
	using namespace System::Collections::Generic;
	using namespace System::Runtime::InteropServices;

	public enum class TNodeType
	{
		World,
		Material,
		Sprite,
		PhysBody,
		Class,
		Scene
	};
	public ref class TWolrdTreeNodeTag
	{
	public:
		TWorldObjectDef* world_object;
		TNodeType NodeType;
		bool IsSpecialNode;
		TWolrdTreeNodeTag(TNodeType NodeType)
		{
			IsSpecialNode = true;
			this->NodeType = NodeType;
		}
		TWolrdTreeNodeTag(TNodeType NodeType, TWorldObjectDef* world_object)
		{
			IsSpecialNode = false;
			this->NodeType = NodeType;
			this->world_object = world_object;
		}
	};

	[DesignerAttribute(BaluEditorControlDesigner::typeid)]
	public ref class BaluEditorControl : public System::Windows::Forms::UserControl
	{
	private:
		bool DesignMode;
		bool Activated;

		TCallbackManagedBridge* callbackbridge;

		Void CreateWorldTree(TreeView^ WorldTreeView, TBaluWorldDef* world);

	public:
		//called by balu editor
		void OnSelectionChangedByEditor(TWorldObjectDef* old_selection, TWorldObjectDef* new_selection);
		void OnPropertiesChangedByEditor(TWorldObjectDef* changed_obj);
		void OnObjectCreatedByEditor(TWorldObjectDef* new_object);

		BaluEditorControl();

		virtual Void OnPaint(PaintEventArgs^ e) override;
		virtual Void OnPaintBackground(PaintEventArgs^ e) override;
		virtual Void OnResize(EventArgs^ e) override;
		virtual Void OnKeyDown(KeyEventArgs^ e) override;
		virtual Void OnKeyPress(KeyPressEventArgs^ e) override;
		virtual Void OnKeyUp(KeyEventArgs^ e) override;
		virtual Void OnMouseClick(MouseEventArgs^ e) override;
		virtual Void OnMouseDoubleClick(MouseEventArgs^ e) override;
		virtual Void OnMouseDown(MouseEventArgs^ e) override;
		//virtual Void OnMouseEnter(EventArgs^ e) override;
		virtual Void OnMouseHover(EventArgs^ e) override;
		virtual Void OnMouseLeave(EventArgs^ e) override;
		virtual Void OnMouseMove(MouseEventArgs^ e) override;
		virtual Void OnMouseUp(MouseEventArgs^ e) override;
		virtual Void OnMouseWheel(MouseEventArgs^ e) override;
		virtual Void OnLoad(EventArgs^ e) override;
		virtual Void WndProc(Message% m) override;

		virtual Void Render();

		Void InitializeEngine();

		Void CreateMaterial();
		Void CreateSprite();
		Void CreatePhysBody();
		Void CreateClass();
		Void CreateScene();

		Void SetSelectedWorldNode(TWolrdTreeNodeTag^ node);
		Void SetEditedWorldNode(TWolrdTreeNodeTag^ node);

		bool CanSetSelectedAsWork();
		void SetSelectedAsWork();

		bool CanEndSelectedAsWork();
		void EndSelectedAsWork();

		void SetToolSelectedObject(String^ name);

		property PropertyGrid^ SelectedObjectProperty;
		property TreeView^ WorldTreeView;
		property ToolStrip^ EditorToolsBar;
		property ListBox^ ToolObjectSelect;
	protected:

		~BaluEditorControl();
	};
}
