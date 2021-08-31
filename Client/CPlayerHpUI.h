#pragma once
#include "CUI.h"
class CPlayer;
class CTexture;
class CPlayerHpUI :
    public CUI
{
public:
    CPlayerHpUI();
    ~CPlayerHpUI();
    CLONE(CPlayerHpUI);
public:
    virtual void Update();
    virtual void Render(HDC _dc);
private:
    CPlayer* m_owenr;
    int m_index;
    CTexture* m_tex;

    friend class CPlayer;
    
};

