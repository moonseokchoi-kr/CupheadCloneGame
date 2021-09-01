#include "pch.h"
#include "CStageScene_02.h"
#include "CCore.h"
#include "CCamera.h"
#include "CMonster.h"
#include "CMonsterFactory.h"
#include "CPlayer.h"
#include "CColliderManager.h"
#include "CSpawnObject.h"
#include "CSound.h"
#include "CKeyManager.h"
CStageScene_02::CStageScene_02()
	:m_currentBoss(nullptr)
{
}

CStageScene_02::~CStageScene_02()
{
}

void CStageScene_02::Enter()
{
	Vec2 resolution = CCore::GetInst()->GetResolution();

	CScene::LoadMap(L"tile\\stage_2.tile");
	CScene::SetCurrnetState(SCENE_STATE::START);
	CColliderManager::GetInst()->CheckGroup(GROUP_TYPE::GROUND, GROUP_TYPE::PLAYER);
	CColliderManager::GetInst()->CheckGroup(GROUP_TYPE::GROUND, GROUP_TYPE::BOSS);
	CColliderManager::GetInst()->CheckGroup(GROUP_TYPE::PLATFORM_OBJ, GROUP_TYPE::PLAYER);
	CColliderManager::GetInst()->CheckGroup(GROUP_TYPE::BOSS, GROUP_TYPE::PLAYER_HITBOX);
	CColliderManager::GetInst()->CheckGroup(GROUP_TYPE::MONSTER_ATTACKBOX, GROUP_TYPE::PLAYER);
	CColliderManager::GetInst()->CheckGroup(GROUP_TYPE::PLAYER_BULLET, GROUP_TYPE::GROUND);
	CColliderManager::GetInst()->CheckGroup(GROUP_TYPE::PLAYER_BULLET, GROUP_TYPE::MONSTER_BULLET);
	CColliderManager::GetInst()->CheckGroup(GROUP_TYPE::PLAYER_BULLET, GROUP_TYPE::MONSTER_HITBOX);
	CColliderManager::GetInst()->CheckGroup(GROUP_TYPE::PLAYER_HITBOX, GROUP_TYPE::MONSTER_BULLET);
	CColliderManager::GetInst()->CheckGroup(GROUP_TYPE::PLAYER_HITBOX, GROUP_TYPE::MONSTER_HITBOX);
	CColliderManager::GetInst()->CheckGroup(GROUP_TYPE::MONSTER_BULLET, GROUP_TYPE::GROUND);

	SetBGM(L"BGM_SLIME");
	GetBGM()->PlayToBGM(true);
	GetBGM()->SetPosition(50.f);
	GetBGM()->SetVolume(20.f);

}

void CStageScene_02::Update()
{
	const vector<CObject*>& boss = GetObjWithType(GROUP_TYPE::BOSS);
	CScene::Update();
	if (GetCurrentState() == SCENE_STATE::START)
	{
		CSpawnObject* playerSpawn = ((CSpawnObject*)GetTarget(GROUP_TYPE::SPAWN_OBJ, L"Spawn_Player"));
		playerSpawn->Spawn();
		playerInfo info = ((CPlayer*)playerSpawn->GetSpawnObj())->GetInfo();
		info.health = GetHp();
		((CPlayer*)playerSpawn->GetSpawnObj())->SetInfo(info);
		CSpawnObject* salSpawn = ((CSpawnObject*)GetTarget(GROUP_TYPE::SPAWN_OBJ, L"Spawn_Slime"));
		salSpawn->Spawn();
		m_currentBoss = salSpawn->GetSpawnObj();
		m_prevBossName = m_currentBoss->GetName();
		CCamera::GetInst()->SetTarget(playerSpawn->GetSpawnObj());
		SetCurrnetState(SCENE_STATE::PLAY);
		return;
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
			ChangeScene(SCENE_TYPE::STAGE_01);
		}
	}

	if (m_currentBoss != nullptr && m_currentBoss->IsDead())
	{
		ChangeScene(SCENE_TYPE::START);
	}
	if (GetTarget(GROUP_TYPE::PLAYER, L"Player")->IsDead())
	{
		SetCurrnetState(SCENE_STATE::GAMEOVER);
		ChangeScene(SCENE_TYPE::START);
	}
}

void CStageScene_02::Exit()
{
	DeleteAll();
}
