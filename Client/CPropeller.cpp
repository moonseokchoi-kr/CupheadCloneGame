#include "pch.h"
#include "CPropeller.h"

#include "CAnimator.h"
#include "CTexture.h"
#include "CGround.h"
#include "CAnimation.h"

#include "CResourceManager.h"
#include "CSceneManager.h"
CPropeller::CPropeller()
	:m_parent(nullptr)
{
	CreateAnimator();
	CTexture* tex = CResourceManager::GetInst()->FindTexture(L"platform_propeller");
	GetAnimator()->CreateAnimation(L"platform_propeller_anim", tex, Vec2(0, 0), Vec2(117, 39), Vec2(117, 0), 0.15f, 9, false);
	GetAnimator()->Play(L"platform_propeller_anim", true);
	
}

CPropeller::~CPropeller()
{
}

void CPropeller::Update()
{
}

void CPropeller::Render(HDC _dc)
{
	ComponentRender(_dc);
}

void CPropeller::FinalUpdate()
{
	CObject::FinalUpdate();

	if (nullptr != m_parent)
	{
		Vec2 parentPos = m_parent->GetPos();
		parentPos += m_offset;
		SetPos(parentPos);
	}

	
	
}
