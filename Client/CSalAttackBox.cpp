#include "pch.h"
#include "CSalAttackBox.h"


#include "CSalBullet.h"
#include "CTimeManager.h"


CSalAttackBox::CSalAttackBox()
	:m_shootCount(0)
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


	CSalBullet* bullet = salBullet->Clone();
	if (m_shootCount == 3)
	{
		bullet->SetBulletType(SAL_BULLET_TYPE::WORM);
	}
	else
	{
		bullet->SetBulletType(SAL_BULLET_TYPE::DUST);

	}
	bullet->SetPos(finalpos + Vec2(80 * m_shootCount, 0));
	bullet->SetMoveDir(Vec2(-1, 0));
	bullet->SetName(L"MonsterBullet");
	bullet->Start();
	CreateObject(bullet, GROUP_TYPE::MONSTER_BULLET);

	++m_shootCount;

	if(m_shootCount <4)
		m_shootCount = 0;
	
}
