#pragma once
#include "CPanelUI.h"
enum class MENU_TYPE
{
	START,
	PAUSE,
};
class CBackGround;
class CMenuPanel :
    public CPanelUI
{
public:
	CMenuPanel();
	~CMenuPanel();
	CLONE(CMenuPanel);
public:
	
	virtual void Render(HDC _dc);
	virtual void MouseOn();
	virtual void MouseLButtonDown();
	virtual void MouseLButtonUp();
	virtual void MouseLButtonClicked();

public:
	void SetTex(BACKGROUND_TYPE _type);
	void UsePauseUI();
	bool IsShow() { return m_isShow; }
	void SetShow(bool _b) { m_isShow = _b; }
private:
	CBackGround* m_backGround;
	CTexture* m_tex;
	MENU_TYPE m_menuType;
	bool m_isShow;
};

