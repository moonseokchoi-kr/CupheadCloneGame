#pragma once
#include "CUI.h"

class CPlayerAttackBox;

class CPlayerWeaponUI :
    public CUI
{
public:
    CPlayerWeaponUI();
    ~CPlayerWeaponUI();
    CLONE(CPlayerWeaponUI);
public:
    virtual void Update();
    virtual void Render(HDC _dc);
public:
    bool IsActive() { return m_isActive; }
    void SetActive(bool _b) { m_isActive = _b; }
private:
    CPlayerAttackBox* m_owner;
    BULLET_TYPE m_bulletType;
    float m_accTime;
    float m_meaningTime;
    bool m_isActive;
    bool m_toggle;
    friend class CPlayerAttackBox;
};

