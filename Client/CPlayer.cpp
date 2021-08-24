#include "pch.h"
#include "CPlayer.h"
#include "CCollider.h"
#include "CPeaShootBullet.h"
#include "CPlayerAttackBox.h"
#include "CSceneManager.h"
#include "CKeyManager.h"
#include "CTimeManager.h"
#include "CPathManager.h"
#include "CResourceManager.h"

#include "CTexture.h"
#include "CAnimator.h"
#include "CRigidBody.h"

#include "CAnimation.h"
#include "CGravity.h"

#include "CPlayerState.h"
#include "CPlayerIdleState.h"
#include "CPlayerAttackState.h"
#include "CPlayerDashState.h"
#include "CPlayerJumpState.h"
#include "CPlayerDeathState.h"
#include "CPlayerHitState.h"

#include "CPlayerStateMachine.h"
#include "CPlayerHitBox.h"

CPlayer::CPlayer()
	: m_weaponMode(1)
	, m_curState(PLAYER_STATE::IDLE)
	, m_prevState(PLAYER_STATE::ATTACK)
	,m_animateTime(1/15.f)
	, m_ai(nullptr)
	,m_hit(false)
	,m_renderToggle(false)
	,m_accTime(0.5f)
{
	
	CreateCollider();

	GetCollider()->SetScale(Vec2(80.f,100.f));
	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
	CTexture* idle_tex = CResourceManager::GetInst()->LoadTexture(L"PlayerIdleTex", L"texture\\cuphead\\player\\idle_sheet.bmp");

	CTexture* turn_tex = CResourceManager::GetInst()->LoadTexture(L"PlayerRunTurnTex", L"texture\\cuphead\\player\\normal_run_turn.bmp");
	
	CTexture* run_tex = CResourceManager::GetInst()->LoadTexture(L"PlayerNormalRunTex", L"texture\\cuphead\\player\\run_sprite.bmp");

	CTexture* run_shoot_tex = CResourceManager::GetInst()->LoadTexture(L"PlayerRunShootTex", L"texture\\cuphead\\player\\run_shoot.bmp");
	CTexture* run_shoot_up_tex = CResourceManager::GetInst()->LoadTexture(L"PlayerRunShootUpTex", L"texture\\cuphead\\player\\direction_up_shoot_sprite.bmp");
	
	CTexture* run_shoot_turn_tex = CResourceManager::GetInst()->LoadTexture(L"PlayerRunShootTurnTex", L"texture\\cuphead\\player\\shoot_run_turn.bmp");
	CTexture* run_shoot_up_turn_tex = CResourceManager::GetInst()->LoadTexture(L"PlayerRunShootUpTurnTex", L"texture\\cuphead\\player\\shoot_up_turn.bmp");


	CTexture* shoot_tex = CResourceManager::GetInst()->LoadTexture(L"PlayerShootTex", L"texture\\cuphead\\player\\shoot_sprite.bmp");

	
	
	CTexture* dash_tex = CResourceManager::GetInst()->LoadTexture(L"PlayerDashTex", L"texture\\cuphead\\player\\dash_sprite.bmp");

	CTexture* jump_tex = CResourceManager::GetInst()->LoadTexture(L"PlayerJumpTex", L"texture\\cuphead\\player\\jump_sprite.bmp");

	CreateAnimator();
	CreateRigidBody();
	CreateGravity();



	GetAnimator()->CreateAnimation(L"PLAYER_IDLE_RIGHT", idle_tex, Vec2(0.f, 0.f), Vec2(98.f, 155.f), Vec2(98.f, 0.f), 1/15.f, 5, false);
	GetAnimator()->CreateAnimation(L"PLAYER_IDLE_LEFT", idle_tex, Vec2(0.f, 155.f), Vec2(98.f, 155.f), Vec2(98.f, 0.f), 1/15.f, 5, true);

	GetAnimator()->CreateAnimation(L"PLAYER_RUN_TURN_LEFT", turn_tex, Vec2(0.f, 164.f), Vec2(135.f, 164.f), Vec2(135.f, 0.f), m_animateTime, 2, true);
	GetAnimator()->CreateAnimation(L"PLAYER_RUN_TURN_RIGHT", turn_tex, Vec2(0.f, 0.f), Vec2(135.f, 164.f), Vec2(135.f, 0.f), m_animateTime, 2, false);

	GetAnimator()->CreateAnimation(L"PLAYER_SHOOT_RUN_TURN_LEFT", run_shoot_turn_tex, Vec2(0.f, 175.f), Vec2(143.f, 175.f), Vec2(143.f, 0.f), m_animateTime, 2, true);
	GetAnimator()->CreateAnimation(L"PLAYER_SHOOT_RUN_TURN_RIGHT", run_shoot_turn_tex, Vec2(0.f, 0.f), Vec2(143.f, 175.f), Vec2(143.f, 0.f), m_animateTime, 2, false);

	GetAnimator()->CreateAnimation(L"PLAYER_SHOOT_RUN_UP_RIGHT",run_shoot_up_tex,Vec2(0.f,0.f),Vec2(143.f,157.f),Vec2(143.f,0.f),m_animateTime, 16, false);
	GetAnimator()->CreateAnimation(L"PLAYER_SHOOT_RUN_UP_LEFT",run_shoot_up_tex,Vec2(0.f,157.f),Vec2(143.f,157.f),Vec2(143.f,0.f),m_animateTime, 16, true);

	GetAnimator()->CreateAnimation(L"PLAYER_SHOOT_RUN_UP_TURN_RIGHT", run_shoot_up_turn_tex, Vec2(0.f, 0.f), Vec2(187.f, 175.f), Vec2(187.f, 0.f), m_animateTime, 2, false);
	GetAnimator()->CreateAnimation(L"PLAYER_SHOOT_RUN_UP_TURN_LEFT", run_shoot_up_turn_tex, Vec2(0.f, 175.f), Vec2(187.f, 175.f), Vec2(187.f, 0.f), m_animateTime, 2, true);


	GetAnimator()->CreateAnimation(L"PLAYER_NORMAL_RUN_LEFT", run_tex, Vec2(0.f, 169.f), Vec2(137.f, 169.f), Vec2(137.f, 0.f), m_animateTime, 16, true);
	GetAnimator()->CreateAnimation(L"PLAYER_NORMAL_RUN_RIGHT", run_tex, Vec2(0.f, 0.f), Vec2(137.f, 169.f), Vec2(137.f, 0.f), m_animateTime, 16, false);

	GetAnimator()->CreateAnimation(L"PLAYER_SHOOT_RUN_LEFT", run_shoot_tex, Vec2(0.f, 168.f), Vec2(144.f, 168.f), Vec2(144.f, 0.f), m_animateTime, 16, true);
	GetAnimator()->CreateAnimation(L"PLAYER_SHOOT_RUN_RIGHT", run_shoot_tex, Vec2(0.f, 0.f), Vec2(144.f, 168.f), Vec2(144.f, 0.f), m_animateTime, 16, false);
	
	GetAnimator()->CreateAnimation(L"PLAYER_SHOOT_DIAGNOAL_DOWN_RIGHT", shoot_tex, Vec2(0.f, 0.f), Vec2(127.f, 172.f), Vec2(127.f, 0.f), m_animateTime, 3, false);
	GetAnimator()->CreateAnimation(L"PLAYER_SHOOT_DIAGNOAL_DOWN_LEFT", shoot_tex, Vec2(381.f, 0.f), Vec2(127.f, 172.f), Vec2(127.f, 0.f), m_animateTime, 3, true);
	GetAnimator()->CreateAnimation(L"PLAYER_SHOOT_DIAGNOAL_UP_RIGHT", shoot_tex, Vec2(762.f, 0.f), Vec2(127.f, 172.f), Vec2(127.f, 0.f), m_animateTime, 3, false);
	GetAnimator()->CreateAnimation(L"PLAYER_SHOOT_DIAGNOAL_UP_LEFT", shoot_tex, Vec2(1143.f, 0.f), Vec2(127.f, 172.f), Vec2(127.f, 0.f), m_animateTime, 3, true);
	GetAnimator()->CreateAnimation(L"PLAYER_SHOOT_STRAGIHT_RIGHT", shoot_tex, Vec2(0.f, 172.f), Vec2(127.f, 172.f), Vec2(127.f, 0.f), m_animateTime, 3, false);
	GetAnimator()->CreateAnimation(L"PLAYER_SHOOT_STRAGIHT_LEFT", shoot_tex, Vec2(381.f,172.f), Vec2(127.f, 172.f), Vec2(127.f, 0.f), m_animateTime, 3, true);
	GetAnimator()->CreateAnimation(L"PLAYER_SHOOT_DOWN", shoot_tex, Vec2(762.f, 172.f), Vec2(127.f, 172.f), Vec2(127.f, 0.f), m_animateTime, 3, false);
	GetAnimator()->CreateAnimation(L"PLAYER_SHOOT_UP", shoot_tex, Vec2(1143.f, 172.f), Vec2(127.f, 172.f), Vec2(127.f, 0.f), m_animateTime, 3, false);

	GetAnimator()->CreateAnimation(L"PLAYER_DASH_GROUND_RIGHT", dash_tex, Vec2(0.f, 0.f), Vec2(326.f, 163.f), Vec2(326.f, 0.f), m_animateTime, 8, false);
	GetAnimator()->CreateAnimation(L"PLAYER_DASH_AIR_RIGHT", dash_tex, Vec2(0.f, 163.f), Vec2(326.f, 163.f), Vec2(326.f, 0.f), m_animateTime, 8, false);
	GetAnimator()->CreateAnimation(L"PLAYER_DASH_GROUND_LEFT", dash_tex, Vec2(0.f, 326.f), Vec2(326.f, 163.f), Vec2(326.f, 0.f), m_animateTime, 8, true);
	GetAnimator()->CreateAnimation(L"PLAYER_DASH_AIR_LEFT", dash_tex, Vec2(0.f, 489.f), Vec2(326.f, 163.f), Vec2(326.f, 0.f), m_animateTime, 8, true);

	GetAnimator()->CreateAnimation(L"PLAYER_JUMP_RIGHT", jump_tex, Vec2(0.f, 0.f), Vec2(93.f, 124.f), Vec2(93.f, 0.f), m_animateTime, 8, false);
	GetAnimator()->CreateAnimation(L"PLAYER_JUMP_LEFT", jump_tex, Vec2(0.f, 124.f), Vec2(93.f, 124.f), Vec2(93.f, 0.f), m_animateTime, 8, true);


	m_info.attackSpeed = 0.15f;
	m_info.dashDist = 300.f;
	m_info.dashtime = 0.1f;
	m_info.health = 3.f;
	m_info.jupAccTime = 0.15f;
	m_info.moveSpeed = 400.f;
	m_info.prevMoveDir = Vec2(0, 0);
	m_info.shootDir = Vec2(1, 0);

	
}



CPlayer::~CPlayer()
{
	delete m_attackBox;
}

void CPlayer::Start()
{
	SetName(L"Player");
	CPlayerStateMachine* ai = new CPlayerStateMachine;
	CPlayerState* state = new CPlayerIdleState;
	ai->AddState(state);
	state = new CPlayerAttackState;
	ai->AddState(state);
	state = new CPlayerJumpState;
	ai->AddState(state);
	state = new CPlayerDashState;
	ai->AddState(state);
	state = new CPlayerHitState;
	ai->AddState(state);
	state = new CPlayerDeathState;
	ai->AddState(state);
	ai->SetCurrentState(PLAYER_STATE::IDLE);
	SetAi(ai);
	CreateAttackBox();
	CreateHitBox();
	if (nullptr != m_attackBox)
	{
		m_attackBox->SetPos(Vec2(50.f, -3.f));
		CBullet* bullet = new CPeaShootBullet;
		m_attackBox->AddBullet(bullet);
		m_attackBox->SetCurrentBullet(BULLET_TYPE::PEASHOOT);
	}
	if (nullptr != m_hitBox)
	{
		m_hitBox->SetScale(Vec2(70.f, 90.f));
		m_hitBox->SetOffset(Vec2(30.f, 0.f));
		m_hitBox->Start();
	}
		
	if (GetRigidBody())
		GetRigidBody()->SetMaxVelocity(400.f);
}

void CPlayer::Update()
{
	if (m_hit)
	{
		m_accTime += fDT;
	}
	if (m_accTime >= m_info.infiniteTime)
	{
		m_hit = false;
	}
	m_attackBox->Update();
	//m_hitBox->Update();
	m_ai->Update();


	SetPrevPos(GetPos());
	m_info.prevMoveDir = GetMoveDir();
	calMoveDir();
	
	if (m_info.health <= 0 && m_ai->GetCurrentState()->GetState() != PLAYER_STATE::DEAD)
	{
		ChangePlayerState(m_ai, PLAYER_STATE::DEAD);
	}
}

void CPlayer::Render(HDC _dc)
{
	if (m_hit)
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
#ifdef _DEBUG
	m_attackBox->Render(_dc);
	//m_hitBox->Render(_dc);
#endif
	
}
void CPlayer::OnCollisionEnter(CCollider* _col)
{
	CObject* obj = _col->GetOwner();

	
	if (obj->GetName() == L"Ground")
	{
		m_isAir = false;
	}

}
void CPlayer::OnCollision(CCollider* _col)
{

}
void CPlayer::OnCollisionExit(CCollider* _col)
{
	CObject* obj = _col->GetOwner();
	if (obj->GetName() == L"Platform" && m_ai->GetCurrentState()->GetState() != PLAYER_STATE::JUMP)
	{
		ChangePlayerState(m_ai, PLAYER_STATE::JUMP);
	}

}
void CPlayer::FinalUpdate()
{
	CObject::FinalUpdate();
	//m_hitBox->FinalUpdate();
}
void CPlayer::SetAi(CPlayerStateMachine* _ai)
{
	m_ai = _ai;
	m_ai->m_owner = this;
}
void CPlayer::CreateAttackBox()
{
	m_attackBox = new CPlayerAttackBox;
	m_attackBox->m_owner = this;
}
void CPlayer::CreateHitBox()
{
	m_hitBox = new CPlayerHitBox;
	m_hitBox->m_owner = this;
}
void CPlayer::UpdateMove()
{
	CRigidBody* rigidBody = GetRigidBody();
	Vec2 moveDir = GetMoveDir();

	
	if (KEY_TAP(KEY::LEFT))
	{

		m_info.shootDir = Vec2(-1, 0);
		if (GetGravity()->IsGround())
		{
			rigidBody->SetVelocity(Vec2(-m_info.moveSpeed, rigidBody->GetVelocity().y));
		}

	}
	if (KEY_TAP(KEY::RIGHT))
	{

		m_info.shootDir = Vec2(-1, 0);
		if (GetGravity()->IsGround())
		{
			rigidBody->SetVelocity(Vec2(m_info.moveSpeed, rigidBody->GetVelocity().y));
		}
	}

	if (GetGravity()->IsGround())
	{
		if (KEY_AWAY(KEY::LEFT) || KEY_AWAY(KEY::RIGHT))
		{
			rigidBody->SetVelocity(Vec2(0.f, rigidBody->GetVelocity().y));
		}
	}
	

	if (KEY_HOLD(KEY::UP))
	{
		m_info.shootDir = Vec2(0, -1);
	}
	if (KEY_HOLD(KEY::DOWN))
	{
		m_info.shootDir = Vec2(0, 1);
	}
	if (KEY_HOLD(KEY::LEFT))
	{
		m_info.shootDir = Vec2(-1, 0);
		if (KEY_HOLD(KEY::UP))
		{
			m_info.shootDir = Vec2(-1, -1);
		}
	
		if (GetGravity()->IsGround())
		{
			rigidBody->SetVelocity(Vec2(-m_info.moveSpeed, rigidBody->GetVelocity().y));
		}
		else
		{
			if (KEY_HOLD(KEY::DOWN))
			{
				m_info.shootDir = Vec2(-1, 1);
			}
		}



	}
	if (KEY_HOLD(KEY::RIGHT))
	{
		m_info.shootDir = Vec2(1, 0);
		if (KEY_HOLD(KEY::UP))
		{
			m_info.shootDir = Vec2(1, -1);
		}
		

		if (GetGravity()->IsGround())
		{
			rigidBody->SetVelocity(Vec2(m_info.moveSpeed, rigidBody->GetVelocity().y));
		}
		else
		{
			if (KEY_HOLD(KEY::DOWN))
			{
				m_info.shootDir = Vec2(1, 1);
			}
		}

	}

	if (GetGravity()->IsGround())
	{
		if (KEY_TAP(KEY::X))
		{
			m_isAir = true;
			GetRigidBody()->SetMaxVelocity(800.f);
			GetRigidBody()->SetVelocity(Vec2(GetRigidBody()->GetVelocity().x, -800.f));
		}
	}

	
	
}


