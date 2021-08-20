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
	bulletInfo info = {};
	info.bulletSpeed = 1000.f;
	info.damege = 1.f;
	info.range = 1600;
	SetInfo(info);
}

CBeamMissile::~CBeamMissile()
{
}

void CBeamMissile::Start()
{
	CBullet::Start();
	m_targetPos = CSceneManager::GetInst()->GetCurrentScene()->GetTarget(GROUP_TYPE::PLAYER, L"Player")->GetPos();\
	m_diff = m_targetPos - GetPos();
	m_diff.Normalize();
}

void CBeamMissile::Update()
{
	
	GetRigidBody()->SetVelocity(m_diff * GetInfo().bulletSpeed);
	GetRigidBody()->AddVelocity(m_diff * GetInfo().bulletSpeed);

	DeleteBullet();
}

void CBeamMissile::Render(HDC _dc)
{
	Vec2 renderPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 scale = GetScale();
	SelectGDI gdi (_dc, BRUSH_TYPE::BLUE);
	Ellipse(
		_dc,
		(int)(renderPos.x - scale.x / 2.f),
		(int)(renderPos.y - scale.y / 2.f),
		(int)(renderPos.x + scale.x / 2.f),
		(int)(renderPos.y + scale.y / 2.f)
	);
}

void CBeamMissile::OnCollisionEnter(CCollider* _col)
{
	if (_col->GetOwner()->GetName() == L"Grond" || _col->GetOwner()->GetName() == L"Player")
	{
		DeleteObject(this);
	}
}

void CBeamMissile::OnCollision(CCollider* _col)
{
}

void CBeamMissile::OnCollisionExit(CCollider* _col)
{
}
