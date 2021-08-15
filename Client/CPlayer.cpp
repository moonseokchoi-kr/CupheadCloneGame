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


#include "CPlayerState.h"
#include "CPlayerIdleState.h"
#include "CPlayerAttackState.h"

#include "CPlayerStateMachine.h"

CPlayer::CPlayer()
	:m_info{200.f, 1, 1, 0.1f, Vec2(1,0), 3}
	, m_weaponMode(1)
	, m_curState(PLAYER_STATE::IDLE)
	, m_prevState(PLAYER_STATE::IDLE)
{
	
	CreateCollider();
	SetName(L"Player");
	GetCollider()->SetScale(Vec2(40.f,60.f));

	CTexture* idle_tex = CResourceManager::GetInst()->LoadTexture(L"PlayerIdleTex", L"texture\\cuphead\\player\\idle_sheet.bmp");

	CTexture* turn_tex = CResourceManager::GetInst()->LoadTexture(L"PlayerRunTurnTex", L"texture\\cuphead\\player\\normal_run_turn.bmp");
	
	CTexture* run_tex = CResourceManager::GetInst()->LoadTexture(L"PlayerNormalRunTex", L"texture\\cuphead\\player\\run_sprite.bmp");

	CTexture* run_shoot_tex = CResourceManager::GetInst()->LoadTexture(L"PlayerRunShootTex", L"texture\\cuphead\\player\\run_shoot.bmp");

	CTexture* run_shoot_turn_tex = CResourceManager::GetInst()->LoadTexture(L"PlayerRunShootTurnTex", L"texture\\cuphead\\player\\shoot_run_turn.bmp");


	CreateAnimator();
	CreateRigidBody();
	
	GetAnimator()->CreateAnimation(L"PLAYER_IDLE_RIGHT", idle_tex, Vec2(0.f, 0.f), Vec2(98.f, 155.f), Vec2(98.f, 0.f), 0.15f, 5, false);
	GetAnimator()->CreateAnimation(L"PLAYER_IDLE_LEFT", idle_tex, Vec2(0.f, 155.f), Vec2(98.f, 155.f), Vec2(98.f, 0.f), 0.15f, 5, true);

	GetAnimator()->CreateAnimation(L"PLAYER_RUN_TURN_LEFT", turn_tex, Vec2(0.f, 164.f), Vec2(135.f, 164.f), Vec2(135.f, 0.f), 0.15f, 2, true);
	GetAnimator()->CreateAnimation(L"PLAYER_RUN_TURN_RIGHT", turn_tex, Vec2(0.f, 0.f), Vec2(135.f, 164.f), Vec2(135.f, 0.f), 0.15f, 2, false);

	GetAnimator()->CreateAnimation(L"PLAYER_SHOOT_RUN_TURN_LEFT", run_shoot_turn_tex, Vec2(0.f, 175.f), Vec2(143.f, 175.f), Vec2(143.f, 0.f), 0.15f, 2, true);
	GetAnimator()->CreateAnimation(L"PLAYER_SHOOT_RUN_TURN_RIGHT", run_shoot_turn_tex, Vec2(0.f, 0.f), Vec2(143.f, 175.f), Vec2(143.f, 0.f), 0.15f, 2, false);

	GetAnimator()->CreateAnimation(L"PLAYER_NORMAL_RUN_LEFT", run_tex, Vec2(0.f, 169.f), Vec2(137.f, 169.f), Vec2(137.f, 0.f), 0.15f, 16, true);
	GetAnimator()->CreateAnimation(L"PLAYER_NORMAL_RUN_RIGHT", run_tex, Vec2(0.f, 0.f), Vec2(137.f, 169.f), Vec2(137.f, 0.f), 0.15f, 16, false);

	GetAnimator()->CreateAnimation(L"PLAYER_SHOOT_RUN_LEFT", run_shoot_tex, Vec2(0.f, 168.f), Vec2(144.f, 168.f), Vec2(144.f, 0.f), 0.15f, 16, true);
	GetAnimator()->CreateAnimation(L"PLAYER_SHOOT_RUN_RIGHT", run_shoot_tex, Vec2(0.f, 0.f), Vec2(144.f, 168.f), Vec2(144.f, 0.f), 0.15f, 16, false);
	
	
	
}



CPlayer::~CPlayer()
{
}

void CPlayer::Start()
{
	CPlayerStateMachine* ai = new CPlayerStateMachine;
	CPlayerState* state = new CPlayerIdleState;
	ai->AddState(state);
	state = new CPlayerAttackState;
	ai->AddState(state);

	ai->SetCurrentState(PLAYER_STATE::IDLE);
	SetAi(ai);
}

void CPlayer::Update()
{
	
	m_ai->Update();


	GetAnimator()->FinalUpdate();

	if (m_info.health <= 0)
	{
		DeleteObject(this);
	}
	
}

void CPlayer::Render(HDC _dc)
{
	ComponentRender(_dc);
}
void CPlayer::OnCollisionEnter(CCollider* _col)
{

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

	if (KEY_TAP(KEY::LEFT))
	{
		rigidBody->AddVelocity(Vec2(m_info.moveDir* m_info.moveSpeed / 2.f, 0.f));
	}
	if (KEY_TAP(KEY::RIGHT))
	{
		rigidBody->AddVelocity(Vec2(m_info.moveDir* m_info.moveSpeed / 2.f, 0.f));
	}


	if (KEY_HOLD(KEY::UP))
	{

	}
	if (KEY_HOLD(KEY::DOWN))
	{
	}
	if (KEY_HOLD(KEY::LEFT))
	{
		rigidBody->AddForce(Vec2(m_info.moveDir* m_info.moveSpeed, 0.f));
	}
	if (KEY_HOLD(KEY::RIGHT))
	{
		rigidBody->AddForce(Vec2(m_info.moveDir* m_info.moveSpeed, 0.f));
	}
}


