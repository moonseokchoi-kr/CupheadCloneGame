#include "pch.h"
#include "CPeaShootBullet.h"
#include "CBullet.h"
#include "CRigidBody.h"
#include "CCollider.h"
#include "CResourceManager.h"
#include "CTexture.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CSound.h"
CPeaShootBullet::CPeaShootBullet()
	:CBullet(BULLET_TYPE::PEASHOOT)
{
	SetName(L"PlayerBullet");
	bulletInfo info = {};
	info.bulletSpeed = 300.f;
	info.damege = 5.f;
	info.range = 1600.f;
	//159/140
	CreateCollider();
	CreateRigidBody();
	CreateAnimator();
	SetScale(Vec2(159.f, 140.f));
	GetCollider()->SetScale(Vec2(85.f, 41.f));
	GetRigidBody()->SetMaxVelocity(1000.f);

	SetInfo(info);

	CTexture* bulletTex = CResourceManager::GetInst()->FindTexture(L"PeashootTex");
	CTexture* bulletDeath = CResourceManager::GetInst()->FindTexture(L"PeashootDeathTex");

	GetAnimator()->CreateAnimation(L"PEASHOOT_DIRECTION_DOWN_RIGHT_INTRO", bulletTex, Vec2(0.f, 0.f), Vec2(159.f, 140.f), Vec2(159.f, 0.f), 1 / 30.f, 3, false);
	GetAnimator()->CreateAnimation(L"PEASHOOT_DIRECTION_UP_RIGHT_INTRO", bulletTex, Vec2(0.f, 140.f), Vec2(159.f, 140.f), Vec2(159.f, 0.f), 1 / 30.f, 3, false);
	GetAnimator()->CreateAnimation(L"PEASHOOT_STRAIGHT_RIGHT_INTRO", bulletTex, Vec2(0.f, 280.f), Vec2(159.f, 140.f), Vec2(159.f, 0.f), 1 / 30.f, 3, false);
	GetAnimator()->CreateAnimation(L"PEASHOOT_DIRECTION_DOWN_RIGHT", bulletTex, Vec2(477.f, 0.f), Vec2(159.f, 140.f), Vec2(159.f, 0.f), 1 / 30.f, 6, false);
	GetAnimator()->CreateAnimation(L"PEASHOOT_DIRECTION_UP_RIGHT", bulletTex, Vec2(477.f, 140.f), Vec2(159.f, 140.f), Vec2(159.f, 0.f), 1 / 30.f, 6, false);
	GetAnimator()->CreateAnimation(L"PEASHOOT_STRAIGHT_RIGHT", bulletTex, Vec2(477.f, 280.f), Vec2(159.f, 140.f), Vec2(159.f, 0.f), 1 / 30.f, 6, false);
	GetAnimator()->CreateAnimation(L"PEASHOOT_DIRECTION_DOWN_LEFT_INTRO", bulletTex, Vec2(954.f, 420.f), Vec2(159.f, 140.f), Vec2(159.f, 0.f), 1 / 30.f, 3, true);
	GetAnimator()->CreateAnimation(L"PEASHOOT_DIRECTION_UP_LEFT_INTRO", bulletTex, Vec2(954.f, 560.f), Vec2(159.f, 140.f), Vec2(159.f, 0.f), 1 / 30.f, 3, true);
	GetAnimator()->CreateAnimation(L"PEASHOOT_STRAIGHT_LEFT_INTRO", bulletTex, Vec2(954.f, 700.f), Vec2(159.f, 140.f), Vec2(159.f, 0.f), 1 / 30.f, 3, true);
	GetAnimator()->CreateAnimation(L"PEASHOOT_DIRECTION_DOWN_LEFT", bulletTex, Vec2(0.f, 420.f), Vec2(159.f, 140.f), Vec2(159.f, 0.f), 1 / 30.f, 6, true);
	GetAnimator()->CreateAnimation(L"PEASHOOT_DIRECTION_UP_LEFT", bulletTex, Vec2(0.f, 560.f), Vec2(159.f, 140.f), Vec2(159.f, 0.f), 1 / 30.f, 6, true);
	GetAnimator()->CreateAnimation(L"PEASHOOT_STRAIGHT_LEFT", bulletTex, Vec2(0.f, 700.f), Vec2(159.f, 140.f), Vec2(159.f, 0.f), 1 / 30.f, 6, true);

	GetAnimator()->CreateAnimation(L"PEASHOOT_DOWN_INTRO", bulletTex, Vec2(0.f, 840.f), Vec2(159.f, 140.f), Vec2(159.f, 0.f), 1 / 30.f, 3, false);
	GetAnimator()->CreateAnimation(L"PEASHOOT_UP_INTRO", bulletTex, Vec2(0.f, 980.f), Vec2(159.f, 140.f), Vec2(159.f, 0.f), 1 / 30.f, 3, false);
	GetAnimator()->CreateAnimation(L"PEASHOOT_DOWN", bulletTex, Vec2(477.f, 840.f), Vec2(159.f, 140.f), Vec2(159.f, 0.f), 1 / 30.f, 6, false);
	GetAnimator()->CreateAnimation(L"PEASHOOT_UP", bulletTex, Vec2(477.f, 980.f), Vec2(159.f, 140.f), Vec2(159.f, 0.f), 1 / 30.f, 6, false);

	GetAnimator()->CreateAnimation(L"PEASHOOT_DEATH", bulletDeath, Vec2(0.f, 0.f), Vec2(249.f, 263.f), Vec2(249.f, 0.f), 1 / 30.f, 6, false);
}

CPeaShootBullet::~CPeaShootBullet()
{

}

void CPeaShootBullet::Update()
{
	if (m_isDead)
	{
		GetCollider()->SetAvaCollide(false);
		GetRigidBody()->SetActive(false);
		GetAnimator()->Play(L"PEASHOOT_DEATH", false);
		if (GetAnimator()->GetCurrentAnim()->IsFinish())
		{
			GetSFX()->Stop(true);
			DeleteObject(this);
		}
		return;
	}
	bulletInfo info = GetInfo();
	Vec2 moveDir = GetMoveDir();
	Vec2 pos = GetPos();
	GetRigidBody()->SetVelocity(moveDir * 1000.f);
	GetRigidBody()->AddVelocity(Vec2(info.bulletSpeed * moveDir.x, info.bulletSpeed * moveDir.y));
	GetAnimator()->Play(m_animName + L"_INTRO", false);
	if(GetAnimator()->GetCurrentAnim()->IsFinish())
		GetAnimator()->Play(m_animName, true);
	DeleteBullet();

}

void CPeaShootBullet::Render(HDC _dc)
{
	ComponentRender(_dc);
}

void CPeaShootBullet::OnCollisionEnter(CCollider* _col)
{
	if (_col->GetOwner()->GetName() == L"MonsterHitBox" || _col->GetOwner()->GetName() == L"Ground" || _col->GetOwner()->GetName() == L"MonsterBullet")
	{
		SetSFX(L"PLAYER_SHOOT_HIT");
		GetSFX()->Play(true);
		GetSFX()->SetPosition(50.f);
		GetSFX()->SetVolume(70.f);
		m_isDead = true;
	}
}

void CPeaShootBullet::OnCollision(CCollider* _col)
{
}

void CPeaShootBullet::OnCollisionExit(CCollider* _col)
{
}
