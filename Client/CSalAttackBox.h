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
private:
    int m_shootCount;
};

