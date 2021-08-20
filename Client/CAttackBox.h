#pragma once
#include "CObject.h"



class CBullet;

class CAttackBox :
    public CObject
{
public:
    CAttackBox();
    virtual ~CAttackBox();
public:

    virtual void Update() override;
    virtual void Render(HDC _dc) override;
    BULLET_TYPE GetCurrentBullet() { return m_current_Bullet; }
    void SetCurrentBullet(BULLET_TYPE _type) { m_current_Bullet = _type; }
    void AddBullet(CBullet* _bullet);
    CObject* GetOwner() { return m_owner; }
    Vec2 GetFinalPos() { return m_finalPos; }
    void SetFinalPos(Vec2 _v) { m_finalPos = _v; }
public:
    virtual void Fire() = 0;
    virtual void ChangeBullet() {};
    CBullet* GetBullet(BULLET_TYPE _type);
private:
    CObject* m_owner;
    Vec2 m_finalPos;
    BULLET_TYPE m_current_Bullet;
    unordered_map<BULLET_TYPE,CBullet*> m_bulletVec;
    float m_accTime;

    friend class CPlayer;
    friend class CSalSpudder;
    friend class CChauncey;
};

