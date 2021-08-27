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
    virtual void Start();
    virtual void Update();
    virtual void Render(HDC _dc);

    void Spawn();
public:
    void SetMonType(MON_TYPE _type);
    void SetGroupType(GROUP_TYPE _type);
    GROUP_TYPE GetGroupType() { return m_groupType; }
    MON_TYPE GetMonType() { return m_monType; }
    bool IsSpawn() { return m_spawned; }
    CObject* GetSpawnObj() { return m_spawnObj; }
	virtual void Save(FILE* _file);
	virtual void Load(FILE* _file);
private:
    GROUP_TYPE m_groupType;
    MON_TYPE m_monType;
    CObject* m_spawnObj;
    bool m_spawned;

};

