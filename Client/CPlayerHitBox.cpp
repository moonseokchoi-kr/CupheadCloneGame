#include "pch.h"
#include "CPlayerHitBox.h"
#include "CCollider.h"
#include "CPlayer.h"
#include "CPlayerStateMachine.h"
#include "CPlayerState.h"
CPlayerHitBox::CPlayerHitBox()
{
	CreateCollider();
}

CPlayerHitBox::~CPlayerHitBox()
{
}

void CPlayerHitBox::Update()
{
	Vec2 pos = m_owner->GetPos();
	SetFinalPos(pos + GetPos());
}
void CPlayerHitBox::OnCollision(CCollider* _col)
{
	CObject* obj = _col->GetOwner();
	if ((obj->GetName() == L"Monster" || obj->GetName() == L"MonsterBullet") && m_owner->GetAi()->GetCurrentState()->GetState() != PLAYER_STATE::HIT && !m_owner->IsHit())
	{
		playerInfo info = m_owner->GetInfo();
		info.health -= 1;
		m_owner->SetInfo(info);
		m_owner->SetHit(true);
		ChangePlayerState(m_owner->GetAi(), PLAYER_STATE::HIT);
	}
}

void CPlayerHitBox::OnCollisionEnter(CCollider* _col)
{
}

void CPlayerHitBox::OnCollisionExit(CCollider* _col)
{
}


