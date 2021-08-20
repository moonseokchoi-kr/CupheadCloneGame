#pragma once
#include "CBullet.h"
class CBeamMissile :
    public CBullet
{
public:
    CBeamMissile();
    ~CBeamMissile();
    CLONE(CBeamMissile);
public:

    // CBullet��(��) ���� ��ӵ�
    virtual void Start() override;
    virtual void Update() override;
    virtual void Render(HDC _dc) override;

private:
    Vec2 m_targetPos;


};

