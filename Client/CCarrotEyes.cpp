#include "pch.h"
#include "CCarrotEyes.h"
#include "CTexture.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CChauncey.h"
#include "CAnimation.h"
#include "FSMAI.h"
#include "CState.h"
#include "CCarrotBossAttackBox.h"
#include "CResourceManager.h"
CCarrotEyes::CCarrotEyes()
	:m_owner(nullptr)
{
	SetScale(Vec2(114.f, 100.f));
	CreateAnimator();
	
	CTexture* eyeTex = CResourceManager::GetInst()->LoadTexture(L"CarrotEyeTex", L"texture\\cuphead\\boss\\carrot_eye.bmp");

	GetAnimator()->CreateAnimation(L"CARROT_EYE", eyeTex, Vec2(0.f, 0.f), Vec2(114.f, 100.f), Vec2(114.f, 0.f), 1 / 16.f, 6, false);
	GetAnimator()->Play(L"CARROT_EYE", true);
}

CCarrotEyes::~CCarrotEyes()
{
}
void CCarrotEyes::Update()
{
	Vec2 pos = m_owner->GetPos() + m_offSet;
	SetPos(pos);
}

void CCarrotEyes::Render(HDC _dc)
{
	if (m_owner->IsHit())
	{
		if (m_owner->m_renderToggle)
		{
			GetAnimator()->SetAlpha(127);
			m_owner->m_renderToggle = false;
		}
		else
		{
			GetAnimator()->SetAlpha(0);
			m_owner->m_renderToggle = true;
		}
	}
	else
	{
		GetAnimator()->SetAlpha(255);
	}
	ComponentRender(_dc);
}
