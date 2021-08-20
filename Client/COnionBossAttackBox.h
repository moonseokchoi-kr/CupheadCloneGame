#pragma once
#include "CAttackBox.h"
class COnionBossAttackBox :
    public CAttackBox
{
public:
    COnionBossAttackBox();
    ~COnionBossAttackBox();
    CLONE(COnionBossAttackBox);
public:
    // CAttackBox을(를) 통해 상속됨
    virtual void Fire() override;
    virtual void Start() override;
private:
    
    float calRandomXPos();

private:
    bool m_toggle;
};

