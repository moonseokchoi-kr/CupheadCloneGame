#include "pch.h"
#include "CSlime.h"
#include "CCollider.h"
#include "CGravity.h"
#include "CRigidBody.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CSlimeAttackBox.h"
#include "CMonsterHitBox.h"
#include "CSound.h"
#include "CResourceManager.h"
#include "CTexture.h"
#include "CCore.h"
#include "FSMAI.h"
#include "CState.h"
#include "CKeyManager.h"
#include "SelectGDI.h"
CSlime::CSlime()
	:m_currentPhase(PHASE::PHASE1)
{
	CreateCollider();
	CreateAnimator();
	CreateRigidBody();
	CreateGravity();
	SetScale(Vec2(220.f, 180.f));
	GetCollider()->SetScale(Vec2(220.f, 180.f));	

	float animateTime = 1/15.f;
	CTexture* lgSlimeAirDownTex = CResourceManager::GetInst()->FindTexture(L"lgSlimeAirDownTex");
	CTexture* lgSlimeAirUpTex = CResourceManager::GetInst()->FindTexture(L"lgSlimeAirUpTex");
	CTexture* lgSlimeDeathTex = CResourceManager::GetInst()->FindTexture(L"lgSlimeDeathTex");
	CTexture* lgSlimeIdleTex = CResourceManager::GetInst()->FindTexture(L"lgSlimeIdleTex");
	CTexture* lgSlimeJumpTex = CResourceManager::GetInst()->FindTexture(L"lgSlimeJumpTex");
	CTexture* lgSlimePunchTex = CResourceManager::GetInst()->FindTexture(L"lgSlimePunchTex");
	CTexture* lgSlimeTurnPunchTex = CResourceManager::GetInst()->FindTexture(L"lgSlimeTurnPunchTex");
	CTexture* lgSlimeUpDownTurnTex = CResourceManager::GetInst()->FindTexture(L"lgSlimeUpDownTurnTex");
	CTexture* slimeAirTurnTex = CResourceManager::GetInst()->FindTexture(L"slimeAirTurnTex");
	CTexture* slimeIntroTex = CResourceManager::GetInst()->FindTexture(L"slimeIntroTex");
	CTexture* slimeMorphTex = CResourceManager::GetInst()->FindTexture(L"slimeMorphTex");
	CTexture* slimePunchTex = CResourceManager::GetInst()->FindTexture(L"slimePunchTex");
	CTexture* slimePunchTurnTex = CResourceManager::GetInst()->FindTexture(L"slimePunchTurnTex");
	CTexture* slimeJumpTex = CResourceManager::GetInst()->FindTexture(L"slimeJumpTex");

	GetAnimator()->CreateAnimation(L"LG_SLIME_AIR_DOWN_LEFT", lgSlimeAirDownTex, Vec2(0.f, 0.f), Vec2(1250.f, 568.f), Vec2(1250.f, 0.f), animateTime, 5, false);
	GetAnimator()->CreateAnimation(L"LG_SLIME_AIR_DOWN_RIGHT", lgSlimeAirDownTex, Vec2(0.f, 568.f), Vec2(1250.f, 568.f), Vec2(1250.f, 0.f), animateTime, 5, true);
	GetAnimator()->CreateAnimation(L"LG_SLIME_AIR_UP_LEFT", lgSlimeAirUpTex, Vec2(0.f, 0.f), Vec2(1250.f, 568.f), Vec2(1250.f, 0.f), animateTime, 4, false);
	GetAnimator()->CreateAnimation(L"LG_SLIME_AIR_UP_RIGHT", lgSlimeAirUpTex, Vec2(0.f, 568.f), Vec2(1250.f, 568.f), Vec2(1250.f, 0.f), animateTime, 4, true);
	
	GetAnimator()->CreateAnimation(L"LG_SLIME_DEATH_LEFT_1", lgSlimeDeathTex, Vec2(0.f, 0.f), Vec2(1250.f, 568.f), Vec2(1250.f, 0.f), animateTime, 10, false);
	GetAnimator()->CreateAnimation(L"LG_SLIME_DEATH_LEFT_2", lgSlimeDeathTex, Vec2(0.f, 568.f), Vec2(1250.f, 568.f), Vec2(1250.f, 0.f), animateTime, 10, false);
	GetAnimator()->CreateAnimation(L"LG_SLIME_DEATH_RIGHT_1", lgSlimeDeathTex, Vec2(0.f, 1136.f), Vec2(1250.f, 568.f), Vec2(1250.f, 0.f), animateTime, 10, true);
	GetAnimator()->CreateAnimation(L"LG_SLIME_DEATH_RIGHT_2", lgSlimeDeathTex, Vec2(0.f, 1704.f), Vec2(1250.f, 568.f), Vec2(1250.f, 0.f), animateTime, 10, true);
	
	GetAnimator()->CreateAnimation(L"LG_SLIME_IDLE_LEFT", lgSlimeIdleTex, Vec2(0.f, 0.f), Vec2(1250.f, 568.f), Vec2(1250.f, 0.f), animateTime, 5, false);
	GetAnimator()->CreateAnimation(L"LG_SLIME_IDLE_RIGHT", lgSlimeIdleTex, Vec2(0.f, 568.f), Vec2(1250.f, 568.f), Vec2(1250.f, 0.f), animateTime, 5, true);
	
	GetAnimator()->CreateAnimation(L"LG_SLIME_JUMP_LEFT", lgSlimeJumpTex, Vec2(0.f, 0.f), Vec2(1250.f, 568.f), Vec2(1250.f, 0.f), animateTime, 8, false);
	GetAnimator()->CreateAnimation(L"LG_SLIME_JUMP_RIGHT", lgSlimeJumpTex, Vec2(0.f, 568.f), Vec2(1250.f, 568.f), Vec2(1250.f, 0.f), animateTime, 8, true);
	
	GetAnimator()->CreateAnimation(L"LG_SLIME_PUNCH_LEFT", lgSlimePunchTex, Vec2(0.f, 0.f), Vec2(1250.f, 568.f), Vec2(1250.f, 0.f), animateTime, 19, false);
	GetAnimator()->CreateAnimation(L"LG_SLIME_PUNCH_RIGHT", lgSlimePunchTex, Vec2(0.f, 568.f), Vec2(1250.f, 568.f), Vec2(1250.f, 0.f), animateTime, 19, true);

	GetAnimator()->CreateAnimation(L"LG_SLIME_PUNCH_TURN_LEFT", lgSlimeTurnPunchTex, Vec2(0.f, 0.f), Vec2(1250.f, 568.f), Vec2(1250.f, 0.f), animateTime, 7, false);
	GetAnimator()->CreateAnimation(L"LG_SLIME_PUNCH_TURN_RIGHT", lgSlimeTurnPunchTex, Vec2(0.f, 568.f), Vec2(1250.f, 568.f), Vec2(1250.f, 0.f), animateTime, 7, true);

	GetAnimator()->CreateAnimation(L"LG_SLIME_UP_DOWN_TURN_LEFT", lgSlimeUpDownTurnTex, Vec2(0.f, 0.f), Vec2(1250.f, 568.f), Vec2(1250.f, 0.f), animateTime, 5, false);
	GetAnimator()->CreateAnimation(L"LG_SLIME_UP_DOWN_TURN_RIGHT", lgSlimeUpDownTurnTex, Vec2(0.f, 568.f), Vec2(1250.f, 568.f), Vec2(1250.f, 0.f), animateTime, 5, true);

	GetAnimator()->CreateAnimation(L"SLIME_AIR_DOWN_LEFT", slimeAirTurnTex, Vec2(0.f, 0.f), Vec2(1250.f, 568.f), Vec2(1250.f, 0.f), animateTime, 3, false);
	GetAnimator()->CreateAnimation(L"SLIME_AIR_UP_LEFT", slimeAirTurnTex, Vec2(0.f, 568.f), Vec2(1250.f, 568.f), Vec2(1250.f, 0.f), animateTime, 3, false);
	GetAnimator()->CreateAnimation(L"SLIME_AIR_DOWN_TURN_LEFT", slimeAirTurnTex, Vec2(0.f, 1136.f), Vec2(1250.f, 568.f), Vec2(1250.f, 0.f), animateTime, 3, false);
	GetAnimator()->CreateAnimation(L"SLIME_AIR_UP_TURN_LEFT", slimeAirTurnTex, Vec2(0.f, 1704.f), Vec2(1250.f, 568.f), Vec2(1250.f, 0.f), animateTime, 3, false);

	GetAnimator()->CreateAnimation(L"SLIME_AIR_DOWN_RIGHT", slimeAirTurnTex, Vec2(0.f, 2272.f), Vec2(1250.f, 568.f), Vec2(1250.f, 0.f), animateTime, 3, true);
	GetAnimator()->CreateAnimation(L"SLIME_AIR_UP_RIGHT", slimeAirTurnTex, Vec2(0.f, 2840.f), Vec2(1250.f, 568.f), Vec2(1250.f, 0.f), animateTime, 3, true);
	GetAnimator()->CreateAnimation(L"SLIME_AIR_DOWN_TURN_RIGHT", slimeAirTurnTex, Vec2(0.f, 3408.f), Vec2(1250.f, 568.f), Vec2(1250.f, 0.f), animateTime, 3, true);
	GetAnimator()->CreateAnimation(L"SLIME_AIR_UP_TURN_RIGHT", slimeAirTurnTex, Vec2(0.f, 3976.f), Vec2(1250.f, 568.f), Vec2(1250.f, 0.f), animateTime, 3, true);


	GetAnimator()->CreateAnimation(L"SLIME_INTRO_1", slimeIntroTex, Vec2(0.f, 0.f), Vec2(1250.f, 568.f), Vec2(1250.f, 0.f), animateTime, 9, false);
	GetAnimator()->CreateAnimation(L"SLIME_INTRO_2", slimeIntroTex, Vec2(0.f, 568.f), Vec2(1250.f, 568.f), Vec2(1250.f, 0.f), animateTime, 9, false);
	GetAnimator()->CreateAnimation(L"SLIME_INTRO_3", slimeIntroTex, Vec2(0.f,1136.f), Vec2(1250.f, 568.f), Vec2(1250.f, 0.f), animateTime, 9, false);

	GetAnimator()->CreateAnimation(L"SLIME_MORPH_LEFT_1", slimeMorphTex, Vec2(0.f, 0.f), Vec2(1250.f, 568.f), Vec2(1250.f, 0.f), animateTime, 24, false);
	GetAnimator()->CreateAnimation(L"SLIME_MORPH_LEFT_2", slimeMorphTex, Vec2(0.f, 568.f), Vec2(1250.f, 568.f), Vec2(1250.f, 0.f), animateTime, 24, false);
	GetAnimator()->CreateAnimation(L"SLIME_MORPH_RIGHT_1", slimeMorphTex, Vec2(0.f, 1136.f), Vec2(1250.f, 568.f), Vec2(1250.f, 0.f), animateTime, 24, true);
	GetAnimator()->CreateAnimation(L"SLIME_MORPH_RIGHT_2", slimeMorphTex, Vec2(0.f, 1704.f), Vec2(1250.f, 568.f), Vec2(1250.f, 0.f), animateTime, 24, true);

	GetAnimator()->CreateAnimation(L"SLIME_PUNCH_LEFT", slimePunchTex, Vec2(0.f, 0.f), Vec2(1250.f, 568.f), Vec2(1250.f, 0.f), animateTime, 16, false);
	GetAnimator()->CreateAnimation(L"SLIME_PUNCH_RIGHT", slimePunchTex, Vec2(0.f, 568.f), Vec2(1250.f, 568.f), Vec2(1250.f, 0.f), animateTime, 16, true);

	GetAnimator()->CreateAnimation(L"SLIME_PUNCH_TURN_LEFT", slimePunchTurnTex, Vec2(0.f, 0.f), Vec2(1250.f, 568.f), Vec2(1250.f, 0.f), animateTime, 6, false);
	GetAnimator()->CreateAnimation(L"SLIME_PUNCH_TURN_RIGHT", slimePunchTurnTex, Vec2(0.f, 568.f), Vec2(1250.f, 568.f), Vec2(1250.f, 0.f), animateTime, 6, true);

	GetAnimator()->CreateAnimation(L"SLIME_JUMP_LEFT", slimeJumpTex, Vec2(0.f, 0.f), Vec2(1250.f, 568.f), Vec2(1250.f, 0.f), animateTime, 9, false);
	GetAnimator()->CreateAnimation(L"SLIME_JUMP_RIGHT", slimeJumpTex, Vec2(0.f, 568.f), Vec2(1250.f, 568.f), Vec2(1250.f, 0.f), animateTime, 9, true);
}

CSlime::~CSlime()
{
}

void CSlime::Start()
{
	CMonster::Start();
	GetHitBox()->SetScale(Vec2(240.f, 200.f));
	GetHitBox()->Start();
	GetAttackBox()->Start();
	CreateVFX();
}

void CSlime::Update()
{
	
	if (GetInfo().hp <= 100.f && m_currentPhase != PHASE::PHASE2 && GetGravity()->IsGround())
	{
		m_currentPhase = PHASE::PHASE2;
		GetRigidBody()->SetActive(false);
		GetHitBox()->GetCollider()->SetAvaCollide(false);
		CSound* sfx = CResourceManager::GetInst()->FindSound(L"SLIME_MORPH");
		sfx->Play(false);
		sfx->SetPosition(50.f);
		sfx->SetVolume(100.f);
		ChangeAIState(GetAi(), MON_STATE::INTRO);
		if (GetMoveDir().x < 0)
		{
			GetAnimator()->Play(L"SLIME_MORPH_LEFT_1", false);
		}
		else
		{
			GetAnimator()->Play(L"SLIME_MORPH_RIGHT_1", false);
		}

		return;
	}
	if (GetInfo().hp <= 0 && GetAi()->GetCurrentState()->GetState() != MON_STATE::DEAD)
	{
		CSound* sfx = CResourceManager::GetInst()->FindSound(L"SLIME_DEATH");
		sfx->Play(false);
		sfx->SetPosition(30.f);
		sfx->SetVolume(100.f);
		ChangeAIState(GetAi(), MON_STATE::DEAD);
		return;
	}
	if (GetAi()->GetCurrentState()->GetState() == MON_STATE::INTRO && GetAnimator()->GetCurrentAnim() == nullptr)
	{
		CSound* sfx = CResourceManager::GetInst()->FindSound(L"SLIME_INTRO");
		sfx->Play(false);
		sfx->SetPosition(30.f);
		sfx->SetVolume(100.f); 
		GetAnimator()->Play(L"SLIME_INTRO_1", false);
	}
		
	m_prevMoveDir = GetMoveDir();
	CMonster::Update();

	if (CCore::GetInst()->IsDebug())
	{
		if (KEY_TAP(KEY::F3))
		{
			monsterInfo info = GetInfo();
			info.hp = 100.f;
			SetInfo(info);
		}
		
	}
}

void CSlime::Render(HDC _dc)
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

void CSlime::CreateAttackBox()
{
	m_attackBox = new CSlimeAttackBox;
	m_attackBox->m_owner = this;
}
