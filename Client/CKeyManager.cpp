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
	//â�� ������ ������� ���� ���������찡 �´��� Ȯ���Ͽ� ó��
	//HWND hWnd = CCore::GetInst()->GetMainHwnd();
	HWND hWnd = GetFocus();

	if (nullptr != hWnd)
	{
		for (int i = 0; i < (int)KEY::LAST; ++i)
		{
			//Ű�� �����ִ�.
			if (GetAsyncKeyState(g_arrVK[i]) & 0x8000)
			{
				if (m_vecKey[i].bPrevPush)
				{
					//��� �������ִ�.
					m_vecKey[i].state = KEY_STATE::HOLD;
				}
				else
				{
					//�����������ʴ�.
					m_vecKey[i].state = KEY_STATE::TAP;
				}
				m_vecKey[i].bPrevPush = true;
			}
			//Ű�� �ȴ����ִ�.
			else
			{
				if (m_vecKey[i].bPrevPush)
				{
					//������ �ִ� �´�
					m_vecKey[i].state = KEY_STATE::AWAY;
				}
				else
				{
					//�������� ����
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
