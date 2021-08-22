#include "pch.h"
#include "CMonSeedBullet.h"
#include "CCollider.h"
#include "CRigidBody.h"
#include "CBlackFlower.h"
#include "CFlyFlower.h"
#include "SelectGDI.h"

#include "CTimeManager.h"
CMonSeedBullet::CMonSeedBullet()
	:CBullet(BULLET_TYPE::MON_SEED_BULLET)
	, m_purplePercent(0.9f)
{
	CreateCollider();
	CreateRigidBody();
	SetScale(Vec2(Vec2(20.f,30.f)));
	GetCollider()->SetScale(Vec2(20.f, 30.f));
	GetRigidBody()->SetMaxVelocity(600.f);

	bulletInfo info = {};
	info.bulletSpeed = 600.f;
	info.damege = 1;
	info.range = 1600;

	SetInfo(info);

	m_toggle = randomPercent();
	if (m_toggle)
	{
		m_createMonster = new CBlackFlower;
	}
	else
	{
		m_createMonster = new CFlyFlower;
	}
}

CMonSeedBullet::~CMonSeedBullet()
{
}

void CMonSeedBullet::Update()
{
	m_accTime += fDT;
	if (m_accTime >= m_initTime)
	{
		Vec2 pos = GetPos();
		GetRigidBody()->SetVelocity(Vec2(0.f, GetInfo().bulletSpeed));
		GetRigidBody()->SetVelocity(Vec2(0.f, GetInfo().bulletSpeed));

		DeleteBullet();
	}
}

void CMonSeedBullet::Render(HDC _dc)
{
	Vec2 renderPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 scale = GetScale();
	if (m_toggle)
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

void CMonSeedBullet::OnCollisionEnter(CCollider* _col)
{
	if (_col->GetOwner()->GetName() == L"Ground")
	{
		CreateObject(m_createMonster, GROUP_TYPE::MONSTER);
		DeleteObject(this);
	}
}

void CMonSeedBullet::OnCollision(CCollider* _col)
{
}

bool CMonSeedBullet::randomPercent()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(0, 1000);
	return dis(gen) / 1000.f >= m_purplePercent;
}
