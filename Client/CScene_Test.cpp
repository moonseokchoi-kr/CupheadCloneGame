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
	Vec2 resolution = CCore::GetInst()->GetResolution();
	SetCurrnetState(SCENE_STATE::PLAY);
	CScene::LoadMap(L"tile\\test_player.tile");
/*	const vector<CObject*>& spawners = GetObjWithType(GROUP_TYPE::SPAWN_OBJ);*/
	CObject* player = new CPlayer;
	player->SetPos(Vec2(200.f, 100.f));
	player->Start();
	CreateObject(player, GROUP_TYPE::PLAYER);

	CMonster* monster = CMonsterFactory::CreateMonster(MON_TYPE::SAL, Vec2(resolution.x - 340.f, 300.f));
	
	CreateObject(monster, GROUP_TYPE::BOSS);

	

	CColliderManager::GetInst()->CheckGroup(GROUP_TYPE::GROUND, GROUP_TYPE::PLAYER);
	CColliderManager::GetInst()->CheckGroup(GROUP_TYPE::GROUND, GROUP_TYPE::MONSTER);
	CColliderManager::GetInst()->CheckGroup(GROUP_TYPE::GROUND, GROUP_TYPE::BOSS);
	CColliderManager::GetInst()->CheckGroup(GROUP_TYPE::PLATFORM_OBJ, GROUP_TYPE::PLAYER);
	CColliderManager::GetInst()->CheckGroup(GROUP_TYPE::BOSS, GROUP_TYPE::PLAYER);
	CColliderManager::GetInst()->CheckGroup(GROUP_TYPE::PLAYER_BULLET, GROUP_TYPE::GROUND);
	CColliderManager::GetInst()->CheckGroup(GROUP_TYPE::PLAYER_BULLET, GROUP_TYPE::MONSTER_BULLET);
	CColliderManager::GetInst()->CheckGroup(GROUP_TYPE::PLAYER_BULLET, GROUP_TYPE::MONSTER_HITBOX);
	CColliderManager::GetInst()->CheckGroup(GROUP_TYPE::PLAYER_HITBOX, GROUP_TYPE::MONSTER_BULLET);
	CColliderManager::GetInst()->CheckGroup(GROUP_TYPE::PLAYER_HITBOX, GROUP_TYPE::MONSTER_HITBOX);
	CColliderManager::GetInst()->CheckGroup(GROUP_TYPE::MONSTER_BULLET, GROUP_TYPE::GROUND);
	

	
	CCamera::GetInst()->SetTarget(player);
	CCamera::GetInst()->SetLookAt(resolution / 2.f);
}

void CScene_Test::Exit()
{
	DeleteAll();
	CCamera::GetInst()->SetTarget(nullptr);
}

void CScene_Test::Update()
{

	CScene::Update();

	if (KEY_TAP(KEY::T))
	{
		ChangeScene(SCENE_TYPE::TOOL);
	}
	if (KEY_TAP(KEY::F1))
	{
		SetDebug();
	}
	if (KEY_TAP(KEY::F2))
	{
		SetDeadState(((CMonster*)GetTarget(GROUP_TYPE::BOSS, L"Potato")));
	}

}

void CScene_Test::Render(HDC _dc)
{
	CScene::Render(_dc);
}