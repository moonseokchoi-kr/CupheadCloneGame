#include "pch.h"
#include "COnionBossAttackBox.h"
#include "CTearBullet.h"
COnionBossAttackBox::COnionBossAttackBox()
	:m_toggle(true)
{
	
}

COnionBossAttackBox::~COnionBossAttackBox()
{
}

void COnionBossAttackBox::Fire()
{
	CBullet* bullet = new CTearBullet;
	CBullet* cloneBullet = ((CTearBullet*)bullet)->Clone();
	cloneBullet->SetPos(Vec2(calRandomXPos(), GetFinalPos().y));
	cloneBullet->SetName(L"MonsterBullet");
	cloneBullet->Start();
	CreateObject(cloneBullet, GROUP_TYPE::MONSTER_BULLET);
}

void COnionBossAttackBox::Start()
{
	SetPos(Vec2(1280 / 2.f, -GetOwner()->GetPos().y - 100.f));
}

float COnionBossAttackBox::calRandomXPos()
{
	float ownerL = GetOwner()->GetPos().x - GetOwner()->GetScale().x / 2.f;
	float ownerR = GetOwner()->GetPos().x + GetOwner()->GetScale().x / 2.f;
	if (m_toggle)
	{
		m_toggle = false;
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<int> dis (0, (int)ownerL-30);
		return dis(gen);
	}
	else
	{
		m_toggle = true;
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<int> dis((int)ownerR + 30, 1450);
		return dis(gen);
	}

}
