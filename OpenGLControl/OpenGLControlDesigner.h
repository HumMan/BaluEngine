// Copyright (C) <2012> <Mgr. Zoltan Tirinda - zolver.blogspot.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software 
// and associated documentation files (the "Software"), to deal in the Software without restriction, 
// including without limitation the rights to use, copy, modify, merge, publish, distribute copies 
// of the Software, and to permit persons to whom the Software is furnished to do so, subject to 
// the following conditions:
//
// The above copyright notice with the original author and this permission notice shall be included 
// in all copies or substantial portions of the Software.
//
// You agree not to advertise or in any way imply that this Work is a product of Your own
//
// The name of the Author may not be used to endorse or promote products derived from the Work without 
// the prior written consent of the Author.
// 
// You agree not to sell, lease, or rent any part of the Work. This does not restrict you from including 
// the Work or any part of the Work inside a larger software distribution that itself is being sold. The 
// Work by itself, though, cannot be sold, leased or rented. 
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING 
// BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


#pragma once


namespace Zolver
{
	//----------------------------------------------------
	using namespace System;
	using namespace System::Drawing;
	using namespace System::Windows::Forms;
	using namespace System::Windows::Forms::Design;
	//----------------------------------------------------


	public ref class OpenGLControlDesigner : ControlDesigner
	{
	protected:
		// methods
		virtual Void OnPaintAdornments(PaintEventArgs^ e) override
		{
			// draw the cross
			Pen^ SimplePen = gcnew Pen(Color::Black, 1);
			e->Graphics->DrawLine(SimplePen, 0, 0, Control->Width-1, Control->Height-1);
			e->Graphics->DrawLine(SimplePen, Control->Width-1, 0, 0, Control->Height-1);
		
			// draw the title text
			Font^ TitleFont = gcnew Font(L"Microsoft Sans Serif", 10, FontStyle::Bold, GraphicsUnit::Point);
			String^ TitleText = L"OpenGL";
			SizeF TitleSize = e->Graphics->MeasureString(TitleText, TitleFont);
			PointF TitlePosition = PointF(Control->Width/2.0F - TitleSize.Width/2.0F, Control->Height/2.0F - TitleSize.Height/2.0F);
			e->Graphics->FillRectangle(gcnew SolidBrush(Control->BackColor), TitlePosition.X-1.0F, TitlePosition.Y-1.0F, TitleSize.Width+1.0F, TitleSize.Height+1.0F);
			e->Graphics->DrawString(TitleText, TitleFont, gcnew SolidBrush(Color::Black), TitlePosition);

			// draw the link text
			Font^ TextFont = gcnew Font(L"Microsoft Sans Serif", 8.25, FontStyle::Regular, GraphicsUnit::Point);
			String^ LinkText = L"zolver.blogspot.com";
			SizeF LinkSize = e->Graphics->MeasureString(LinkText, TextFont);
			PointF LinkPosition = PointF(Control->Width - LinkSize.Width - 5.0F, Control->Height - LinkSize.Height - 5.0F);
			e->Graphics->FillRectangle(gcnew SolidBrush(Control->BackColor),LinkPosition.X-1.0F, LinkPosition.Y-1.0F, LinkSize.Width+1.0F, LinkSize.Height+1.0F);
			e->Graphics->DrawString(LinkText, TextFont, gcnew SolidBrush(Color::Black), LinkPosition);

			// draw the author text		
			String^ AutorText = L"Zoltan Tirinda";
			SizeF AutorSize = e->Graphics->MeasureString(AutorText, TextFont);
			PointF AutorPosition = PointF(Control->Width - AutorSize.Width - 8.0F, LinkPosition.Y - AutorSize.Height);
			e->Graphics->FillRectangle(gcnew SolidBrush(Control->BackColor), AutorPosition.X-1.0F, AutorPosition.Y-1.0F, AutorSize.Width+1.0F, AutorSize.Height+1.0F);
			e->Graphics->DrawString(AutorText, TextFont, gcnew SolidBrush(Color::Black), AutorPosition);

			// draw the rectangle
			e->Graphics->DrawRectangle(SimplePen, 0, 0, Control->Width-1, Control->Height-1);
		}
	};
}