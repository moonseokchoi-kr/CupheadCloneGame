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
	CTearBullet* bullet = new CTearBullet;
	bullet->SetPos(Vec2(calRandomXPos(), GetPos().y));
	bullet->SetName(L"MonsterBullet");
	bullet->Start();
	CreateObject(bullet, GROUP_TYPE::MONSTER_BULLET);
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
		return (float)dis(gen);
	}
	else
	{
		m_toggle = true;
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<int> dis((int)ownerR + 30, 1450);
		return (float)dis(gen);
	}

}
