#include "scriptClasses.h"

#include <Windows.h>

const int WinVirtKey[] =
{
	VK_BACK,
	VK_TAB,
	VK_RETURN,
	VK_LSHIFT,
	VK_RSHIFT,
	VK_LCONTROL,
	VK_RCONTROL,
	VK_LMENU,
	VK_RMENU,
	VK_PAUSE,
	VK_CAPITAL,
	VK_ESCAPE,
	VK_SPACE,
	VK_PRIOR,
	VK_NEXT,
	VK_END,
	VK_HOME,
	VK_LEFT,
	VK_UP,
	VK_RIGHT,
	VK_DOWN,
	VK_PRINT,
	VK_INSERT,
	VK_DELETE,
	VK_NUMPAD0,
	VK_NUMPAD1,
	VK_NUMPAD2,
	VK_NUMPAD3,
	VK_NUMPAD4,
	VK_NUMPAD5,
	VK_NUMPAD6,
	VK_NUMPAD7,
	VK_NUMPAD8,
	VK_NUMPAD9,
	VK_MULTIPLY,
	VK_ADD,
	VK_SUBTRACT,
	VK_DIVIDE,
	VK_F1,
	VK_F2,
	VK_F3,
	VK_F4,
	VK_F5,
	VK_F6,
	VK_F7,
	VK_F8,
	VK_F9,
	VK_F10,
	VK_F11,
	VK_F12,
	VK_NUMLOCK,
	VK_SCROLL,
	-1
};

int ToBaluChar(char key)
{
	if (IsIn(key, 'A', 'Z'))return key;
	if (IsIn(key, '0', '9'))return key;
	switch ((unsigned char)key)
	{
	case VK_OEM_1:		return (unsigned char)':';
	case VK_OEM_PLUS:	return (unsigned char)'+';
	case VK_OEM_COMMA:	return (unsigned char)',';
	case VK_OEM_MINUS:	return (unsigned char)'-';
	case VK_OEM_PERIOD:	return (unsigned char)'.';
	case VK_OEM_2:		return (unsigned char)'?';
	case VK_OEM_3:		return (unsigned char)'~';
	case VK_OEM_4:		return (unsigned char)'{';
	case VK_OEM_5:		return (unsigned char)'|';
	case VK_OEM_6:		return (unsigned char)'}';
	case VK_OEM_7:		return (unsigned char)'"';
	}
	return -1;
}

int ToBaluSpecKey(int key)
{
	assert(WinVirtKey[BVK_MAX] == -1);//размер должен быть одинаковым
	for (int i = 0; i <= BVK_MAX; i++)
		if (key == WinVirtKey[i])return i;
	return -1;
}