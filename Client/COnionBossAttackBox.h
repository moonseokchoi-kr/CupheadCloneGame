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
    // CAttackBox��(��) ���� ��ӵ�
    virtual void Fire() override;
    virtual void Start() override;
private:
    
    float calRandomXPos();

private:
    bool m_toggle;
};

