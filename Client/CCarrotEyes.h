#pragma once
#include "CObject.h"

class CChauncey;
class CCarrotEyes :
    public CObject
{
public:
    CCarrotEyes();
    ~CCarrotEyes();
    CLONE(CCarrotEyes)
public:
    // CObject을(를) 통해 상속됨
    virtual void Update() override;
    virtual void Render(HDC _dc) override;
private:
    CChauncey* m_owner;
    Vec2 m_offSet;

    friend class CChauncey;
};

