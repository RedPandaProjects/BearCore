#include "BearCore.hpp"
#ifdef WINDOWS
static BearCore::BearMap<int32, int32> LToWinowsKey;
BearCore::BearMap<int32, int32> GFromWinowsKey;
struct Initializer 
{
	Initializer()
	{
		RegisterWindowsKey('A',BearCore::BearInput::KeyA);
		RegisterWindowsKey('B',BearCore::BearInput::KeyB);
		RegisterWindowsKey('C',BearCore::BearInput::KeyC);
		RegisterWindowsKey('D',BearCore::BearInput::KeyD);
		RegisterWindowsKey('E',BearCore::BearInput::KeyE);
		RegisterWindowsKey('F',BearCore::BearInput::KeyF);
		RegisterWindowsKey('G',BearCore::BearInput::KeyG);
		RegisterWindowsKey('H',BearCore::BearInput::KeyH);
		RegisterWindowsKey('I',BearCore::BearInput::KeyI);
		RegisterWindowsKey('J',BearCore::BearInput::KeyJ);
		RegisterWindowsKey('K',BearCore::BearInput::KeyK);
		RegisterWindowsKey('L',BearCore::BearInput::KeyL);
		RegisterWindowsKey('M',BearCore::BearInput::KeyM);
		RegisterWindowsKey('N',BearCore::BearInput::KeyN);
		RegisterWindowsKey('O',BearCore::BearInput::KeyO);
		RegisterWindowsKey('P',BearCore::BearInput::KeyP);
		RegisterWindowsKey('Q',BearCore::BearInput::KeyQ);
		RegisterWindowsKey('R',BearCore::BearInput::KeyR);
		RegisterWindowsKey('S',BearCore::BearInput::KeyS);
		RegisterWindowsKey('T',BearCore::BearInput::KeyT);
		RegisterWindowsKey('U',BearCore::BearInput::KeyU);
		RegisterWindowsKey('V',BearCore::BearInput::KeyV);
		RegisterWindowsKey('W',BearCore::BearInput::KeyW);
		RegisterWindowsKey('X',BearCore::BearInput::KeyX);
		RegisterWindowsKey('Y',BearCore::BearInput::KeyY);
		RegisterWindowsKey('Z',BearCore::BearInput::KeyZ);
		RegisterWindowsKey('0',BearCore::BearInput::KeyNum0);
		RegisterWindowsKey('1',BearCore::BearInput::KeyNum1);
		RegisterWindowsKey('2',BearCore::BearInput::KeyNum2);
		RegisterWindowsKey('3',BearCore::BearInput::KeyNum3);
		RegisterWindowsKey('4',BearCore::BearInput::KeyNum4);
		RegisterWindowsKey('5',BearCore::BearInput::KeyNum5);
		RegisterWindowsKey('6',BearCore::BearInput::KeyNum6);
		RegisterWindowsKey('7',BearCore::BearInput::KeyNum7);
		RegisterWindowsKey('8',BearCore::BearInput::KeyNum8);
		RegisterWindowsKey('9',BearCore::BearInput::KeyNum9);
		RegisterWindowsKey(VK_ESCAPE,BearCore::BearInput::KeyEscape);
		RegisterWindowsKey(VK_LCONTROL,BearCore::BearInput::KeyLControl);
		RegisterWindowsKey(VK_LSHIFT,BearCore::BearInput::KeyLShift);
		RegisterWindowsKey(VK_LMENU,BearCore::BearInput::KeyLAlt);
		RegisterWindowsKey(VK_LWIN,BearCore::BearInput::KeyLSystem);
		RegisterWindowsKey(VK_RCONTROL,BearCore::BearInput::KeyRControl);
		RegisterWindowsKey(VK_RSHIFT,BearCore::BearInput::KeyRShift);
		RegisterWindowsKey(VK_RMENU,BearCore::BearInput::KeyRAlt);
		RegisterWindowsKey(VK_RWIN,BearCore::BearInput::KeyRSystem);
		RegisterWindowsKey(VK_APPS,BearCore::BearInput::KeyMenu);
		RegisterWindowsKey(VK_OEM_4,BearCore::BearInput::KeyLBracket);
		RegisterWindowsKey(VK_OEM_6,BearCore::BearInput::KeyRBracket);
		RegisterWindowsKey(VK_OEM_1,BearCore::BearInput::KeySemiColon);
		RegisterWindowsKey(VK_OEM_COMMA,BearCore::BearInput::KeyComma);
		RegisterWindowsKey(VK_OEM_PERIOD,BearCore::BearInput::KeyPeriod);
		RegisterWindowsKey(VK_OEM_7,BearCore::BearInput::KeyQuote);
		RegisterWindowsKey(VK_OEM_2,BearCore::BearInput::KeySlash);
		RegisterWindowsKey(VK_OEM_5,BearCore::BearInput::KeyBackSlash);
		RegisterWindowsKey(VK_OEM_3,BearCore::BearInput::KeyTilde);
		RegisterWindowsKey(VK_OEM_PLUS,BearCore::BearInput::KeyEqual);
		RegisterWindowsKey(VK_OEM_MINUS,BearCore::BearInput::KeyDash);
		RegisterWindowsKey(VK_SPACE,BearCore::BearInput::KeySpace);
		RegisterWindowsKey(VK_RETURN,BearCore::BearInput::KeyReturn);
		RegisterWindowsKey(VK_BACK,BearCore::BearInput::KeyBackSpace);
		RegisterWindowsKey(VK_TAB,BearCore::BearInput::KeyTab);
		RegisterWindowsKey(VK_PRIOR,BearCore::BearInput::KeyPageUp);
		RegisterWindowsKey(VK_NEXT,BearCore::BearInput::KeyPageDown);
		RegisterWindowsKey(VK_END,BearCore::BearInput::KeyEnd);
		RegisterWindowsKey(VK_HOME,BearCore::BearInput::KeyHome);
		RegisterWindowsKey(VK_INSERT,BearCore::BearInput::KeyInsert);
		RegisterWindowsKey(VK_DELETE,BearCore::BearInput::KeyDelete);
		RegisterWindowsKey(VK_ADD,BearCore::BearInput::KeyAdd);
		RegisterWindowsKey(VK_SUBTRACT,BearCore::BearInput::KeySubtract);
		RegisterWindowsKey(VK_MULTIPLY,BearCore::BearInput::KeyMultiply);
		RegisterWindowsKey(VK_DIVIDE,BearCore::BearInput::KeyDivide);
		RegisterWindowsKey(VK_LEFT,BearCore::BearInput::KeyLeft);
		RegisterWindowsKey(VK_RIGHT,BearCore::BearInput::KeyRight);
		RegisterWindowsKey(VK_UP,BearCore::BearInput::KeyUp);
		RegisterWindowsKey(VK_DOWN,BearCore::BearInput::KeyDown);
		RegisterWindowsKey(VK_NUMPAD0,BearCore::BearInput::KeyNumpad0);
		RegisterWindowsKey(VK_NUMPAD1,BearCore::BearInput::KeyNumpad1);
		RegisterWindowsKey(VK_NUMPAD2,BearCore::BearInput::KeyNumpad2);
		RegisterWindowsKey(VK_NUMPAD3,BearCore::BearInput::KeyNumpad3);
		RegisterWindowsKey(VK_NUMPAD4,BearCore::BearInput::KeyNumpad4);
		RegisterWindowsKey(VK_NUMPAD5,BearCore::BearInput::KeyNumpad5);
		RegisterWindowsKey(VK_NUMPAD6,BearCore::BearInput::KeyNumpad6);
		RegisterWindowsKey(VK_NUMPAD7,BearCore::BearInput::KeyNumpad7);
		RegisterWindowsKey(VK_NUMPAD8,BearCore::BearInput::KeyNumpad8);
		RegisterWindowsKey(VK_NUMPAD9,BearCore::BearInput::KeyNumpad9);
		RegisterWindowsKey(VK_F1,BearCore::BearInput::KeyF1);
		RegisterWindowsKey(VK_F2,BearCore::BearInput::KeyF2);
		RegisterWindowsKey(VK_F3,BearCore::BearInput::KeyF3);
		RegisterWindowsKey(VK_F4,BearCore::BearInput::KeyF4);
		RegisterWindowsKey(VK_F5,BearCore::BearInput::KeyF5);
		RegisterWindowsKey(VK_F6,BearCore::BearInput::KeyF6);
		RegisterWindowsKey(VK_F7,BearCore::BearInput::KeyF7);
		RegisterWindowsKey(VK_F8,BearCore::BearInput::KeyF8);
		RegisterWindowsKey(VK_F9,BearCore::BearInput::KeyF9);
		RegisterWindowsKey(VK_F10,BearCore::BearInput::KeyF10);
		RegisterWindowsKey(VK_F11,BearCore::BearInput::KeyF11);
		RegisterWindowsKey(VK_F12,BearCore::BearInput::KeyF12);
		RegisterWindowsKey(VK_PAUSE,BearCore::BearInput::KeyPause);
		RegisterWindowsKey(VK_LBUTTON,BearCore::BearInput::KeyMouseLeft);
		RegisterWindowsKey(VK_RBUTTON,BearCore::BearInput::KeyMouseRight);
		RegisterWindowsKey(VK_MBUTTON,BearCore::BearInput::KeyMouseMiddle);
	}
	void RegisterWindowsKey(int32 win, BearCore::BearInput::Key key)
	{
		LToWinowsKey.insert(key, win);
		GFromWinowsKey.insert(win,key);
	}
	~Initializer()
	{

	}
	 
};
Initializer Initializer;
#endif
bool BearCore::BearInput::KeyState(Key key)
{
#ifdef WINDOWS
	auto item = LToWinowsKey.find(key);
	if (item != LToWinowsKey.end())
		return ::GetKeyState(item->second) & 0x8000;
#endif
	return false;
}

BearCore::BearVector2<float> BearCore::BearInput::GetMousePosition()
{
	POINT P;
	GetCursorPos(&P);
	return BearCore::BearFVector2(static_cast<float>(P.x), static_cast<float>(P.y));
}

void BearCore::BearInput::SetMousePosition(const BearCore::BearVector2<float>& position)
{
	POINT point = { static_cast<LONG>(position.x),  static_cast<LONG>(position.y) };
	SetCursorPos(static_cast<LONG>(position.x), static_cast<LONG>(position.y));
}
