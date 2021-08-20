#include "pch.h"
#include "CCarrotMissle.h"
#include "CCollider.h"
#include "CRigidBody.h"
#include "CPlayer.h"
#include "CCamera.h"

#include "CSceneManager.h"
#include "CScene.h"
#include "SelectGDI.h"


CCarrotMissle::CCarrotMissle()
	:CBullet(BULLET_TYPE::CARROT_MISSILE)
	,m_maxAngle(Vec2(1,-1))
	,m_target(nullptr)
{
	CreateCollider();
	CreateRigidBody();
	
	GetCollider()->SetScale(Vec2(30.f, 70.f));
	GetRigidBody()->SetMaxVelocity(300.f);
	m_target = CSceneManager::GetInst()->GetCurrentScene()->GetTarget(GROUP_TYPE::PLAYER, L"Player");


	bulletInfo info = {};
	info.bulletSpeed = 300.f;
	info.health = 24.f;
	info.damege = 1.f;
	info.range = 1600.f;
}

CCarrotMissle::~CCarrotMissle()
{
}

void CCarrotMissle::Update()
{
	Vec2 pos = GetPos();
	Vec2 targetPos = m_target->GetPos();
	Vec2 diff = pos - targetPos;
	diff.Normalize();
	
	if (diff.Distance() > m_maxAngle.Distance())
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

void CCarrotMissle::Render(HDC _dc)
{
	Vec2 renderPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 scale = GetScale();
	SelectGDI gdi(_dc, BRUSH_TYPE::RED);
	Ellipse(
		_dc,
		(int)(renderPos.x - scale.x / 2.f),
		(int)(renderPos.y - scale.y / 2.f),
		(int)(renderPos.x + scale.x / 2.f),
		(int)(renderPos.y + scale.y / 2.f)
	);
}

void CCarrotMissle::OnCollisionEnter(CCollider* _col)
{
}

void CCarrotMissle::OnCollision(CCollider* _col)
{
}

void CCarrotMissle::OnCollisionExit(CCollider* _col)
{
}
