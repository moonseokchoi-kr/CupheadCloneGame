#include "CObject.h"
#pragma once
class CHitBox :
    public CObject
{
public:
    CHitBox();
    virtual ~CHitBox();
public:
    virtual void Start() override;
    virtual void Render(HDC _dc) override;
public:
    void SetFinalPos(Vec2 _v) { m_finalPos = _v; }
    Vec2 GetFinalPos() { return m_finalPos; }
private:
    Vec2 m_finalPos;
};

