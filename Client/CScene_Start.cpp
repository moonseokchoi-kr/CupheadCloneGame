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
int CScene_Start::nX = 0;
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

	CObject* player = new CPlayer;
	CreateObject(player, GROUP_TYPE::PLAYER, resolution / 2.f, Vec2(80.f, 40.f));

	CMonster* monster = CMonsterFactory::CreateMonster(MON_TYPE::NORMAL, Vec2(resolution / 2.f - Vec2(0.f, 300.f)));
	CreateObject(monster, GROUP_TYPE::MONSTER);
	
	
	
	CColliderManager::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PLAYER);
	//카메라 설정
	CCamera::GetInst()->SetTarget(player);
	
	
	
}

void CScene_Start::Exit()
{
	DeleteAll();
}

void CScene_Start::Update()
{
	CScene::Update();
	//ChanageScene();
}

void CScene_Start::Render(HDC _dc)
{
	CScene::Render(_dc);

}
