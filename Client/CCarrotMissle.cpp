#include "pch.h"
#include "CCarrotMissle.h"
#include "CCollider.h"
#include "CRigidBody.h"
#include "CPlayer.h"
#include "CCamera.h"
#include "CTexture.h"
#include "CResourceManager.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CSound.h"
#include "CSceneManager.h"
#include "CScene.h"
#include "SelectGDI.h"
#include "CTimeManager.h"

CCarrotMissle::CCarrotMissle()
	:CBullet(BULLET_TYPE::CARROT_MISSILE)
	,m_maxAngle(Vec2(0.5f,0.5f))
	,m_accTime(0)
	,m_target(nullptr)
{
	CreateCollider();
	CreateRigidBody();
	CreateAnimator();
	SetScale(Vec2(40.f, 70.f));
	GetCollider()->SetScale(Vec2(40.f, 80.f));
	GetCollider()->SetOffsetPos(Vec2(0.f, 10.f));
	GetRigidBody()->SetMaxVelocity(200.f);
	m_target = CSceneManager::GetInst()->GetCurrentScene()->GetTarget(GROUP_TYPE::PLAYER, L"Player");


	bulletInfo info = {};
	info.bulletSpeed = 400.f;
	info.damege = 1.f;
	info.range = 1600.f;
	info.health = 3;
	SetInfo(info);

	CTexture* missleTex = CResourceManager::GetInst()->FindTexture(L"CarrotMissileTex");
	GetAnimator()->CreateAnimation(L"CARROT_MISSILE_DEATH", missleTex, Vec2(0.f, 0.f), Vec2(437.f, 395.f), Vec2(437.f, 0.f), 1 / 16.f, 10, false);
	GetAnimator()->CreateAnimation(L"CARROT_MISSILE_LOOP", missleTex, Vec2(4370.f , 0.f), Vec2(437.f, 395.f), Vec2(437.f, 0.f), 1 / 16.f, 6, false);
}

CCarrotMissle::~CCarrotMissle()
{
}

void CCarrotMissle::Update()
{
	if (isDead)
	{
		GetCollider()->SetAvaCollide(false);
		GetRigidBody()->SetActive(false);
		GetAnimator()->Play(L"CARROT_MISSILE_DEATH", false);
		if (GetAnimator()->GetCurrentAnim()->IsFinish())
			DeleteObject(this);
		return;
	}
	Vec2 pos = GetPos();
	Vec2 targetPos = m_target->GetPos();
	Vec2 diff = targetPos - pos;
	diff.Normalize();
	GetAnimator()->Play(L"CARROT_MISSILE_LOOP", true);
	GetRigidBody()->SetVelocity(Vec2(diff.x * GetInfo().bulletSpeed, diff.y * GetInfo().bulletSpeed));
	GetRigidBody()->AddVelocity(Vec2(diff.x * GetInfo().bulletSpeed, diff.y * GetInfo().bulletSpeed));
	if (IsHit())
	{
		m_accTime += fDT;
		if (m_accTime >= 0.1f)
		{
			SetHit(false);
		}
			
	}

	DeleteBullet();
}

void CCarrotMissle::Render(HDC _dc)
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

void CCarrotMissle::OnCollisionEnter(CCollider* _col)
{
	if (_col->GetOwner()->GetName() == L"Grond" || _col->GetOwner()->GetName() == L"PlayerHitBox")
	{
		isDead = true;
		return;
	}
	if (_col->GetOwner()->GetName() == L"PlayerBullet")
	{
		bulletInfo info = GetInfo();
		if (info.health <= 0)
		{
			SetSFX(L"CARROT_MISSILE_DEATH");
			GetSFX()->Play(false);
			GetSFX()->SetPosition(50.f);
			GetSFX()->SetVolume(100.f);
			isDead = true;
			return;
		}
		info.health -= 1;
		m_accTime = 0;
		SetInfo(info);
		SetHit(true);
	}
}

void CCarrotMissle::OnCollision(CCollider* _col)
{
	if (_col->GetOwner()->GetName() == L"PlayerBullet")
	{

		bulletInfo info = GetInfo();
		if (info.health <= 0)
		{
			isDead = true;
			return;
		}
		info.health -= 1;
		m_accTime = 0;
		SetHit(true);
		SetInfo(info);
	}
}

void CCarrotMissle::OnCollisionExit(CCollider* _col)
{
}
