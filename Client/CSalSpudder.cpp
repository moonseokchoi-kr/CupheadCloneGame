#include "pch.h"
#include "CSalSpudder.h"
#include "CSalAttackBox.h"
#include "CCollider.h"
#include "CRigidBody.h"
#include "CAnimator.h"
#include "CResourceManager.h"
#include "CMonsterHitBox.h"
#include "CTexture.h"
#include "CAnimation.h"
#include "CVFXObject.h"
#include "SelectGDI.h"
#include "CSalBullet.h"
#include "FSMAI.h"
#include "CState.h"
#include "CSound.h"
CSalSpudder::CSalSpudder()
	:m_animatedTime(1/15.f)
{
	CreateCollider();
	CreateAnimator();
	GetCollider()->SetScale(Vec2(380.f, 430.f));
	CTexture* idleTex = CResourceManager::GetInst()->FindTexture(L"PotatoIdleTex");//5
	CTexture* deathTex = CResourceManager::GetInst()->FindTexture(L"PotatoDeathTex");//34
	CTexture* introTex = CResourceManager::GetInst()->FindTexture(L"PotatoIntroTex");//11
	CTexture* shootTex = CResourceManager::GetInst()->FindTexture(L"PotatoShootTex");//22

	GetAnimator()->CreateAnimation(L"POTATO_IDLE", idleTex, Vec2(0.f,0.f),Vec2(540,456),Vec2(540.f,0.f), m_animatedTime, 5, false);
	GetAnimator()->CreateAnimation(L"POTATO_DEATH", deathTex, Vec2(0.f, 0.f), Vec2(540, 456), Vec2(540.f, 0.f), m_animatedTime, 34, false);
	GetAnimator()->CreateAnimation(L"POTATO_INTRO", introTex, Vec2(0.f, 0.f), Vec2(540, 456), Vec2(540.f, 0.f), m_animatedTime, 11, false);
	GetAnimator()->CreateAnimation(L"POTATO_SHOOT", shootTex, Vec2(0.f, 0.f), Vec2(540, 456), Vec2(540.f, 0.f), m_animatedTime, 22, false);
}

CSalSpudder::~CSalSpudder()
{
}
void CSalSpudder::Start()
{
	CMonster::Start();
	GetHitBox()->SetScale(Vec2(360.f, 380.f));
	GetHitBox()->Start();

	CSound* sfx = CResourceManager::GetInst()->FindSound(L"POTATO_INTRO");
	sfx->Play(false);
	sfx->SetPosition(50.f);
	sfx->SetVolume(100.f);


}
void CSalSpudder::Update()
{
	if (GetInfo().hp <= 0 && GetAi()->GetCurrentState()->GetState() != MON_STATE::DEAD)
	{
		ChangeAIState(GetAi(), MON_STATE::DEAD);
		return;
	}
	if (GetAi()->GetCurrentState()->GetState() == MON_STATE::INTRO && GetAnimator()->GetCurrentAnim()== nullptr)
	{
		
		if (nullptr == GetVFX()->GetAnimator()->GetCurrentAnim())
		{
			GetVFX()->SetOffset(Vec2(-20.f, 80.f));
			GetVFX()->SetType(VFX_TYPE::INTRO_DUST);
		}

 			
 		if(GetVFX()->GetAnimator()->GetCurrentAnim()->GetCurrentFrame() == 8)
			GetAnimator()->Play(L"POTATO_INTRO", false);
	}
		
	CMonster::Update();

}
void CSalSpudder::Render(HDC _dc)
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
	CMonster::Render(_dc);
}

void CSalSpudder::CreateAttackBox()
{
	m_attackBox = new CSalAttackBox;
	m_attackBox->m_owner = this;
}
