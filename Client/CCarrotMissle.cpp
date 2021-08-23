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
	,m_maxAngle(Vec2(0.5f,0.5f))
	,m_target(nullptr)
{
	CreateCollider();
	CreateRigidBody();
	SetScale(Vec2(40.f, 40.f));
	GetCollider()->SetScale(Vec2(30.f, 70.f));
	GetRigidBody()->SetMaxVelocity(300.f);
	m_target = CSceneManager::GetInst()->GetCurrentScene()->GetTarget(GROUP_TYPE::PLAYER, L"Player");


	bulletInfo info = {};
	info.bulletSpeed = 400.f;
	info.health = 24.f;
	info.damege = 1.f;
	info.range = 800.f;
	info.health = 3.f;
	SetInfo(info);
}

CCarrotMissle::~CCarrotMissle()
{
}

void CCarrotMissle::Update()
{
	Vec2 pos = GetPos();
	Vec2 targetPos = m_target->GetPos();
	Vec2 diff = targetPos - pos;
	diff.Normalize();
	

	
	GetRigidBody()->SetVelocity(Vec2(diff.x * GetInfo().bulletSpeed, diff.y * GetInfo().bulletSpeed));
	GetRigidBody()->AddVelocity(Vec2(diff.x * GetInfo().bulletSpeed, diff.y * GetInfo().bulletSpeed));

	if (GetInfo().health <= 0)
	{
		DeleteObject(this);
	}
	DeleteBullet();
}

void CCarrotMissle::Render(HDC _dc)
{
	Vec2 renderPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 scale = GetScale();
	SelectGDI gdi(_dc, BRUSH_TYPE::RED);
	Rectangle(
		_dc,
		(int)(renderPos.x - scale.x / 2.f),
		(int)(renderPos.y - scale.y / 2.f),
		(int)(renderPos.x + scale.x / 2.f),
		(int)(renderPos.y + scale.y / 2.f)
	);
}

void CCarrotMissle::OnCollisionEnter(CCollider* _col)
{
	if (_col->GetOwner()->GetName() == L"Grond" || _col->GetOwner()->GetName() == L"Player")
	{
		DeleteObject(this);
	}
	if (_col->GetOwner()->GetName() == L"PlayerBullet")
	{
		bulletInfo info = GetInfo();
		info.health -= 1;
		SetInfo(info);
	}
}

void CCarrotMissle::OnCollision(CCollider* _col)
{
}

void CCarrotMissle::OnCollisionExit(CCollider* _col)
{
}
