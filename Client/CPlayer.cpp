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
	, m_moveSpeed(200.f)
	, m_shootDir(Vec2(1.f, 0.f))
	, m_weaponMode(1)
	, m_health(1)
{
	CreateCollider();
	SetName(L"Player");
	GetCollider()->SetScale(Vec2(40.f,60.f));

	CTexture* idle_left_tex = CResourceManager::GetInst()->LoadTexture(L"PlayerIdleLeftTex", L"texture\\cuphead\\cuphead_idle_left.bmp");
	CTexture* idle_right_tex = CResourceManager::GetInst()->LoadTexture(L"PlayerIdleRightTex", L"texture\\cuphead\\cuphead_idle_right.bmp");

	CTexture* turn_left_tex = CResourceManager::GetInst()->LoadTexture(L"PlayerRunTurnLeftTex", L"texture\\cuphead\\cuphead_normal_run_turn_left.bmp");
	CTexture* turn_right_tex = CResourceManager::GetInst()->LoadTexture(L"PlayerRunTurnRightTex", L"texture\\cuphead\\cuphead_normal_run_turn_right.bmp");
	
	CTexture* run_left_tex = CResourceManager::GetInst()->LoadTexture(L"PlayerNormalRunLeftTex", L"texture\\cuphead\\cuphead_normal_run_left.bmp");
	CTexture* run_right_tex = CResourceManager::GetInst()->LoadTexture(L"PlayerNormalRunRightTex", L"texture\\cuphead\\cuphead_normal_run_right.bmp");

	CreateAnimator();
	CreateRigidBody();
	
	GetAnimator()->CreateAnimation(L"PLAYER_IDLE_LEFT", idle_left_tex, Vec2(0, 0), Vec2(98.f, 155.f), Vec2(98.f, 0.f), 0.15f, 5, true);
	GetAnimator()->CreateAnimation(L"PLAYER_IDLE_RIGHT", idle_right_tex, Vec2(0, 0), Vec2(98.f, 155.f), Vec2(98.f, 0.f), 5.f / 60.f, 5, false);
	GetAnimator()->CreateAnimation(L"PLAYER_RUN_TURN_LEFT", turn_left_tex, Vec2(0, 0), Vec2(179.f, 164.f), Vec2(179.f, 0.f), 2.f/60.f, 2, true);
	GetAnimator()->CreateAnimation(L"PLAYER_RUN_TURN_RIGHT", turn_right_tex, Vec2(0, 0), Vec2(179.f, 164.f), Vec2(179.f, 0.f), 2.f / 60.f, 2, false);
	GetAnimator()->CreateAnimation(L"PLAYER_NORMAL_RUN_LEFT", run_left_tex, Vec2(0, 0), Vec2(223.f, 169.f), Vec2(223.f, 0.f), 16.f/60.f, 16, true);
	GetAnimator()->CreateAnimation(L"PLAYER_NORMAL_RUN_RIGHT",	run_right_tex, Vec2(0, 0), Vec2(223.f, 169.f), Vec2(223.f, 0.f), 16.f/60.f, 16, false);

	GetAnimator()->Play(L"PLAYER_IDLE_LEFT",true);

	m_subweapon = new PlayerSubweapon;
	m_subweapon->m_owner = this;

	//CreateObject(m_subweapon, GROUP_TYPE::PLAYER, GetPos(), m_subweapon->GetScale());
}



CPlayer::~CPlayer()
{
}

void CPlayer::Update()
{
	CRigidBody* rigidBody = GetRigidBody();

	if (KEY_TAP(KEY::A))
	{
		rigidBody->AddVelocity(Vec2(-m_moveSpeed/2.f, 0.f));
	}
	if (KEY_TAP(KEY::D))
	{
		rigidBody->AddVelocity(Vec2(m_moveSpeed/2.f, 0.f));
	}


	if (KEY_HOLD(KEY::W))
	{
		
	}
	if (KEY_HOLD(KEY::S))
	{
;
	}
	if (KEY_HOLD(KEY::A))
	{
		rigidBody->AddForce(Vec2(-m_moveSpeed, 0.f));
	}
	if (KEY_HOLD(KEY::D))
	{
		rigidBody->AddForce(Vec2(m_moveSpeed, 0.f));
	}
	if (KEY_HOLD(KEY::SPACE))
	{
		fire();
	}
	

	GetAnimator()->FinalUpdate();

	if (m_health <= 0)
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
