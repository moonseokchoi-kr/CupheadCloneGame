#pragma once
#include "CObject.h"

class CChaserBullet;
class CHomingBulletTraile :
    public CObject
{
public:
	CHomingBulletTraile();
	~CHomingBulletTraile();
    CLONE(CHomingBulletTraile);
public:
	// CObject��(��) ���� ��ӵ�
	virtual void Update() override;

    virtual void Render(HDC _dc) override;
public:
    void SetOffset(Vec2 _v) { m_offSet = _v; }
private:
    CChaserBullet* m_owner;
    Vec2 m_offSet;

    friend class CChaserBullet;


};

