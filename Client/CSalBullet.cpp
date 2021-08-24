#include "pch.h"
#include "CSalBullet.h"
#include "CRigidBody.h"
#include "CCollider.h"



#include "SelectGDI.h"

CSalBullet::CSalBullet()
	:CBullet(BULLET_TYPE::SAL_BULLET)
{
	CreateCollider();
	CreateRigidBody();
	SetScale(Vec2(30.f, 30.f));
	GetCollider()->SetScale(Vec2(30.f, 30.f));

	bulletInfo info = {};
	info.range = 1600.f;
	info.bulletSpeed = 800.f;
	info.damege = 1;
	info.health = 3;
	GetRigidBody()->SetMaxVelocity(info.bulletSpeed);
	SetInfo(info);
	SetName(L"MonsterBullet");
}

CSalBullet::~CSalBullet()
{
}

void CSalBullet::Update()
{
	Vec2 pos = GetPos();
	bulletInfo info = GetInfo();
	Vec2 moveDir = GetMoveDir();
	GetRigidBody()->SetVelocity(moveDir * 800.f);
	GetRigidBody()->AddVelocity(Vec2(info.bulletSpeed * moveDir.x, info.bulletSpeed * moveDir.y));
	DeleteBullet();
}

void CSalBullet::Render(HDC _dc)
{
	Vec2 renderPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 scale = GetScale();
	if (m_currentBulletType == SAL_BULLET_TYPE::DUST)
	{
		Rectangle(
			_dc,
			(int)(renderPos.x - scale.x / 2.f),
			(int)(renderPos.y - scale.y / 2.f),
			(int)(renderPos.x + scale.x / 2.f),
			(int)(renderPos.y + scale.y / 2.f)
		);
	}
	else
	{
		SelectGDI gdi(_dc, BRUSH_TYPE::PURPLE);
		Ellipse(
			_dc,
			(int)(renderPos.x - scale.x / 2.f),
			(int)(renderPos.y - scale.y / 2.f),
			(int)(renderPos.x + scale.x / 2.f),
			(int)(renderPos.y + scale.y / 2.f)
		);
	}
	
}

void CSalBullet::OnCollisionEnter(CCollider* _col)
{
}

void CSalBullet::OnCollision(CCollider* _col)
{
}

void CSalBullet::OnCollisionExit(CCollider* _col)
{
}
