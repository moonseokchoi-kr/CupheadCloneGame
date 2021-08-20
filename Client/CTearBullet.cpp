#include "pch.h"
#include "CTearBullet.h"
#include "CCollider.h"
#include "CRigidBody.h"
#include "SelectGDI.h"
CTearBullet::CTearBullet()
	:CBullet(BULLET_TYPE::TEAR)
	, m_redTearPercent(0.85f)
{
	CreateCollider();
	CreateRigidBody();
	SetScale(Vec2(Vec2(20.f, 60.f)));
	GetCollider()->SetScale(Vec2(20.f, 60.f));
	GetRigidBody()->SetMaxVelocity(600.f);

	bulletInfo info = {};
	info.bulletSpeed = 600.f;
	info.damege = 1;
	info.range = 1600;

	SetInfo(info);

	m_toggle = randomPercent();
}

CTearBullet::~CTearBullet()
{
}

void CTearBullet::Update()
{
	Vec2 pos = GetPos();
	GetRigidBody()->SetVelocity(Vec2(0.f,GetInfo().bulletSpeed));
	GetRigidBody()->SetVelocity(Vec2(0.f, GetInfo().bulletSpeed));

	DeleteBullet();
}

bool CTearBullet::randomPercent()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(0, 1000);
	return dis(gen) / 1000.f >= m_redTearPercent;
}

void CTearBullet::Render(HDC _dc)
{
	Vec2 renderPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 scale = GetScale();
	if (m_toggle)
	{
		SelectGDI gdi(_dc, BRUSH_TYPE::RED);

		Ellipse(
			_dc,
			(int)(renderPos.x - scale.x / 2.f),
			(int)(renderPos.y - scale.y / 2.f),
			(int)(renderPos.x + scale.x / 2.f),
			(int)(renderPos.y + scale.y / 2.f)
		);
	}
	else
	{
		SelectGDI gdi(_dc, BRUSH_TYPE::BLUE);

		Ellipse(
			_dc,
			(int)(renderPos.x - scale.x / 2.f),
			(int)(renderPos.y - scale.y / 2.f),
			(int)(renderPos.x + scale.x / 2.f),
			(int)(renderPos.y + scale.y / 2.f)
		);
	}
}
