#include "pch.h"
#include "CSpawnObject.h"
#include "CPlayer.h"
#include "CMonsterFactory.h"

#include "CSceneManager.h"
#include "CCamera.h"

#include "SelectGDI.h"



CSpawnObject::CSpawnObject()
	:m_groupType(GROUP_TYPE::PLAYER)
	,m_monType(MON_TYPE::NONE)
{
	SetScale(Vec2(50.f, 50.f));
}

CSpawnObject::~CSpawnObject()
{
}


void CSpawnObject::Update()
{
}

void CSpawnObject::Render(HDC _dc)
{
	Vec2 pos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 scale = GetScale();
	if (CSceneManager::GetInst()->GetCurrentScene()->GetSceneName() != L"Tool Scene")
	{
		return;
	}
	SelectGDI gdi(_dc, BRUSH_TYPE::HOLLOW);
	
	if (GROUP_TYPE::PLAYER == m_groupType)
	{
		SelectGDI gdi2(_dc, PEN_TYPE::GREEN_BOLD);

		Ellipse(
			_dc,
			(int)pos.x,
			(int)pos.y,
			(int)(pos.x + scale.x),
			(int)(pos.y + scale.y)
		);
		return;
	}

	SelectGDI gdi1(_dc, PEN_TYPE::RED_BOLD);
	Ellipse(
		_dc,
		(int)pos.x,
		(int)pos.y,
		(int)(pos.x + scale.x),
		(int)(pos.y + scale.y)
	);
}

void CSpawnObject::Spawn()
{
	Vec2 pos = CCamera::GetInst()->GetRenderPos(GetPos());
	if (GROUP_TYPE::PLAYER == m_groupType)
	{
		CObject* playerObj = new CPlayer;
		playerObj->SetPos(pos);
		CreateObject(playerObj, m_groupType);
	}


	if (MON_TYPE::NONE != m_monType && GROUP_TYPE::END != m_groupType)
	{
		CMonster* monObj = CMonsterFactory::CreateMonster(m_monType, pos);
		CreateObject((CObject*)monObj, m_groupType);
	}
	
}
