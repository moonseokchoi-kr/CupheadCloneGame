#include "pch.h"
#include "CBullet.h"
#include "CAttackBox.h"
#include "CCollider.h"
#include "CRigidBody.h"
#include "CTimeManager.h"
CBullet::CBullet(BULLET_TYPE _type)
	:m_bulletType(_type)
	,m_attackBox(nullptr)
{
	CreateCollider();
	CreateRigidBody();
	SetScale(Vec2(10.f, 10.f));
	GetCollider()->SetScale(Vec2(10.f, 10.f));
	GetRigidBody()->SetMaxVelocity(1000.f);
}

CBullet::~CBullet()
{
}


void CBullet::Start()
{
	m_initPos = GetPos();
}

void CBullet::Render(HDC _dc)
{
	Vec2 renderPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 scale = GetScale();
	Ellipse(
		_dc,
		(int)(renderPos.x - scale.x / 2.f),
		(int)(renderPos.y - scale.y / 2.f),
		(int)(renderPos.x + scale.x / 2.f),
		(int)(renderPos.y + scale.y / 2.f)
	);
	ComponentRender(_dc);
}


void CBullet::OnCollisionEnter(CCollider* _col)
{
	CObject* owner = _col->GetOwner();
	if (owner->GetName() == L"Monster" || owner->GetName() == L"Ground")
	{
		int a = 0;
		DeleteObject(this);
	}
}

void CBullet::OnCollision(CCollider* _col)
{
	CObject* owner = _col->GetOwner();
	if (owner->GetName() == L"Monster" || owner->GetName() == L"Ground")
	{
		int a = 0;
		DeleteObject(this);
	}
}

void CBullet::OnCollisionExit(CCollider* _col)
{

}

void CBullet::DeleteBullet()
{
	float dist = GetPos().Distance(m_initPos);
	if (dist > m_info.range)
		DeleteObject(this);
}
