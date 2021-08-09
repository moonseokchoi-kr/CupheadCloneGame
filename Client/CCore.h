#pragma once
/// <summary>
/// �����ӿ�ũ�� ���� ������ ����ϴ� �Լ��� �����ӿ�ũ�� �������̴�
/// </summary>
/// 
/// �ۼ��� �ֹ���
/// 
/// 
/// 
/// ����:
/// 1.0- �⺻���� �ۼ� 2021-06-30
/// 1.1- GetMainHwnd�Լ� �߰� 2021-07-19
/// 1.2- menu��ŷ ����,  texture��� 2021-07-31
/// 1.3- Clear�Լ� ���� 2021-08-01

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
	HWND	m_hWnd;//�ý��� id
	POINT	m_ptResolution;//â �ػ�
	POINT	m_ptMonitorResolution;//������ػ�
	HDC		m_hDc; //�ȼ�����


	// ���ֻ���ϴ� GDI Object
	array<HBRUSH,(UINT)BRUSH_TYPE::END> m_brushs;
	array<HPEN, (UINT)PEN_TYPE::END>   m_pens;
	
	CTexture* m_memTex;
	HMENU	m_menu;
	

};

