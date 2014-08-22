#pragma once

namespace Editor
{
	using namespace System;
	using namespace System::Drawing;
	using namespace System::Windows::Forms;
	using namespace System::Windows::Forms::Design;

	public ref class BaluEditorControlDesigner : ControlDesigner
	{
	protected:
		virtual Void OnPaintAdornments(PaintEventArgs^ e) override
		{
			Pen^ SimplePen = gcnew Pen(Color::Black, 1);
			e->Graphics->DrawLine(SimplePen, 0, 0, Control->Width - 1, Control->Height - 1);
			e->Graphics->DrawLine(SimplePen, Control->Width - 1, 0, 0, Control->Height - 1);

			Font^ TitleFont = gcnew Font(L"Microsoft Sans Serif", 10, FontStyle::Bold, GraphicsUnit::Point);
			String^ TitleText = L"BaluEditor";
			SizeF TitleSize = e->Graphics->MeasureString(TitleText, TitleFont);
			PointF TitlePosition = PointF(Control->Width / 2.0F - TitleSize.Width / 2.0F, Control->Height / 2.0F - TitleSize.Height / 2.0F);
			e->Graphics->FillRectangle(gcnew SolidBrush(Control->BackColor), TitlePosition.X - 1.0F, TitlePosition.Y - 1.0F, TitleSize.Width + 1.0F, TitleSize.Height + 1.0F);
			e->Graphics->DrawString(TitleText, TitleFont, gcnew SolidBrush(Color::Black), TitlePosition);

			e->Graphics->DrawRectangle(SimplePen, 0, 0, Control->Width - 1, Control->Height - 1);
		}
	};
}