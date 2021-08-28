#include "pch.h"
#include "CMonsterHitBox.h"
#include "CCollider.h"
#include "CMonster.h"
#include "CBullet.h"
CMonsterHitBox::CMonsterHitBox()
	:m_owner(nullptr)
{
	CreateCollider();
	SetName(L"MonsterHitBox");
}

CMonsterHitBox::~CMonsterHitBox()
{
}
void CMonsterHitBox::Start()
{
	GetCollider()->SetScale(GetScale());
	CreateObject(this, GROUP_TYPE::MONSTER_HITBOX);
}
void CMonsterHitBox::Update()
{
	Vec2 pos = m_owner->GetPos();
	SetPos(pos + GetOffset());
}
void CMonsterHitBox::FinalUpdate()
{
	CObject::FinalUpdate();
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


