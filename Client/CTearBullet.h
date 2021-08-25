#pragma once
#include "CBullet.h"

enum class TEAR_BULLET_TYPE
{
    A,
    B,
    C,
    P,
};

class CTearBullet :
    public CBullet
{
public:
    CTearBullet();
    ~CTearBullet();
    CLONE(CTearBullet);
public:    
    virtual void Render(HDC _dc);

    // CBullet을(를) 통해 상속됨
    virtual void Update() override;

    virtual void OnCollisionEnter(CCollider* _col);
    virtual void OnCollision(CCollider* _col);
private:
    void randomTear();
private:
    TEAR_BULLET_TYPE m_type;
    bool isDead;
};

