#include "pch.h"
#include "CStartScene.h"
#include "CBackGround.h"
#include "CPanelUI.h"
#include "CTextUI.h"
#include "CMenuPanel.h"
#include "CMenuButtonUI.h"
#include "CCore.h"
#include "CCamera.h"
CStartScene::CStartScene()
{
}

CStartScene::~CStartScene()
{
}

void CStartScene::Enter()
{
	SetCurrnetState(SCENE_STATE::START);
	Vec2 resolution = CCore::GetInst()->GetResolution();
	CCore::GetInst()->SetDebug(true);
	CBackGround* titleMenu = new CBackGround;
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
// 	CMenuButtonUI* exitButton = new CMenuButtonUI;
// 	exitButton->SetScale(Vec2(320.f, 78.f));
// 	exitButton->SetPos(Vec2(-152.f, -menuPanel->GetScale().y / 2.f + 246.f));
// 	exitButton->SetIndex(3);
//	menuPanel->AddChild(exitButton);

	CreateObject(menuPanel, GROUP_TYPE::UI);
	CCamera::GetInst()->SetLookAt(resolution / 2.f);
}

void CStartScene::Update()
{
	CScene::Update();
}

void CStartScene::Exit()
{
	DeleteAll();
}
