#include "pch.h"
#include "CMonsterHitBox.h"
#include "CCollider.h"
#include "CMonster.h"
#include "CBullet.h"
CMonsterHitBox::CMonsterHitBox()
	:m_owner(nullptr)
{
	CreateCollider();
}

CMonsterHitBox::~CMonsterHitBox()
{
}
void CMonsterHitBox::Update()
{
	Vec2 pos = m_owner->GetPos();
	SetFinalPos(pos + GetPos());
}
void CMonsterHitBox::OnCollision(CCollider* _col)
{
}

void CMonsterHitBox::OnCollisionEnter(CCollider* _col)
{
	CObject* obj = _col->GetOwner();
	if (obj->GetName() == L"PlayerBullet")
	{
		monsterInfo info = m_owner->GetInfo();
		info.hp -= ((CBullet*)obj)->GetInfo().damege;
	}
}

void CMonsterHitBox::OnCollisionExit(CCollider* _col)
{
}


