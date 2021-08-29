#pragma once
#include "CMonster.h"

enum class PHASE
{
    PHASE1,
    PHASE2,
};

class CSlime :
    public CMonster
{
public:
    CSlime();
    ~CSlime();
    CLONE(CSlime);
public:
    virtual void Start();
    virtual void Update();
    virtual void Render(HDC _dc);

protected:
    virtual void CreateAttackBox();
};

