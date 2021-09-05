#include "pch.h"
#include "CMonsterHitBox.h"
#include "CCollider.h"
#include "CMonster.h"
#include "CBullet.h"
#include "CTimeManager.h"
CMonsterHitBox::CMonsterHitBox()
	:m_owner(nullptr)
	, m_accTime(0)
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
	if (m_owner->IsHit())
	{
		m_accTime += fDT;
		if (m_accTime >= 0.1f)
		{
			m_owner->SetHit(false);
		}
	}
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
		m_owner->SetHit(true);
		m_owner->SetInfo(info);
		m_accTime = 0;
	}
}

void CMonsterHitBox::OnCollisionExit(CCollider* _col)
{
}


