#include "pch.h"
#include "CTearBullet.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CTexture.h"
#include "CResourceManager.h"
#include "CRigidBody.h"
#include "SelectGDI.h"
CTearBullet::CTearBullet()
	:CBullet(BULLET_TYPE::TEAR_BULLET)
	, m_type(TEAR_BULLET_TYPE::A)
{
	CreateCollider();
	CreateRigidBody();
	CreateAnimator();
	SetScale(Vec2(Vec2(20.f, 60.f)));
	GetCollider()->SetScale(Vec2(20.f, 60.f));
	GetRigidBody()->SetMaxVelocity(600.f);

	bulletInfo info = {};
	info.bulletSpeed = 600.f;
	info.damege = 1;
	info.range = 1600;
	info.isParring = false;
	SetInfo(info);

	randomTear();

	CTexture* bulletTex = CResourceManager::GetInst()->LoadTexture(L"TearBulletTex", L"texture\\cuphead\\boss\\onion_tear.bmp");
	CTexture* deathTex = CResourceManager::GetInst()->LoadTexture(L"TearBulletDeathTex", L"texture\\cuphead\\boss\\onion_tear_death.bmp");

	GetAnimator()->CreateAnimation(L"A_LOOP", bulletTex, Vec2(0.f, 0.f), Vec2(231.f, 147.f), Vec2(231.f,0.f), 1 / 16.f, 3, false);
	GetAnimator()->CreateAnimation(L"B_LOOP", bulletTex, Vec2(693.f, 0.f), Vec2(231.f, 147.f), Vec2(231.f,0.f), 1 / 16.f, 3, false);
	GetAnimator()->CreateAnimation(L"C_LOOP", bulletTex, Vec2(0.f, 187.f), Vec2(231.f, 147.f), Vec2(231.f,0.f), 1 / 16.f, 3, false);
	GetAnimator()->CreateAnimation(L"P_LOOP", bulletTex, Vec2(693.f, 147.f), Vec2(231.f, 147.f), Vec2(231.f,0.f), 1 / 16.f, 3, false);
	GetAnimator()->CreateAnimation(L"A_DEATH", deathTex, Vec2(0.f, 0.f), Vec2(231.f, 147.f), Vec2(231.f, 0.f), 1 / 16.f, 7, false);
	GetAnimator()->CreateAnimation(L"B_DEATH", deathTex, Vec2(1617.f, 0.f), Vec2(231.f, 147.f), Vec2(231.f, 0.f), 1 / 16.f, 7, false);
	GetAnimator()->CreateAnimation(L"C_DEATH", deathTex, Vec2(3234.f, 0.f), Vec2(231.f, 147.f), Vec2(231.f, 0.f), 1 / 16.f, 7, false);
	GetAnimator()->CreateAnimation(L"P_DEATH", deathTex, Vec2(4851.f, 0.f), Vec2(231.f, 147.f), Vec2(231.f, 0.f), 1 / 16.f, 6, false);

}

CTearBullet::~CTearBullet()
{
}

void CTearBullet::Update()
{
	Vec2 pos = GetPos();
	GetRigidBody()->SetVelocity(Vec2(0.f,GetInfo().bulletSpeed));
	GetRigidBody()->SetVelocity(Vec2(0.f, GetInfo().bulletSpeed));
	
	DeleteBullet();
	if (isDead)
	{
		GetCollider()->SetAvaCollide(false);
		GetRigidBody()->SetActive(false);
		switch (m_type)
		{
		case TEAR_BULLET_TYPE::A:
		{
			GetAnimator()->Play(L"A_DEATH", false);
		}
			break;
		case TEAR_BULLET_TYPE::B:
		{
			GetAnimator()->Play(L"B_DEATH", false);
		}
			break;
		case TEAR_BULLET_TYPE::C:
		{
			GetAnimator()->Play(L"C_DEATH", false);
		}
			break;
		case TEAR_BULLET_TYPE::P:
		{
			GetAnimator()->Play(L"P_DEATH", false);
		}
			break;
		default:
			break;
		}
		if (GetAnimator()->GetCurrentAnim()->IsFinish())
		{
			DeleteObject(this);
		}
	}
	else
	{
		switch (m_type)
		{
		case TEAR_BULLET_TYPE::A:
		{
			GetAnimator()->Play(L"A_LOOP", true);
		}
		break;
		case TEAR_BULLET_TYPE::B:
		{
			GetAnimator()->Play(L"B_LOOP", true);
		}
		break;
		case TEAR_BULLET_TYPE::C:
		{
			GetAnimator()->Play(L"C_LOOP", true);
		}
		break;
		case TEAR_BULLET_TYPE::P:
		{
			GetAnimator()->Play(L"P_LOOP", true);
		}
		break;
		default:
			break;
		}
	}
}

void CTearBullet::OnCollisionEnter(CCollider* _col)
{
	if (_col->GetOwner()->GetName() == L"PlayerHitBox" || _col->GetOwner()->GetName() == L"Ground")
	{
		isDead = true;
	}
}

void CTearBullet::OnCollision(CCollider* _col)
{
	CObject* obj = _col->GetOwner();
	if (obj->GetName() == L"PlayerHitBox")
	{
		isDead = true;
	}

}

void CTearBullet::randomTear()
{
	random_device rd;
	std::mt19937_64 gen(rd());
	std::uniform_int_distribution<int>  dis(0, 1000);
	float percent = dis(gen) / 1000.f;
	if (percent < 0.39f)
	{
		m_type = TEAR_BULLET_TYPE::A;
	}
	if (0.39f <= percent && percent < 0.67f)
	{
		m_type = TEAR_BULLET_TYPE::B;

	}
	if (0.67f <= percent && percent < 0.85f)
	{
		m_type = TEAR_BULLET_TYPE::C;
	}
	if (0.85f <= percent && percent < 1.f)
	{
		m_type = TEAR_BULLET_TYPE::P;
	}

}

void CTearBullet::Render(HDC _dc)
{
	ComponentRender(_dc);
}
