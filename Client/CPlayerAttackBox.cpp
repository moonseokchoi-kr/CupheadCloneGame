#include "pch.h"
#include "CPlayerAttackBox.h"
#include "CPlayer.h"
#include "CTimeManager.h"
#include "CRigidBody.h"
#include "CCollider.h"
#include "CPeaShootBullet.h"
#include "CPlayerStateMachine.h"
#include "CPlayerState.h"
CPlayerAttackBox::CPlayerAttackBox()
	:m_accTime(0)
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
			CreateObject(bullet, GROUP_TYPE::PLAYER_BULLET);
			m_accTime = 0.0f;
		}
	}
		break;
	case BULLET_TYPE::SPREAD:
		//bullet = static_cast<CSpreadBullet*>(GetBullet(GetCurrentBullet()));
		break;
	case BULLET_TYPE::ROUNDABOUT:
		//bullet = static_cast<CRoundaboutBullet*>(GetBullet(GetCurrentBullet()));
		break;
	default:
		break;
	}

}

void CPlayerAttackBox::ChangeBullet()
{
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
	}
	if (info.shootDir == Vec2(1, 1))
	{
		SetPos(Vec2(60.f, 90.f));
	}
	if (info.shootDir == Vec2(1, -1))
	{
		SetPos(Vec2(30.f, -13.f));
	}
	if (info.shootDir == Vec2(-1, 0))
	{
		SetPos(Vec2(-60.f, 45.f));
	}
	if (info.shootDir == Vec2(-1, 1))
	{
		SetPos(Vec2(-30.f, 90.f));
	}
	if (info.shootDir == Vec2(-1, -1))
	{
		SetPos(Vec2(-60.f, -13.f));
	}
	if (info.shootDir == Vec2(0, -1))
	{
		SetPos(Vec2(30.f, -45.f));
	}
	if (info.shootDir == Vec2(0, 1))
	{
		SetPos(Vec2(0.f, 100.f));
	}
}
