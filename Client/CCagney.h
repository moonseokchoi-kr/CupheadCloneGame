#pragma once
#include "CMonster.h"
class CCagney :
    public CMonster
{
public:
    CCagney();
    ~CCagney();
    CLONE(CCagney);
public:
    virtual void Update();
    virtual void Render(HDC _dc);

protected:
    virtual void CreateAttackBox();
};

