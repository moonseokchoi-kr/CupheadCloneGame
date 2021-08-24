#pragma once
#include "CBullet.h"

enum class SAL_BULLET_TYPE
{
    DUST,
    WORM,
};

class CSalBullet :
    public CBullet
{
public:
    CSalBullet();
    ~CSalBullet();
    CLONE(CSalBullet);
public:
    virtual void Update();
    virtual void Render(HDC _dc);
    virtual void OnCollisionEnter(CCollider* _col);
    virtual void OnCollision(CCollider* _col);
    virtual void OnCollisionExit(CCollider* _col);
public:
    void SetBulletType(SAL_BULLET_TYPE _type) { m_currentBulletType = _type; }
    SAL_BULLET_TYPE GetBulletType() { return m_currentBulletType; }

private:
    SAL_BULLET_TYPE m_currentBulletType;

};

