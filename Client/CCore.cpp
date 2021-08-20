#include "pch.h"
#include "CCore.h"
#include "CObject.h"

#include "CTimeManager.h"
#include "CKeyManager.h"
#include "CSceneManager.h"
#include "CPathManager.h"
#include "CColliderManager.h"
#include "CUIManager.h"
#include "CCamera.h"
#include "CResourceManager.h"
#include "CGameObjectManager.h"
#include "CTexture.h"


#include "resource.h"
#include "SelectGDI.h"
CCore::CCore()
	:m_hDc(nullptr)
	, m_hWnd(nullptr)
	, m_ptMonitorResolution{}
	, m_ptResolution{}
	, m_memTex(nullptr)
	, m_menu{}
	, m_brushs{}
	, m_pens{}
{
}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDc);

	for (int i = 0; i < m_pens.size(); ++i)
	{
		DeleteObject(m_pens[i]);
	}
	DestroyMenu(m_menu);
}

int CCore::InitCore(HWND _hwnd, POINT _resolution)
{
	m_hWnd = _hwnd;
	m_ptResolution = _resolution;
	m_ptToolResolution = { 1600,960 };
	m_ptMonitorResolution = { GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN) };

	changeWindowSize(Vec2((float)m_ptResolution.x,(float)m_ptResolution.y), false);
	//DeviceContext설정
	m_hDc = GetDC(m_hWnd);
	m_menu = LoadMenu(nullptr, MAKEINTRESOURCEW(IDC_CLIENT));
	m_memTex = CResourceManager::GetInst()->CreateTexture(L"BackBuffer", m_ptToolResolution.x, m_ptToolResolution.y);
	
	CKeyManager::GetInst()->Init();
	CTimeManager::GetInst()->Init();
	CPathManager::GetInst()->Init();
	CCamera::GetInst()->Init();
	CSceneManager::GetInst()->Init();
	

	CreateBrushPen();
	
	return S_OK;
}

void CCore::Progress()
{
	//Manager Update
	CTimeManager::GetInst()->Update();
	CKeyManager::GetInst()->Update();
	CCamera::GetInst()->Update();
	CUIManager::GetInst()->Update();


	// ============
	// Scene Update
	// ============
	CSceneManager::GetInst()->Update();
	
	/// ==========
	/// 충돌체크
	/// ===========
	CColliderManager::GetInst()->Update();

	//이벤트 체크

	CGameObjectManager::GetInst()->Update();

	///	============
	///	 Rendering	
	/// ============
	/// 
	Clear();

 	CSceneManager::GetInst()->Render(m_memTex->GetDC());
	CCamera::GetInst()->Render(m_memTex->GetDC());

	BitBlt(m_hDc, 0, 0, m_ptResolution.x, m_ptResolution.y, m_memTex->GetDC(), 0, 0, SRCCOPY);

	SetWindowText(m_hWnd, CTimeManager::GetInst()->GetTitle());

	//이벤트 지연처리
	CEventManager::GetInst()->Update();
}

void CCore::CreateBrushPen()
{
	m_brushs[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	m_brushs[TYPE_NUMBER(BRUSH_TYPE::BLACK)] = (HBRUSH)GetStockObject(BLACK_BRUSH);
	m_pens[TYPE_NUMBER(PEN_TYPE::HOLLOW)] = (HPEN)GetStockObject(NULL_PEN);
	m_pens[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_pens[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0,255, 0));
	m_pens[TYPE_NUMBER(PEN_TYPE::GREEN_BOLD)] = CreatePen(PS_SOLID, 3, RGB(0, 255, 0));
	m_pens[TYPE_NUMBER(PEN_TYPE::RED_BOLD)] = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	m_pens[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	m_pens[(UINT)PEN_TYPE::BLUE_BOLD] = CreatePen(PS_SOLID, 3, RGB(0, 0, 255));
	m_pens[(UINT)PEN_TYPE::BLACK] = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	m_pens[(UINT)PEN_TYPE::WHITE] = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
}



void CCore::DockMenu()
{
	SetMenu(m_hWnd, m_menu);
	changeWindowSize(GetResolution(), true);
}

void CCore::DockMenu(Vec2 _resolution)
{
	SetMenu(m_hWnd, m_menu);
	m_ptResolution = {(int)_resolution.x, (int)_resolution.y};
	changeWindowSize(_resolution, true);
}

void CCore::UnDockMenu()
{
	SetMenu(m_hWnd, nullptr);
	changeWindowSize(Vec2(1280,768), false);
}

void CCore::changeWindowSize(Vec2 _resolution, bool _isDock)
{
	RECT rt = { 0,0,_resolution.x, _resolution.y };
	m_ptResolution = { (int)_resolution.x, (int)_resolution.y };
	//윈도우크기 계산
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, _isDock);
	//윈도우 창위치 설정, 크기설정
	SetWindowPos(m_hWnd, nullptr, m_ptMonitorResolution.x / 2 - _resolution.x / 2, m_ptMonitorResolution.y / 2 - _resolution.y / 2, rt.right - rt.left, rt.bottom - rt.top, 0);
}

void CCore::Clear()
{
	SelectGDI gdi(m_memTex->GetDC(), BRUSH_TYPE::BLACK);
	Rectangle(m_memTex->GetDC(), -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);
}



