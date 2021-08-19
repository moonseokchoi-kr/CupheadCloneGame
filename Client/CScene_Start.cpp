#include "pch.h"

#include "CObject.h"

#include "CScene_Start.h"
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

CScene_Start::CScene_Start()
	:m_background(nullptr)
{
}

CScene_Start::~CScene_Start()
{
}

void CScene_Start::Enter()
{
	Vec2 resolution = CCore::GetInst()->GetResolution();

	CScene::LoadMap(L"tile\\test_player.tile");
	const vector<CObject*>& spawners = GetObjWithType(GROUP_TYPE::SPAWN_OBJ);
	((CSpawnObject*)spawners[0])->Spawn();

	// 	player->Start();
	// 	CreateObject(player, GROUP_TYPE::PLAYER, resolution / 2.f, Vec2(80.f, 40.f));

	CMonster* monster = CMonsterFactory::CreateMonster(MON_TYPE::SAL, spawners[0]->GetPos()-Vec2(200.f,0.f));
	
	CreateObject(monster, GROUP_TYPE::MONSTER);



	CColliderManager::GetInst()->CheckGroup(GROUP_TYPE::GROUND, GROUP_TYPE::PLAYER);
	CColliderManager::GetInst()->CheckGroup(GROUP_TYPE::GROUND, GROUP_TYPE::MONSTER);
	CColliderManager::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PLAYER);
	CColliderManager::GetInst()->CheckGroup(GROUP_TYPE::PLATFORM_OBJ, GROUP_TYPE::PLAYER);
	CColliderManager::GetInst()->CheckGroup(GROUP_TYPE::PLAYER_BULLET, GROUP_TYPE::MONSTER);
	CColliderManager::GetInst()->CheckGroup(GROUP_TYPE::PLAYER_BULLET, GROUP_TYPE::GROUND);
	CColliderManager::GetInst()->CheckGroup(GROUP_TYPE::PLAYER_BULLET, GROUP_TYPE::PLATFORM_OBJ);

	//CCamera::GetInst()->SetLookAt(resolution / 2.f);
	
}

void CScene_Start::Exit()
{
	DeleteAll();
	CCamera::GetInst()->SetTarget(nullptr);
}

void CScene_Start::Update()
{

	CScene::Update();
	if (!GetObjWithType(GROUP_TYPE::PLAYER).empty())
	{
		CObject* player = GetObjWithType(GROUP_TYPE::PLAYER)[0];
		//카메라 설정
		CCamera::GetInst()->SetTarget(player);
	}
	if (KEY_TAP(KEY::T))
	{
		ChangeScene(SCENE_TYPE::TOOL);
	}
}

void CScene_Start::Render(HDC _dc)
{
	CScene::Render(_dc);
}
