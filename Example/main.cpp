
#include <box2d.h>
#include <baluRender.h>
#include <baluEngine.h>
#include <baluScript.h>
#include "../Source/scriptClasses.h"

TBaluEngine* engine;

char buf1[1000];
int curr_buf1;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message,WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	case WM_SIZE:
		if(engine)
			engine->SetViewport(TVec2i(LOWORD(lParam),HIWORD(lParam)));
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
		break;
	case WM_CHAR:
		{	
			if(wParam>=30)
			{
				//char dd[1000];
				//dd[0]=wParam;
				//dd[1]='1';
				//dd[2]='2';
				//dd[3]='3';
				//dd[4]='r';
				//*(int*)&dd[8]=12356;
				//va_list list=&dd[0];
				//vsprintf(&buf1[curr_buf1],"%c _ %c %i",list);
				//curr_buf1+=vsprintf(&buf1[curr_buf1],"%c",list);
				//curr_buf1+=sprintf_s(buf1[curr_buf1],"%c",wParam);
				//SetWindowText(hWnd,&buf1[0]);
			}
		}
		break;
	case WM_MOUSEWHEEL:
		engine->OnMouseScroll(GET_WHEEL_DELTA_WPARAM(wParam));
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

HDC hDC;
HWND hWnd;

TTime time;

char buf[1000];

void UpdateControls()
{
	unsigned char key_states[256];
	GetKeyboardState(&key_states[0]);
	engine->UpdateKeyStates(&key_states[0]);
	TVec2i v=GetCursorPos();
	POINT local_corner;
	local_corner.x=0;
	local_corner.y=0;
	if(!ClientToScreen(hWnd,&local_corner))
	{
		int i=GetLastError();
		sprintf_s(buf1,"%i\nWindow handle: %i",i,hWnd);
		//MessageBox(0,buf1,L"Error",MB_OK);
	}
	v[0]-=local_corner.x;
	v[1]-=local_corner.y;
	engine->UpdateMouseState(KeyDown(VK_LBUTTON),KeyDown(VK_MBUTTON),KeyDown(VK_RBUTTON),v);
}

void InitEngine()
{
	curr_buf1=0;
	{
		engine->AddMaterial("mat1","..\\textures\\Crate005_ebox.png",TVec4(Randf(),Randf(),Randf(),1));
		engine->AddMaterial("mat2","..\\textures\\container_001a.png",TVec4(Randf(),Randf(),Randf(),1));
		TBaluShape shape;
		float density=0.01;
		float rad=0.3;
		//shape.SetAsCircle(rad,density);
		float k = 0.35;
		shape.SetAsBox(TVec2(1*k, 1*k), density);
		engine->AddShape("shape1",shape);
		density=0;
		shape.SetAsBox(TVec2(65*k, 2*k), density);
		engine->AddShape("shape2",shape);

		engine->AddSprite("sprite1","shape1","mat1",TVec2(1,1),0,TVec2(0,0),-1);
		engine->AddSprite("sprite2","shape2","mat2",TVec2(65,2),0,TVec2(0,0),-1);

		TBaluClass o;
		o.SetMembers("float t;");
		//o.SetEvent(EVENT_CREATE,
		//	"\n t=0;//t=Randf();vec2 tttt=Cross(vec2(0,1),vec2(1,1));\
		//	//sprite.shape.SetAsBox(vec2(0.3,0.3),0.01);");
		//o.SetEvent(EVENT_STEP,
		//	"\n vec2 v=Normalize(Mouse.WorldPos-pos);\
		//	\n //sprite.local_angle=Sign(v[1])*Acos(v[0])+t;\
		//	\n if(Mouse.Button.Left){t-=0.2;}if(Mouse.Button.Right){t+=0.2;}");
		//o.SetEvent(EVENT_GLOBALMOUSEDOWN,
		//	"\n if(button==TMouseButton.Middle)t+=0.2;");
		//o.SetEvent(EVENT_KEYUP,
		//	"\n");
		//o.SetEvent(EVENT_KEYDOWN,
		//	"\n");

		TBaluClass o1;
		o1.SetMembers("float arr;");
		//o1.SetMembers("int[][10] arr;");
		o1.SetEvent(TBaluEvent::EVENT_STEP,
			"sprite.local_angle+=Time.Step;\n");

		TBaluClass mouse_contrl;
		mouse_contrl.SetMembers("float arr;");
		//mouse_contrl.SetEvent(EVENT_STEP,
		//	"\n float ox=0,oy=0,coeff=1.0;\
		//	\n if(Keyboard.Pressed('A'))ox=-1;\
		//	\n if(Keyboard.Pressed('D'))ox=1;\
		//	\n if(Keyboard.Pressed('S'))oy=-1;\
		//	\n if(Keyboard.Pressed('W'))oy=1;\
		//	\n if(Keyboard.Pressed(TVirtKey.LShift))coeff=5.0;\
		//	\n Screen.SetPos(Screen.Pos+vec2(ox,oy)*Screen.Size[0]*0.01*coeff);");


		//mouse_contrl.SetEvent(EVENT_GLOBALMOUSEWHEEL,
		//	"Screen.SetSize(Screen.Size*(1.0+0.1*delta));");

		engine->AddClass("Obj2","sprite2",o1);
		engine->AddClass("Obj1","sprite1",o);
		engine->AddClass("MouseContrl","sprite1",mouse_contrl);
		////
		engine->AddInstance("MouseContrl",TVec2(0,-10),0);
		engine->AddInstance("Obj2",TVec2(0,-0.6),0);
		engine->AddInstance("Obj2",TVec2(6,-1),45*M_PI/180);
		engine->AddInstance("Obj2",TVec2(-6,-0.8),-45*M_PI/180);
		for(int i=5;i<=10;i++)
			for(int k=-8;k<=8;k++)
			{
				engine->AddInstance("Obj1",TVec2(k*1+i*0.2,i*4),0);
			}
	}
	UpdateControls();
	engine->Start();
}

static DWORD last_tick_count;

void MainLoop()
{
	//time.Tick();
	//if(time.ShowFPS())
	//{
	//	sprintf(&buf[0],"%7.1f FPS",time.GetFPS());
	//	SetWindowText(hWnd,&buf[0]);
	//}
	if(GetTickCount()-last_tick_count<14)
	{
		Sleep(5);
		return;
	}
	float step_time=(GetTickCount()-last_tick_count)/1000.0f;
	last_tick_count=GetTickCount();
	{
		UpdateControls();
		engine->Step(step_time,GetTickCount()/1000.0f);
	}
}

int WINAPI WinMain (HINSTANCE hInstance,
					HINSTANCE hPrevInstance,
					LPSTR lpCmdLine,
					int iCmdShow)
{

	MSG msg;
	/* register window class */
	WNDCLASS wc = {0};
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon (NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor (NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH) GetStockObject (BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = L"Sample";
	RegisterClass (&wc);

	/* create main window */
	hWnd = CreateWindow (
		wc.lpszClassName, L"Sample",
		WS_OVERLAPPEDWINDOW| WS_VISIBLE|WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_POPUPWINDOW | WS_VISIBLE,
		50, 50, 1000,1000,/*GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),*/
		NULL, NULL, hInstance, NULL);

	RECT rect;
	GetClientRect(hWnd,&rect);

	engine=new TBaluEngine(hWnd,TVec2i(rect.right-rect.left,rect.bottom-rect.top));

	InitEngine();

	last_tick_count=GetTickCount();

	time.Start();

	/* program main loop */
	while (true)
	{
		/* check for messages */
		if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
		{
			/* handle or dispatch messages */
			if (msg.message == WM_QUIT)
				break;
			else
			{
				TranslateMessage (&msg);
				DispatchMessage (&msg);
			}
		}
		else
			MainLoop();
	}

	delete engine;

	/* destroy the window explicitly */
	DestroyWindow(hWnd);

	return 0;
}