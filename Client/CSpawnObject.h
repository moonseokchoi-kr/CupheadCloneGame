#pragma once
#include "CGameObject.h"

class CMonsterFactory;
class CMonster;

class CSpawnObject :
    public CGameObject
{
public:
    CSpawnObject();
    ~CSpawnObject();
    CLONE(CSpawnObject);
public:
    virtual void Update();
    virtual void Render(HDC _dc);

    void Spawn();
public:
    void SetMonType(MON_TYPE _type) { m_monType = _type; }
    void SetGroupType(GROUP_TYPE _type) { m_groupType = _type; }
private:
    GROUP_TYPE m_groupType;
    MON_TYPE m_monType;

};

