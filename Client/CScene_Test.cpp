#include "pch.h"

#include "CObject.h"

#include "CScene_Test.h"
#include "CPlayer.h"

#include "CTexture.h"

#include "CPathManager.h"
#include "CResourceManager.h"
#include "CColliderManager.h"
#include "CTimeManager.h"
#include "CCore.h"
#include "CCamera.h"


#include "CMonster.h"

#include "CSpawnObject.h"

#include "CKeyManager.h"
#include "CScene.h"

CScene_Test::CScene_Test()
	:m_background(nullptr)
{
}

CScene_Test::~CScene_Test()
{
}

void CScene_Test::Enter()
{
	CCore::GetInst()->SetDebug(true);
	Vec2 resolution = CCore::GetInst()->GetResolution();
	SetCurrnetState(SCENE_STATE::START);
	CScene::LoadMap(L"tile\\test.tile");
	CColliderManager::GetInst()->CheckGroup(GROUP_TYPE::GROUND, GROUP_TYPE::PLAYER);
	CColliderManager::GetInst()->CheckGroup(GROUP_TYPE::GROUND, GROUP_TYPE::MONSTER);
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

void CScene_Test::Exit()
{
	DeleteAll();
	CCamera::GetInst()->SetTarget(nullptr);
}

void CScene_Test::Update()
{
	Vec2 resolution = CCore::GetInst()->GetResolution();
	CScene::Update();
	if (GetCurrentState() == SCENE_STATE::START)
	{
		const vector<CObject*>& spawnObjs = GetObjWithType(GROUP_TYPE::SPAWN_OBJ);
		if (spawnObjs.empty())
		{
			SetCurrnetState(SCENE_STATE::PLAY);
			return;
		}
		for (CObject* obj : spawnObjs)
		{
			((CSpawnObject*)obj)->Spawn();
		}
		CSpawnObject* playerSpawn = ((CSpawnObject*)GetTarget(GROUP_TYPE::SPAWN_OBJ, L"Spawn_Player"));
		if (nullptr != playerSpawn)
		{
			CCamera::GetInst()->SetTarget(playerSpawn->GetSpawnObj());
		}
		else
			CCamera::GetInst()->SetLookAt(resolution);
		SetCurrnetState(SCENE_STATE::PLAY);
		return;
	}


	if (KEY_TAP(KEY::T))
	{
		ChangeScene(SCENE_TYPE::TOOL);
	}
	if (KEY_TAP(KEY::F1))
	{
		SetDebug();
	}

}

void CScene_Test::Render(HDC _dc)
{
	CScene::Render(_dc);
}
