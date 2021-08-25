#pragma once
#include "CAttackBox.h"
class CSalAttackBox :
    public CAttackBox
{
public:
    CSalAttackBox();
    ~CSalAttackBox();
    CLONE(CSalAttackBox);
public:
    virtual void Fire();
public:
    void SetBulletSpeed(float _speed) { m_bulletSpeed = _speed; }
private:
    int m_shootCount;
    float m_bulletSpeed;
};

