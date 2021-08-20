#pragma once
#include "CAttackBox.h"
class CCarrotBossAttackBox :
    public CAttackBox
{
public:
    CCarrotBossAttackBox();
    ~CCarrotBossAttackBox();
    CLONE(CCarrotBossAttackBox);
public:
    virtual void Update() override;
    // CAttackBox을(를) 통해 상속됨
    virtual void Fire() override;
    ATTACK_PATT GetCurrentPatt() { return m_currnetPatt; }
public:
    void ChangeAttack();

private:
    ATTACK_PATT m_currnetPatt;
    array<float, 6> m_missieX;
};

