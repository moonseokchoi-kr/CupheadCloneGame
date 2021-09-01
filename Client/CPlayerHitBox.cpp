#include "pch.h"
#include "CPlayerHitBox.h"
#include "CCollider.h"
#include "CPlayer.h"
#include "CRigidBody.h"
#include "CPlayerStateMachine.h"
#include "CPlayerState.h"
CPlayerHitBox::CPlayerHitBox()
	:m_owner(nullptr)
{
	CreateCollider();
	SetName(L"PlayerHitBox");
}

CPlayerHitBox::~CPlayerHitBox()
{
}

void CPlayerHitBox::Start()
{
	GetCollider()->SetScale(GetScale());
	CreateObject(this, GROUP_TYPE::PLAYER_HITBOX);
}

void CPlayerHitBox::Update()
{
	Vec2 pos = m_owner->GetPos();
	SetPos(GetOffset() + pos);
}
void CPlayerHitBox::OnCollision(CCollider* _col)
{

}

void CPlayerHitBox::OnCollisionEnter(CCollider* _col)
{
	CObject* obj = _col->GetOwner();
	if (obj->GetName() == L"Slime" || obj->GetName() == L"Potato" || obj->GetName() == L"Onion")
	{
		playerInfo info = m_owner->GetInfo();
		Vec2 moveDir = m_owner->GetMoveDir();
		if (!m_owner->IsInfinite())
			info.health -= 1;
		m_owner->GetRigidBody()->SetVelocity(Vec2(-moveDir.x * 200.f, 200.f));
		m_owner->GetRigidBody()->AddForce(Vec2(-moveDir.x * 200.f, 200.f));
		m_owner->SetInfo(info);
		m_owner->SetHit(true);
		ChangePlayerState(m_owner->GetAi(), PLAYER_STATE::HIT);
	}
	if ((obj->GetName() == L"MonsterBullet"|| obj->GetName() == L"BeamBullet") && m_owner->GetAi()->GetCurrentState()->GetState() != PLAYER_STATE::HIT&& !m_owner->IsHit())
	{
		playerInfo info = m_owner->GetInfo();
		if(!m_owner->IsInfinite())
			info.health -= 1;
		m_owner->SetInfo(info);
		m_owner->SetHit(true);
		ChangePlayerState(m_owner->GetAi(), PLAYER_STATE::HIT);
	}
}

void CPlayerHitBox::OnCollisionExit(CCollider* _col)
{
}


