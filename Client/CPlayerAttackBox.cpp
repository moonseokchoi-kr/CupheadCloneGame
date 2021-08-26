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
	playerInfo info = ((CPlayer*)GetOwner())->GetInfo();
	Vec2 pos = GetOwner()->GetPos();
	//�÷��̾��� ��ġ���� ���� ���ùڽ� ��ġ�� ����
	//���� ��� ���͸� ���� ����(��)�� ���Ѵ�.
	//�÷��̾��� ��ġ�� ������͸� �����Ѵ�.
	//���� ���Ͱ� ������ġ

	if (info.shootDir.isZero())
		return;
	Vec2 diff = GetFinalPos() - pos;
	float dist = diff.Distance();
	Vec2 p = info.shootDir * dist;
	SetFinalPos(pos + p);
}
