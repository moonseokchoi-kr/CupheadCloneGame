#pragma once
#include "CBullet.h"

class CMonster;
class CMonSeedBullet :
    public CBullet
{
public:
    CMonSeedBullet();
    ~CMonSeedBullet();
    CLONE(CMonSeedBullet);

public:
    // CBullet을(를) 통해 상속됨
    virtual void Update() override;

    virtual void Render(HDC _dc) override;

    virtual void OnCollisionEnter(CCollider* _col) override;
    virtual void OnCollision(CCollider* _col) override;
private:
    bool randomPercent();
private:
    CMonster* m_createMonster;
    float m_purplePercent;
    float m_toggle;
    float m_initTime;
    float m_accTime;
};

