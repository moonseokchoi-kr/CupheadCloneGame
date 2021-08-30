#pragma once
#include "CButtonUI.h"
class CMenuButtonUI :
    public CButtonUI
{
public:
    CMenuButtonUI();
    ~CMenuButtonUI();
    CLONE(CMenuButtonUI);
public:
    virtual void Render(HDC _dc);
public:
    void SetIndex(int _idx) { m_index = _idx; }
   
private:
    int m_index;
    int m_width;
    int m_heigth;
    CTexture* m_tex;
};

