#include "pch.h"
#include "CChauncey.h"
#include "CCarrotBossAttackBox.h"
#include "CCarrotEyes.h"
#include "CMonsterHitBox.h"
#include "CCollider.h"
#include "CTexture.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CResourceManager.h"
#include "CMonsterHitBox.h"
#include "FSMAI.h"
#include "CState.h"
#include "CSound.h"
#include "SelectGDI.h"
CChauncey::CChauncey()
{
	CreateAnimator();
	SetScale(Vec2(395.f,552.f));

	
	CTexture* introTex = CResourceManager::GetInst()->FindTexture(L"CarrotIntroTex");
	CTexture* idleTex = CResourceManager::GetInst()->FindTexture(L"CarrotIdleTex");
	CTexture* deathTex = CResourceManager::GetInst()->FindTexture(L"CarrotDeathTex");
	CTexture* shootTex = CResourceManager::GetInst()->FindTexture(L"CarrotShootTex");
	CTexture* transitTex = CResourceManager::GetInst()->FindTexture(L"CarrotTrasitTex");
	

	GetAnimator()->CreateAnimation(L"CARROT_INTRO", introTex, Vec2(0.f, 0.f), Vec2(595.f, 552.f), Vec2(595.f, 0.f), 1 / 16.f, 25, false);
	GetAnimator()->CreateAnimation(L"CARROT_IDLE", idleTex, Vec2(0.f, 0.f), Vec2(595.f, 552.f), Vec2(595.f, 0.f), 1 / 16.f, 22, false);
	GetAnimator()->CreateAnimation(L"CARROT_DEATH", deathTex, Vec2(0.f, 0.f), Vec2(595.f, 552.f), Vec2(595.f, 0.f), 1 / 16.f, 13, false);
	GetAnimator()->CreateAnimation(L"CARROT_SHOOT", shootTex, Vec2(0.f, 0.f), Vec2(595.f, 552.f), Vec2(595.f, 0.f), 1 / 16.f, 4, false);
	GetAnimator()->CreateAnimation(L"CARROT_TRANSIT", transitTex, Vec2(0.f, 0.f), Vec2(595.f, 552.f), Vec2(595.f, 0.f), 1 / 16.f, 9, false);
	
}

CChauncey::~CChauncey()
{
}

void CChauncey::Start()
{
	CMonster::Start();
	CreateEyes();
	m_eyes->m_offSet = Vec2(-5.f, -30.f);
	GetHitBox()->SetScale(GetScale() - Vec2(200.f, 300.f));
	GetHitBox()->GetCollider()->SetOffsetPos(Vec2(0.f, -40.f));
	GetHitBox()->SetOffset(Vec2(0.f, 50.f));
	GetHitBox()->Start();
}

void CChauncey::Update()
{
	if (GetInfo().hp <= 0)
	{
		CSound* sfx = CResourceManager::GetInst()->FindSound(L"CARROT_DEATH");
		sfx->Play(false);
		sfx->SetPosition(50.f);
		sfx->SetVolume(100.f);
		GetHitBox()->GetCollider()->SetAvaCollide(false);
		ChangeAIState(GetAi(), MON_STATE::DEAD);
		return;
	}
	if (GetAi()->GetCurrentState()->GetState() == MON_STATE::INTRO && GetAnimator()->GetCurrentAnim() == nullptr)
	{
		CSound* sfx = CResourceManager::GetInst()->FindSound(L"CARROT_INTRO");
		sfx->Play(false);
		sfx->SetPosition(50.f);
		sfx->SetVolume(100.f);
		GetAnimator()->Play(L"CARROT_INTRO", false);
	}
	GetHitBox()->Update();
	m_eyes->Update();
	CMonster::Update();


}

void CChauncey::Render(HDC _dc)
{
	if (IsHit())
	{
		if (m_renderToggle)
		{
			GetAnimator()->SetAlpha(127);
			m_renderToggle = false;
		}
		else
		{
			GetAnimator()->SetAlpha(0);
			m_renderToggle = true;
		}
	}
	else
	{
		GetAnimator()->SetAlpha(255);
	}
	ComponentRender(_dc);
	if (GetAi()->GetCurrentState()->GetState() == MON_STATE::ATTACK && ((CCarrotBossAttackBox*)m_attackBox)->GetCurrentPatt() == ATTACK_PATT::PATT2)
	{
		m_eyes->Render(_dc);
	}
}

void CChauncey::FinalUpdate()
{
	CMonster::FinalUpdate();
	if (GetAi()->GetCurrentState()->GetState() == MON_STATE::ATTACK && ((CCarrotBossAttackBox*)m_attackBox)->GetCurrentPatt() == ATTACK_PATT::PATT2)
	{
		m_eyes->FinalUpdate();
	}
}

void CChauncey::OnCollision(CCollider* _col)
{
}

void CChauncey::OnCollisionEnter(CCollider* _col)
{
}

void CChauncey::CreateAttackBox()
{
	m_attackBox = new CCarrotBossAttackBox;
	m_attackBox->m_owner = this;
}

void CChauncey::CreateEyes()
{
	m_eyes = new CCarrotEyes;
	m_eyes->m_owner = this;
}
