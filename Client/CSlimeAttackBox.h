#pragma once
#include "CAttackBox.h"
class CSlimeAttackBox :
    public CAttackBox
{
public:
    CSlimeAttackBox();
    ~CSlimeAttackBox();
    CLONE(CSlimeAttackBox);
public:

    virtual void Update() override;
    // CAttackBox을(를) 통해 상속됨
    virtual void Fire() override;
    virtual void Render(HDC _dc) override;
public:
    Vec2 GetOffset() { return m_offset; }
    void SetOffset(Vec2 _v) { m_offset = _v; }
    ATTACK_PATT GetCurrentPatt() { return m_currentAttackPatt; }

public:
    Vec2 m_offset;
    float m_attackCount;
    ATTACK_PATT m_currentAttackPatt;
};

