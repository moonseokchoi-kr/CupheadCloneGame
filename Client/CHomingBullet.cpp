#include "pch.h"
#include "CHomingBullet.h"
#include "CCollider.h"
#include "CScene.h"
#include "CSceneManager.h"
#include "CTimeManager.h"
#include "CResourceManager.h"
#include "CAnimator.h"
CHomingBullet::CHomingBullet()
	:m_bulletDamege(0.3f),
	m_bulletDirection{},
	m_bulletShootPos{},
	m_bulletSpeed(800.f),
	m_target(nullptr),
	m_theata(0),
	m_distance(100.f),
	m_targetDist(400.f)
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(40.f, 40.f));
	
	CTexture* tex = CResourceManager::GetInst()->LoadTexture(L"HOMING_BULLET", L"texture\\homing_bullet.bmp");
	
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"HOMING_BULLET", tex, Vec2(0, 0), Vec2(50, 60), Vec2(50, 0), 0.1f, 8, false);
	GetAnimator()->Play(L"HOMING_BULLET", true);
}

CHomingBullet::~CHomingBullet()
{
}

void CHomingBullet::Update()
{
	const vector<CObject*>& monsters = CSceneManager::GetInst()->GetCurrentScene()->GetObjWithType(GROUP_TYPE::MONSTER);

	TraceTarget(monsters);
	Vec2 pos = GetPos();

	if (nullptr!= m_target)
	{
		if (m_targetDist)
		{
			m_bulletDirection = m_target->GetPos() - pos;
			m_bulletDirection.Normalize();
		}
		else
		{
			m_bulletDirection = Vec2(1.f, 0.f);
		}
		pos = pos + (m_bulletDirection * m_bulletSpeed * fDT);

	}
	else
	{
		m_bulletDirection = Vec2(1.f, 0.f);

		pos = pos+ (m_bulletDirection * m_bulletSpeed * fDT);

		TraceTarget(monsters);
	}
	SetPos(pos);

}

void CHomingBullet::Render(HDC _dc)
{
	ComponentRender(_dc);
}

void CHomingBullet::FinalUpdate()
{
	CObject::FinalUpdate();
}



void CHomingBullet::OnCollisionEnter(CCollider* _col)
{
	if (_col->GetOwner()->GetName() == L"Monster")
	{
		DeleteObject(this);
	}
}

void CHomingBullet::TraceTarget(vector<CObject*> _monsters)
{
	if (_monsters.size() == 0)
	{
		m_target = nullptr;
		m_targetDist = 100000.f;
	}
	// 타겟과의 거리를 계산
	Vec2 pos = GetPos();
	float minDist = 100000.f;
	// 가장 가까운 타겟을 타겟팅
	for (int i = 0; i < _monsters.size(); ++i)
	{
		CObject* monster = _monsters[i];
		float dist = monster->GetPos().Distance(pos);
		if (minDist > dist)
		{
			minDist = dist;
			m_target = monster;
		}
	}
	m_targetDist = minDist;
}
