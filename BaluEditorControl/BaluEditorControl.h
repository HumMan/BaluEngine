#pragma once

class TCallbackManagedBridge;

namespace EngineInterface
{
	class IBaluWorldObject;
	class IBaluWorld;
	class IAbstractEditor;
}

class BaluEditorControlPrivate;
class BaluEditorOpenglWindowPrivate;

namespace Editor
{
	using namespace System;
	using namespace System::Diagnostics;
	using namespace System::Windows::Forms;
	using namespace System::ComponentModel;
	using namespace System::Threading;
	using namespace System::Collections::Generic;
	using namespace System::Runtime::InteropServices;

	using namespace EngineInterface;

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
		IAbstractEditor* BaluEditorControl::CreateEditorOfWorldObject(IBaluWorldObject* obj);
	public:
		//called by balu editor
		void OnSelectionChangedByEditor(IBaluWorldObject* old_selection, IBaluWorldObject* new_selection);
		void OnPropertiesChangedByEditor(IBaluWorldObject* changed_obj);
		void OnObjectCreatedByEditor(IBaluWorldObject* new_object);

		//BaluEditorControl();
		BaluEditorControl(IntPtr handle);
		void BeginFrame();
		void EndFrame();

		virtual Void Resize(int width, int height) override;

		virtual Void MouseDown(MouseEventArgs^ e) override;
		virtual Void MouseMove(MouseEventArgs^ e) override;
		virtual Void MouseUp(MouseEventArgs^ e) override;
		virtual Void MouseWheel(MouseEventArgs^ e) override;

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

		!BaluEditorControl();
	};

	//public ref class BaluEditorOpenglWindow
	//{
	//private:

	//	BaluEditorOpenglWindowPrivate* p;
	//public:
	//	BaluEditorOpenglWindow(IntPtr handle);
	//	void BeginFrame();
	//	void EndFrame();
	//};
}
