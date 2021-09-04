#pragma once
#include "CMonster.h"

class CVFXObject;
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
    virtual void FinalUpdate();
    virtual void Render(HDC _dc);

public:
    virtual void OnCollisionEnter(CCollider* _col);
public:
    CVFXObject* GetBigTear() { return m_bigTear; }
protected:
    virtual void CreateAttackBox();
private:
    CVFXObject* m_bigTear;
};

