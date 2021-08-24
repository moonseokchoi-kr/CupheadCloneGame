#include "pch.h"
#include "CSalSpudder.h"
#include "CSalAttackBox.h"
#include "CCollider.h"
#include "CRigidBody.h"
#include "CAnimator.h"
#include "CResourceManager.h"
#include "CMonsterHitBox.h"
#include "CTexture.h"
#include "SelectGDI.h"
#include "CSalBullet.h"
CSalSpudder::CSalSpudder()
	:m_animatedTime(1/15.f)
{
	CreateCollider();
	CreateAnimator();
	GetCollider()->SetScale(Vec2(500.f, 430.f));
	CTexture* idleTex = CResourceManager::GetInst()->LoadTexture(L"PotatoIdleTex", L"texture\\cuphead\\boss\\potato_idle.bmp");//5
	CTexture* deathTex = CResourceManager::GetInst()->LoadTexture(L"PotatoDeathTex", L"texture\\cuphead\\boss\\potato_death.bmp");//34
	CTexture* introTex = CResourceManager::GetInst()->LoadTexture(L"PotatoIntroTex", L"texture\\cuphead\\boss\\potato_intro.bmp");//11
	CTexture* shootTex = CResourceManager::GetInst()->LoadTexture(L"PotatoShootTex", L"texture\\cuphead\\boss\\potato_shoot.bmp");//22

	GetAnimator()->CreateAnimation(L"POTATO_IDLE", idleTex, Vec2(0.f,0.f),Vec2(540,456),Vec2(540.f,0.f), m_animatedTime, 5, false);
	GetAnimator()->CreateAnimation(L"POTATO_DEATH", deathTex, Vec2(0.f, 0.f), Vec2(540, 456), Vec2(540.f, 0.f), m_animatedTime, 34, false);
	GetAnimator()->CreateAnimation(L"POTATO_INTRO", introTex, Vec2(0.f, 0.f), Vec2(540, 456), Vec2(540.f, 0.f), m_animatedTime, 11, false);
	GetAnimator()->CreateAnimation(L"POTATO_SHOOT", shootTex, Vec2(0.f, 0.f), Vec2(540, 456), Vec2(540.f, 0.f), m_animatedTime, 22, false);

	GetAnimator()->Play(L"POTATO_INTRO", false);
}

CSalSpudder::~CSalSpudder()
{
}
void CSalSpudder::Update()
{
	CMonster::Update();
	if (GetInfo().hp <= 0)
	{
		ChangeAIState(GetAi(), MON_STATE::DEAD);
	}
}
void CSalSpudder::Render(HDC _dc)
{
	ComponentRender(_dc);
}

void CSalSpudder::CreateAttackBox()
{
	m_attackBox = new CSalAttackBox;
	m_attackBox->m_owner = this;
}
