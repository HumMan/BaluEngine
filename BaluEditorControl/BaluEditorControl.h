#pragma once

class TWorldObjectDef;
class TCallbackManagedBridge;

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

	[DesignerAttribute(BaluEditorControlDesigner::typeid)]
	public ref class BaluEditorControl : public System::Windows::Forms::UserControl
	{
	private:
		bool DesignMode;
		bool Activated;

		TCallbackManagedBridge* callbackbridge;
	public:
		BaluEditorControl();

		void OnSelectionChangedByEditor(TWorldObjectDef* old_selection, TWorldObjectDef* new_selection);

		virtual Void OnPaint(PaintEventArgs^ e) override;
		virtual Void OnPaintBackground(PaintEventArgs^ e) override;
		virtual Void OnResize(EventArgs^ e) override;
		virtual Void OnKeyDown(KeyEventArgs^ e) override;
		virtual Void OnKeyPress(KeyPressEventArgs^ e) override;
		virtual Void OnKeyUp(KeyEventArgs^ e) override;
		virtual Void OnMouseClick(MouseEventArgs^ e) override;
		virtual Void OnMouseDoubleClick(MouseEventArgs^ e) override;
		virtual Void OnMouseDown(MouseEventArgs^ e) override;
		virtual Void OnMouseEnter(EventArgs^ e) override;
		virtual Void OnMouseHover(EventArgs^ e) override;
		virtual Void OnMouseLeave(EventArgs^ e) override;
		virtual Void OnMouseMove(MouseEventArgs^ e) override;
		virtual Void OnMouseUp(MouseEventArgs^ e) override;
		virtual Void OnMouseWheel(MouseEventArgs^ e) override;
		virtual Void OnLoad(EventArgs^ e) override;
		virtual Void WndProc(Message% m) override;

		virtual Void Render();

		property PropertyGrid^ SelectedObjectProperty;
		property TreeView^ WorldTreeView;
	protected:

		~BaluEditorControl();
	};
}
