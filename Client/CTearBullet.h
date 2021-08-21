#pragma once
#include "CBullet.h"
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
private:
    bool randomPercent();
private:
    float m_redTearPercent;
    bool m_toggle;
    
    
};

