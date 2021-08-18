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

void CBullet::Update()
{
	Vec2 pos = GetPos();
	GetRigidBody()->SetVelocity(m_info.moveDir*1000.f);
	GetRigidBody()->AddVelocity(Vec2(m_info.bulletSpeed * m_info.moveDir.x, m_info.bulletSpeed * m_info.moveDir.y));
	
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