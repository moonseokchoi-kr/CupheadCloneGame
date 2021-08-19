#pragma once
#include "CAttackBox.h"
class CPlayerAttackBox :
    public CAttackBox
{
public:
	CPlayerAttackBox();
	~CPlayerAttackBox();
	CLONE(CPlayerAttackBox);
public:
	virtual void Update() override;

public:
	virtual void Fire();
	void ChangeBullet();

private:
	void rotateCreateBulletPos();

private:
	float m_accTime;
	
};

