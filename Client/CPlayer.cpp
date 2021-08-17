#include "pch.h"
#include "CPlayer.h"
#include "CCollider.h"
#include "CBullet.h"

#include "CSceneManager.h"
#include "CKeyManager.h"
#include "CTimeManager.h"
#include "CPathManager.h"
#include "CResourceManager.h"

#include "CTexture.h"
#include "CAnimator.h"
#include "PlayerSubweapon.h"
#include "CRigidBody.h"

#include "CAnimation.h"
#include "CGravity.h"

#include "CPlayerState.h"
#include "CPlayerIdleState.h"
#include "CPlayerAttackState.h"
#include "CPlayerDashState.h"
#include "CPlayerJumpState.h"


#include "CPlayerStateMachine.h"


CPlayer::CPlayer()
	:m_info{500.f, Vec2(1,0),0.15f, 0.1f, 0.15f,300.f,Vec2(1,0), 3}
	, m_weaponMode(1)
	, m_curState(PLAYER_STATE::IDLE)
	, m_prevState(PLAYER_STATE::IDLE)
	,m_animateTime(1/30.f)
	, m_ai(nullptr)
{
	
	CreateCollider();

	GetCollider()->SetScale(Vec2(80.f,150.f));
	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
	CTexture* idle_tex = CResourceManager::GetInst()->LoadTexture(L"PlayerIdleTex", L"texture\\cuphead\\player\\idle_sheet.bmp");

	CTexture* turn_tex = CResourceManager::GetInst()->LoadTexture(L"PlayerRunTurnTex", L"texture\\cuphead\\player\\normal_run_turn.bmp");
	
	CTexture* run_tex = CResourceManager::GetInst()->LoadTexture(L"PlayerNormalRunTex", L"texture\\cuphead\\player\\run_sprite.bmp");

	CTexture* run_shoot_tex = CResourceManager::GetInst()->LoadTexture(L"PlayerRunShootTex", L"texture\\cuphead\\player\\run_shoot.bmp");

	CTexture* run_shoot_turn_tex = CResourceManager::GetInst()->LoadTexture(L"PlayerRunShootTurnTex", L"texture\\cuphead\\player\\shoot_run_turn.bmp");

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


	
}



CPlayer::~CPlayer()
{
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
	ai->SetCurrentState(PLAYER_STATE::IDLE);
	SetAi(ai);

	if (GetRigidBody())
		GetRigidBody()->SetMaxVelocity(500.f);
}

void CPlayer::Update()
{
	
	m_ai->Update();


	if (m_info.health <= 0)
	{
		DeleteObject(this);
	}
	SetPrevPos(GetPos());
	m_info.prevMoveDir = GetMoveDir();
	calMoveDir();
	
}

void CPlayer::Render(HDC _dc)
{
	ComponentRender(_dc);
}
void CPlayer::OnCollisionEnter(CCollider* _col)
{
	CObject* obj = _col->GetOwner();
	if (obj->GetName() == L"Monster")
	{
		int a = 0;
	}
	if (obj->GetName() == L"Ground")
	{
		m_isAir = false;
	}

}
void CPlayer::OnCollision(CCollider* _col)
{
	CObject* obj = _col->GetOwner();
	if (obj->GetName() == L"Monster")
	{
		int a = 0;
	}

}
void CPlayer::OnCollisionExit(CCollider* _col)
{
	CObject* obj = _col->GetOwner();
	if (obj->GetName() == L"Monster")
	{
		int a = 0;
	}

}
void CPlayer::FinalUpdate()
{
	CObject::FinalUpdate();
}
void CPlayer::SetAi(CPlayerStateMachine* _ai)
{
	m_ai = _ai;
	m_ai->m_owner = this;
}
/// <summary>
/// Bullet을 발사하는 함수
/// </summary>
void CPlayer::fire()
{
	Vec2 position = GetPos();
	CBullet* bullet = new CBullet;
	bullet->SetFirePos(Vec2(position.x, position.y - 10.f));
	bullet->SetName(L"PlayerBullet");
	CreateObject(bullet, GROUP_TYPE::PLAYER_BULLET, Vec2(position.x, position.y - 10.f), Vec2(25.f, 25.f));
}




void CPlayer::UpdateMove()
{
	CRigidBody* rigidBody = GetRigidBody();
	Vec2 moveDir = GetMoveDir();

	if (GetGravity()->IsGround())
	{
		if (KEY_TAP(KEY::LEFT))
		{

			rigidBody->SetVelocity(Vec2(moveDir.x * m_info.moveSpeed, rigidBody->GetVelocity().y));
		}
		if (KEY_TAP(KEY::RIGHT))
		{
			rigidBody->SetVelocity(Vec2(moveDir.x * m_info.moveSpeed, rigidBody->GetVelocity().y));
		}

		if (KEY_AWAY(KEY::LEFT) || KEY_AWAY(KEY::RIGHT))
		{
			rigidBody->SetVelocity(Vec2(0.f, rigidBody->GetVelocity().y));
		}

		if (KEY_HOLD(KEY::UP))
		{
			m_info.shootDir = Vec2(0, 1);
		}
		if (KEY_HOLD(KEY::DOWN))
		{
			m_info.shootDir = Vec2(0, -1);
		}
		if (KEY_HOLD(KEY::LEFT))
		{
			m_info.shootDir = Vec2(1, 0);
			if (KEY_HOLD(KEY::UP))
			{
				m_info.shootDir = Vec2(-1, 1);
			}
			if (KEY_HOLD(KEY::DOWN))
			{
				m_info.shootDir = Vec2(-1, -1);
			}
			rigidBody->AddForce(Vec2(moveDir.x * m_info.moveSpeed, 0.f));
		}
		if (KEY_HOLD(KEY::RIGHT))
		{
			if (KEY_HOLD(KEY::UP))
			{
				m_info.shootDir = Vec2(1, 1);
			}
			if (KEY_HOLD(KEY::DOWN))
			{
				m_info.shootDir = Vec2(1, -1);
			}
			rigidBody->AddForce(Vec2(moveDir.x * m_info.moveSpeed, 0.f));
		}

		if (KEY_TAP(KEY::X))
		{
			m_isAir = true;
			GetRigidBody()->SetVelocity(Vec2(GetRigidBody()->GetVelocity().x, -1000.f));
		}
	}
	
}


