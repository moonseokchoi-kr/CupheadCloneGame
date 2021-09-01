#include "pch.h"
#include "CSalAttackBox.h"
#include "CSound.h"

#include "CSalBullet.h"
#include "CTimeManager.h"


CSalAttackBox::CSalAttackBox()
	:m_shootCount(0)
	,m_bulletSpeed(600.f)
{
	SetPos(Vec2(-150.f, 150.f));
	
}

CSalAttackBox::~CSalAttackBox()
{
}

void CSalAttackBox::Fire()
{
	
	Vec2 finalpos = GetFinalPos();
	CSalBullet* salBullet = new CSalBullet;
	salBullet->SetPos(finalpos);
	salBullet->SetMoveDir(Vec2(-1, 0));
	salBullet->SetName(L"MonsterBullet");
	bulletInfo info = salBullet->GetInfo();
	info.bulletSpeed = m_bulletSpeed;
	salBullet->SetInfo(info);
	if (m_shootCount == 3)
	{
		SetSFX(L"POTATO_WORM");
		GetSFX()->Play(false);
		GetSFX()->SetPosition(50.f);
		GetSFX()->SetVolume(100.f);
		salBullet->SetBulletType(SAL_BULLET_TYPE::WORM);
	}
	else
	{
		SetSFX(L"POTATO_DUST_" + to_wstring(m_shootCount + 1));
		GetSFX()->Play(false);
		GetSFX()->SetPosition(50.f);
		GetSFX()->SetVolume(100.f);
		salBullet->SetBulletType(SAL_BULLET_TYPE::DUST);

	}
	
	salBullet->Start();
	CreateObject(salBullet, GROUP_TYPE::MONSTER_BULLET);

	++m_shootCount;

	if(m_shootCount >3)
		m_shootCount = 0;
	
}
