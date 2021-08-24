#pragma once
#include "CMonster.h"
class CSalSpudder :
    public CMonster
{
public:
    CSalSpudder();
    ~CSalSpudder();
    CLONE(CSalSpudder);
public:
    virtual void Update();
    virtual void Render(HDC _dc);
    virtual void CreateAttackBox();
public:
   
private:
    float m_animatedTime;
};

