#include "pch.h"
#include "CCarrotBossAttackBox.h"
#include "CSound.h"
#include "CCore.h"
#include "CCarrotMissle.h"
#include "CBeamMissile.h"
#include "CMonster.h"
CCarrotBossAttackBox::CCarrotBossAttackBox()
	:m_currnetPatt(ATTACK_PATT::PATT1)
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

		SetPos(Vec2(0.f, -GetOwner()->GetPos().y - 100));

	}
	else
	{;
		SetPos(Vec2(0.f, -100.f));
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
	CBeamMissile* beam = new CBeamMissile;
	CCarrotMissle* carrotMissile = new CCarrotMissle;

	switch (m_currnetPatt)
	{
	case ATTACK_PATT::PATT1:
	{
		carrotMissile->SetPos(Vec2(m_missieX[dis(gen)], GetPos().y));
		carrotMissile->SetName(L"MonsterBullet");
		carrotMissile->Start();
		CreateObject(carrotMissile, GROUP_TYPE::MONSTER_BULLET);
	}
		break;
	case ATTACK_PATT::PATT2:
	{
		SetSFX(L"CARROT_MIND_MEID_BEAM_FIRE");
		GetSFX()->SetPosition(50.f);
		GetSFX()->SetVolume(80.f);
		GetSFX()->Play(false);
		beam->SetPos(GetOffset());
		beam->SetName(L"BeamBullet");
		beam->Start();
		CreateObject(beam, GROUP_TYPE::MONSTER_BULLET);
	}
		break;
	default:
		break;
	}
}

void CCarrotBossAttackBox::ChangeAttack()
{
	if (ATTACK_PATT::PATT1 == m_currnetPatt)
	{
		SetSFX(L"CARROT_MIND_MEID_START");
		GetSFX()->SetPosition(50.f);
		GetSFX()->SetVolume(100.f);
		GetSFX()->Play(false);
		m_currnetPatt = ATTACK_PATT::PATT2;
	}
	else
	{
		//유도미사일
		SetSFX(L"CARROT_MIND_MEID_LOOP");
		GetSFX()->SetPosition(50.f);
		GetSFX()->SetVolume(100.f);
		GetSFX()->Play(false);
		m_currnetPatt = ATTACK_PATT::PATT1;
	}
}
