#include "pch.h"
#include "CPeaShootBullet.h"
#include "CBullet.h"
#include "CRigidBody.h"
#include "CCollider.h"


CPeaShootBullet::CPeaShootBullet()
	:CBullet(BULLET_TYPE::PEASHOOT)
{
	SetName(L"Player_bullet");
	bulletInfo info = {};
	info.bulletSpeed = 300.f;
	info.damege = 5.f;
	info.range = 1600.f;

	CreateCollider();
	CreateRigidBody();
	SetScale(Vec2(10.f, 10.f));
	GetCollider()->SetScale(Vec2(10.f, 10.f));
	GetRigidBody()->SetMaxVelocity(1000.f);

	SetInfo(info);
}

CPeaShootBullet::~CPeaShootBullet()
{

}

void CPeaShootBullet::Update()
{
	bulletInfo info = GetInfo();
	Vec2 moveDir = GetMoveDir();
	Vec2 pos = GetPos();
	GetRigidBody()->SetVelocity(moveDir * 1000.f);
	GetRigidBody()->AddVelocity(Vec2(info.bulletSpeed * moveDir.x, info.bulletSpeed * moveDir.y));
	DeleteBullet();
}

void CPeaShootBullet::Render(HDC _dc)
{
	CBullet::Render(_dc);
}

void CPeaShootBullet::OnCollisionEnter(CCollider* _col)
{
	if (_col->GetOwner()->GetName() == L"Monster" || _col->GetOwner()->GetName() == L"Ground")
	{
		DeleteObject(this);
	}
}

void CPeaShootBullet::OnCollision(CCollider* _col)
{
}

void CPeaShootBullet::OnCollisionExit(CCollider* _col)
{
}
