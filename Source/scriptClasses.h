#pragma once

static const char* script_base_classes="\
\n class sealed int\
\n 	{\
\n 	private:\
\n 		dword unnamed;\
\n 	public:\
\n 		constr(int v) bytecode{};\
\n 		constr(float v) bytecode{ASM_FLOAT_TO_INT;};\
\n 		\
\n 		operator static = (int& l,int r)bytecode{ASM_ASSIGN 0,1;};\
\n 		operator static +=(int& l,int r)bytecode{ASM_INT_PLUS_A;};\
\n 		operator static -=(int& l,int r)bytecode{ASM_INT_MINUS_A;};\
\n 		operator static *=(int& l,int r)bytecode{ASM_INT_MUL_A;};\
\n 		operator static /=(int& l,int r)bytecode{ASM_INT_DIV_A;};\
\n 		operator static %=(int& l,int r)bytecode{ASM_INT_MOD_A;};\
\n 		operator static +(int l,int r):int bytecode{ASM_INT_PLUS;};\
\n 		operator static -(int l,int r):int bytecode{ASM_INT_MINUS;};\
\n 		operator static *(int l,int r):int bytecode{ASM_INT_MUL;};\
\n 		operator static /(int l,int r):int bytecode{ASM_INT_DIV;};\
\n 		operator static %(int l,int r):int bytecode{ASM_INT_MOD;};\
\
\n 		operator static -(int  l):int bytecode{ASM_INT_UNARY_MINUS;};\
\n 		operator static -(int& l):int bytecode{ASM_R_INT_UNARY_MINUS;};\
\
\n 		operator static < (int l,int r):bool bytecode{ASM_INT_LESS;};\
\n 		operator static <=(int l,int r):bool bytecode{ASM_INT_LESS_EQ;};\
\n 		operator static ==(int l,int r):bool bytecode{ASM_EQUAL 0,0,1;};\
\n 		operator static !=(int l,int r):bool bytecode{ASM_NOT_EQUAL 0,0,1;};\
\n 		operator static > (int l,int r):bool bytecode{ASM_INT_GREATER;};\
\n 		operator static >=(int l,int r):bool bytecode{ASM_INT_GREATER_EQ;};\
\n\
\n 		conversion static (int& v):float bytecode{ASM_R_INT_TO_FLOAT;};\
\n 		conversion static (int  v):float bytecode{ASM_INT_TO_FLOAT;};\
\n 		conversion static (int& v):bool  bytecode{ASM_R_INT_TO_BOOL;};\
\n 		conversion static (int  v):bool  bytecode{ASM_INT_TO_BOOL;};\
\n 	}\
\n 	func static Abs(int v		):int bytecode{ASM_INT_ABS;};\
\n 	func static Max(int v0,int v1):int bytecode{ASM_INT_MAXIMUM;};\
\n 	func static Min(int v0,int v1):int bytecode{ASM_INT_MINIMUM;};\
\n 	func static Sign(int v		):int bytecode{ASM_INT_SIGN;};\
\
\n 	class sealed float\
\n 	{\
\n 	private:\
\n 		dword unnamed;\
\n 	public:\
\n 		constr(float v) bytecode{};\
\n 		\
\n 		operator static = (float& l,float r)bytecode{ASM_ASSIGN 0,1;};\
\n 		operator static +=(float& l,float r)bytecode{ASM_FLOAT_PLUS_A;};\
\n		operator static -=(float& l,float r)bytecode{ASM_FLOAT_MINUS_A;};\
\n		operator static *=(float& l,float r)bytecode{ASM_FLOAT_MUL_A;};\
\n		operator static /=(float& l,float r)bytecode{ASM_FLOAT_DIV_A;};\
\n\
\n		operator static +(float l,float r):float bytecode{ASM_FLOAT_PLUS;};\
\n		operator static -(float l,float r):float bytecode{ASM_FLOAT_MINUS;};\
\n		operator static *(float l,float r):float bytecode{ASM_FLOAT_MULT;};\
\n		operator static /(float l,float r):float bytecode{ASM_FLOAT_DIV;};\
\n\
\n		operator static -(float  l):float bytecode{ASM_FLOAT_UNARY_MINUS;};\
\n		operator static -(float& l):float bytecode{ASM_R_FLOAT_UNARY_MINUS;};\
\n\
\n		operator static < (float l,float r):bool bytecode{ASM_FLOAT_LESS;};\
\n		operator static <=(float l,float r):bool bytecode{ASM_FLOAT_LESS_EQ;};\
\n		operator static ==(float l,float r):bool bytecode{ASM_EQUAL 0,0,1;};\
\n		operator static !=(float l,float r):bool bytecode{ASM_NOT_EQUAL 0,0,1;};\
\n		operator static > (float l,float r):bool bytecode{ASM_FLOAT_GREATER;};\
\n		operator static >=(float l,float r):bool bytecode{ASM_FLOAT_GREATER_EQ;};\
\n\
\n		conversion static (float& v):bool  bytecode{ASM_R_FLOAT_TO_BOOL;};\
\n		conversion static (float  v):bool  bytecode{ASM_FLOAT_TO_BOOL;};\
\n		conversion static (float  v):vec2  bytecode{ASM_FLOAT_TO_VEC2;};\
\n	}\
\n	func static Abs		(float v):float bytecode{ASM_FLOAT_ABS;};\
\n	func static Asin	(float v):float bytecode{ASM_FLOAT_ASIN;};\
\n	func static Acos	(float v):float bytecode{ASM_FLOAT_ACOS;};\
\n	func static Atan	(float v):float bytecode{ASM_FLOAT_ATAN;};\
\n	func static Ceil	(float v):float bytecode{ASM_FLOAT_CEIL;};\
\n	func static Clamp	(float min,float max,float v):float bytecode{ASM_FLOAT_CLAMP;};\
\n	func static Cos		(float v):float bytecode{ASM_FLOAT_COS;};\
\n	func static DegToRad(float v):float bytecode{ASM_FLOAT_DEG_TO_RAD;};\
\n	func static Exp		(float v):float bytecode{ASM_FLOAT_EXP;};\
\n	func static Floor	(float v):float bytecode{ASM_FLOAT_FLOOR;};\
\n	func static Frac	(float v):float bytecode{ASM_FLOAT_FRAC;};\
\n	func static Log		(float v):float bytecode{ASM_FLOAT_LOG;};\
\n	func static Log2	(float v):float bytecode{ASM_FLOAT_LOG2;};\
\n	func static Log10	(float v):float bytecode{ASM_FLOAT_LOG10;};\
\n	func static Max		(float v0,float v1):float bytecode{ASM_FLOAT_MAX;};\
\n	func static Min		(float v0,float v1):float bytecode{ASM_FLOAT_MIN;};\
\n	func static Pow		(float v,float pow):float bytecode{ASM_FLOAT_POW;};\
\n	func static RadToDeg(float v):float bytecode{ASM_FLOAT_RAD_TO_DEG;};\
\n	func static Randf():float bytecode{ASM_FLOAT_RAND;};\
\n	func static Sign	(float v):float bytecode{ASM_FLOAT_SIGN;};\
\n	func static Sin		(float v):float bytecode{ASM_FLOAT_SIN;};\
\n	func static Sqrt	(float v):float bytecode{ASM_FLOAT_SQRT;};\
\n	func static Sqr		(float v):float bytecode{ASM_FLOAT_SQR;};\
\n	func static Tan		(float v):float bytecode{ASM_FLOAT_TAN;};\
\n	func static Trunc	(float v):float bytecode{ASM_FLOAT_TRUNC;};\
\n\
\n	func static Print	(float v) bytecode{ASM_FLOAT_PRINT;};\
\n\
\n 	class sealed vec2\
\n 	{\
\n 	private:\
\n 		float[2] unnamed;\
\n 	public:\
\n 		constr(float v0,float v1) bytecode{};\
\n 		\
\n 		operator static = (vec2& l,vec2 r)bytecode{ASM_ASSIGN 0,2;};\
\n 		operator static +=(vec2& l,vec2 r)bytecode{ASM_VEC2_PLUS_A;};\
\n		operator static -=(vec2& l,vec2 r)bytecode{ASM_VEC2_MINUS_A;};\
\n		operator static *=(vec2& l,vec2 r)bytecode{ASM_VEC2_MUL_A;};\
\n		operator static /=(vec2& l,vec2 r)bytecode{ASM_VEC2_DIV_A;};\
\n\
\n		operator static +(vec2 l,vec2 r):vec2 bytecode{ASM_VEC2_PLUS;};\
\n		operator static -(vec2 l,vec2 r):vec2 bytecode{ASM_VEC2_MINUS;};\
\n		operator static *(vec2 l,vec2 r):vec2 bytecode{ASM_VEC2_MULT;};\
\n		operator static /(vec2 l,vec2 r):vec2 bytecode{ASM_VEC2_DIV;};\
\n\
\n		operator static -(vec2  l):vec2 bytecode{ASM_VEC2_UNARY_MINUS;};\
\n		operator static -(vec2& l):vec2 bytecode{ASM_R_VEC2_UNARY_MINUS;};\
\n		operator static [](vec2& v,int id):float bytecode{ASM_RV_VEC2_GET_ELEMENT;};\
\n		operator static [](vec2 v,int id):float bytecode{ASM_VV_VEC2_GET_ELEMENT;};\
\n	}\
\n	func static Cross	(vec2 v0,vec2 v1):float bytecode{ASM_VEC2_CROSS;};\
\n	func static Distance(vec2 v0,vec2 v1):float bytecode{ASM_VEC2_DISTANCE;};\
\n	func static Dot		(vec2 v0,vec2 v1):float bytecode{ASM_VEC2_DOT;};\
\n	func static Length	(vec2 v0):float bytecode{ASM_VEC2_LENGTH;};\
\n	func static Normalize(vec2 v0):float bytecode{ASM_VEC2_NORMALIZE;};\
\n	func static Reflect	 (vec2 v0,vec2 v1):float bytecode{ASM_VEC2_REFLECT;};\
\n\
\n	class sealed char\
\n	{\
\n	private:\
\n		dword unnamed;\
\n	public:\
\n		constr(char v) bytecode{};\
\n		operator static = (char& l,char r)bytecode{ASM_ASSIGN 0,1;};\
\n\
\n		operator static ==(char l,char r):bool bytecode{ASM_EQUAL 0,0,1;};\
\n		operator static !=(char l,char r):bool bytecode{ASM_NOT_EQUAL 0,0,1;};\
\n	}\
\n\
\n	class sealed bool\
\n	{\
\n	private:\
\n		dword unnamed;\
\n	public:\
\n		constr(bool v) bytecode{};\
\n		operator static = (bool& l,bool r)bytecode{ASM_ASSIGN 0,1;};\
\n\
\n		operator static ==(bool l,bool r):bool bytecode{ASM_EQUAL 0,0,1;};\
\n		operator static !=(bool l,bool r):bool bytecode{ASM_NOT_EQUAL 0,0,1;};\
\n		operator static &&(bool l,bool r):bool bytecode{ASM_BOOL_AND;};\
\n		operator static ||(bool l,bool r):bool bytecode{ASM_BOOL_OR;};\
\n		operator static ! (bool l):bool bytecode{ASM_BOOL_NOT;};\
\n\
\n		conversion static (bool& v):float bytecode{ASM_R_INT_TO_FLOAT;};\
\n		conversion static (bool  v):float bytecode{ASM_INT_TO_FLOAT;};\
\n		conversion static (bool  v):int bytecode{};\
\n	}\
\n\
\n	class TDynArray<T>\
\n	{\
\n		TDynArrayInternalFields unnamed;\
\n		constr\
\n		{\
\n			bytecode{ASM_R_DYN_ARR_DEF_CONSTR CreateArrayElementClassId(T);};\
\n		}\
\n		constr(TDynArray& use_source)\
\n		{\
\n			bytecode{ASM_RR_DYN_ARR_COPY_CONSTR;};\
\n		}\
\n		destr\
\n		{\
\n			bytecode{ASM_R_DYN_ARR_DESTR;};\
\n		}\
\n		operator static [](TDynArray& v,int id):&T\
\n			bytecode{ASM_RV_DYN_ARR_GET_ELEMENT;};\
\n		operator static =(TDynArray& left,TDynArray& right)//TODO шаблонный класс не имеет доступа к своему шаблону(нельзя объявить this шаблон с другими параметрами т.к. он воспринимается как класс)\
\n		{\
\n			bytecode{ASM_DYN_ARR_ASSIGN 1;};\
\n		}\
\n		operator static =(TDynArray& left,TDynArray right)\
\n		{\
\n			bytecode{ASM_DYN_ARR_ASSIGN 0;};\
\n		}\
\n		operator static ==(TDynArray& left,TDynArray& right):bool\
\n		{\
\n			bytecode{ASM_DYN_ARR_EQUAL 1,1;};\
\n		}\
\n		operator static ==(TDynArray& left,TDynArray right):bool\
\n		{\
\n			bytecode{ASM_DYN_ARR_EQUAL 1,0;};\
\n		}\
\n		operator static ==(TDynArray left,TDynArray& right):bool\
\n		{\
\n			bytecode{ASM_DYN_ARR_EQUAL 0,1;};\
\n		}\
\n		operator static ==(TDynArray left,TDynArray right):bool\
\n		{\
\n			bytecode{ASM_DYN_ARR_EQUAL 0,0;};\
\n		}\
\n		func SetHigh(int high)	bytecode{ASM_RV_DYN_ARR_SET_HIGH;};\
\n		func GetHigh:int		bytecode{ASM_R_DYN_ARR_GET_HIGH;};\
\n	}";

class TBaluEngine;

typedef TVirtualMachine::TStaticArr<b2_maxPolygonVertices,TVec2> TVertices;

struct TExternMethod
{
	TExternalMethod method_body;
	char* method_name;
	int id;
	TExternMethod():method_name(NULL),id(-1),method_body(NULL){}
	TExternMethod(TExternalMethod use_body,char* use_name):method_body(use_body),method_name(use_name){}
};

struct TButton
{
	int Left;
	int Right;
	int Middle;
};

struct TBaluMouse
{
	friend class TBaluEngine;
	TBaluEngine* engine;
	int clip_enable;
	TVec2 clip_lower_right;
	TVec2 clip_upper_left;
	
	TButton Button;
	TVec2 Pos;
	TVec2 WorldPos;
	BSCRIPT_VOID_METHOD2(TBaluMouse,EnableClip,TVec2,use_lower_right,TVec2,use_upper_left)
	{
		clip_lower_right=use_lower_right;
		clip_upper_left=use_upper_left;
	}
	BSCRIPT_VOID_METHOD(TBaluMouse,DisableClip)
	{
	}
	BSCRIPT_VOID_METHOD1(TBaluMouse,SetPos,TVec2,use_pos)
	{
	}
	void static LinkExternMethods(TVector<TExternMethod>& methods)
	{
		methods.Push(TExternMethod(EnableClip,	"func extern TGame.TMouse.EnableClip(vec2 lower_right,vec2 upper_left)"));
		methods.Push(TExternMethod(DisableClip,	"func extern TGame.TMouse.DisableClip"));
		methods.Push(TExternMethod(SetPos,		"func extern TGame.TMouse.SetPos(vec2 pos)"));
	}
};

static const char* script_mouse="\
\n enum TMouseButton\
\n {\
\n 	Left,\
\n 	Middle,\
\n 	Right\
\n }\
\n class TMouse\
\n {\
\n 	class TButton\
\n 	{\
\n 		bool Left,Right,Middle;\
\n 	}\
\n readonly:\
\n  int engine;\
\n  bool clip_enable;\
\n  vec2 clip_lower_right;\
\n  vec2 clip_upper_left;\
\n 	TButton Button;\
\n 	vec2 Pos;\
\n 	vec2 WorldPos;\
\n 	func extern EnableClip(vec2 lower_right,vec2 upper_left);\
\n 	func extern DisableClip;\
\n 	func extern SetPos(vec2 pos);\
\n }";


enum TBaluMouseButton
{
	LEFT,
	MIDDLE,
	RIGHT
};

enum TBaluEngineVirtKey
{
	BVK_Backspace=0,
	BVK_Tab,
	BVK_Enter,
	BVK_LShift,
	BVK_RShift,
	BVK_LCtrl,
	BVK_RCtrl,
	BVK_LAlt,
	BVK_RAlt,
	BVK_Pause,
	BVK_CapsLock,
	BVK_Escape,
	BVK_Space,
	BVK_PageUp,
	BVK_PageDown,
	BVK_End,
	BVK_Home,
	BVK_Left,
	BVK_Up,
	BVK_Right,
	BVK_Down,
	BVK_PrintScreen,
	BVK_Insert,
	BVK_Delete,
	BVK_NumPad0,
	BVK_NumPad1,
	BVK_NumPad2,
	BVK_NumPad3,
	BVK_NumPad4,
	BVK_NumPad5,
	BVK_NumPad6,
	BVK_NumPad7,
	BVK_NumPad8,
	BVK_NumPad9,
	BVK_Multiply,
	BVK_Add,
	BVK_Substract,
	BVK_Divide,
	BVK_F1,
	BVK_F2,
	BVK_F3,
	BVK_F4,
	BVK_F5,
	BVK_F6,
	BVK_F7,
	BVK_F8,
	BVK_F9,
	BVK_F10,
	BVK_F11,
	BVK_F12,
	BVK_NumLock,
	BVK_ScrollLock,
	BVK_MAX
};

const int WinVirtKey[]=
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

inline int ToBaluChar(char key)
{
	if(IsIn(key,'A','Z'))return key;
	if(IsIn(key,'0','9'))return key;
	switch((unsigned char)key)
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

inline int ToBaluSpecKey(int key)
{
	assert(WinVirtKey[BVK_MAX]==-1);//размер должен быть одинаковым
	for(int i=0;i<=BVK_MAX;i++)
		if(key==WinVirtKey[i])return i;
	return -1;
}

struct TBaluKeyboard
{
	friend class TBaluEngine;
private:
	TBaluEngine* engine;
	TVirtualMachine::TStaticArr<256,int> chars;
	TVirtualMachine::TStaticArr<BVK_MAX,int> special;
public:
	BSCRIPT_METHOD1(int,TBaluKeyboard,PressedChar,char,key)
	{
		if(IsIn(key,'A','Z')||IsIn(key,'0','9')||
			key==':'||
			key=='+'||
			key==','||
			key=='-'||
			key=='.'||
			key=='?'||
			key=='~'||
			key=='{'||
			key=='|'||
			key=='}'||
			key=='"')return chars[(unsigned char)key]&1;
		throw "TBaluKeyboard.PressedChar Unknown char";
	}
	BSCRIPT_METHOD1(int,TBaluKeyboard,PressedVirtKey,int,virt_key)
	{
		if(IsIn(virt_key,0,BVK_MAX-1))return special[virt_key]&128;
		throw "TBaluKeyboard.PressedVirtKey Unknown key";
	}
	BSCRIPT_METHOD1(int,TBaluKeyboard,Toggled,int,virt_key)
	{
		if(IsIn(virt_key,0,BVK_MAX-1))return special[virt_key]&1;
		throw "TBaluKeyboard.Toggled Unknown key";
	}
	void static LinkExternMethods(TVector<TExternMethod>& methods)
	{
		methods.Push(TExternMethod(PressedChar,	"func extern TGame.TKeyboard.Pressed(char key):bool)"));
		methods.Push(TExternMethod(PressedVirtKey,"func extern TGame.TKeyboard.Pressed(TVirtKey key):bool"));
		methods.Push(TExternMethod(Toggled,		"func extern TGame.TKeyboard.Toggled(TVirtKey key):bool"));
	}
};

static const char* script_keyboard="\
\n enum TVirtKey\
\n {\
\n Backspace,\
\n Tab,\
\n Enter,\
\n LShift,\
\n RShift,\
\n LCtrl,\
\n RCtrl,\
\n LAlt,\
\n RAlt,\
\n Pause,\
\n CapsLock,\
\n Escape,\
\n Space,\
\n PageUp,\
\n PageDown,\
\n End,\
\n Home,\
\n Left,\
\n Up,\
\n Right,\
\n Down,\
\n PrintScreen,\
\n Insert,\
\n Delete,\
\n NumPad0,\
\n NumPad1,\
\n NumPad2,\
\n NumPad3,\
\n NumPad4,\
\n NumPad5,\
\n NumPad6,\
\n NumPad7,\
\n NumPad8,\
\n NumPad9,\
\n Multiply,\
\n Add,\
\n Substract,\
\n Divide,\
\n F1,\
\n F2,\
\n F3,\
\n F4,\
\n F5,\
\n F6,\
\n F7,\
\n F8,\
\n F9,\
\n F10,\
\n F11,\
\n F12,\
\n NumLock,\
\n ScrollLock\
\n }\
\n class TKey\
\n {\
\n private:\
\n int key;\
\n public:\
\n func extern IsChar:bool;\
\n func extern IsSpecial:bool;\
\n }\
\n class TKeyboard\
\n {\
\n private:\
\n  int engine;\
\n	int[256] chars;\
\n	int[52] special;\
\n public:\
\n func extern Pressed(char key):bool;\
\n func extern Pressed(TVirtKey key):bool;\
\n func extern Toggled(TVirtKey key):bool;\
\n }";



struct TBaluTime
{
	TBaluEngine* engine;
	float fps_limit;
	float Current;
	float Step;
	float FPS;
	BSCRIPT_VOID_METHOD1(TBaluTime,LimitFPS,float,max_fps)
	{
		fps_limit=max_fps;
	}
	void static LinkExternMethods(TVector<TExternMethod>& methods)
	{
		methods.Push(TExternMethod(LimitFPS,	"func extern TGame.TTime.LimitFPS(float max_fps)"));
	}
};

static const char* script_time="\
\n class TTime\
\n {\
\n private:\
\n 	int engine;\
\n  float fps_limit;\
\n readonly:\
\n 	float Current;\
\n 	float Step;\
\n 	float FPS;\
\n 	func extern LimitFPS(float max_fps);\
\n }";



struct TBaluScreen
{
	TBaluEngine* engine;
	TVec2 Pos;
	float Angle;
	TVec2 Size;
	BSCRIPT_VOID_METHOD2(TBaluScreen,AssignOp,TBaluScreen*,left,TBaluScreen*,right)
	{	
	}
	BSCRIPT_VOID_METHOD1(TBaluScreen,SetPos,TVec2,use_pos);
	BSCRIPT_VOID_METHOD1(TBaluScreen,SetSize,TVec2,use_size);
	void static LinkExternMethods(TVector<TExternMethod>& methods)
	{
		methods.Push(TExternMethod(SetPos,	"func extern TGame.TScreen.SetPos(vec2 pos)"));
		methods.Push(TExternMethod(SetSize,	"func extern TGame.TScreen.SetSize(vec2 pos)"));
	}
};

static const char* script_screen="\
\n class TScreen\
\n {\
\n int engine;\
\n readonly:\
\n 	vec2  Pos;\
\n 	float Angle;\
\n 	vec2 Size;\
\n 	operator extern static =(TScreen& left, TScreen right);\
\n 	func extern SetPos(vec2 pos);\
\n 	//func extern SetAngle(float angle);\
\n 	func extern SetSize(vec2 size);\
\n 	func extern ScreenToWorld(vec2 screen_pos):vec2;\
\n 	func extern WorldToScreen(vec2 world_pos):vec2;\
\n 	constr {engine=0;}\
\n }";



static const char* script_texture="\
\n class TTexture\
\n {\
\n private:\
\n 	int id;\
\n public:\
\n 	constr \
\n 	{\
\n 		id=0;\
\n 	}\
\n }";


struct TBaluMaterial
{
	enum TBlendMode
	{
		BM_NONE,
		BM_ALPHA_BLEND
	};
	TTextureId texture;
	TBlendMode blend_mode;
	TVec4 color;
	void static LinkExternMethods(TVector<TExternMethod>& methods)
	{
	}
};

static const char* script_material="\
\n class TColor\
\n {\
\n float r,g,b,a;\
\n }\
\n class TMaterial\
\n {\
\n 	TTexture texture;\
\n 	int blend_mode;\
\n 	TColor color;\
\n }";


struct TBaluShape
{
	friend class TBaluEngine;
	enum TFigureType
	{
		FT_NONE=0,
		FT_BOX=1,
		FT_CIRCLE=2,
		FT_POLYGON=3
	};	
	b2Body* body;
	b2Shape* shape;
	TFigureType type;
	float density;
	//union
	//{
	TVertices vertices;
	int vertex_count;
	float radius;
	float box_size_x;
	float box_size_y;
	//};
	int shape_id;

	void UpdatePhysShape()
	{
		if(body!=NULL)
		{
			switch(type)
			{
			case TBaluShape::FT_CIRCLE:
				{		
					b2CircleDef circle;
					circle.radius=radius;
					circle.density=density;
					body->CreateShape(&circle);
					body->SetMassFromShapes();
				}
				break;
			case TBaluShape::FT_POLYGON:
				{			
					b2PolygonDef poly;
					poly.density=density;
					poly.vertexCount=vertex_count;
					for(int i=0;i<vertex_count;i++)
						poly.vertices[i].Set(vertices[i][0],vertices[i][0]);
					body->CreateShape(&poly);
				}
				break;
			case TBaluShape::FT_BOX:
				{
					b2PolygonDef poly;
					poly.density=density;
					poly.SetAsBox(box_size_x,box_size_y);
					if(body->GetShapeList()!=NULL)
					{
						b2Shape* s=body->GetShapeList();
						body->DestroyShape(s);
					}
					body->CreateShape(&poly);	
				}
				break;
			}
			body->SetMassFromShapes();
		}
	}
	BSCRIPT_VOID_METHOD2(TBaluShape,SetAsBox,TVec2,use_box_size,float,use_density)
	{
		type=FT_BOX;
		density=use_density;
		box_size_x=use_box_size[0];
		box_size_y=use_box_size[1];
		UpdatePhysShape();
	}
	BSCRIPT_VOID_METHOD2(TBaluShape,SetAsCircle,float,use_radius,float,use_density)
	{
		type=FT_CIRCLE;
		density=use_density;
		radius=use_radius;
		UpdatePhysShape();
	}
	BSCRIPT_VOID_METHOD3(TBaluShape,SetAsPoly,TVertices,use_vertices,int,use_vertex_count,float,use_density)
	{
		type=FT_POLYGON;
		density=use_density;
		vertex_count=use_vertex_count;
		for(int i=0;i<use_vertex_count;i++)
			vertices[i]=use_vertices[i];
		UpdatePhysShape();
	}
	void Init()
	{
		body=0;
		shape=0;
		type=FT_NONE;
		density=0;
		radius=0.01f;
		shape_id=-1;
		vertex_count=0;
	}
	TBaluShape()
	{
		Init();
	}
	void static Constr(int*& stack,int* first_param,int* _obj)
	{
		((TBaluShape*)_obj)->Init();
	}
	void static LinkExternMethods(TVector<TExternMethod>& methods)
	{
		methods.Push(TExternMethod(SetAsBox,	"func   extern TGame.TShape.SetAsBox(vec2 size,float density)"));
		methods.Push(TExternMethod(SetAsPoly,"func   extern TGame.TShape.SetAsPoly(vec2[8] vertices,int count,float density)"));
		methods.Push(TExternMethod(Constr,	"constr extern TGame.TShape"));
	}
};

static const char* script_shape="\
\n class TShape\
\n {\
\n 	private:\
\n 	int body;\
\n 	int shape;//pointer used by external methods\
\n 	readonly:\
\n 	int type;\
\n	float density;\
\n 	vec2[8] vertices;\
\n 	int vertex_count;\
\n 	float radius;\
\n	vec2 box_size;\
\n	int shape_id;\
\n 	public:\
\n 	constr extern;\
\n 	func extern SetAsBox(vec2 size,float density); \
\n 	func extern SetAsPoly(vec2[8] vertices,int count,float density); \
\n }";


struct TBaluBody
{
	friend class TBaluEngine;
	enum TFigureType
	{
		FT_NONE=0,
		FT_BOX=1,
		FT_CIRCLE=2,
		FT_POLYGON=3
	};	
	b2World* world;
	b2Body* body;
	TVirtualMachine::TDynArr shapes;
	BSCRIPT_VOID_METHOD(TBaluBody,Constr)
	{
	}
	BSCRIPT_VOID_METHOD1(TBaluBody,CopyConstr,TBaluBody*,copy_from)
	{
	}
	BSCRIPT_VOID_METHOD(TBaluBody,Destr)
	{
	}
	void AddShape(const TBaluShape& shape)
	{
	}
	BSCRIPT_VOID_METHOD2(TBaluBody,Add,TBaluShape*,shape,int*,shape_id)
	{
	}
	BSCRIPT_VOID_METHOD1(TBaluBody,Erase,int,shape_id)
	{
	}
	void static OperatorPlusAssign(int*& stack,int* first_param,int* _obj)
	{
		((TBaluBody*)first_param)->AddShape(*(TBaluShape*)(first_param+1));
	}
	void static LinkExternMethods(TVector<TExternMethod>& methods)
	{
		methods.Push(TExternMethod(Constr,				"constr extern TGame.TBody"));
		methods.Push(TExternMethod(CopyConstr,			"constr extern TGame.TBody(TBody& copy_from)"));
		methods.Push(TExternMethod(Destr,				"destr extern TGame.TBody"));
		methods.Push(TExternMethod(OperatorPlusAssign,	"operator extern static TGame.TBody.+=(TBody& body,TShape shape)"));
		methods.Push(TExternMethod(Add,					"func extern TGame.TBody.Push(TShape& shape,int& shape_id)"));
		methods.Push(TExternMethod(Erase,				"func extern TGame.TBody.Erase(int shape_id)"));
	}
};

static const char* script_body	="\
\n class TBody\
\n {\
\n 	private:\
\n 	int phys_world;//pointer used by external methods\
\n 	int phys_body;//pointer used by external methods\
\n 	TShape[] shapes;\
\n 	readonly:\
\n 	constr extern;\
\n 	destr extern;\
\n 	constr extern (TBody& copy_from);\
\n 	operator extern static +=(TBody& body,TShape shape);\
\n 	func extern Push(TShape& shape,int& shape_id);\
\n 	func extern Erase(int shape_id);\
\n 	readonly:\
\n 	float Mass,I;\
\n 	bool IsBullet,IsStatic,IsDynamic;\
\n }";


struct TBaluSprite
{
	TBaluShape shape;
	TBaluMaterial material;
	TVec2 size;
	float local_angle;
	TVec2 local_pos;
	float z_bias;
	void static LinkExternMethods(TVector<TExternMethod>& methods)
	{
	}
};

static const char* script_sprite="\
\n class TSprite\
\n {\
\n 	TShape shape;\
\n 	TMaterial material;\
\n 	vec2 size;\
\n 	float local_angle;\
\n 	vec2 local_pos;\
\n 	float z_bias;\
\n }";

class TBaluClass;
struct TBaluInstance
{
	TBaluClass* class_pointer;
	TVec2 pos;
	float angle;
	TBaluSprite sprite;
	void static LinkExternMethods(TVector<TExternMethod>& methods)
	{
	}
};

static const char* script_instance="\
\n class TInstance\
\n {\
\n 	int class_pointer;\
\n 	vec2 pos;\
\n 	float angle;\
\n 	TSprite sprite;\
\n 	constr\
\n 	{\
\n 		class_pointer=0;\
\n 		//pos=vec2(0.0,0.0);\
\n 		angle=0.0;\
\n 	}\
\n }";

static const char* script_global_vars="\
\n TMouse static Mouse;\
\n TKeyboard static Keyboard;\
\n TScreen static Screen;\
\n TTime static Time;";






