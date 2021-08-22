#include "pch.h"
#include "CCarrotBossAttackBox.h"

#include "CCore.h"
#include "CCarrotMissle.h"
#include "CBeamMissile.h"
#include "CMonster.h"
CCarrotBossAttackBox::CCarrotBossAttackBox()

{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(0, 1);
	m_currnetPatt = (ATTACK_PATT)dis(gen);
	float tearm = (1450 - 100) / 8;
	for (int i = 0; i < m_missieX.size(); ++i)
	{
		m_missieX[i] = tearm * (i + 1);
	}
}

CCarrotBossAttackBox::~CCarrotBossAttackBox()
{
}

void CCarrotBossAttackBox::Update()
{	
	CAttackBox::Update();
	Vec2 resolution = CCore::GetInst()->GetResolution();
	if (ATTACK_PATT::PATT1 == m_currnetPatt)
	{
		SetPos(Vec2(0.f, -GetOwner()->GetPos().y -100));
		
	}
	else
	{
		SetPos(Vec2(0.f, -200.f));
	}
	
}

void CCarrotBossAttackBox::Fire()
{
	if (!((CMonster*)GetOwner())->GetTarget())
	{
		return;
	}
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(0, 5);
	CBullet* bullet = nullptr;
	CBullet* cloneBullet = nullptr;
	switch (m_currnetPatt)
	{
	case ATTACK_PATT::PATT1:
	{
		bullet = new CCarrotMissle;
		cloneBullet = ((CCarrotMissle*)bullet)->Clone();
		cloneBullet->SetPos(Vec2(m_missieX[dis(gen)], GetFinalPos().y));
	}
		break;
	case ATTACK_PATT::PATT2:
	{
		bullet = new CBeamMissile;
		cloneBullet = ((CBeamMissile*)bullet)->Clone();
		cloneBullet->SetPos(GetFinalPos());
	}
		break;
	default:
		break;
	}
	cloneBullet->SetName(L"MonsterBullet");
	cloneBullet->Start();
	CreateObject(cloneBullet, GROUP_TYPE::MONSTER_BULLET);
}

void CCarrotBossAttackBox::ChangeAttack()
{
	if (ATTACK_PATT::PATT1 == m_currnetPatt)
	{
		m_currnetPatt = ATTACK_PATT::PATT2;
	}
	else
	{
		m_currnetPatt = ATTACK_PATT::PATT1;
	}
}
