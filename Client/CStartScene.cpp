#include "pch.h"
#include "CStartScene.h"
#include "CBackGround.h"
#include "CPanelUI.h"
#include "CTextUI.h"
#include "CMenuPanel.h"
#include "CMenuButtonUI.h"
#include "CResourceManager.h"
#include "CCore.h"
#include "CSound.h"
#include "CVFXObject.h"
#include "CCamera.h"
CStartScene::CStartScene()
{
}

CStartScene::~CStartScene()
{
}

void CStartScene::Enter()
{
	Vec2 resolution = CCore::GetInst()->GetResolution();

	SetCurrnetState(SCENE_STATE::START);
	
	CCore::GetInst()->SetDebug(true);
	CBackGround* titleMenu = new CBackGround(false);
	titleMenu->SetType(BACKGROUND_TYPE::TITLE);
	titleMenu->SetPos(Vec2(resolution / 2.f));
	CreateObject(titleMenu, GROUP_TYPE::BACK_GROUND);
	CMenuPanel* menuPanel = new CMenuPanel;
	menuPanel->SetPos(Vec2(resolution / 2.f) + Vec2(0.f, 180.f));
	menuPanel->SetScale(Vec2(400.f, 384.f));
	CMenuButtonUI* startButton = new CMenuButtonUI;
	startButton->SetScale(Vec2(320.f, 78.f));
	startButton->SetPos(Vec2(-152.f, -menuPanel->GetScale().y/2.f+138.f));
	startButton->SetIndex(2);
	startButton->SetClickedCallBack((SCENE_MEM_FUNC_SCENE_TYPE)&ChangeScene, (DWORD_PTR)SCENE_TYPE::STAGE_01);
	menuPanel->AddChild(startButton);
	CMenuButtonUI* toolButton = new CMenuButtonUI;
	toolButton->SetScale(Vec2(320.f, 78.f));
	toolButton->SetPos(Vec2(-152.f, -menuPanel->GetScale().y / 2.f + 246.f));
	toolButton->SetIndex(4);
	toolButton->SetClickedCallBack((SCENE_MEM_FUNC_SCENE_TYPE)&ChangeScene, (DWORD_PTR)SCENE_TYPE::TOOL);
	menuPanel->AddChild(toolButton);
	
	SetBGM(L"BGM_TITLE");
	GetBGM()->PlayToBGM(true);
	GetBGM()->SetPosition(50.f);
	GetBGM()->SetVolume(20.f);

	CreateObject(menuPanel, GROUP_TYPE::UI);
	
}

void CStartScene::Update()
{
	CScene::Update();
}

void CStartScene::Exit()
{
	DeleteAll();
	GetBGM()->Stop();
}
