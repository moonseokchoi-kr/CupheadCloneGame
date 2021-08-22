#include "pch.h"
#include "CSeedBullet.h"
#include "CCollider.h"
#include "CRigidBody.h"

#include "CSceneManager.h"
#include "CTimeManager.h"
#include "SelectGDI.h"
CSeedBullet::CSeedBullet()
	:CBullet(BULLET_TYPE::SEED_BULLET)
	,m_initTime(0.15f)
	,m_accTime(0)
	,m_targetSelect(false)
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

CSeedBullet::~CSeedBullet()
{
}

void CSeedBullet::Start()
{
	CBullet::Start();
	
}

void CSeedBullet::Update()
{
	m_accTime += fDT;
	if (m_accTime >= m_initTime)
	{
		if (!m_targetSelect)
		{
			m_prevDiff = m_diff;
			m_targetPos = CSceneManager::GetInst()->GetCurrentScene()->GetTarget(GROUP_TYPE::PLAYER, L"Player")->GetPos();
			m_diff = m_targetPos - GetPos();
			m_diff.Normalize();
			m_targetSelect = true;
		}
		else
		{
			GetRigidBody()->SetVelocity(m_diff * GetInfo().bulletSpeed);
			GetRigidBody()->AddVelocity(m_diff * GetInfo().bulletSpeed);

			DeleteBullet();
		}
	
	}
	
}

void CSeedBullet::Render(HDC _dc)
{
	Vec2 renderPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 scale = GetScale();
	SelectGDI gdi(_dc, BRUSH_TYPE::GREEN);
	Rectangle(
		_dc,
		(int)(renderPos.x - scale.x / 2.f),
		(int)(renderPos.y - scale.y / 2.f),
		(int)(renderPos.x + scale.x / 2.f),
		(int)(renderPos.y + scale.y / 2.f)
	);
	ComponentRender(_dc);
}

void CSeedBullet::OnCollisionEnter(CCollider* _col)
{
	if (_col->GetOwner()->GetName() == L"Ground" || _col->GetOwner()->GetName() == L"Player")
	{
		DeleteObject(this);
	}
}

void CSeedBullet::OnCollision(CCollider* _col)
{
}

bool CSeedBullet::randomPercent()
{
	return false;
}

void CSeedBullet::rotate()
{
	Vec2 pos = GetPos();
	Vec2 scale = GetScale();
	array<Vec2, 3> point;
	array<Vec2, 3> directVec;
	array<float, 3> distVec;
	//lt
	point[0] = Vec2(pos.x - scale.x / 2.f, pos.y - scale.x / 2.f);
	//rt
	point[1] = Vec2(pos.x + scale.x / 2.f, pos.y - scale.x / 2.f);
	//lb
	point[2] = Vec2(pos.x - scale.x / 2.f, pos.y + scale.x / 2.f);


	for(int i = 0; i < point.size(); ++i)
	{
		distVec[i] = pos.Distance(point[i]);
		Vec2 diff = point[0] - pos;
		directVec[i] = diff.Normalize();
	}
	Vec2 moveDiff = m_diff - m_prevDiff;
	float cross = m_diff.Cross(m_prevDiff);
	float angle = acosf(moveDiff.x + moveDiff.y);
	for (int i = 0; i < point.size(); ++i)
	{
		//벡터회전은 나중에 구현
	}

}
