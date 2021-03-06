#include "pch.h"
#include "CSlimeAttackBox.h"
#include "CCollider.h"
#include "CSound.h"
#include "CRigidBody.h"
#include "CSlime.h"
#include "CPlayer.h"
CSlimeAttackBox::CSlimeAttackBox()
	:m_attackCount(0)
	,m_currentAttackPatt(ATTACK_PATT::PATT1)
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(300.f,300.f));
	GetCollider()->SetAvaCollide(false);
	SetName(L"SlimeAttackBox");
}

CSlimeAttackBox::~CSlimeAttackBox()
{
}

void CSlimeAttackBox::Start()
{
	CreateObject(this, GROUP_TYPE::MONSTER_ATTACKBOX);
}

void CSlimeAttackBox::Update()
{
	//펀치 공격에만 동작
	//페이즈 1의 펀치인지 2의 펀치인지를 잘 파악해서 동작
	Vec2 pos = GetOwner()->GetPos();
	SetPos(pos + m_offset);
}

void CSlimeAttackBox::Fire()
{
	if (m_currentAttackPatt == ATTACK_PATT::PATT2)
	{
		SetSFX(L"SLIME_PUNCH");
		GetSFX()->SetPosition(50.f);
		GetSFX()->SetVolume(20.f);
		GetSFX()->Play(false);
	}
	else
	{
		SetSFX(L"LG_SLIME_PUNCH");
		GetSFX()->SetPosition(50.f);
		GetSFX()->SetVolume(80.f);
		GetSFX()->Play(false);
	}
}

void CSlimeAttackBox::Render(HDC _dc)
{
	ComponentRender(_dc);
}

void CSlimeAttackBox::OnCollisionEnter(CCollider* _col)
{
	CObject* obj = _col->GetOwner();
	if (obj->GetName() == L"Player")
	{
		playerInfo  info = ((CPlayer*)obj)->GetInfo();
		info.health -= 1;
		((CPlayer*)obj)->SetHit(true);
		ChangePlayerState(((CPlayer*)obj)->GetAi(), PLAYER_STATE::HIT);
	}
}

void CSlimeAttackBox::OnCollision(CCollider* _col)
{
	CObject* obj = _col->GetOwner();
	if (obj->GetName() == L"Player")
	{
		playerInfo  info = ((CPlayer*)obj)->GetInfo();
		((CPlayer*)obj)->SetHit(true);
	}
}

void CSlimeAttackBox::OnCollisionExit(CCollider* _col)
{
}

Vec2 CSlimeAttackBox::GetTargetDiff()
{
	return Vec2();
}
