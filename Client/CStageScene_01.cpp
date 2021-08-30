#include "pch.h"
#include "CStageScene_01.h"
#include "CCore.h"
#include "CCamera.h"
#include "CMonster.h"
#include "CMonsterFactory.h"
#include "CPlayer.h"
#include "CColliderManager.h"
#include "CSpawnObject.h"
#include "CKeyManager.h"
CStageScene_01::CStageScene_01()
	:m_currentBoss(nullptr)
{
}

CStageScene_01::~CStageScene_01()
{
}

void CStageScene_01::Enter()
{
	Vec2 resolution = CCore::GetInst()->GetResolution();

	CScene::LoadMap(L"tile\\stage_1.tile");
	CScene::SetCurrnetState(SCENE_STATE::START);
	

	
	
	CColliderManager::GetInst()->CheckGroup(GROUP_TYPE::GROUND, GROUP_TYPE::PLAYER);
	CColliderManager::GetInst()->CheckGroup(GROUP_TYPE::GROUND, GROUP_TYPE::BOSS);
	CColliderManager::GetInst()->CheckGroup(GROUP_TYPE::PLATFORM_OBJ, GROUP_TYPE::PLAYER);
	CColliderManager::GetInst()->CheckGroup(GROUP_TYPE::BOSS, GROUP_TYPE::PLAYER);
	CColliderManager::GetInst()->CheckGroup(GROUP_TYPE::MONSTER_ATTACKBOX, GROUP_TYPE::PLAYER);
	CColliderManager::GetInst()->CheckGroup(GROUP_TYPE::PLAYER_BULLET, GROUP_TYPE::GROUND);
	CColliderManager::GetInst()->CheckGroup(GROUP_TYPE::PLAYER_BULLET, GROUP_TYPE::MONSTER_BULLET);
	CColliderManager::GetInst()->CheckGroup(GROUP_TYPE::PLAYER_BULLET, GROUP_TYPE::MONSTER_HITBOX);
	CColliderManager::GetInst()->CheckGroup(GROUP_TYPE::PLAYER_HITBOX, GROUP_TYPE::MONSTER_BULLET);
	CColliderManager::GetInst()->CheckGroup(GROUP_TYPE::PLAYER_HITBOX, GROUP_TYPE::MONSTER_HITBOX);
	CColliderManager::GetInst()->CheckGroup(GROUP_TYPE::MONSTER_BULLET, GROUP_TYPE::GROUND);

	
}

void CStageScene_01::Update()
{
	const vector<CObject*>& boss = GetObjWithType(GROUP_TYPE::BOSS);
	CScene::Update();
	if (GetCurrentState() == SCENE_STATE::START)
	{
		CSpawnObject* playerSpawn = ((CSpawnObject*)GetTarget(GROUP_TYPE::SPAWN_OBJ, L"Spawn_Player"));
		playerSpawn->Spawn();
		CSpawnObject* salSpawn = ((CSpawnObject*)GetTarget(GROUP_TYPE::SPAWN_OBJ, L"Spawn_Potato"));
		salSpawn->Spawn();
		m_currentBoss = salSpawn->GetSpawnObj();
		m_prevBossName = m_currentBoss->GetName();
		CCamera::GetInst()->SetTarget(playerSpawn->GetSpawnObj());
		SetCurrnetState(SCENE_STATE::PLAY);
	}
	if (KEY_TAP(KEY::F1))
	{
		SetDebug();
	}
	if (CCore::GetInst()->IsDebug())
	{
		if (KEY_TAP(KEY::F2))
		{
			SetDeadState((CMonster*)m_currentBoss);
		}

		if (KEY_TAP(KEY::F7))
		{
			ChangeScene(SCENE_TYPE::STAGE_02);
		}
	}

	if (m_currentBoss != nullptr&&m_currentBoss->IsDead())
	{
		if (m_prevBossName == L"Potato")
		{
			CSpawnObject* onionSpawn = ((CSpawnObject*)GetTarget(GROUP_TYPE::SPAWN_OBJ, L"Spawn_Onion"));
			onionSpawn->Spawn();
			m_currentBoss = onionSpawn->GetSpawnObj();
			m_prevBossName = m_currentBoss->GetName();
			return;
		}
		else if (m_prevBossName == L"Carrot")
		{
			ChangeScene(SCENE_TYPE::STAGE_02);
		}
		else
		{
			CSpawnObject* carrotSpawn = ((CSpawnObject*)GetTarget(GROUP_TYPE::SPAWN_OBJ, L"Spawn_Carrot"));
			carrotSpawn->Spawn();
			m_currentBoss = carrotSpawn->GetSpawnObj();
			m_prevBossName = m_currentBoss->GetName();
		}
	}
}


void CStageScene_01::Exit()
{
	DeleteAll();
}
