#pragma once
/// <summary>
/// 프레임워크의 메인 로직을 담당하는 함수로 프레임워크의 시작점이다
/// </summary>
/// 
/// 작성자 최문석
/// 
/// 
/// 
/// 버전:
/// 1.0- 기본구조 작성 2021-06-30
/// 1.1- GetMainHwnd함수 추가 2021-07-19
/// 1.2- menu도킹 구현,  texture면경 2021-07-31
/// 1.3- Clear함수 구현 2021-08-01

class CTexture;

class CCore
{
	SINGLE(CCore);
public:
	int InitCore(HWND _hwnd, POINT _resolution);

	void Progress();

	void CreateBrushPen();
public:
	HDC GetMainDC() { return m_hDc; }
	HWND GetMainHwnd() { return m_hWnd; }
	Vec2 GetResolution() { return Vec2((int)m_ptResolution.x,(int)m_ptResolution.y); }
	HBRUSH GetBrush(BRUSH_TYPE _brushType) { return m_brushs[(UINT)_brushType]; }
	HPEN GetPen(PEN_TYPE _penType) { return m_pens[(UINT)_penType]; }

public:
	void DockMenu();
	void UnDockMenu();
	void Clear();
private:
	void changeWindowSize(Vec2 _resolution, bool _isDock);
	
private:
	HWND	m_hWnd;//시스템 id
	POINT	m_ptResolution;//창 해상도
	POINT	m_ptMonitorResolution;//모니터해상도
	HDC		m_hDc; //픽셀버퍼


	// 자주사용하는 GDI Object
	array<HBRUSH,(UINT)BRUSH_TYPE::END> m_brushs;
	array<HPEN, (UINT)PEN_TYPE::END>   m_pens;
	
	CTexture* m_memTex;
	HMENU	m_menu;
	

};

