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
	

	public enum class ERenderStyle
	{
		SystemRender=0,	// render when OnPaint is called
		Auto,			// render in a loop
		Manual			// render when a user triggers a rendering manually
	};



	[DesignerAttribute(OpenGLControlDesigner::typeid)]
	public ref class OpenGLControl : public System::Windows::Forms::UserControl
	{
	private:
		// fields
		Boolean FShowFrameRate;	
		Boolean FPreciseTiming;
		Boolean FAutomaticSwapBuffer;
		String^ FText;
		ERenderStyle FRenderStyle;
		Single FMaxFrameRate;
		Single FAverageFrameRate;
		Int32 FAverageFrameRateBase;
		Int64 FRenderedFrameCount;

		// methods
		Void ActivateOpenGLRendering(IntPtr WindowHandle);		// activate OpenGL mode at the beginning
		Void DeactivateOpenGLRendering(IntPtr WindowHandle);	// deactivate the OpenGL mode at the end
		Void ActionThread_Execute(Object^ WindowHandle);
		Void CreateThread();
		Void StartThread();
		Void TerminateThread();
		Void SaveRenderingTime(Int64 ElapsedTime);
		Void ActualizeFrameRate();
		Void EnqueueAction(Delegate^ AsyncAction, ... array<Object^>^ Args);	// actions to be called asynchronously
		Void DoActions();										// triggers the appropriate actions

		// members
		Queue<Int64>^ RenderingTimes; 
		Stopwatch^ RenderingWatch;
		Boolean Activated;				// true if the ActivateOpenGLRendering was successful	
		HDC hdc;						// device context
		HGLRC hrc;						// rendering context
		Threading::Thread^ ActionThread;// the events are triggered on this thread
		ManualResetEvent^ Terminated;	// is used to signalize termination for the EventThread
		ManualResetEvent^ WaitLock;
		String^ ErrorMessage;			// indicates what kind of error occurred during the activation		
		Queue<Tuple<Delegate^, array<Object^>^>^>^ ActionQueue;	// contains the unprocessed actions with their arguments
		Object^ ActionQueueLock;		// used for locking the ActionQueue
		Object^ DoActionsLock;	

		// property
		property Int64 TicksPerFrame
		{
			Int64 get();
		}

		property Int64 TicksPerMilisecond
		{
			Int64 get();
		}

	public:
		// constructor
		OpenGLControl();

		// custom events
		event EventHandler^ OpenGLInit;	
		event EventHandler^ OpenGLRender;
		event EventHandler^ OpenGLResize;
		event KeyEventHandler^ OpenGLKeyDown;
		event KeyPressEventHandler^ OpenGLKeyPress;
		event KeyEventHandler^ OpenGLKeyUp;
		event MouseEventHandler^ OpenGLMouseClick;
		event MouseEventHandler^ OpenGLMouseDoubleClick;
		event MouseEventHandler^ OpenGLMouseDown;
		event EventHandler^ OpenGLMouseEnter;
		event EventHandler^ OpenGLMouseHover;
		event EventHandler^ OpenGLMouseLeave;
		event MouseEventHandler^ OpenGLMouseMove;
		event MouseEventHandler^ OpenGLMouseUp;
		event MouseEventHandler^ OpenGLMouseWheel;
		
		// methods
		virtual Void Refresh() override;	// the refresh method is not available (empty) for this control to avoid painting 'collisions'
		virtual Void Render();				// the user can manually trigger a rendering in manual mode	
		Void BeginSynchronization();		// the queued actions will not be triggered until EndSynchronize is called
		Void EndSynchronization();	
		Void SwapBuffers();

		// properties
		[Browsable(true)]
		[DesignerSerializationVisibility(DesignerSerializationVisibility::Visible)]
		property String^ Text
		{
			virtual String^ get() override;
			virtual Void set(String^ value) override;
		}

		property ERenderStyle RenderStyle
		{
			ERenderStyle get();
			Void set(ERenderStyle value);
		}
		
		property Boolean PreciseTiming
		{
			Boolean get();
			Void set(Boolean value);
		}

		property Boolean ShowFrameRate		// if true, the actual framerate is displayed in the top left corner
		{
			Boolean get();
			Void set(Boolean value);
		}	  

		property Single MaxFrameRate
		{
			Single get();
			Void set(Single value);
		}

		property Int32 AverageFrameRateBase	// count of the frames from which the average framerate is computed
		{
			Int32 get();
			Void set(Int32 value);
		}

		[DescriptionAttribute("If false, please call OpenGLControl->SwapBuffers() manually")]
		property Boolean AutomaticSwapBuffer
		{
			Boolean get();
			Void set(Boolean value);
		}

		[Browsable(false)]
		property Int64 RenderedFrameCount
		{
			Int64 get();
			private: Void set(Int64 value);
		}

		[Browsable(false)]
		property Single AverageFrameRate		// returns the actual framerate
		{
			Single get();
			private: Void set(Single value);
		}

	protected:
		// destructor
		~OpenGLControl();

		// catch the events user events	
		virtual Void OnPaint(PaintEventArgs^ e) override;	// this and the next function was overridden, to avoid painting collisions
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
		virtual Void CreateHandle() override;
		virtual Void DestroyHandle() override;
		virtual Void WndProc(Message% m) override;

		// custom methods
		virtual Void OnRenderFrameRate(EventArgs^ e);		// renders the actual framerate to the Top Left corner
		virtual Void OnOpenGLRender(Object^ obj, EventArgs^ e);
		virtual Void OnOpenGLResize(Object^ obj, EventArgs^ e);
		virtual Void OnOpenGLInit(Object^ obj, EventArgs^ e);
		virtual Void OnOpenGLKeyDown(Object^ obj, KeyEventArgs^ e);
		virtual Void OnOpenGLKeyPress(Object^ obj, KeyPressEventArgs^ e);
		virtual Void OnOpenGLKeyUp(Object^ obj, KeyEventArgs^ e);
		virtual Void OnOpenGLMouseClick(Object^ obj, MouseEventArgs^ e);
		virtual Void OnOpenGLMouseDoubleClick(Object^ obj, MouseEventArgs^ e);
		virtual Void OnOpenGLMouseDown(Object^ obj, MouseEventArgs^ e);
		virtual Void OnOpenGLMouseEnter(Object^ obj, EventArgs^ e);
		virtual Void OnOpenGLMouseHover(Object^ obj, EventArgs^ e);
		virtual Void OnOpenGLMouseLeave(Object^ obj, EventArgs^ e);
		virtual Void OnOpenGLMouseMove(Object^ obj, MouseEventArgs^ e);
		virtual Void OnOpenGLMouseUp(Object^ obj, MouseEventArgs^ e);
		virtual Void OnOpenGLMouseWheel(Object^ obj, MouseEventArgs^ e);
	};
}
