#pragma once
#include "CMonster.h"
class COllieBullb :
    public CMonster
{
public:
    COllieBullb();
    ~COllieBullb();
    CLONE(COllieBullb);
public:
    virtual void Start();
    virtual void Update();
    virtual void Render(HDC _dc);

public:
    virtual void OnCollisionEnter(CCollider* _col);
protected:
    virtual void CreateAttackBox();

};

