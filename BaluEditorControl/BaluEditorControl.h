#pragma once

class TCallbackManagedBridge;

namespace EngineInterface
{
	class IBaluWorldObject;
	class IBaluWorld;
}

class BaluEditorControlPrivate;

namespace Editor
{
	using namespace System;
	using namespace System::Diagnostics;
	using namespace System::Windows::Forms;
	using namespace System::ComponentModel;
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
		IBaluWorldObject* world_object;
		TNodeType NodeType;
		bool IsSpecialNode;
		TWolrdTreeNodeTag(TNodeType NodeType)
		{
			IsSpecialNode = true;
			this->NodeType = NodeType;
		}
		TWolrdTreeNodeTag(TNodeType NodeType, IBaluWorldObject* world_object)
		{
			IsSpecialNode = false;
			this->NodeType = NodeType;
			this->world_object = world_object;
		}
	};

	public ref class BaluEditorControl
	{
	private:

		BaluEditorControlPrivate* p;

		Void CreateWorldTree(TreeView^ WorldTreeView, EngineInterface::IBaluWorld* world);

	public:
		//called by balu editor
		void OnSelectionChangedByEditor(IBaluWorldObject* old_selection, IBaluWorldObject* new_selection);
		void OnPropertiesChangedByEditor(IBaluWorldObject* changed_obj);
		void OnObjectCreatedByEditor(IBaluWorldObject* new_object);

		BaluEditorControl();

		virtual Void OnResize(EventArgs^ e) override;
		virtual Void OnKeyDown(KeyEventArgs^ e) override;
		virtual Void OnKeyPress(KeyPressEventArgs^ e) override;
		virtual Void OnKeyUp(KeyEventArgs^ e) override;
		virtual Void OnMouseClick(MouseEventArgs^ e) override;
		virtual Void OnMouseDoubleClick(MouseEventArgs^ e) override;
		virtual Void OnMouseDown(MouseEventArgs^ e) override;
		virtual Void OnMouseMove(MouseEventArgs^ e) override;
		virtual Void OnMouseUp(MouseEventArgs^ e) override;
		virtual Void OnMouseWheel(MouseEventArgs^ e) override;

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

		void SetToolSelectedObject(System::String^ name);

		void SaveWorldTo(System::String^ path);
		void LoadWorldFrom(System::String^ path);

		property PropertyGrid^ SelectedObjectProperty;
		property TreeView^ WorldTreeView;
		property ToolStrip^ EditorToolsBar;
		property ListBox^ ToolObjectSelect;
	protected:

		~BaluEditorControl();
	};
}
