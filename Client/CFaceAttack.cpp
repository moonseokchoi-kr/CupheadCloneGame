#include "pch.h"
#include "CFaceAttack.h"
#include "CCollider.h"
#include "CTimeManager.h"
CFaceAttack::CFaceAttack()
	:CBullet(BULLET_TYPE::FACE_ATTACK)
	, m_accTime(0)
	, m_initTime(0.3)
	, m_mainTime(0.5)
	, m_maxSize(1221)
	,m_isAttackFinish(true)
{
	CreateCollider();
	SetScale(Vec2(200.f, 100.f));
	GetCollider()->SetScale(Vec2(340.f, 226.f));
	GetCollider()->SetAvaCollide(false);
	bulletInfo info = {};
	info.bulletSpeed = 1000.f;
	info.damege = 1.f;
	info.range = 1600;
	SetInfo(info);
}

CFaceAttack::~CFaceAttack()
{
}

void CFaceAttack::Update()
{
	m_accTime += fDT;
	if (GetCollider()->CanCollide() && m_accTime>=m_initTime)
	{
		//콜라이더 설정을 위해 현재 위치를 제대로 받을것
		Vec2 scale = GetCollider()->GetScale();
		if (scale.x <= m_maxSize)
		{
			m_isAttackFinish = false;
			scale.x = 1225;
			GetCollider()->SetScale(scale);
			m_accTime = 0;
		}
		else
		{
			if (m_accTime >= m_mainTime)
			{
				if (scale.x > 340.f)
				{
					scale.x = 330.f;
					GetCollider()->SetScale(scale);
					GetCollider()->SetAvaCollide(false);
					m_accTime = 0;
					m_isAttackFinish= true;
				}

			}

		}
	}
}

void CFaceAttack::Render(HDC _dc)
{

	Vec2 renderPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 scale = GetScale();
	
	ComponentRender(_dc);
}

void CFaceAttack::OnCollisionEnter(CCollider* _col)
{
	if (_col->GetOwner()->GetName() == L"Grond" || _col->GetOwner()->GetName() == L"Player")
	{
		int a = 0;
	}
}

void CFaceAttack::OnCollision(CCollider* _col)
{
}
