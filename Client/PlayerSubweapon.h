#pragma once
#include "CObject.h"

class CPlayer;
class CCollider;

class PlayerSubweapon :
    public CObject
{
public:
    PlayerSubweapon();
    ~PlayerSubweapon();
public:
    virtual void Update();
    virtual void Render(HDC _dc);
    virtual void FinalUpdate();
    virtual void OnCollisionEnter(CCollider* _col);
    CLONE(PlayerSubweapon)
private:
    virtual void fire();
private:
    CPlayer* m_owner;

    float m_cooltime;
    UINT m_weaponMode;
    float m_acc;
    friend class CPlayer;
};

