#include "pch.h"
#include "CDartBullet.h"
#include "CScene.h"
#include "CTexture.h"
#include "CAnimator.h"
#include "CCollider.h"

#include "CSceneManager.h"
#include "CTimeManager.h"
#include "CResourceManager.h"
CDartBullet::CDartBullet()
	:m_target(nullptr)
	,m_range(1000.f)
	, m_dirction{}
	, m_bulletSpeed(600.f)
	, m_isCal(false)
{
	m_target = CSceneManager::GetInst()->GetCurrentScene()->GetObjWithType(GROUP_TYPE::PLAYER)[0];
	
	CreateCollider();
	GetCollider()->SetScale(Vec2(16.f, 20.f));

	CTexture* tex = CResourceManager::GetInst()->LoadTexture(L"DART_BULLET", L"texture\\dart_bullet.bmp");

	CreateAnimator();

	GetAnimator()->CreateAnimation(L"DART_BULLET", tex, Vec2(0, 0), Vec2(26.67f, 40.f), Vec2(26.67f, 0.f), 0.1f, 6);

	GetAnimator()->Play(L"DART_BULLET", true);
}

CDartBullet::~CDartBullet()
{
	
}

void CDartBullet::Update()
{
	Vec2 pos = GetPos();
	if (!m_isCal)
	{
		m_dirction = m_target->GetPos() - pos;
		m_dirction.Normalize();
		m_isCal = true;
	}
	
	pos = pos+ (m_dirction * m_bulletSpeed * fDT);

	SetPos(pos);
	GetAnimator()->FinalUpdate();
}

void CDartBullet::Render(HDC _dc)
{
	ComponentRender(_dc);
}

void CDartBullet::OnCollisionEnter(CCollider* _col)
{
	if (_col->GetOwner()->GetName() == L"Player")
	{
		DeleteObject(this);
	}
}

void CDartBullet::FinalUpdate()
{
	CObject::FinalUpdate();
}
