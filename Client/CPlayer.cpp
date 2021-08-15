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

CPlayer::CPlayer()
	:m_moveDir(1)
	,m_prevMoveDir(1)
	, m_moveSpeed(200.f)
	, m_shootDir(Vec2(1.f, 0.f))
	, m_weaponMode(1)
	, m_health(1)
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
	//GetAnimator()->Play(L"PLAYER_IDLE_RIGTH",true);

// 	m_subweapon = new PlayerSubweapon;
// 	m_subweapon->m_owner = this;

	//CreateObject(m_subweapon, GROUP_TYPE::PLAYER, GetPos(), m_subweapon->GetScale());
}



CPlayer::~CPlayer()
{
}

void CPlayer::Update()
{
	
	updateState();
	updateAnimation();
	UpdateMove();


	GetAnimator()->FinalUpdate();

	if (m_health <= 0)
	{
		DeleteObject(this);
	}
	m_prevState = m_curState;
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

void CPlayer::updateState()
{
	if (KEY_TAP(KEY::LEFT))
	{
		m_prevMoveDir = m_moveDir;
		m_moveDir = -1;

		if (!m_attack)
			m_curState = PLAYER_STATE::TURN;
		else
			m_curState = PLAYER_STATE::ATTACKTURN;
	}
	if (KEY_TAP(KEY::RIGHT))
	{
		m_prevMoveDir = m_moveDir;
		m_moveDir = 1;
		if (!m_attack)
			m_curState = PLAYER_STATE::TURN;
		else
			m_curState = PLAYER_STATE::ATTACKTURN;
	}
	if (KEY_HOLD(KEY::LEFT))
	{
		if (!m_attack)
			m_curState = PLAYER_STATE::RUN;
		else
			m_curState = PLAYER_STATE::ATTACKRUN;
	}
	if (KEY_HOLD(KEY::RIGHT))
	{
		if (!m_attack)
			m_curState = PLAYER_STATE::RUN;
		else
			m_curState = PLAYER_STATE::ATTACKRUN;
	}
	if (0.f == GetRigidBody()->GetSpeed() && !m_attack)
	{
		m_curState = PLAYER_STATE::IDLE;
	}

	if (KEY_TAP(KEY::SPACE))
	{
		m_attack = true;
		if (PLAYER_STATE::IDLE == m_curState)
			PLAYER_STATE::ATTACK;
	}
	if (KEY_AWAY(KEY::SPACE))
	{
		m_attack = false;
	}
}

void CPlayer::UpdateMove()
{
	CRigidBody* rigidBody = GetRigidBody();

	if (KEY_TAP(KEY::LEFT))
	{
		rigidBody->AddVelocity(Vec2(m_moveDir*m_moveSpeed / 2.f, 0.f));
	}
	if (KEY_TAP(KEY::RIGHT))
	{
		rigidBody->AddVelocity(Vec2(m_moveDir*m_moveSpeed / 2.f, 0.f));
	}


	if (KEY_HOLD(KEY::UP))
	{

	}
	if (KEY_HOLD(KEY::DOWN))
	{
	}
	if (KEY_HOLD(KEY::LEFT))
	{
		rigidBody->AddForce(Vec2(m_moveDir*m_moveSpeed, 0.f));
	}
	if (KEY_HOLD(KEY::RIGHT))
	{
		rigidBody->AddForce(Vec2(m_moveDir*m_moveSpeed, 0.f));
	}
}

void CPlayer::updateAnimation()
{
	switch (m_curState)
	{

	case PLAYER_STATE::IDLE:
	{
		if (-1 == m_moveDir)
			GetAnimator()->Play(L"PLAYER_IDLE_LEFT", true);
		else
			GetAnimator()->Play(L"PLAYER_IDLE_RIGHT", true);
	}
		break;
	case PLAYER_STATE::TURN:
	{
		if (-1 == m_prevMoveDir)
			GetAnimator()->Play(L"PLAYER_RUN_TURN_RIGHT", true);
		else
			GetAnimator()->Play(L"PLAYER_RUN_TURN_LEFT", true);
	}
		break;
	case PLAYER_STATE::RUN:
	{
		
		if (-1 == m_moveDir)
			GetAnimator()->Play(L"PLAYER_NORMAL_RUN_LEFT", true);
		else
			GetAnimator()->Play(L"PLAYER_NORMAL_RUN_RIGHT", true);

	}
		break;
	case PLAYER_STATE::DASH:
		break;
	case PLAYER_STATE::HIT:
		break;
	case PLAYER_STATE::ATTACK:
		break;
	case PLAYER_STATE::DEAD:
		break;
	default:
		break;
	}
}
