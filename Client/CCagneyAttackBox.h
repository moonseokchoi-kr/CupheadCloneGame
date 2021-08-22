#pragma once
#include "CAttackBox.h"

class CFaceAttack;
class CCagneyAttackBox :
    public CAttackBox
{
public:
	CCagneyAttackBox();
	~CCagneyAttackBox();
	CLONE(CCagneyAttackBox);
public:
	virtual void Update() override;
	// CAttackBox을(를) 통해 상속됨
	virtual void Fire() override;
	ATTACK_PATT GetCurrentPatt() { return m_currnetPatt; }
	void SetCurrnetPatt(ATTACK_PATT _patt) { m_currnetPatt = _patt; }
public:
	void ChangeAttack();
private:
	int setXPos();
private:
	ATTACK_PATT m_currnetPatt;
	CFaceAttack* m_faceAttack;
	int m_seedBulletCount;
};

