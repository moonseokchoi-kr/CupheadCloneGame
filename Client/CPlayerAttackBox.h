#pragma once
#include "CAttackBox.h"
class CPlayerWeaponUI;
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
	virtual void Render(HDC _dc);
	virtual void Fire();
	void ChangeBullet();
	void ExFire();
	void CreateWeaponUI();
	void PlaySpawnAnimation();
	void SetVisible(bool _b) { m_isVisible = _b; }
private:
	void rotateCreateBulletPos();
private:
	bool m_isVisible;
	float m_accTime;
	wstring m_bulletAnimName;
	CPlayerWeaponUI* m_weaponUI;

	friend class CPlayerWeaponUI;
};

