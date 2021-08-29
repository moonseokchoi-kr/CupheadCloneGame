#include "pch.h"
#include "CSpawnObject.h"
#include "CPlayer.h"
#include "CMonsterFactory.h"

#include "CSceneManager.h"
#include "CCamera.h"
#include "CMonster.h"

#include "SelectGDI.h"



CSpawnObject::CSpawnObject()
	:m_groupType(GROUP_TYPE::END)
	,m_monType(MON_TYPE::NONE)
	,m_spawned(false)
	,m_spawnObj(nullptr)
{
	SetScale(Vec2(50.f, 50.f));
}

CSpawnObject::~CSpawnObject()
{
	if (CSceneManager::GetInst()->GetCurrentScene()->GetSceneName() == L"Tool Scene" && !m_spawnObj->IsDead())
	{
		//DeleteObject(m_spawnObj);
	}
}


void CSpawnObject::Start()
{
	switch (m_groupType)
	{
	case GROUP_TYPE::PLAYER:
	{
		m_spawnObj = new CPlayer;
		SetName(L"Spawn_"+m_spawnObj->GetName());
	}
		break;
	case GROUP_TYPE::BOSS:
	{
		switch (m_monType)
		{
		case MON_TYPE::SLIME:
		{

		}
			break;
		case MON_TYPE::OLLIE:
		{
			CMonster* monObj = CMonsterFactory::CreateMonster(m_monType, Vec2(0,0));
			m_spawnObj = ((CObject*)monObj);
			SetName(L"Spawn_" + m_spawnObj->GetName());
		}
			break;
		case MON_TYPE::CHAUNCEY:
		{
			CMonster* monObj = CMonsterFactory::CreateMonster(m_monType, Vec2(0, 0));
			m_spawnObj = ((CObject*)monObj);
			SetName(L"Spawn_" + m_spawnObj->GetName());
		}
			break;
		case MON_TYPE::SAL:
		{
			CMonster* monObj = CMonsterFactory::CreateMonster(m_monType, Vec2(0, 0));
			m_spawnObj = ((CObject*)monObj);
			SetName(L"Spawn_" + m_spawnObj->GetName());
		}
			break;
		case MON_TYPE::NONE:
		default:
			break;
		}
	}
		break;
	}
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
			(int)(pos.x - scale.x / 2.f),
			(int)(pos.y - scale.y / 2.f),
			(int)(pos.x + scale.x / 2.f),
			(int)(pos.y + scale.y / 2.f)
		);
		return;
	}

	SelectGDI gdi1(_dc, PEN_TYPE::RED_BOLD);
	Ellipse(
		_dc,
		(int)(pos.x - scale.x / 2.f),
		(int)(pos.y - scale.y / 2.f),
		(int)(pos.x + scale.x / 2.f),
		(int)(pos.y + scale.y / 2.f)
	);
}

void CSpawnObject::Spawn()
{
	Vec2 pos = GetPos();
	if(!m_spawned){
		if (GROUP_TYPE::PLAYER == m_groupType)
		{
			
			m_spawnObj->SetPos(pos);
			m_spawnObj->Start();
			m_spawned = true;
			CreateObject(m_spawnObj, m_groupType);
		}


		if (MON_TYPE::NONE != m_monType && GROUP_TYPE::BOSS == m_groupType)
		{
			m_spawnObj->SetPos(pos);
			CreateObject(m_spawnObj, m_groupType);
			m_spawned = true;
		}
		
	}
	else
	{
		m_spawnObj->SetPos(GetPos());
	}
}

void CSpawnObject::SetMonType(MON_TYPE _type)
{
	if (MON_TYPE::NONE != _type)
	{
		m_monType = _type;
	}

}

void CSpawnObject::SetGroupType(GROUP_TYPE _type)
{
	
	m_groupType = _type;
	
}

void CSpawnObject::Save(FILE* _file)
{
	CGameObject::Save(_file);
	int groupType = TYPE_NUMBER(m_groupType);
	int monType = TYPE_NUMBER(m_monType);
	fwrite(&groupType, sizeof(int), 1, _file);
	fwrite(&monType, sizeof(int), 1, _file);
}

void CSpawnObject::Load(FILE* _file)
{
	CGameObject::Load(_file);
	int groupType = 0;
	int monType = 0;
	fread(&groupType, sizeof(int), 1, _file);
	fread(&monType, sizeof(int), 1, _file);
	m_groupType = (GROUP_TYPE)groupType;
	m_monType = (MON_TYPE)monType;
}
