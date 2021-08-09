#pragma once
#include "CUI.h"


/// <summary>
/// ui���� �г��� ����� ����ϴ� ui
/// 
/// �ۼ��� : �ֹ���
/// 
/// ����
/// 1.0 - �г� ui �ۼ� 2021-07-22
/// </summary>
class CPanelUI :
    public CUI
{
public:
	CPanelUI(bool _cameraAffeted);
	~CPanelUI();
public:

	virtual void MouseOn();
	virtual void MouseLButtonDown();
	virtual void MouseLButtonUp();
	virtual void MouseLButtonClicked();

	CLONE(CPanelUI);
private:

	Vec2 m_curMousePos;
	Vec2 m_dragStart;
};

