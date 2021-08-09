#include "pch.h"
#include "CNinja.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CTexture.h"
#include "CDartBullet.h"
#include "CBullet.h"
#include "CHomingBullet.h"
#include "CResourceManager.h"
#include "CTimeManager.h"


CNinja::CNinja()
	:m_distance(500.f)
	, m_fallingSpeed(400.f)
	, m_walkingSpeed(300.f)
	, m_bGround(false)
	, m_attack(false)
	, m_attackTime(1.f)
	, m_acc(0)
	, m_health(5)
	, m_moveDirection(Vec2(0, 1))
{
	SetName(L"Monster");
	CreateAnimator();
	CTexture* tex = CResourceManager::GetInst()->LoadTexture(L"NINJA_ATTACK", L"texture\\ninja_attack.bmp");
	GetAnimator()->CreateAnimation(L"NINJA_ATTACK", tex, Vec2(100, 0), Vec2(100, 90), Vec2(100, 0), 0.5f, 3);
	tex = CResourceManager::GetInst()->LoadTexture(L"NINJA_FALLING", L"texture\\ninja_falling.bmp");
	GetAnimator()->CreateAnimation(L"NINJA_FALLING", tex, Vec2(0, 0), Vec2(100, 90), Vec2(100, 0), 0.1f, 4);
	tex = CResourceManager::GetInst()->LoadTexture(L"NINJA_WALKING", L"texture\\ninja_walking.bmp");
	GetAnimator()->CreateAnimation(L"NINJA_WALKING", tex, Vec2(0, 0), Vec2(100, 90), Vec2(100, 0), 0.1f, 5);

	m_moveDirection.Normalize();
	GetAnimator()->Play(L"NINJA_FALLING", false);
	CreateCollider();
	GetCollider()->SetScale(Vec2(60.f, 80.f));
}

CNinja::~CNinja()
{
}

void CNinja::Update()
{
	Vec2 pos = GetPos();
	if (m_bGround)
	{
		if (m_changeAnimation)
		{
			GetAnimator()->Play(L"NINJA_WALKING", true);
		}
		m_moveDirection = Vec2(-1, 0);
		if (pos.x > WINDOW_WIDTH - m_distance)
		{
			pos.x += m_moveDirection.x * m_walkingSpeed * fDT;
		}
		else
		{
			m_attack = true;
			GetAnimator()->Play(L"NINJA_ATTACK", true);
			m_moveDirection = Vec2(5.f, -5.f);
			m_moveDirection.Normalize();
			m_bGround = false;
			
			
		}
		GetAnimator()->FinalUpdate();
	}
	else 
	{
		if (m_attack)
		{
			
			pos.x += m_moveDirection.x * m_walkingSpeed * fDT;
			pos.y += m_moveDirection.y * m_fallingSpeed * fDT;
			GetAnimator()->FinalUpdate();
			
			m_acc += fDT;
			
			if (!m_bGround)
			{	
				GetAnimator()->Play(L"NINJA_FALLING", false);
				GetAnimator()->GetCurrentAnim()->SetFrame(0);
				if (m_acc >= m_attackTime)
				{
					GetAnimator()->Play(L"NINJA_ATTACK", true);
					GetAnimator()->GetCurrentAnim()->SetFrame(2);
					m_acc = 0;
					fire();
				}
			}
			
		}
		else
		{
			pos.y += m_moveDirection.y * m_fallingSpeed * fDT;
		}
	}
	m_changeAnimation = GetAnimator()->IsFinish();
	SetPos(pos);

	if (m_health <= 0)
	{
		DeleteObject(this);
	}
}

void CNinja::Render(HDC _dc)
{
	ComponentRender(_dc);
}

void CNinja::FinalUpdate()
{
	CObject::FinalUpdate();
}

void CNinja::OnCollisionEnter(CCollider* _col)
{
	if (_col->GetOwner()->GetName() == L"Ground")
	{
		m_bGround = true;
	}
	if (_col->GetOwner()->GetName() == L"PlayerBullet")
	{
		CBullet* bullet = (CBullet*)_col->GetOwner();
		m_health -= bullet->GetDamege();
	}
	if (_col->GetOwner()->GetName() == L"SubweaponBullet")
	{
		CHomingBullet* bullet = (CHomingBullet*)_col->GetOwner();
		m_health -= bullet->GetDamege();
	}
}

void CNinja::fire()
{
	CObject* dartBullet = new CDartBullet;
	dartBullet->SetName(L"MonsterBullet");
	CreateObject(dartBullet, GROUP_TYPE::MONSTER_BULLET, Vec2(GetPos().x - GetScale().x / 2.f, GetPos().y - GetScale().y / 2.f), Vec2(27.f, 40.f));
}
