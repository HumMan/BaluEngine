#pragma once

#include <vector>

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

	using namespace EngineInterface;

	public enum class TNodeType
	{
		World,
		Material,
		Sprite,
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

	class TEventsEditorPrivate;

	public ref class TEventsEditor
	{
	internal:
		TEventsEditorPrivate* p;
		TEventsEditor(IBaluWorld* world, const char* assets_dir);
		void FindAllEvents();
		void Clear();
	public:
		bool TEventsEditor::CompileScripts(array<String^>^% errors_list);
		void Initialize();
		!TEventsEditor();
		array<String^>^ GetEventsList(int event_type);
		int GetEventsCount(int event_type);
		array<TNodeType>^ GetEventParameters(int event_type, int event_id);
		array<String^>^ GetObjectsList(TNodeType object_type);
		void SetEventParameter(int event_type, int event_id, String^ object_name);
		String^ GetEventScript(int event_type, int event_id);
		void SetEventScript(int event_type, int event_id, String^ script);

		int GetEventTypesCount();
		String^ GetEventTypeName(int event_type);
		int EventTypeFromName(String^ name);
	};

	public ref class BaluEditorControl
	{
	private:

		BaluEditorControlPrivate* p;

		void CreateWorldTree(TreeView^ WorldTreeView, EngineInterface::IBaluWorld* world);
		IAbstractEditor* CreateEditorOfWorldObject(IBaluWorldObject* obj);
		void DestroyEditorOfWorldObject(IBaluWorldObject* obj);
		void CreateEditorScene();
		void DestroyEditorScene();
	public:
		String^ GetAssetsDir();

		bool ToolNeedObjectSelect(std::vector<IBaluWorldObject*>& selection_list);

		//called by balu editor
		void OnSelectionChangedByEditor(IBaluWorldObject* old_selection, IBaluWorldObject* new_selection);
		void OnPropertiesChangedByEditor(IBaluWorldObject* changed_obj);
		void OnObjectCreatedByEditor(IBaluWorldObject* new_object);

		//BaluEditorControl();
		BaluEditorControl(IntPtr handle, String^ assets_dir);

		void Destroy();
		void BeginFrame();
		void EndFrame();

		virtual void Resize(int width, int height) override;
		void SetViewport(int width, int height);

		virtual void MouseDown(MouseEventArgs^ e) override;
		virtual void MouseMove(MouseEventArgs^ e) override;
		virtual void MouseUp(MouseEventArgs^ e) override;
		virtual void MouseWheel(MouseEventArgs^ e) override;

		virtual void Render();

		void InitializeEngine();

		TEventsEditor^ GetEventsEditor();

		void CreateMaterial();
		void CreateSprite();
		void CreateClass();
		void CreateScene();

		void SetSelectedWorldNode(TWolrdTreeNodeTag^ node);
		void SetEditedWorldNode(TWolrdTreeNodeTag^ node);

		bool CanSetSelectedAsWork();
		void SetSelectedAsWork();

		bool CanEndSelectedAsWork();
		void EndSelectedAsWork();

		void SetToolSelectedObject(String^ name);

		void SaveWorldTo(String^ path);
		void LoadWorldFrom(String^ path);
		void LoadDemoWorld();

		property PropertyGrid^ SelectedObjectProperty;
		property TreeView^ WorldTreeView;
		property ToolStrip^ EditorToolsBar;
		property ToolStrip^ ToolStateToolsBar;
		property ListBox^ ToolObjectSelect;

		!BaluEditorControl();

	protected:

		
	};
}
