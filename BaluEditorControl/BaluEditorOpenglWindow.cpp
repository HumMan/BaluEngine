#include "BaluEditorControl.h"

#include "../Source/EngineInterfaces.h"

using namespace EngineInterface;

class BaluEditorOpenglWindowPrivate
{
public:
	IDirector* director;
};

namespace Editor
{
	BaluEditorOpenglWindow::BaluEditorOpenglWindow(IntPtr handle)
	{
		p = new BaluEditorOpenglWindowPrivate();
		p->director = CreateDirector();
		p->director->Initialize((void*)handle.ToPointer());
	}
	void BaluEditorOpenglWindow::BeginFrame()
	{
		p->director->BeginFrame();
	}
	void BaluEditorOpenglWindow::EndFrame()
	{
		p->director->EndFrame();
	}
};