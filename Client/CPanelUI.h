#pragma once
#include "CUI.h"


/// <summary>
/// ui에서 패널의 기능을 담당하는 ui
/// 
/// 작성자 : 최문석
/// 
/// 버전
/// 1.0 - 패널 ui 작성 2021-07-22
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

