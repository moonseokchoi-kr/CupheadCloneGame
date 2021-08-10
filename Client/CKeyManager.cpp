#include "pch.h"
#include "CKeyManager.h"
#include "CCore.h"
int g_arrVK[(int)KEY::LAST] =
{
	VK_UP,// 	UP,
	VK_DOWN,// 	DOWN,
	VK_LEFT,// 	LEFT,
	VK_RIGHT,// 	RIGHT,

	'Q',// 	Q,
	'W',// 	W,
	'E',// 	E,
	'R',// 	R,
	'T',// 	T,
	'Y',// 	Y,
	'U',// 	U,
	'I',// 	I,
	'O',// 	O,
	'P',// 	P,
	'A',// 	A,
	'S',// 	S,
	'D',// 	D,
	'F',// 	F,
	'G',// 	G,
	'H',// 	H,
	'Z',// 	Z,
	'X',// 	X,
	'C',// 	C,
	'V',// 	V,
	'B',// 	B,

	VK_MENU,// 	ALT,
	VK_LCONTROL,// 	CTRL,
	VK_LSHIFT,// 	LSHIFT,
	VK_SPACE,// 	SPACE,
	VK_RETURN,// 	ENTER,
	VK_DELETE,//DELETE
	VK_ESCAPE,// 	ESC,


	WM_MOUSEMOVE,// 	MOUSE_MOVE,
	VK_LBUTTON,// 	MOUSE_LBUTTON,
	VK_RBUTTON// 	MOUSE_RBUTTON,

	// 	LAST,
};




CKeyManager::CKeyManager()
{

}

CKeyManager::~CKeyManager()
{

}

void CKeyManager::Init()
{
	for (int i = 0; i <(int) KEY::LAST; ++i)
	{
		m_vecKey.push_back(tKeyInfo{ KEY_STATE::NONE, false });
	}
}

void CKeyManager::Update()
{
	//창이 여러개 띄워질때 현재 메인윈도우가 맞는지 확인하여 처리
	//HWND hWnd = CCore::GetInst()->GetMainHwnd();
	HWND hWnd = GetFocus();

	if (nullptr != hWnd)
	{
		for (int i = 0; i < (int)KEY::LAST; ++i)
		{
			//키가 눌려있다.
			if (GetAsyncKeyState(g_arrVK[i]) & 0x8000)
			{
				if (m_vecKey[i].bPrevPush)
				{
					//계속 누르고있다.
					m_vecKey[i].state = KEY_STATE::HOLD;
				}
				else
				{
					//누르고있지않다.
					m_vecKey[i].state = KEY_STATE::TAP;
				}
				m_vecKey[i].bPrevPush = true;
			}
			//키가 안눌려있다.
			else
			{
				if (m_vecKey[i].bPrevPush)
				{
					//누르고 있다 뗏다
					m_vecKey[i].state = KEY_STATE::AWAY;
				}
				else
				{
					//누른적이 없다
					m_vecKey[i].state = KEY_STATE::NONE;
				}
				m_vecKey[i].bPrevPush = false;
			}
		}

		POINT ptPos = {};
		GetCursorPos(&ptPos);
		ScreenToClient(CCore::GetInst()->GetMainHwnd(), &ptPos);
		m_currentMousePos = Vec2((float)ptPos.x, (float)ptPos.y);
	}
	else
	{
		for (int i = 0; i < (UINT)KEY::LAST; ++i)
		{
			m_vecKey[i].bPrevPush = false;
			if (KEY_STATE::TAP == m_vecKey[i].state || KEY_STATE::HOLD == m_vecKey[i].state)
			{
				m_vecKey[i].state = KEY_STATE::AWAY;
			}
			else if (KEY_STATE::AWAY == m_vecKey[i].state)
			{
				m_vecKey[i].state = KEY_STATE::NONE;
			}
		}
	}
}
