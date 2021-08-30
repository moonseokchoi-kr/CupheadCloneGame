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
#include "CPlayerDuckState.h"
#include "CPlayerIntroState.h"
#include "CPlayerStateMachine.h"
#include "CPlayerHitBox.h"
#include "CCore.h"

CPlayer::CPlayer()
	: m_weaponMode(1)
	, m_curState(PLAYER_STATE::IDLE)
	, m_prevState(PLAYER_STATE::ATTACK)
	, m_animateTime(1 / 30.f)
	, m_ai(nullptr)
	, m_hit(false)
	, m_renderToggle(false)
	, m_infinite(false)
	,m_accTime(0.5f)
{
	SetName(L"Player");
	CreateCollider();
	//526 230
	GetCollider()->SetScale(Vec2(80.f, 120.f));
	GetCollider()->SetOffsetPos(Vec2(0.f, 50.f));
	CTexture* idle_tex = CResourceManager::GetInst()->LoadTexture(L"PlayerIdleTex", L"texture\\cuphead\\player\\player_idle.bmp");
	CTexture* intro_tex = CResourceManager::GetInst()->LoadTexture(L"PlayerIntroTex", L"texture\\cuphead\\player\\player_intro.bmp");
	CTexture* death_tex = CResourceManager::GetInst()->LoadTexture(L"PlayerDeathTex", L"texture\\cuphead\\player\\player_death.bmp");
	CTexture* turn_tex = CResourceManager::GetInst()->LoadTexture(L"PlayerRunTurnTex", L"texture\\cuphead\\player\\player_turn.bmp");
	CTexture* duck_tex = CResourceManager::GetInst()->LoadTexture(L"PlayerDucKTex", L"texture\\cuphead\\player\\player_duck.bmp");
	
	CTexture* run_tex = CResourceManager::GetInst()->LoadTexture(L"PlayerNormalRunTex", L"texture\\cuphead\\player\\player_run.bmp");

	CTexture* aim_tex = CResourceManager::GetInst()->LoadTexture(L"PlayerAimTex", L"texture\\cuphead\\player\\player_aim.bmp");
	CTexture* dash_tex = CResourceManager::GetInst()->LoadTexture(L"PlayerDashTex", L"texture\\cuphead\\player\\player_dash.bmp");

	CTexture* shoot_tex = CResourceManager::GetInst()->LoadTexture(L"PlayerShootTex", L"texture\\cuphead\\player\\player_shoot.bmp");
	CTexture* exShoot_tex = CResourceManager::GetInst()->LoadTexture(L"PlayerExShootTex", L"texture\\cuphead\\player\\player_ex_shoot.bmp");
	CTexture* exShootAir_tex = CResourceManager::GetInst()->LoadTexture(L"PlayerExShootAirTex", L"texture\\cuphead\\player\\player_ex_shoot_air.bmp");

	CTexture* jump_tex = CResourceManager::GetInst()->LoadTexture(L"PlayerJumpTex", L"texture\\cuphead\\player\\player_jump.bmp");
	CTexture* hit_tex = CResourceManager::GetInst()->LoadTexture(L"PlayerHitTex", L"texture\\cuphead\\player\\player_hit.bmp");

	CreateAnimator();
	CreateRigidBody();
	CreateGravity();



	GetAnimator()->CreateAnimation(L"PLAYER_DUCK_IDLE_RIGHT", idle_tex, Vec2(0.f, 0.f), Vec2(326.f, 230.f), Vec2(326.f, 0.f), 1/30.f, 5, false);
	GetAnimator()->CreateAnimation(L"PLAYER_DUCK_IDLE_LEFT", idle_tex, Vec2(0.f, 230.f), Vec2(326.f, 230.f), Vec2(326.f, 0.f), 1 / 30.f, 5, true);
	GetAnimator()->CreateAnimation(L"PLAYER_IDLE_RIGHT", idle_tex, Vec2(0.f, 460.f), Vec2(326.f, 230.f), Vec2(326.f, 0.f), 1 / 30.f, 5, false);
	GetAnimator()->CreateAnimation(L"PLAYER_IDLE_LEFT", idle_tex, Vec2(0.f, 690.f), Vec2(326.f, 230.f), Vec2(326.f, 0.f), 1 / 30.f, 5, true);



	GetAnimator()->CreateAnimation(L"PLAYER_RUN_TURN_RIGHT", turn_tex, Vec2(0.f, 0.f), Vec2(326.f,230.f), Vec2(326.f, 0.f), m_animateTime, 2, false);
	GetAnimator()->CreateAnimation(L"PLAYER_RUN_TURN_LEFT", turn_tex, Vec2(1304.f, 230.f), Vec2(326.f, 230.f), Vec2(326.f, 0.f), m_animateTime, 2, true);
	GetAnimator()->CreateAnimation(L"PLAYER_SHOOT_RUN_TURN_RIGHT", turn_tex, Vec2(1304.f, 0.f), Vec2(326.f, 230.f), Vec2(326.f, 0.f), m_animateTime, 2, false);
	GetAnimator()->CreateAnimation(L"PLAYER_SHOOT_RUN_TURN_LEFT", turn_tex, Vec2(0.f, 230.f), Vec2(326.f, 230.f), Vec2(326.f, 0.f), m_animateTime, 2, true);
	GetAnimator()->CreateAnimation(L"PLAYER_SHOOT_RUN_UP_TURN_RIGHT", turn_tex, Vec2(652.f, 0.f), Vec2(326.f, 230.f), Vec2(326.f, 0.f), m_animateTime, 2, false);
	GetAnimator()->CreateAnimation(L"PLAYER_SHOOT_RUN_UP_TURN_LEFT", turn_tex, Vec2(652.f, 230.f), Vec2(326.f,230.f), Vec2(326.f, 0.f), m_animateTime, 2, true);
	
	GetAnimator()->CreateAnimation(L"PLAYER_NORMAL_RUN_RIGHT", run_tex, Vec2(0.f, 0.f), Vec2(326.f, 230.f), Vec2(326.f, 0.f), m_animateTime, 16, false);
	GetAnimator()->CreateAnimation(L"PLAYER_NORMAL_RUN_LEFT", run_tex, Vec2(0.f, 230.f), Vec2(326.f, 230.f), Vec2(326.f, 0.f), m_animateTime, 16, true);
	GetAnimator()->CreateAnimation(L"PLAYER_SHOOT_RUN_RIGHT", run_tex, Vec2(0.f, 460.f), Vec2(326.f, 230.f), Vec2(326.f, 0.f), m_animateTime, 16, false);
	GetAnimator()->CreateAnimation(L"PLAYER_SHOOT_RUN_LEFT", run_tex, Vec2(0.f, 690.f), Vec2(326.f, 230.f), Vec2(326.f, 0.f), m_animateTime, 16, true);
	GetAnimator()->CreateAnimation(L"PLAYER_SHOOT_RUN_UP_RIGHT", run_tex, Vec2(0.f, 920.f), Vec2(326.f, 230.f), Vec2(326.f, 0.f), m_animateTime, 16, false);
	GetAnimator()->CreateAnimation(L"PLAYER_SHOOT_RUN_UP_LEFT", run_tex, Vec2(0.f, 1150.f), Vec2(326.f, 230.f), Vec2(326.f, 0.f), m_animateTime, 16, true);

	GetAnimator()->CreateAnimation(L"PLAYER_EX_SHOOT_DIGNOAL_UP_RIGHT", exShoot_tex, Vec2(0.f, 0.f), Vec2(326.f, 230.f), Vec2(326.f, 0.f), m_animateTime, 13, false);
	GetAnimator()->CreateAnimation(L"PLAYER_EX_SHOOT_DIGNOAL_UP_LEFT", exShoot_tex, Vec2(0.f, 230.f), Vec2(326.f, 230.f), Vec2(326.f, 0.f), m_animateTime, 13, true);
	GetAnimator()->CreateAnimation(L"PLAYER_EX_SHOOT_RIGHT", exShoot_tex, Vec2(0.f, 460.f), Vec2(326.f, 230.f), Vec2(326.f, 0.f), m_animateTime, 13, false);
	GetAnimator()->CreateAnimation(L"PLAYER_EX_SHOOT_LEFT", exShoot_tex, Vec2(0.f, 690.f), Vec2(326.f, 230.f), Vec2(326.f, 0.f), m_animateTime, 13, true);
	GetAnimator()->CreateAnimation(L"PLAYER_EX_SHOOT_UP_RIGHT", exShoot_tex, Vec2(0.f, 920.f), Vec2(326.f, 230.f), Vec2(326.f, 0.f), m_animateTime, 13, false);
	GetAnimator()->CreateAnimation(L"PLAYER_EX_SHOOT_UP_LEFT", exShoot_tex, Vec2(0.f, 1150.f), Vec2(326.f, 230.f), Vec2(326.f, 0.f), m_animateTime, 13, true);


	GetAnimator()->CreateAnimation(L"PLAYER_EX_SHOOT_DIAGNOAL_DOWN_RIGHT_AIR", exShootAir_tex, Vec2(0.f, 0.f), Vec2(326.f, 230.f), Vec2(326.f, 0.f), m_animateTime, 6, false);
	GetAnimator()->CreateAnimation(L"PLAYER_EX_SHOOT_DIAGNOAL_DOWN_LEFT_AIR", exShootAir_tex, Vec2(0.f, 230.f), Vec2(326.f, 230.f), Vec2(326.f, 0.f), m_animateTime, 6, true);
	GetAnimator()->CreateAnimation(L"PLAYER_EX_SHOOT_DIGNOAL_UP_RIGHT_AIR", exShootAir_tex, Vec2(0.f, 460.f), Vec2(326.f, 230.f), Vec2(326.f, 0.f), m_animateTime, 6, false);
	GetAnimator()->CreateAnimation(L"PLAYER_EX_SHOOT_DIGNOAL_UP_LEFT_AIR", exShootAir_tex, Vec2(0.f, 690.f), Vec2(326.f, 230.f), Vec2(326.f, 0.f), m_animateTime, 6, true);
	GetAnimator()->CreateAnimation(L"PLAYER_EX_SHOOT_DOWN_AIR_RIGHT", exShootAir_tex, Vec2(0.f, 920.f), Vec2(326.f, 230.f), Vec2(326.f, 0.f), m_animateTime, 6, false);
	GetAnimator()->CreateAnimation(L"PLAYER_EX_SHOOT_DOWN_AIR_LEFT", exShootAir_tex, Vec2(0.f, 1150.f), Vec2(326.f, 230.f), Vec2(326.f, 0.f), m_animateTime, 6, true);

	GetAnimator()->CreateAnimation(L"PLAYER_EX_SHOOT_RIGHT_AIR", exShootAir_tex, Vec2(0.f, 1380.f), Vec2(326.f, 230.f), Vec2(326.f, 0.f), m_animateTime, 6, false);
	GetAnimator()->CreateAnimation(L"PLAYER_EX_SHOOT_LEFT_AIR", exShootAir_tex, Vec2(0.f, 1610.f), Vec2(326.f, 230.f), Vec2(326.f, 0.f), m_animateTime, 6, true);
	GetAnimator()->CreateAnimation(L"PLAYER_EX_SHOOT_UP_RIGHT_AIR", exShootAir_tex, Vec2(0.f, 1840.f), Vec2(326.f, 230.f), Vec2(326.f, 0.f), m_animateTime, 6, false);
	GetAnimator()->CreateAnimation(L"PLAYER_EX_SHOOT_UP_LEFT_AIR", exShootAir_tex, Vec2(0.f, 2070.f), Vec2(326.f, 230.f), Vec2(326.f, 0.f), m_animateTime, 6, true);

	GetAnimator()->CreateAnimation(L"PLAYER_SHOOT_UP", shoot_tex, Vec2(0.f, 0.f), Vec2(326.f, 230.f), Vec2(326.f, 0.f), m_animateTime, 3, false);
	GetAnimator()->CreateAnimation(L"PLAYER_SHOOT_DUCK_RIGHT", shoot_tex, Vec2(0.f, 230.f), Vec2(326.f, 230.f), Vec2(326.f, 0.f), m_animateTime, 3, false);
	GetAnimator()->CreateAnimation(L"PLAYER_SHOOT_DUCK_LEFT", shoot_tex, Vec2(0.f, 460.f), Vec2(326.f, 230.f), Vec2(326.f, 0.f), m_animateTime, 3, true);
	GetAnimator()->CreateAnimation(L"PLAYER_SHOOT_DIAGNOAL_UP_RIGHT", shoot_tex, Vec2(0.f, 690.f), Vec2(326.f, 230.f), Vec2(326.f, 0.f), m_animateTime, 3, false);
	GetAnimator()->CreateAnimation(L"PLAYER_SHOOT_DIAGNOAL_UP_LEFT", shoot_tex, Vec2(0.f, 920.f), Vec2(326.f, 230.f), Vec2(326.f, 0.f), m_animateTime, 3, true);
	GetAnimator()->CreateAnimation(L"PLAYER_SHOOT_STRAGIHT_RIGHT", shoot_tex, Vec2(0.f, 1150.f), Vec2(326.f, 230.f), Vec2(326.f, 0.f), m_animateTime, 3, false);
	GetAnimator()->CreateAnimation(L"PLAYER_SHOOT_STRAGIHT_LEFT", shoot_tex, Vec2(0.f,1380.f), Vec2(326.f, 230.f), Vec2(326.f, 0.f), m_animateTime, 3, true);


	GetAnimator()->CreateAnimation(L"PLAYER_DASH_AIR_RIGHT", dash_tex, Vec2(0.f, 0.f), Vec2(326.f, 230.f), Vec2(326.f, 0.f), m_animateTime, 8, false);
	GetAnimator()->CreateAnimation(L"PLAYER_DASH_GROUND_RIGHT", dash_tex, Vec2(0.f, 230.f), Vec2(326.f, 230.f), Vec2(326.f, 0.f), m_animateTime, 8, false);
	GetAnimator()->CreateAnimation(L"PLAYER_DASH_AIR_LEFT", dash_tex, Vec2(0.f, 460.f), Vec2(326.f, 230.f), Vec2(326.f, 0.f), m_animateTime, 8, true);
	GetAnimator()->CreateAnimation(L"PLAYER_DASH_GROUND_LEFT", dash_tex, Vec2(0.f, 690.f), Vec2(326.f, 230.f), Vec2(326.f, 0.f), m_animateTime, 8, true);

	GetAnimator()->CreateAnimation(L"PLAYER_JUMP_RIGHT", jump_tex, Vec2(0.f, 0.f), Vec2(326.f, 230.f), Vec2(326.f, 0.f), m_animateTime, 8, false);
	GetAnimator()->CreateAnimation(L"PLAYER_JUMP_LEFT", jump_tex, Vec2(0.f, 230.f), Vec2(326.f, 230.f), Vec2(326.f, 0.f), m_animateTime, 8, true);
	
	GetAnimator()->CreateAnimation(L"PLAYER_DEATH", death_tex, Vec2(0.f, 0.f), Vec2(326.f, 230.f), Vec2(326.f, 0.f), m_animateTime, 25, false);
	GetAnimator()->CreateAnimation(L"PLAYER_HIT_AIR_RIGHT", hit_tex, Vec2(0.f, 0.f), Vec2(326.f, 230.f), Vec2(326.f, 0.f), m_animateTime, 6, false);
	GetAnimator()->CreateAnimation(L"PLAYER_HIT_RIGHT", hit_tex, Vec2(0.f, 230.f), Vec2(326.f, 230.f), Vec2(326.f, 0.f), m_animateTime, 6, false);
	GetAnimator()->CreateAnimation(L"PLAYER_HIT_AIR_LEFT", hit_tex, Vec2(0.f, 460.f), Vec2(326.f, 230.f), Vec2(326.f, 0.f), m_animateTime, 6, true);
	GetAnimator()->CreateAnimation(L"PLAYER_HIT_LEFT", hit_tex, Vec2(0.f, 690.f), Vec2(326.f, 230.f), Vec2(326.f, 0.f), m_animateTime, 6, true);
	GetAnimator()->CreateAnimation(L"PLAYER_DUCK_RIGHT", duck_tex, Vec2(0.f, 0.f), Vec2(326.f, 230.f), Vec2(326.f, 0.f), m_animateTime, 7, false);
	GetAnimator()->CreateAnimation(L"PLAYER_DUCK_LEFT", duck_tex, Vec2(0.f, 230.f), Vec2(326.f, 230.f), Vec2(326.f, 0.f), m_animateTime, 7, true);
	GetAnimator()->CreateAnimation(L"PLAYER_INTRO_1", intro_tex, Vec2(0.f, 0.f), Vec2(326.f, 230.f), Vec2(326.f, 0.f), m_animateTime, 14, false);
	GetAnimator()->CreateAnimation(L"PLAYER_INTRO_2", intro_tex, Vec2(0.f, 230.f), Vec2(326.f, 230.f), Vec2(326.f, 0.f), m_animateTime, 14, false);



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
	if(CSceneManager::GetInst()->GetCurrentScene()->GetSceneName() == L"Tool Scene")
		DeleteObject(m_hitBox);
}

void CPlayer::Start()
{
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
	state = new CPlayerDuckState;
	ai->AddState(state);
	state = new CPlayerIntroState;
	ai->AddState(state);
	ai->SetCurrentState(PLAYER_STATE::INTRO);
	SetAi(ai);
	CreateAttackBox();
	CreateHitBox();
	if (nullptr != m_attackBox)
	{
		CBullet* bullet = new CPeaShootBullet;
		m_attackBox->AddBullet(bullet);
		m_attackBox->SetCurrentBullet(BULLET_TYPE::PEASHOOT);
	}
	if (nullptr != m_hitBox)
	{
		m_hitBox->SetScale(Vec2(70.f, 90.f));
		m_hitBox->SetOffset(Vec2(0.f, 30.f));
		m_hitBox->Start();
	}
		
	if (GetRigidBody())
		GetRigidBody()->SetMaxVelocity(400.f);
}

void CPlayer::Update()
{
	if (m_ai->GetCurrentState()->GetState() == PLAYER_STATE::INTRO && GetAnimator()->GetCurrentAnim() == nullptr)
	{
		GetAnimator()->Play(L"PLAYER_INTRO_1", false);
	}
	if (m_info.health <= 0 && m_ai->GetCurrentState()->GetState() != PLAYER_STATE::DEAD)
	{
		ChangePlayerState(m_ai, PLAYER_STATE::DEAD);
		return;
	}
	if (m_hit)
	{
		m_accTime += fDT;
	}
	if (m_accTime >= m_info.infiniteTime)
	{
		m_hit = false;
		m_accTime = 0;
	}
	m_attackBox->Update();
	//m_hitBox->Update();
	m_ai->Update();


	SetPrevPos(GetPos());
	m_info.prevMoveDir = GetMoveDir();
	calMoveDir();
	
	if (CCore::GetInst()->IsDebug())
	{
		if (KEY_TAP(KEY::F5))
		{
			if (m_infinite)
				m_infinite = false;
			else
				m_infinite = true;
		}
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
	if (CSceneManager::GetInst()->GetCurrentScene()->GetSceneName() == L"Tool Scene")
		return;
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

	if (KEY_TAP(KEY::C))
	{
		m_attackBox->ChangeBullet();
	}
	
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

		m_info.shootDir = Vec2(1, 0);
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
		if (GetGravity()->IsGround() && m_ai->GetCurrentState()->GetState() != PLAYER_STATE::DUCK)
		{
			if (GetMoveDir().x < 0)
			{
				GetAnimator()->Play(L"PLAYER_DUCK_LEFT",true);
			}
			else
			{
				GetAnimator()->Play(L"PLAYER_DUCK_RIGHT", true);
			}
			ChangePlayerState(m_ai, PLAYER_STATE::DUCK);
		}
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


