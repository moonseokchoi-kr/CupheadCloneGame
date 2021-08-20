#include "pch.h"
#include "CBeamMissile.h"
#include "CCollider.h"
#include "CRigidBody.h"
#include "CScene.h"
#include "CSceneManager.h"
#include "SelectGDI.h"


CBeamMissile::CBeamMissile()
	:CBullet(BULLET_TYPE::BEAM_BULLET)
{
	CreateCollider();
	CreateRigidBody();
	SetScale(Vec2(60.f, 60.f));
	GetCollider()->SetScale(Vec2(60.f, 60.f));
	GetRigidBody()->SetMaxVelocity(600.f);
}

CBeamMissile::~CBeamMissile()
{
}

void CBeamMissile::Start()
{
	CBullet::Start();
	m_targetPos = CSceneManager::GetInst()->GetCurrentScene()->GetTarget(GROUP_TYPE::PLAYER, L"Player")->GetPos();
}

void CBeamMissile::Update()
{
	Vec2 diff = m_targetPos - GetPos();
	diff.Normalize();
	GetRigidBody()->SetVelocity(diff * GetInfo().bulletSpeed);
	GetRigidBody()->AddVelocity(diff * GetInfo().bulletSpeed);

	DeleteBullet();
}

void CBeamMissile::Render(HDC _dc)
{
	Vec2 renderPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 scale = GetScale();
	SelectGDI(_dc, BRUSH_TYPE::BLUE);
	Ellipse(
		_dc,
		(int)(renderPos.x - scale.x / 2.f),
		(int)(renderPos.y - scale.y / 2.f),
		(int)(renderPos.x + scale.x / 2.f),
		(int)(renderPos.y + scale.y / 2.f)
	);
}
