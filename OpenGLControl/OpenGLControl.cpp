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


#include "stdafx.h"


namespace Zolver
{
	OpenGLControl::OpenGLControl() : UserControl()
	{
		// initialize
		Activated = false;
		PreciseTiming = false;
		ActionQueue = gcnew Queue<Tuple<Delegate^,array<Object^>^>^>();
		ActionQueueLock = gcnew Object();
		DoActionsLock = gcnew Object();
		AverageFrameRateBase = 1;
		AverageFrameRate = 0.0F;
		RenderingTimes = gcnew Queue<Int64>();
		RenderingWatch = gcnew Stopwatch();
		MaxFrameRate = 60.0F;
		AutomaticSwapBuffer = true;
		SetStyle(ControlStyles::ResizeRedraw, true);

		if (!DesignMode)
			RenderStyle = ERenderStyle::Auto;

		// Activate the OpenGL rendering just in runtime (not in design time)
		if (DesignMode || LicenseManager::UsageMode!=LicenseUsageMode::Runtime)
			return;

		CreateThread();
	}



	OpenGLControl::~OpenGLControl()
	{
		TerminateThread();	
	}



	Void OpenGLControl::CreateThread()	
	{
		// the OpenGL operations are done on different thread to avoid UI lagging
		Terminated = gcnew ManualResetEvent(false);
		WaitLock = gcnew ManualResetEvent(false);
		ActionThread = gcnew Thread(gcnew ParameterizedThreadStart(this, &OpenGLControl::ActionThread_Execute));
		ActionThread->Priority = Threading::ThreadPriority::AboveNormal;
	}



	Void OpenGLControl::StartThread()
	{
		// do not start the ActionThread in the constructor, 
		// because in some rare cases the OpenGLInit event will be
		// triggered before the user binds to this event
		if (ActionThread)
			ActionThread->Start(Handle);
	}



	Void OpenGLControl::TerminateThread()
	{
		// activate the Terminated ResetEvent to indicate we want to finish the RenderingThread
		if (Terminated)
			Terminated->Set();

		WaitLock->Set();

		// wait until the thread finishes
		if (ActionThread)
			ActionThread->Join();
	}



	Void OpenGLControl::ActivateOpenGLRendering(IntPtr WindowHandle)
	{
		ErrorMessage = "";
		hdc = NULL;
		hrc = NULL;
		HWND hwnd = NULL;	// control handle
		GLuint PixelFormat;	// pixel format of the drawing surface
		
		static PIXELFORMATDESCRIPTOR pfd =				
		{
			sizeof(PIXELFORMATDESCRIPTOR),				
			1,											// Version number should be 1
			PFD_DRAW_TO_WINDOW |
			PFD_SUPPORT_OPENGL |
			PFD_DOUBLEBUFFER,
			PFD_TYPE_RGBA,								// PixelType
			32,											// ColorDepth
			0, 0, 0, 0, 0, 0,							// Color bits ignored 
			0,											// No alpha buffer  
			0,											// Shift bit ignored  
			0,											// No accumulation buffer 
			0, 0, 0, 0,									// Accum bits ignored  
			16,											// DepthBits
			0,											// StencilBits
			0,											// AuxBuffer
			0,											// LayerType Ignored
			0,											// Reserved
			0, 0, 0										// LayerMasks
		};

		// handle to the actual user control
		hwnd = (HWND)WindowHandle.ToPointer();

		// get the Device Context associated to the hwnd
		if (!(hdc=GetDC(hwnd)))
		{
			DeactivateOpenGLRendering(WindowHandle);
			ErrorMessage = "The GL Device Context was not created!";
			return;
		}

		// choose the nearest PixelFormat
		if (!(PixelFormat=ChoosePixelFormat(hdc, &pfd)))
		{
			DeactivateOpenGLRendering(WindowHandle);
			ErrorMessage = "Can't Find A Suitable PixelFormat!";
			return;
		}

		if (!SetPixelFormat(hdc, PixelFormat, &pfd))		
		{
			DeactivateOpenGLRendering(WindowHandle);	
			ErrorMessage = "Can't Set The PixelFormat!";
			return;						
		}

		// we need to create the rendering context for the actual UserControl
		if (!(hrc=wglCreateContext(hdc)))
		{
			DeactivateOpenGLRendering(WindowHandle);
			ErrorMessage = "The GL Rendering Context was not created!";
			return;			
		}

		// we need to make the Device and also the RenderingContext current for the actual thread
		// this action is done just once, because each OpenGL component has its own rendering thread
		if (!wglMakeCurrent(hdc, hrc))
		{
			DeactivateOpenGLRendering(WindowHandle);
			ErrorMessage = "The GL Rendering Context Can't be Activated!";
			return;
		}

		Activated = true;
	}



	Void OpenGLControl::DeactivateOpenGLRendering(IntPtr WindowHandle)
	{
		Activated = false;

		if (hrc)
		{
			// reset the current context
			wglMakeCurrent(NULL, NULL);

			// release the rendering context
			wglDeleteContext(hrc);
		}

		if (hdc)
		{
			// release the device context
			ReleaseDC((HWND)WindowHandle.ToPointer(), hdc);		
		}
	}



	Void OpenGLControl::Refresh()
	{
		// we need to "deactivate" the Refresh method to avoid painting collisions
		if (DesignMode || !Activated)
		{
			__super::Refresh();
			return;
		}

		if (!DesignMode && RenderStyle==ERenderStyle::SystemRender)
			EnqueueAction(gcnew EventHandler(this, &OpenGLControl::OnOpenGLRender), this, EventArgs::Empty);
	}



	Void OpenGLControl::OnPaint(PaintEventArgs^ e)
	{
		// we need to "deactivate" this method to avoid painting collisions
		if (DesignMode || !Activated)
		{
			__super::OnPaint(e);

			Pen^ SimplePen = gcnew Pen(ForeColor, 1);
			e->Graphics->DrawLine(SimplePen, 0, 0, Width-1, Height-1);
			e->Graphics->DrawLine(SimplePen, Width-1, 0, 0, Height-1);			
			e->Graphics->DrawRectangle(SimplePen, 0, 0, Width-1, Height-1);

			SizeF s = e->Graphics->MeasureString(ErrorMessage, Font);
			PointF p = PointF(Width/2.0F - s.Width/2.0F, Height/2.0F - s.Height/2.0F);
			e->Graphics->FillRectangle(gcnew SolidBrush(BackColor), p.X-1.0F, p.Y-1.0F, s.Width+1.0F, s.Height+1.0F);
			e->Graphics->DrawString(ErrorMessage, Font, gcnew SolidBrush(ForeColor), p);
			return;
		}

		// render when the system requested a repaint
		if (!DesignMode && RenderStyle==ERenderStyle::SystemRender)
			EnqueueAction(gcnew EventHandler(this, &OpenGLControl::OnOpenGLRender), this, EventArgs::Empty);
	}



	Void OpenGLControl::OnPaintBackground(PaintEventArgs^ e)
	{
		// we need to "deactivate" this method to avoid painting collisions
		if (DesignMode || !Activated)
			__super::OnPaintBackground(e);
	}



	Void OpenGLControl::ActionThread_Execute(Object^ WindowHandle)
	{
		// as the first step we need to activate the OpenGL rendering
		ActivateOpenGLRendering((IntPtr)WindowHandle);

		// if the activation was not successful then the next actions are pointless
		if (!Activated)
			return;	

		// first of all trigger the initialize event
		EnqueueAction(gcnew EventHandler(this, &OpenGLControl::OnOpenGLInit), this, EventArgs::Empty);

		// do until the termination was not requested
		while (!Terminated->WaitOne(0))
		{
			// render if necessary
			if (RenderStyle==ERenderStyle::Auto)
				EnqueueAction(gcnew EventHandler(this, &OpenGLControl::OnOpenGLRender), this, EventArgs::Empty);

			DoActions();

			// wait for the new events
			if (RenderStyle!=ERenderStyle::Auto)
				WaitLock->WaitOne();
		}

		// at the end of the thread it is necessary to deactivate the OpenGL rendering
		DeactivateOpenGLRendering((IntPtr)WindowHandle);
	}



	Void OpenGLControl::Render()
	{
		if (!Activated || RenderStyle==ERenderStyle::Auto)
			return;

		EnqueueAction(gcnew EventHandler(this, &OpenGLControl::OnOpenGLRender), this, EventArgs::Empty);
	}



	Void OpenGLControl::EnqueueAction(Delegate^ AsyncAction, ... array<Object^>^ Args)
	{
		// avoid cross thread collisions
		Monitor::Enter(ActionQueueLock);
		try 
		{
			Tuple<Delegate^, array<Object^>^>^ ActionItem = Tuple::Create(AsyncAction, Args);
			ActionQueue->Enqueue(ActionItem);
			WaitLock->Set();
		}
		finally
		{
			Monitor::Exit(ActionQueueLock);
		}		
	}



	Void OpenGLControl::DoActions()
	{
		// import the actions to a local structure (do not block the ActionQueue for a long time)
		Queue<Tuple<Delegate^, array<Object^>^>^>^ TemporaryActionQueue;
		Monitor::Enter(ActionQueueLock);
		try
		{
			TemporaryActionQueue = gcnew Queue<Tuple<Delegate^, array<Object^>^>^>(ActionQueue);
			ActionQueue->Clear();
			WaitLock->Reset();
		}
		finally
		{
			Monitor::Exit(ActionQueueLock);
		}

		// perform the events
		Monitor::Enter(DoActionsLock);
		try
		{
			while (!Terminated->WaitOne(0) && TemporaryActionQueue->Count > 0)
			{
				Tuple<Delegate^, array<Object^>^>^ ActionItem = TemporaryActionQueue->Dequeue();
				ActionItem->Item1->DynamicInvoke(ActionItem->Item2);
			}
		}
		finally
		{
			Monitor::Exit(DoActionsLock);
		}
	}



	Void OpenGLControl::OnResize(EventArgs^ e)
	{
		__super::OnResize(e);

		if (!Activated || DesignMode)
			return;

		EnqueueAction(gcnew EventHandler(this, &OpenGLControl::OnOpenGLResize), this, e);
	}



	Void OpenGLControl::OnKeyDown(KeyEventArgs^ e)
	{
		if (!Activated || DesignMode)
			return;

		EnqueueAction(gcnew KeyEventHandler(this, &OpenGLControl::OnOpenGLKeyDown), this, e);
	}



	Void OpenGLControl::OnKeyPress(KeyPressEventArgs^ e)
	{
		if (!Activated || DesignMode)
			return;

		EnqueueAction(gcnew KeyPressEventHandler(this, &OpenGLControl::OnOpenGLKeyPress), this, e);
	}



	Void OpenGLControl::OnKeyUp(KeyEventArgs^ e)
	{
		if (!Activated || DesignMode)
			return;

		EnqueueAction(gcnew KeyEventHandler(this, &OpenGLControl::OnOpenGLKeyUp), this, e);
	}



	Void OpenGLControl::OnMouseClick(MouseEventArgs^ e)
	{
		if (!Activated || DesignMode)
			return;

		EnqueueAction(gcnew MouseEventHandler(this, &OpenGLControl::OnOpenGLMouseClick), this, e);
	}



	Void OpenGLControl::OnMouseDoubleClick(MouseEventArgs^ e)
	{
		if (!Activated || DesignMode)
			return;

		EnqueueAction(gcnew MouseEventHandler(this, &OpenGLControl::OnOpenGLMouseDoubleClick), this, e);
	}



	Void OpenGLControl::OnMouseDown(MouseEventArgs^ e)
	{
		if (!Activated || DesignMode)
			return;

		EnqueueAction(gcnew MouseEventHandler(this, &OpenGLControl::OnOpenGLMouseDown), this, e);
	}



	Void OpenGLControl::OnMouseEnter(EventArgs^ e)
	{
		if (!Activated || DesignMode)
			return;

		EnqueueAction(gcnew EventHandler(this, &OpenGLControl::OnOpenGLMouseEnter), this, e);
	}



	Void OpenGLControl::OnMouseHover(EventArgs^ e)
	{
		if (!Activated || DesignMode)
			return;

		EnqueueAction(gcnew EventHandler(this, &OpenGLControl::OnOpenGLMouseHover), this, e);
	}



	Void OpenGLControl::OnMouseLeave(EventArgs^ e)
	{
		if (!Activated || DesignMode)
			return;

		EnqueueAction(gcnew EventHandler(this, &OpenGLControl::OnOpenGLMouseLeave), this, e);
	}



	Void OpenGLControl::OnMouseMove(MouseEventArgs^ e)
	{
		if (!Activated || DesignMode)
			return;

		EnqueueAction(gcnew MouseEventHandler(this, &OpenGLControl::OnOpenGLMouseMove), this, e);
	}



	Void OpenGLControl::OnMouseUp(MouseEventArgs^ e)
	{
		if (!Activated || DesignMode)
			return;

		EnqueueAction(gcnew MouseEventHandler(this, &OpenGLControl::OnOpenGLMouseUp), this, e);
	}



	Void OpenGLControl::OnMouseWheel(MouseEventArgs^ e)
	{
		if (!Activated || DesignMode)
			return;

		EnqueueAction(gcnew MouseEventHandler(this, &OpenGLControl::OnOpenGLMouseWheel), this, e);
	}



	Void OpenGLControl::OnLoad(EventArgs^ e)
	{
		StartThread();
	}



	Void OpenGLControl::CreateHandle()
	{
		__super::CreateHandle();

		if (RecreatingHandle)
			CreateThread();
	}



	Void OpenGLControl::DestroyHandle()	
	{
		// Handle recreation is very rare, but we need to handle it
		if (RecreatingHandle)
			TerminateThread();

		__super::DestroyHandle();
	}



	Void OpenGLControl::WndProc(Message% m)
	{
		switch (m.Msg)
		{
		case WM_PAINT:
			OnPaint(gcnew PaintEventArgs(Graphics::FromHwnd(Handle), ClientRectangle));
			break;

		case WM_ERASEBKGND:
			OnPaintBackground(gcnew PaintEventArgs(Graphics::FromHwnd(Handle), ClientRectangle));
			break;
		}

		__super::WndProc(m);
	}



	Void OpenGLControl::OnRenderFrameRate(EventArgs^ e)
	{
		// string to be printed
		String^ FrameRateString = String::Format("{0:0.0}", AverageFrameRate);

		// convert the managed string into char array
		char* str = (char*)(Marshal::StringToHGlobalAnsi(FrameRateString)).ToPointer();
		char* p = str;

		glDisable(GL_LIGHTING);

		// Set up the Orthographic projection
		glViewport(0, 0, Width, Height);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0, Width, 0, Height);
		glScalef(1, -1, 1);
		glTranslatef(0, -Height, 0);

		// draw the text's background
		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex2f(0.0f, 0.0f);
		glVertex2f(FrameRateString->Length*10.0f, 0.0f);
		glVertex2f(FrameRateString->Length*10.0f, 20.0f);
		glVertex2f(0.0f, 20.0f);
		glEnd();

		// draw the text
		glColor3f(1.0f, 1.0f, 0.2f);
		glRasterPos2f(3.0f, 16.0f);

		//while (*p != '\0')
		{ 
			//glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *p++);
		}

		// release the allocated string
		Marshal::FreeHGlobal(IntPtr((void*)str));
	}



	Void OpenGLControl::OnOpenGLRender(Object^ obj, EventArgs^ e)
	{
		// compute the average framerate
		if (RenderingWatch->IsRunning)
		{
			// do not render more often then the MaxFrameRate allows
			Int64 ElapsedTicks = RenderingWatch->ElapsedTicks;
			if (RenderStyle==ERenderStyle::Auto  &&  ElapsedTicks < TicksPerFrame)
			{
				// if the required time is still larger than 2 milliseconds, then sleep for 1 millisecond
				if (!PreciseTiming && (TicksPerFrame-ElapsedTicks) > TicksPerMilisecond*2)
					Thread::Sleep(1);

				return;
			}

			SaveRenderingTime(ElapsedTicks);
		}	

		// restart the time measurement
		RenderingWatch->Restart();

		// the rendering itself
		OpenGLRender(this, e);

		// render also the framerate if necessary
		if (ShowFrameRate)
			OnRenderFrameRate(EventArgs::Empty);

		// swap the buffers to display the rendered image
		if (AutomaticSwapBuffer)
			this->SwapBuffers();

		RenderedFrameCount = RenderedFrameCount + 1;
	}



	Void OpenGLControl::OnOpenGLResize(Object^ obj, EventArgs^ e)
	{
		OpenGLResize(this, e);
	}



	Void OpenGLControl::OnOpenGLInit(Object^ obj, EventArgs^ e)
	{
		OpenGLInit(this, e);
	}



	Void OpenGLControl::OnOpenGLKeyDown(Object^ obj, KeyEventArgs^ e)
	{
		OpenGLKeyDown(this, e);
	}



	Void OpenGLControl::OnOpenGLKeyPress(Object^ obj, KeyPressEventArgs^ e)
	{
		OpenGLKeyPress(this, e);
	}



	Void OpenGLControl::OnOpenGLKeyUp(Object^ obj, KeyEventArgs^ e)
	{
		OpenGLKeyUp(this, e);
	}



	Void OpenGLControl::OnOpenGLMouseClick(Object^ obj, MouseEventArgs^ e)
	{
		OpenGLMouseClick(this, e);
	}



	Void OpenGLControl::OnOpenGLMouseDoubleClick(Object^ obj, MouseEventArgs^ e)
	{
		OpenGLMouseDoubleClick(this, e);
	}



	Void OpenGLControl::OnOpenGLMouseDown(Object^ obj, MouseEventArgs^ e)
	{
		OpenGLMouseDown(this, e);
	}



	Void OpenGLControl::OnOpenGLMouseEnter(Object^ obj, EventArgs^ e)
	{
		OpenGLMouseEnter(this, e);
	}



	Void OpenGLControl::OnOpenGLMouseHover(Object^ obj, EventArgs^ e)
	{
		OpenGLMouseHover(this, e);
	}



	Void OpenGLControl::OnOpenGLMouseLeave(Object^ obj, EventArgs^ e)
	{
		OpenGLMouseLeave(this, e);
	}



	Void OpenGLControl::OnOpenGLMouseMove(Object^ obj, MouseEventArgs^ e)
	{
		OpenGLMouseMove(this, e);
	}



	Void OpenGLControl::OnOpenGLMouseUp(Object^ obj, MouseEventArgs^ e)
	{
		OpenGLMouseUp(this, e);
	}



	Void OpenGLControl::OnOpenGLMouseWheel(Object^ obj, MouseEventArgs^ e)
	{
		OpenGLMouseWheel(this, e);
	}



	Void OpenGLControl::SaveRenderingTime(Int64 ElapsedTime)
	{
		// remove the unwanted values
		while (RenderingTimes->Count>=AverageFrameRateBase)
			RenderingTimes->Dequeue();

		RenderingTimes->Enqueue(ElapsedTime);
		ActualizeFrameRate();
	}



	Void OpenGLControl::ActualizeFrameRate()
	{
		Int64 Sum = 0;
		for each(Int64 RenderingTime in RenderingTimes)
			Sum += RenderingTime;

		if (RenderingTimes->Count == 0  ||  Sum == 0)
		{
			AverageFrameRate = 0.0F;
			return;
		}

		AverageFrameRate = (Single)(Stopwatch::Frequency) / (Single)(Sum / RenderingTimes->Count);
	}



	Void OpenGLControl::BeginSynchronization()
	{
		if (ActionThread->ManagedThreadId == Thread::CurrentThread->ManagedThreadId)
			throw gcnew InvalidOperationException("Do not call the BeginSynchronization() from the OpenGLControl's ActionThread!");
		
		// wait for the actions in progress to complete
		Monitor::Enter(DoActionsLock);
	}



	Void OpenGLControl::EndSynchronization()
	{
		if (ActionThread->ManagedThreadId == Thread::CurrentThread->ManagedThreadId)
			throw gcnew InvalidOperationException("Do not call the EndSynchronization() from the OpenGLControl's ActionThread!");

		Monitor::Exit(DoActionsLock);
	}



	Void OpenGLControl::SwapBuffers()
	{
		if (Activated)
			::SwapBuffers(hdc);
	}



	Int64 OpenGLControl::TicksPerFrame::get()
	{
		if (MaxFrameRate <= 0.0F)
			return Int64::MaxValue;

		// number of TicksPerSecond divided by the number of FramesPerSecond = NumberOfTicksPerSecond
		return Stopwatch::Frequency / (Int64)(MaxFrameRate);
	}



	Int64 OpenGLControl::TicksPerMilisecond::get()
	{
		return Stopwatch::Frequency / 1000;
	}



	String^ OpenGLControl::Text::get()
	{
		return FText;
	}



	Void OpenGLControl::Text::set(String^ value)
	{
		FText = value;
	}



	Boolean OpenGLControl::PreciseTiming::get()
	{
		return FPreciseTiming;
	}



	Void OpenGLControl::PreciseTiming::set(Boolean value)
	{
		FPreciseTiming = value;
	}



	Boolean OpenGLControl::ShowFrameRate::get()
	{
		return FShowFrameRate;
	}



	Void OpenGLControl::ShowFrameRate::set(Boolean value)
	{
		FShowFrameRate = value;
	}



	ERenderStyle OpenGLControl::RenderStyle::get()
	{
		return FRenderStyle;
	}



	Void OpenGLControl::RenderStyle::set(ERenderStyle value)
	{
		FRenderStyle = value;

		// custom painting during runtime
		if (!DesignMode && LicenseManager::UsageMode==LicenseUsageMode::Runtime)
		{
			SetStyle(ControlStyles::UserPaint, RenderStyle==ERenderStyle::SystemRender);	// if false the Paint event is not raised
			SetStyle(ControlStyles::ResizeRedraw, RenderStyle==ERenderStyle::SystemRender);	// if false the Resize event is not raised
		}
	}



	Single OpenGLControl::MaxFrameRate::get()
	{
		return FMaxFrameRate;
	}



	Void OpenGLControl::MaxFrameRate::set(Single value)
	{
		if (value < 0.0F)
		{	
			FMaxFrameRate = 0.0F;
			return;
		}

		FMaxFrameRate = value;

		// we need to reset also the saved rendering times, 
		// because the new rendering speed can affect the average time
		RenderingTimes->Clear();
	}



	Single OpenGLControl::AverageFrameRate::get()
	{
		return FAverageFrameRate;
	}



	Void OpenGLControl::AverageFrameRate::set(Single value)
	{
		FAverageFrameRate = value;
	}



	Int64 OpenGLControl::RenderedFrameCount::get()
	{
		return FRenderedFrameCount;
	}



	Void OpenGLControl::RenderedFrameCount::set(Int64 value)
	{
		FRenderedFrameCount = value;
	}



	Int32 OpenGLControl::AverageFrameRateBase::get()
	{
		return FAverageFrameRateBase;
	}



	Void OpenGLControl::AverageFrameRateBase::set(Int32 value)
	{
		if (value <= 0)		
		{
			FAverageFrameRateBase = 1;
			return;
		}

		FAverageFrameRateBase = value;	
	}



	Boolean OpenGLControl::AutomaticSwapBuffer::get()
	{
		return FAutomaticSwapBuffer;
	}



	Void OpenGLControl::AutomaticSwapBuffer::set(Boolean value)
	{
		FAutomaticSwapBuffer = value;
	}
}