#pragma once
namespace Editor
{
	//---------------------------------------------------------
	using namespace System;
	using namespace System::Diagnostics;
	using namespace System::ComponentModel;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;
	using namespace System::Threading;
	using namespace System::Collections::Generic;
	using namespace System::Runtime::InteropServices;
	//---------------------------------------------------------

	[DesignerAttribute(BaluEditorControlDesigner::typeid)]
	public ref class BaluEditorControl : public System::Windows::Forms::UserControl
	{
	private:
		

	public:
		// constructor
		BaluEditorControl();
		virtual Void OnResize(EventArgs^ e) override;
		virtual Void Render();
	protected:
		// destructor
		~BaluEditorControl();
	};
}
