#include "pch.h"
#include "COllieBullb.h"
#include "CCollider.h"
#include "COnionBossAttackBox.h"
#include "FSMAI.h"
#include "CState.h"
#include "CMonsterHitBox.h"
#include "CTexture.h"
#include "CAnimator.h"
#include "CResourceManager.h"
#include "SelectGDI.h"
COllieBullb::COllieBullb()
{
	CreateCollider();
	CreateAnimator();
	SetScale(Vec2(568.f, 656.f));
	GetCollider()->SetScale(Vec2(300.f, 500.f));
	GetCollider()->SetOffsetPos(Vec2(0.f, 50.f));
	CTexture* introTex = CResourceManager::GetInst()->LoadTexture(L"OnionIntroTex", L"texture\\cuphead\\boss\\onion_intro.bmp");
	CTexture* idleTex = CResourceManager::GetInst()->LoadTexture(L"OnionIdleTex", L"texture\\cuphead\\boss\\onion_idle.bmp");
	CTexture* cryingTex = CResourceManager::GetInst()->LoadTexture(L"OnionCryingTex", L"texture\\cuphead\\boss\\onion_crying.bmp");
	CTexture* deathTex = CResourceManager::GetInst()->LoadTexture(L"OnionDeathTex", L"texture\\cuphead\\boss\\onion_death.bmp");

	GetAnimator()->CreateAnimation(L"ONION_INTRO", introTex, Vec2(0.f, 0.f), Vec2(568.f, 656.f), Vec2(568.f, 0.f), 1 / 16.f, 24, false);
	GetAnimator()->CreateAnimation(L"ONION_IDLE_1", idleTex, Vec2(0.f, 0.f), Vec2(568.f, 656.f), Vec2(568.f, 0.f), 1 / 16.f, 15, false);
	GetAnimator()->CreateAnimation(L"ONION_IDLE_2", idleTex, Vec2(0.f, 0.f), Vec2(568.f, 656.f), Vec2(568.f, 0.f), 1 / 16.f, 15, true);
	GetAnimator()->CreateAnimation(L"ONION_CRYING", cryingTex, Vec2(0.f, 0.f), Vec2(568.f, 656.f), Vec2(568.f, 0.f), 1 / 16.f, 22, false);
	GetAnimator()->CreateAnimation(L"ONION_DEATH_1", deathTex, Vec2(0.f, 0.f), Vec2(568.f, 656.f), Vec2(568.f, 0.f), 1 / 16.f, 16, false);
	GetAnimator()->CreateAnimation(L"ONION_DEATH_2", deathTex, Vec2(0.f, 656.f), Vec2(568.f, 656.f), Vec2(568.f, 0.f), 1 / 16.f, 16, false);


}

COllieBullb::~COllieBullb()
{
}

void COllieBullb::Start()
{
	CMonster::Start();
	GetHitBox()->SetScale(Vec2(400.f, 380.f));
	GetHitBox()->Start();
}

void COllieBullb::Update()
{
	if (GetAi()->GetCurrentState()->GetState() == MON_STATE::INTRO)
		GetAnimator()->Play(L"ONION_INTRO", false);
	CMonster::Update();
	if (GetInfo().hp <= 0)
	{
		ChangeAIState(GetAi(), MON_STATE::DEAD);
	}
}

void COllieBullb::Render(HDC _dc)
{
	ComponentRender(_dc);
#ifdef _DEBUG
	GetHitBox()->Render(_dc);
#endif
}

void COllieBullb::OnCollisionEnter(CCollider* _col)
{
	if (_col->GetOwner()->GetName() == L"Player_bullet")
	{
		if (GetAi()->GetCurrentState()->GetState() == MON_STATE::IDLE)
		{
			ChangeAIState(GetAi(), MON_STATE::ATTACK);
		}
	}
}

void COllieBullb::CreateAttackBox()
{
	m_attackBox = new COnionBossAttackBox;
	m_attackBox->m_owner = this;
	m_attackBox->Start();
}
