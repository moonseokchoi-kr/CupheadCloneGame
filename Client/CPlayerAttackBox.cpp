#include "pch.h"
#include "CPlayerAttackBox.h"
#include "CPlayer.h"
#include "CTimeManager.h"
#include "CRigidBody.h"
#include "CCollider.h"
#include "CPeaShootBullet.h"
#include "CPlayerStateMachine.h"
#include "CPlayerState.h"
#include "CChaserBullet.h"
#include "CPlayerWeaponUI.h"
#include "CResourceManager.h"
#include "CTexture.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CSound.h"
CPlayerAttackBox::CPlayerAttackBox()
	:m_accTime(0)
	,m_weaponUI(nullptr)
	,m_isVisible(false)
{
	CreateCollider();
	CreateAnimator();
	GetCollider()->SetScale(Vec2(40.f, 40.f));
	SetSFX(L"PLAYER_FIRE_LOOP");
	CTexture* tex = CResourceManager::GetInst()->FindTexture(L"PlayerSpawnTex");
	GetAnimator()->CreateAnimation(L"CHASER_SPAWN", tex, Vec2(0.f, 0.f), Vec2(112.f, 105.f), Vec2(112.f, 0.f), 1 / 30.f, 4, false);
	GetAnimator()->CreateAnimation(L"PEASHOT_SPAWN", tex, Vec2(448.f, 0.f), Vec2(112.f, 105.f), Vec2(112.f, 0.f), 1 / 30.f, 4, false);
}

CPlayerAttackBox::~CPlayerAttackBox()
{
}

void CPlayerAttackBox::Update()
{
	rotateCreateBulletPos();
	CAttackBox::Update();
}


void CPlayerAttackBox::Render(HDC _dc)
{
	if(m_isVisible)
		ComponentRender(_dc);
}

void CPlayerAttackBox::Fire()
{
	Vec2 finalPos = GetPos();
	m_accTime += fDT;
	playerInfo pInfo = ((CPlayer*)GetOwner())->GetInfo();
	GetSFX()->Play(false);
	m_isVisible = true;
	switch (GetCurrentBullet())
	{
	case BULLET_TYPE::PEASHOOT:
	{
		GetAnimator()->Play(L"PEASHOT_SPAWN", true);
		CPeaShootBullet* bullet = new CPeaShootBullet;
		if (m_accTime >= pInfo.attackSpeed)
		{
			if (finalPos.isZero())
				return;
			bullet->SetPos(finalPos);
			bullet->SetMoveDir(pInfo.shootDir);
			bullet->Start();
			bullet->SetAnimName(m_bulletAnimName);
			CreateObject(bullet, GROUP_TYPE::PLAYER_BULLET);
			m_accTime = 0.0f;
		}
	}
		break;
	case BULLET_TYPE::CHASER:
	{
		GetAnimator()->Play(L"CHASER_SPAWN", true);
		CChaserBullet* bullet = new CChaserBullet;
		if (m_accTime >= pInfo.attackSpeed)
		{
			if (finalPos.isZero())
				return;
			bullet->SetPos(finalPos);
			bullet->Start();
			CreateObject(bullet, GROUP_TYPE::PLAYER_BULLET);
			m_accTime = 0.0f;
		}
	}
		break;
	default:
		break;
	}
}

void CPlayerAttackBox::ChangeBullet()
  {
	if (GetCurrentBullet() == BULLET_TYPE::PEASHOOT)
	{
		
		SetSFX(L"PLAYER_HOMING_LOOP");
		GetSFX()->SetPosition(50.f);
		GetSFX()->SetVolume(100.f);
		SetCurrentBullet(BULLET_TYPE::CHASER);
	}
	else
	{
		SetSFX(L"PLAYER_FIRE_LOOP");
		GetSFX()->SetPosition(50.f);
		GetSFX()->SetVolume(70.f);
		SetCurrentBullet(BULLET_TYPE::PEASHOOT);
	}
	m_weaponUI->m_isActive = true;
}

void CPlayerAttackBox::ExFire()
{  
}

void CPlayerAttackBox::CreateWeaponUI()
{
	m_weaponUI = new CPlayerWeaponUI;
	m_weaponUI->m_owner = this;
	m_weaponUI->m_bulletType = BULLET_TYPE::PEASHOOT;
	CreateObject(m_weaponUI, GROUP_TYPE::UI);
}

void CPlayerAttackBox::PlaySpawnAnimation()
{
	switch (GetCurrentBullet())
	{
	case BULLET_TYPE::PEASHOOT:
	{
		
	}
		break;
	case BULLET_TYPE::CHASER:
	{
		
	}
		break;
	default:
		break;
	}
	if (GetAnimator()->GetCurrentAnim()->GetCurrentFrame() == 3)
	{
		GetAnimator()->GetCurrentAnim()->SetFrame(0);
	}
}

void CPlayerAttackBox::rotateCreateBulletPos()
{
	if (((CPlayer*)GetOwner())->GetAi()->GetCurrentState()->GetState() == PLAYER_STATE::DUCK)
	{
		return;
	}
	playerInfo info = ((CPlayer*)GetOwner())->GetInfo();
	
	if (info.shootDir == Vec2(1, 0))
	{
		SetOffset(Vec2(60.f, 45.f));
		m_bulletAnimName = L"PEASHOOT_STRAIGHT_RIGHT";
	}
	if (info.shootDir == Vec2(1, 1))
	{
		SetOffset(Vec2(60.f, 90.f));
		m_bulletAnimName = L"PEASHOOT_DIRECTION_DOWN_RIGHT";
	}
	if (info.shootDir == Vec2(1, -1))
	{
		SetOffset(Vec2(30.f, -13.f));
		m_bulletAnimName = L"PEASHOOT_DIRECTION_UP_RIGHT";
	}
	if (info.shootDir == Vec2(-1, 0))
	{
		SetOffset(Vec2(-60.f, 45.f));
		m_bulletAnimName = L"PEASHOOT_STRAIGHT_LEFT";
	}
	if (info.shootDir == Vec2(-1, 1))
	{
		SetOffset(Vec2(-30.f, 90.f));
		m_bulletAnimName = L"PEASHOOT_DIRECTION_DOWN_LEFT";
	}
	if (info.shootDir == Vec2(-1, -1))
	{
		SetOffset(Vec2(-60.f, -13.f));
		m_bulletAnimName = L"PEASHOOT_DIRECTION_UP_LEFT";
	}
	if (info.shootDir == Vec2(0, -1))
	{
		SetOffset(Vec2(30.f, -45.f));
		m_bulletAnimName = L"PEASHOOT_UP";
	}
	if (info.shootDir == Vec2(0, 1))
	{
		SetOffset(Vec2(0.f, 100.f));
		m_bulletAnimName = L"PEASHOOT_DOWN";
	}
}
