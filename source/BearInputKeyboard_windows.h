using namespace BearCore;
bool BearInputKeyboard::IsPreesKey(Key k) 
{
	int vkey = 0;
	switch (k)
	{
	default:                   vkey = 0;             break;
	case BearInputKeyboard::A:          vkey = 'A';           break;
	case BearInputKeyboard::B:          vkey = 'B';           break;
	case BearInputKeyboard::C:          vkey = 'C';           break;
	case BearInputKeyboard::D:          vkey = 'D';           break;
	case BearInputKeyboard::E:          vkey = 'E';           break;
	case BearInputKeyboard::F:          vkey = 'F';           break;
	case BearInputKeyboard::G:          vkey = 'G';           break;
	case BearInputKeyboard::H:          vkey = 'H';           break;
	case BearInputKeyboard::I:          vkey = 'I';           break;
	case BearInputKeyboard::J:          vkey = 'J';           break;
	case BearInputKeyboard::K:          vkey = 'K';           break;
	case BearInputKeyboard::L:          vkey = 'L';           break;
	case BearInputKeyboard::M:          vkey = 'M';           break;
	case BearInputKeyboard::N:          vkey = 'N';           break;
	case BearInputKeyboard::O:          vkey = 'O';           break;
	case BearInputKeyboard::P:          vkey = 'P';           break;
	case BearInputKeyboard::Q:          vkey = 'Q';           break;
	case BearInputKeyboard::R:          vkey = 'R';           break;
	case BearInputKeyboard::S:          vkey = 'S';           break;
	case BearInputKeyboard::T:          vkey = 'T';           break;
	case BearInputKeyboard::U:          vkey = 'U';           break;
	case BearInputKeyboard::V:          vkey = 'V';           break;
	case BearInputKeyboard::W:          vkey = 'W';           break;
	case BearInputKeyboard::X:          vkey = 'X';           break;
	case BearInputKeyboard::Y:          vkey = 'Y';           break;
	case BearInputKeyboard::Z:          vkey = 'Z';           break;
	case BearInputKeyboard::Num0:       vkey = '0';           break;
	case BearInputKeyboard::Num1:       vkey = '1';           break;
	case BearInputKeyboard::Num2:       vkey = '2';           break;
	case BearInputKeyboard::Num3:       vkey = '3';           break;
	case BearInputKeyboard::Num4:       vkey = '4';           break;
	case BearInputKeyboard::Num5:       vkey = '5';           break;
	case BearInputKeyboard::Num6:       vkey = '6';           break;
	case BearInputKeyboard::Num7:       vkey = '7';           break;
	case BearInputKeyboard::Num8:       vkey = '8';           break;
	case BearInputKeyboard::Num9:       vkey = '9';           break;
	case BearInputKeyboard::Escape:     vkey = VK_ESCAPE;     break;
	case BearInputKeyboard::LControl:   vkey = VK_LCONTROL;   break;
	case BearInputKeyboard::LShift:     vkey = VK_LSHIFT;     break;
	case BearInputKeyboard::LAlt:       vkey = VK_LMENU;      break;
	case BearInputKeyboard::LSystem:    vkey = VK_LWIN;       break;
	case BearInputKeyboard::RControl:   vkey = VK_RCONTROL;   break;
	case BearInputKeyboard::RShift:     vkey = VK_RSHIFT;     break;
	case BearInputKeyboard::RAlt:       vkey = VK_RMENU;      break;
	case BearInputKeyboard::RSystem:    vkey = VK_RWIN;       break;
	case BearInputKeyboard::Menu:       vkey = VK_APPS;       break;
	case BearInputKeyboard::LBracket:   vkey = VK_OEM_4;      break;
	case BearInputKeyboard::RBracket:   vkey = VK_OEM_6;      break;
	case BearInputKeyboard::SemiColon:  vkey = VK_OEM_1;      break;
	case BearInputKeyboard::Comma:      vkey = VK_OEM_COMMA;  break;
	case BearInputKeyboard::Period:     vkey = VK_OEM_PERIOD; break;
	case BearInputKeyboard::Quote:      vkey = VK_OEM_7;      break;
	case BearInputKeyboard::Slash:      vkey = VK_OEM_2;      break;
	case BearInputKeyboard::BackSlash:  vkey = VK_OEM_5;      break;
	case BearInputKeyboard::Tilde:      vkey = VK_OEM_3;      break;
	case BearInputKeyboard::Equal:      vkey = VK_OEM_PLUS;   break;
	case BearInputKeyboard::Dash:       vkey = VK_OEM_MINUS;  break;
	case BearInputKeyboard::Space:      vkey = VK_SPACE;      break;
	case BearInputKeyboard::Return:     vkey = VK_RETURN;     break;
	case BearInputKeyboard::BackSpace:  vkey = VK_BACK;       break;
	case BearInputKeyboard::Tab:        vkey = VK_TAB;        break;
	case BearInputKeyboard::PageUp:     vkey = VK_PRIOR;      break;
	case BearInputKeyboard::PageDown:   vkey = VK_NEXT;       break;
	case BearInputKeyboard::End:        vkey = VK_END;        break;
	case BearInputKeyboard::Home:       vkey = VK_HOME;       break;
	case BearInputKeyboard::Insert:     vkey = VK_INSERT;     break;
	case BearInputKeyboard::Delete:     vkey = VK_DELETE;     break;
	case BearInputKeyboard::Add:        vkey = VK_ADD;        break;
	case BearInputKeyboard::Subtract:   vkey = VK_SUBTRACT;   break;
	case BearInputKeyboard::Multiply:   vkey = VK_MULTIPLY;   break;
	case BearInputKeyboard::Divide:     vkey = VK_DIVIDE;     break;
	case BearInputKeyboard::Left:       vkey = VK_LEFT;       break;
	case BearInputKeyboard::Right:      vkey = VK_RIGHT;      break;
	case BearInputKeyboard::Up:         vkey = VK_UP;         break;
	case BearInputKeyboard::Down:       vkey = VK_DOWN;       break;
	case BearInputKeyboard::Numpad0:    vkey = VK_NUMPAD0;    break;
	case BearInputKeyboard::Numpad1:    vkey = VK_NUMPAD1;    break;
	case BearInputKeyboard::Numpad2:    vkey = VK_NUMPAD2;    break;
	case BearInputKeyboard::Numpad3:    vkey = VK_NUMPAD3;    break;
	case BearInputKeyboard::Numpad4:    vkey = VK_NUMPAD4;    break;
	case BearInputKeyboard::Numpad5:    vkey = VK_NUMPAD5;    break;
	case BearInputKeyboard::Numpad6:    vkey = VK_NUMPAD6;    break;
	case BearInputKeyboard::Numpad7:    vkey = VK_NUMPAD7;    break;
	case BearInputKeyboard::Numpad8:    vkey = VK_NUMPAD8;    break;
	case BearInputKeyboard::Numpad9:    vkey = VK_NUMPAD9;    break;
	case BearInputKeyboard::F1:         vkey = VK_F1;         break;
	case BearInputKeyboard::F2:         vkey = VK_F2;         break;
	case BearInputKeyboard::F3:         vkey = VK_F3;         break;
	case BearInputKeyboard::F4:         vkey = VK_F4;         break;
	case BearInputKeyboard::F5:         vkey = VK_F5;         break;
	case BearInputKeyboard::F6:         vkey = VK_F6;         break;
	case BearInputKeyboard::F7:         vkey = VK_F7;         break;
	case BearInputKeyboard::F8:         vkey = VK_F8;         break;
	case BearInputKeyboard::F9:         vkey = VK_F9;          break;
	case BearInputKeyboard::F10:        vkey = VK_F10;        break;
	case BearInputKeyboard::F11:        vkey = VK_F11;        break;
	case BearInputKeyboard::F12:        vkey = VK_F12;        break;
	case BearInputKeyboard::F13:        vkey = VK_F13;        break;
	case BearInputKeyboard::F14:        vkey = VK_F14;        break;
	case BearInputKeyboard::F15:        vkey = VK_F15;        break;
	case BearInputKeyboard::Pause:      vkey = VK_PAUSE;      break;
	}

	return (GetAsyncKeyState(vkey) & 0x8000) != 0;
}
bool BearInputKeyboard::IsMouseButtonPress(MouseKey k) 
{
	int vkey = 0;
	switch (k)
	{
	case MouseLeft:     vkey = GetSystemMetrics(SM_SWAPBUTTON) ? VK_RBUTTON : VK_LBUTTON; break;
	case MouseRight:    vkey = GetSystemMetrics(SM_SWAPBUTTON) ? VK_LBUTTON : VK_RBUTTON; break;
	case MouseMiddle:   vkey = VK_MBUTTON;  break;
	case MouseXButton1: vkey = VK_XBUTTON1; break;
	case MouseXButton2: vkey = VK_XBUTTON2; break;
	default:              vkey = 0;           break;
	}

	return (GetAsyncKeyState(vkey) & 0x8000) != 0;
}
BearVector2<uint32> BearInputKeyboard::GetMousePosition() 
{
	POINT point;
	GetCursorPos(&point);
	return BearVector2<uint32>(point.x, point.y);
}
void BearInputKeyboard::SetMousePosition(BearVector2<uint32> pos) 
{
	SetCursorPos(pos.x, pos.y);
}
