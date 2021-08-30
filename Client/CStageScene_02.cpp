#include "pch.h"
#include "CStageScene_02.h"
#include "CCore.h"
#include "CCamera.h"
#include "CMonster.h"
#include "CMonsterFactory.h"
#include "CPlayer.h"
#include "CColliderManager.h"
#include "CSpawnObject.h"
#include "CKeyManager.h"
CStageScene_02::CStageScene_02()
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

}

void CStageScene_02::Update()
{
	const vector<CObject*>& boss = GetObjWithType(GROUP_TYPE::BOSS);
	CScene::Update();
	if (GetCurrentState() == SCENE_STATE::START)
	{
		CSpawnObject* playerSpawn = ((CSpawnObject*)GetTarget(GROUP_TYPE::SPAWN_OBJ, L"Spawn_Player"));
		playerSpawn->Spawn();
		CSpawnObject* salSpawn = ((CSpawnObject*)GetTarget(GROUP_TYPE::SPAWN_OBJ, L"Spawn_Slime"));
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
			ChangeScene(SCENE_TYPE::STAGE_01);
		}
	}

	if (m_currentBoss != nullptr && m_currentBoss->IsDead())
	{
		int a = 0;
	}
}

void CStageScene_02::Exit()
{
	DeleteAll();
}
