#include "pch.h"
#include "CSalBullet.h"
#include "CRigidBody.h"
#include "CCollider.h"
#include "CResourceManager.h"
#include "CTexture.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "SelectGDI.h"
#include "CTimeManager.h"
CSalBullet::CSalBullet()
	:CBullet(BULLET_TYPE::SAL_BULLET)
	,m_currentBulletType(SAL_BULLET_TYPE::DUST)
{
	CreateCollider();
	CreateRigidBody();
	CreateAnimator();
	SetScale(Vec2(30.f, 30.f));
	GetCollider()->SetScale(Vec2(60.f, 60.f));

	bulletInfo info = {};
	info.range = 1600.f;
	info.bulletSpeed = 600.f;
	info.damege = 1;
	info.health = 3;
	GetRigidBody()->SetMaxVelocity(info.bulletSpeed);
	SetInfo(info);
	SetName(L"MonsterBullet");

	CTexture* dustBullet = CResourceManager::GetInst()->FindTexture(L"PotatoDustBullet");
	CTexture* wormBullet = CResourceManager::GetInst()->FindTexture(L"PotatoWormBullet");

	GetAnimator()->CreateAnimation(L"POTATO_DUST_BULLET_LOOP", dustBullet, Vec2(0.f, 0.f), Vec2(350.f, 327.f), Vec2(350.f, 0.f), 1 / 16.f, 8, false);
	GetAnimator()->CreateAnimation(L"POTATO_DUST_BULLET_DEATH", dustBullet, Vec2(2800.f, 0.f), Vec2(350.f, 327.f), Vec2(350.f, 0.f), 1 / 16.f, 7, false);
	GetAnimator()->CreateAnimation(L"POTATO_WORM_BULLET_LOOP", wormBullet, Vec2(0.f, 0.f), Vec2(350.f, 327.f), Vec2(350.f, 0.f), 1 / 16.f, 4, false);
	GetAnimator()->CreateAnimation(L"POTATO_WORM_BULLET_DEATH", wormBullet, Vec2(1400.f, 0.f), Vec2(350.f, 327.f), Vec2(350.f, 0.f), 1 / 16.f, 5, false);
}

CSalBullet::~CSalBullet()
{
}

void CSalBullet::Update()
{
	Vec2 pos = GetPos();
	bulletInfo info = GetInfo();
	Vec2 moveDir = GetMoveDir();
	GetRigidBody()->SetVelocity(moveDir * GetInfo().bulletSpeed);
	GetRigidBody()->AddVelocity(Vec2(info.bulletSpeed * moveDir.x, info.bulletSpeed * moveDir.y));
	if (IsHit())
	{
		m_accTime += fDT;
		if (m_accTime >= 0.1f)
		{
			SetHit(false);
		}
	}
	if (m_currentBulletType == SAL_BULLET_TYPE::DUST)
	{
		GetAnimator()->Play(L"POTATO_DUST_BULLET_LOOP", true);
	}
	else
	{
		GetAnimator()->Play(L"POTATO_WORM_BULLET_LOOP", true);
	}
	DeleteBullet();
	if (isDead)
	{
		GetCollider()->SetAvaCollide(false);
		GetRigidBody()->SetActive(false);

		if (m_currentBulletType == SAL_BULLET_TYPE::DUST)
		{
			GetAnimator()->Play(L"POTATO_DUST_BULLET_DEATH", false);
		}
		else
		{
			GetAnimator()->Play(L"POTATO_WORM_BULLET_DEATH", false);
		}

	
		if (GetAnimator()->GetCurrentAnim()->IsFinish())
			DeleteObject(this);
	}
}

void CSalBullet::Render(HDC _dc)
{
	if (IsHit())
	{
		if (m_renderToggle)
		{
			GetAnimator()->SetAlpha(127);
			m_renderToggle = false;
		}
		else
		{
			GetAnimator()->SetAlpha(0);
			m_renderToggle = true;
		}
	}
	else
	{
		GetAnimator()->SetAlpha(255);
	}
	ComponentRender(_dc);
}

void CSalBullet::OnCollisionEnter(CCollider* _col)
{
	CObject* obj = _col->GetOwner();
	if (obj->GetName() == L"PlayerHitBox")
	{
		isDead = true;
	}
}

void CSalBullet::OnCollision(CCollider* _col)
{
	CObject* obj = _col->GetOwner();
	if (obj->GetName() == L"PlayerHitBox")
	{
		isDead = true;
	}
	if (obj->GetName() == L"PlayerBullet" && m_currentBulletType == SAL_BULLET_TYPE::WORM)
	{
		bulletInfo info = GetInfo();
		info.health -= 1;
		if (info.health <= 0)
		{
			isDead = true;
			return;
		}
		SetHit(true);
		SetInfo(info);
	}
}

void CSalBullet::OnCollisionExit(CCollider* _col)
{
}
