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
CPlayerAttackBox::CPlayerAttackBox()
	:m_accTime(0)
	,m_weaponUI(nullptr)
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(40.f, 40.f));
}

CPlayerAttackBox::~CPlayerAttackBox()
{
}

void CPlayerAttackBox::Update()
{
	rotateCreateBulletPos();
	CAttackBox::Update();
}


void CPlayerAttackBox::Fire()
{
	Vec2 finalPos = GetFinalPos();
	m_accTime += fDT;
	playerInfo pInfo = ((CPlayer*)GetOwner())->GetInfo();
	

	switch (GetCurrentBullet())
	{
	case BULLET_TYPE::PEASHOOT:
	{
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
		pInfo.attackSpeed = 0.5f;
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
		SetCurrentBullet(BULLET_TYPE::CHASER);
	}
	else
	{
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

void CPlayerAttackBox::rotateCreateBulletPos()
{
	if (((CPlayer*)GetOwner())->GetAi()->GetCurrentState()->GetState() == PLAYER_STATE::DUCK)
	{
		return;
	}
	playerInfo info = ((CPlayer*)GetOwner())->GetInfo();
	
	if (info.shootDir == Vec2(1, 0))
	{
		SetPos(Vec2(60.f, 45.f));
		m_bulletAnimName = L"PEASHOOT_STRAIGHT_RIGHT";
	}
	if (info.shootDir == Vec2(1, 1))
	{
		SetPos(Vec2(60.f, 90.f));
		m_bulletAnimName = L"PEASHOOT_DIRECTION_DOWN_RIGHT";
	}
	if (info.shootDir == Vec2(1, -1))
	{
		SetPos(Vec2(30.f, -13.f));
		m_bulletAnimName = L"PEASHOOT_DIRECTION_UP_RIGHT";
	}
	if (info.shootDir == Vec2(-1, 0))
	{
		SetPos(Vec2(-60.f, 45.f));
		m_bulletAnimName = L"PEASHOOT_STRAIGHT_LEFT";
	}
	if (info.shootDir == Vec2(-1, 1))
	{
		SetPos(Vec2(-30.f, 90.f));
		m_bulletAnimName = L"PEASHOOT_DIRECTION_DOWN_LEFT";
	}
	if (info.shootDir == Vec2(-1, -1))
	{
		SetPos(Vec2(-60.f, -13.f));
		m_bulletAnimName = L"PEASHOOT_DIRECTION_UP_LEFT";
	}
	if (info.shootDir == Vec2(0, -1))
	{
		SetPos(Vec2(30.f, -45.f));
		m_bulletAnimName = L"PEASHOOT_UP";
	}
	if (info.shootDir == Vec2(0, 1))
	{
		SetPos(Vec2(0.f, 100.f));
		m_bulletAnimName = L"PEASHOOT_DOWN";
	}
}
