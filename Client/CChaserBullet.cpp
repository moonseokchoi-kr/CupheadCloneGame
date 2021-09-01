#include "pch.h"
#include "CChaserBullet.h"
#include "CCollider.h"
#include "CRigidBody.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CSceneManager.h"
#include "CScene.h"
#include "CSound.h"
#include "CResourceManager.h"
#include "CHomingBulletTraile.h"
CChaserBullet::CChaserBullet()
	:CBullet(BULLET_TYPE::CHASER)
	, m_fx(nullptr)
	, m_target(nullptr)
	, m_isDead(false)
{
	CreateCollider();
	CreateRigidBody();
	CreateAnimator();
	SetScale(Vec2(40.f, 70.f));
	GetCollider()->SetScale(Vec2(40.f, 80.f));
	GetCollider()->SetOffsetPos(Vec2(0.f, 10.f));
	GetRigidBody()->SetMaxVelocity(600.f);
	m_target = CSceneManager::GetInst()->GetCurrentScene()->GetTarget(GROUP_TYPE::MONSTER_HITBOX, L"MonsterHitBox");
	m_maxAngle = Vec2(1.f, 0.7f);

	bulletInfo info = {};
	info.bulletSpeed = 600.f;
	info.damege = 7.f;
	info.range = 1600.f;
	info.health = 3;
	SetInfo(info);

	CTexture* homingTex = CResourceManager::GetInst()->FindTexture(L"HomingBulletTex");
	CTexture* homingDeathTex= CResourceManager::GetInst()->FindTexture(L"HomingBulletDeathTex");
	GetAnimator()->CreateAnimation(L"CHASER_LOOP", homingTex, Vec2(0.f, 0.f), Vec2(51.f, 54.f), Vec2(51.f, 0.f), 1 / 30.f, 8, false);
	GetAnimator()->CreateAnimation(L"CHASER_DEATH", homingDeathTex, Vec2(0.f, 0.f), Vec2(95.f, 109.f), Vec2(95.f, 0.f), 1 / 30.f, 4, false);

	m_target = CSceneManager::GetInst()->GetCurrentScene()->GetTarget(GROUP_TYPE::MONSTER_HITBOX, L"MonsterHitBox");

}

CChaserBullet::~CChaserBullet()
{
	delete m_fx;
}

void CChaserBullet::Start()
{
	CBullet::Start();
	m_fx = new CHomingBulletTraile;

	m_fx->m_owner = this;
}

void CChaserBullet::Update()
{
	if (m_isDead)
	{
		GetCollider()->SetAvaCollide(false);
		GetRigidBody()->SetActive(false);
		GetAnimator()->Play(L"CHASER_DEATH", false);
		if (GetAnimator()->GetCurrentAnim()->IsFinish())
		{
			GetSFX()->Stop(true);
			DeleteObject(this);
		}
		return;
	}
	m_fx->Update();
	GetAnimator()->Play(L"CHASER_LOOP", true);
	Vec2 diff = m_target->GetPos() - GetPos();
	float angle = m_target->GetPos().Cross(GetPos());
	diff.Normalize();
	if (angle < 0)
	{
		diff *= -1;
		m_maxAngle *= -1;
	}
	m_fx->SetOffset(Vec2(diff.x *40.f, 0.f));
	if (diff > m_maxAngle)
	{
		GetRigidBody()->SetVelocity(Vec2(m_maxAngle.x * GetInfo().bulletSpeed, m_maxAngle.y * GetInfo().bulletSpeed));
		GetRigidBody()->AddVelocity(Vec2(m_maxAngle.x * GetInfo().bulletSpeed, m_maxAngle.y * GetInfo().bulletSpeed));
	}
	else
	{
		GetRigidBody()->SetVelocity(Vec2(diff.x * GetInfo().bulletSpeed, diff.y * GetInfo().bulletSpeed));
		GetRigidBody()->AddVelocity(Vec2(diff.x * GetInfo().bulletSpeed, diff.y * GetInfo().bulletSpeed));
	}
	DeleteBullet();
}

void CChaserBullet::FinalUpdate()
{
	CObject::FinalUpdate();
	m_fx->FinalUpdate();
}

void CChaserBullet::Render(HDC _dc)
{
	ComponentRender(_dc);
	m_fx->Render(_dc);
}

void CChaserBullet::OnCollisionEnter(CCollider* _col)
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

void CChaserBullet::OnCollision(CCollider* _col)
{

}

void CChaserBullet::OnCollisionExit(CCollider* _col)
{
}
