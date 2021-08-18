#pragma once
#include "CUI.h"

class CGameObject;

class CTextUI :
    public CUI
{
public:
    CTextUI(bool _cameraAffeted);
    CLONE(CTextUI);
public:
    virtual void Update();
    virtual void Render(HDC _dc);

public:
    void SetText(const wstring& _str) { m_text = _str; };
    void SetMouseFollow(bool _b) { isMouseAttached = _b; }

private:
   wstring m_text;
   bool isMouseAttached;
};

