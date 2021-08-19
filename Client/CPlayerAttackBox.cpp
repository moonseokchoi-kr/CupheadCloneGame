#include "pch.h"
#include "CPlayerAttackBox.h"
#include "CPlayer.h"
#include "CTimeManager.h"
#include "CRigidBody.h"
#include "CCollider.h"
#include "CPeaShootBullet.h"
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
	CAttackBox::Update();
	rotateCreateBulletPos();
}


void CPlayerAttackBox::Fire()
{
	Vec2 finalPos = GetFinalPos();
	m_accTime += fDT;
	playerInfo pInfo = ((CPlayer*)GetOwner())->GetInfo();
	CBullet* bullet = nullptr;

	switch (GetCurrentBullet())
	{
	case BULLET_TYPE::PEASHOOT:
		bullet = static_cast<CPeaShootBullet*>(GetBullet(GetCurrentBullet()));
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
	if (m_accTime >= pInfo.attackSpeed)
	{
		if (finalPos.isZero())
			return;
		if (nullptr == bullet)
			return;
		CPeaShootBullet* cloneBullet = ((CPeaShootBullet*)bullet)->Clone();
		cloneBullet->SetPos(finalPos);
		cloneBullet->SetMoveDir(pInfo.shootDir);
		cloneBullet->Start();
		CreateObject(cloneBullet, GROUP_TYPE::PLAYER_BULLET);
		m_accTime = 0.0f;
	}
}

void CPlayerAttackBox::ChangeBullet()
{
}

void CPlayerAttackBox::rotateCreateBulletPos()
{
	playerInfo info = ((CPlayer*)GetOwner())->GetInfo();
	Vec2 pos = GetOwner()->GetPos();
	//플레이어의 위치에서 현재 어택박스 위치를 뺀다
	//나온 결과 백터를 방향 벡터(숫)에 곱한다.
	//플레이어의 위치와 결과벡터를 외적한다.
	//나온 벡터가 최종위치

	if (info.shootDir.isZero())
		return;
	Vec2 diff = GetFinalPos() - pos;
	float dist = diff.Distance();
	Vec2 p = info.shootDir * dist;
	SetFinalPos(pos + p);
}
