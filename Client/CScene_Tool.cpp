#include "pch.h"
#include "CScene_Tool.h"
#include "CTile.h"
#include "CPanelUI.h"
#include "CButtonUI.h"
#include "CTextUI.h"
#include "CTileButtonUI.h"
#include "CBackGround.h"
#include "CGameObject.h"
#include "CGround.h"
#include "CForeGround.h"
#include "CSpawnObject.h"

#include "CKeyManager.h"
#include "CPathManager.h"
#include "CCore.h"
#include "CCamera.h"
#include "CSceneManager.h"
#include "CResourceManager.h"
#include "CGameObjectManager.h"
#include "CTexture.h"
#include "CUIManager.h"
#include "resource.h"
#include "CColliderManager.h"


///
/// 현재 진행상황
/// 
/// 1. 배경오브젝트 드래그앤 드랍으로 옮길 수 있음
/// 2. 버튼 UI로 필요한 Obejct 선택가능
/// 
/// 해야할것
/// 1. 만들어진 오브젝트 지울수 있게 하기
/// 2. 각각에 항목 표시하는 글씨 적기
/// 3. 게임 오브젝트(비, 플랫폼, 번개 제작)
/// 4. 게임 오브젝트 드래그앤 드랍으로 배치하기
/// 5. 구름 오브젝트 제작


CScene_Tool::CScene_Tool()
	:m_cilckedImageIdx(-1)
{
}

CScene_Tool::~CScene_Tool()
{
}

void CScene_Tool::Update()
{
	CScene::Update();
	CGameObject* focusObj = CGameObjectManager::GetInst()->GetFocusObj();
	CSpawnObject* spawnObj = static_cast<CSpawnObject*>(focusObj);
	if(focusObj)
	{
		m_focusPos->SetText(L"Position:(" + to_wstring((int)focusObj->GetPos().x) + L" , " + to_wstring((int)focusObj->GetPos().y) + L")");
		m_focusScale->SetText(L"Scale:(" + to_wstring((int)focusObj->GetScale().x) + L" , " + to_wstring((int)focusObj->GetScale().y) + L")");
	}
	if (spawnObj)
	{
		
	}
	if (!CUIManager::GetInst()->GetFocusedUI())
	{
		if(m_cilckedImageIdx > -1 && !focusObj)
			CreateGameObject();
	}
	
	if (KEY_TAP(KEY::DELT) && focusObj)
		DeleteGameObject();
	if (spawnObj && (spawnObj->GetGroupType() == GROUP_TYPE::PLAYER || spawnObj->GetGroupType() == GROUP_TYPE::BOSS))
	{
		if (nullptr == spawnObj)
			return;
		spawnObj->Spawn();
	}

	if (KEY_HOLD(KEY::LCTRL))
	{
		if (KEY_TAP(KEY::S))
		{
			SaveMapData();
		}
		else if(KEY_TAP(KEY::O))
		{
			LoadMapData();
		}
		else if (KEY_TAP(KEY::R))
		{
			CGameObjectManager::GetInst()->SetFocusedObj(nullptr);
			DeleteGroup(GROUP_TYPE::BACK_GROUND);
			DeleteGroup(GROUP_TYPE::GAME_OBJ);
			DeleteGroup(GROUP_TYPE::FORE_GROUND);
		}
	}
	if (KEY_TAP(KEY::T))
	{
		wstring relativePath = CPathManager::GetInst()->GetContentPath();
		relativePath += L"tile\\test.tile";
		SaveMap(relativePath);
		ChangeScene(SCENE_TYPE::TEST);
		m_isGoTest = true;
	}
	
	if (KEY_TAP(KEY::ESC))
	{
		ShowPauseUI();
	}
}
	

void CScene_Tool::Enter()
{
	if (m_isGoTest)
		LoadMap(L"tile\\test.tile");
	Vec2 resolution = Vec2(1600, 960);
	CCore::GetInst()->DockMenu(resolution);
	CCore::GetInst()->SetDebug(true);
	SetCurrnetState(SCENE_STATE::PLAY);
	/*CreateTile(5, 5);*/

	CUI* parentUI = new CPanelUI(false);
	parentUI->SetScale(Vec2(400.f, 450.f));
	parentUI->SetPos(Vec2(resolution.x - parentUI->GetScale().x, 100.f));
	parentUI->SetName(L"TilePanelUI");
	
	CUI* textPanel = new CPanelUI(false);
	textPanel->SetScale(Vec2(parentUI->GetScale().x, 100.f));
	textPanel->SetPos(Vec2(resolution.x - parentUI->GetScale().x, 0.f ));
	textPanel->SetName(L"TextPanelUI");
	
	m_focusPos = new CTextUI(false);
	m_focusPos->SetPos(Vec2(10.f,10.f));
	textPanel->AddChild(m_focusPos);

	m_focusScale = new CTextUI(false);
	m_focusScale->SetPos(Vec2(10.f, 30.f));
	textPanel->AddChild(m_focusScale);

	m_focusObjText = new CTextUI(false);
	m_focusObjText->SetPos(Vec2(10.f, 50.f));
	textPanel->AddChild(m_focusObjText);

	CUI* textMouse = new CTextUI(false);
	((CTextUI*)textMouse)->SetMouseFollow(true);
	
	AddObject(textPanel, GROUP_TYPE::UI);
	AddObject(textMouse, GROUP_TYPE::UI);
	
	//타일 UI설정
	CTileButtonUI* tileUI = new CTileButtonUI(false);

	CreatePauseUI();
	
	int row = 4;
	int col = 4;
	float yTerm = (parentUI->GetScale().y - 60.f) / (col+2);
	float xTerm = (parentUI->GetScale().x - 60.f) / (row+1);
	for (int i = 0; i <col; ++i)
	{
		for (int j = 0; j < row; ++j)
		{
			CTileButtonUI* newChild = tileUI->Clone();
			newChild->SetPos(Vec2(xTerm*(j+1), yTerm * (i + 1)));
			newChild->SetTileidx(i+j*col);
			newChild->SetName(L"TileButtonUI");
			newChild->SetClickedCallBack(this, (SCENE_MEM_FUNC)&CScene_Tool::GetTileUIidx);
			parentUI->AddChild(newChild);
		}
	}

	AddObject(parentUI, GROUP_TYPE::UI);

	CBackGround* back_obj = new CBackGround;


	CCamera::GetInst()->SetLookAt(resolution / 2.f);

	CColliderManager::GetInst()->CheckGroup(GROUP_TYPE::GROUND, GROUP_TYPE::PLAYER);
	CColliderManager::GetInst()->CheckGroup(GROUP_TYPE::GROUND, GROUP_TYPE::MONSTER);
	CColliderManager::GetInst()->CheckGroup(GROUP_TYPE::GROUND, GROUP_TYPE::BOSS);
	CColliderManager::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PLAYER);
	CColliderManager::GetInst()->CheckGroup(GROUP_TYPE::PLATFORM_OBJ, GROUP_TYPE::PLAYER);
	CColliderManager::GetInst()->CheckGroup(GROUP_TYPE::PLAYER_BULLET, GROUP_TYPE::MONSTER);
	CColliderManager::GetInst()->CheckGroup(GROUP_TYPE::PLAYER_BULLET, GROUP_TYPE::BOSS);
	CColliderManager::GetInst()->CheckGroup(GROUP_TYPE::PLAYER_BULLET, GROUP_TYPE::GAME_OBJ);
	CColliderManager::GetInst()->CheckGroup(GROUP_TYPE::PLAYER_BULLET, GROUP_TYPE::PLATFORM_OBJ);
	CColliderManager::GetInst()->CheckGroup(GROUP_TYPE::PLAYER_BULLET, GROUP_TYPE::MONSTER_BULLET);
	CColliderManager::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER_BULLET);
	CColliderManager::GetInst()->CheckGroup(GROUP_TYPE::MONSTER_BULLET, GROUP_TYPE::GROUND);
	CColliderManager::GetInst()->CheckGroup(GROUP_TYPE::MONSTER_BULLET, GROUP_TYPE::PLATFORM_OBJ);

}

void CScene_Tool::Exit()
{
	CCore::GetInst()->UnDockMenu();
	DeleteAll();
}


void CScene_Tool::SaveMap(const wstring& _path)
{
	FILE* file = nullptr;

	_wfopen_s(&file, _path.c_str(), L"wb");
	
	assert(file);

	
	const vector<CObject*> backgrounds = GetObjWithType(GROUP_TYPE::BACK_GROUND);
	for (CObject* backGround : backgrounds)
	{
		fputs("B\n", file);
		((CBackGround*)backGround)->Save(file);
		fputs("\n", file);
	}

	
	const vector<CObject*> gameObjs = GetObjWithType(GROUP_TYPE::GAME_OBJ);
	for (CObject* gameObj : gameObjs)
	{
		switch (((CGameObject*)gameObj)->GetType())
		{
		case GAMEOBJECT_TYPE::SPAWN:
		{
			fputs("S\n", file);
			((CSpawnObject*)gameObj)->Save(file);
			fputs("\n", file);
		}
		break;
		case GAMEOBJECT_TYPE::GROUND:
		{
			fputs("G\n", file);
			((CGround*)gameObj)->Save(file);
			fputs("\n", file);
		}
		break;
		case GAMEOBJECT_TYPE::FLOWER_PLATFORM_A:
		case GAMEOBJECT_TYPE::FLOWER_PLATFORM_B:
		case GAMEOBJECT_TYPE::FLOWER_PLATFORM_C:
		{
			fputs("P\n", file);
			((CGround*)gameObj)->Save(file);
			fputs("\n", file);
		}
		break;
		default:
			break;
		}
	}
	const vector<CObject*> foreGrounds = GetObjWithType(GROUP_TYPE::FORE_GROUND);
	for(CObject* foreGround:foreGrounds)
	{
		fputs("F\n", file);
		((CForeGround*)foreGround)->Save(file);
		fputs("\n", file);
	}

	fputs("E", file);
	fclose(file);
}

void CScene_Tool::SaveMapData()
{
	OPENFILENAME ofn = {};
	//file name
	wchar_t szFile[256] = {};
	wstring strTileFolder = CPathManager::GetInst()->GetContentPath();
	strTileFolder += L"tile";
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = CCore::GetInst()->GetMainHwnd();
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = L"All\0*.*\0Tile\0*.tile\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = strTileFolder.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;


	if (GetSaveFileName(&ofn))
	{
		SaveMap(szFile);
	}
}

void CScene_Tool::LoadMapData()
{
	OPENFILENAME ofn = {};
	//file name
	wchar_t szFile[256] = {};
	wstring strTileFolder = CPathManager::GetInst()->GetContentPath();
	strTileFolder += L"tile";
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = CCore::GetInst()->GetMainHwnd();
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = L"All\0*.*\0Tile\0*.tile\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = strTileFolder.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	if (GetOpenFileName(&ofn))
	{
		wstring relativePath = CPathManager::GetInst()->GetRelativePath(szFile);
		LoadMap(relativePath);
	}
	CGameObjectManager::GetInst()->SetFocusedObj(nullptr);
}

void CScene_Tool::GetTileUIidx(int _idx)
{
	m_cilckedImageIdx = _idx;

	if (0 <= m_cilckedImageIdx&& m_cilckedImageIdx < 4)
	{
		CGameObjectManager::GetInst()->SetCurrnetGroup(GROUP_TYPE::BACK_GROUND);
	}
	else if (4 <= m_cilckedImageIdx && m_cilckedImageIdx < 8)
	{
		CGameObjectManager::GetInst()->SetCurrnetGroup(GROUP_TYPE::FORE_GROUND);
	}
	else
	{
		CGameObjectManager::GetInst()->SetCurrnetGroup(GROUP_TYPE::GAME_OBJ);
	}
}

void CScene_Tool::CreateGameObject()
{
	if (KEY_TAP(KEY::MOUSE_LBUTTON))
	{
		CGameObject* gameObj = nullptr;
		Vec2 mousePos = CCamera::GetInst()->GetRealPos(MOUSE_POS);
		switch (CGameObjectManager::GetInst()->GetCurrentGroup())
		{

		case GROUP_TYPE::BACK_GROUND:
		{
			if (m_cilckedImageIdx > 1)
				return;
			gameObj = new CBackGround;
			gameObj->SetPos(Vec2(1450 / 2.f, 960 / 2.f));
			((CBackGround*)gameObj)->SetType((BACKGROUND_TYPE)m_cilckedImageIdx);
			AddObject(gameObj, GROUP_TYPE::BACK_GROUND);
			m_cilckedImageIdx = -1;
		}
		break;
		case GROUP_TYPE::FORE_GROUND:
		{
			gameObj = new CForeGround;
			gameObj->SetPos(mousePos);
			((CForeGround*)gameObj)->SetType((FOREGROUND_TYPE)m_cilckedImageIdx);
			AddObject(gameObj, GROUP_TYPE::FORE_GROUND);
			m_cilckedImageIdx = -1;

		}
		break;
		case GROUP_TYPE::GAME_OBJ:
		{

			switch ((GAMEOBJECT_TYPE)m_cilckedImageIdx)
			{
			case GAMEOBJECT_TYPE::FLOWER_PLATFORM_A:
			{
				gameObj = new CGround;
				gameObj->SetType(GAMEOBJECT_TYPE::FLOWER_PLATFORM_A);
				gameObj->SetPos(mousePos);
				gameObj->Start();
				AddObject(gameObj, GROUP_TYPE::GAME_OBJ);
				m_cilckedImageIdx = -1;
			}
			break;
			case GAMEOBJECT_TYPE::FLOWER_PLATFORM_B:
			{
				gameObj = new CGround;
				gameObj->SetType(GAMEOBJECT_TYPE::FLOWER_PLATFORM_B);
				gameObj->SetPos(mousePos);
				gameObj->Start();
				AddObject(gameObj, GROUP_TYPE::GAME_OBJ);
				m_cilckedImageIdx = -1;
			}
			break;
			case GAMEOBJECT_TYPE::FLOWER_PLATFORM_C:
			{
				gameObj = new CGround;
				gameObj->SetType(GAMEOBJECT_TYPE::FLOWER_PLATFORM_C);
				gameObj->SetPos(mousePos);
				gameObj->Start();
				AddObject(gameObj, GROUP_TYPE::GAME_OBJ);
				m_cilckedImageIdx = -1;
			}
			break;
			case GAMEOBJECT_TYPE::GROUND:
			{
				gameObj = new CGround;
				gameObj->SetPos(mousePos);
				gameObj->SetType(GAMEOBJECT_TYPE::GROUND);
				gameObj->Start();
				AddObject(gameObj, GROUP_TYPE::GAME_OBJ);
				m_cilckedImageIdx = -1;
			}
			break;
			case GAMEOBJECT_TYPE::SPAWN:
			{
				gameObj = new CSpawnObject;
				gameObj->SetPos(mousePos);
				gameObj->SetType(GAMEOBJECT_TYPE::SPAWN);

				AddObject(gameObj, GROUP_TYPE::GAME_OBJ);
				m_cilckedImageIdx = -1;
			}
			break;
			default:
				break;
			}
		}
		break;
		default:
			break;
		}
		CGameObjectManager::GetInst()->SetFocusedObj(gameObj);
	}
}

/// <summary>
/// 배경을 삭제하는 함수, 현재 선택한 개체를 지우는 함수 delete키를 이용
/// </summary>
void CScene_Tool::DeleteGameObject()
{

	const vector<CObject*>& backObjs = GetObjWithType(CGameObjectManager::GetInst()->GetCurrentGroup());
	
	for (CObject* obj : backObjs)
	{
		if (obj == CGameObjectManager::GetInst()->GetFocusObj())
		{
			DeleteObject(obj);
			CGameObjectManager::GetInst()->SetFocusedObj(nullptr);
		}
	}
}



//
// Tile Count Window Proc
//
INT_PTR CALLBACK MapSizeProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			UINT iXCount = GetDlgItemInt(hDlg, IDC_EDIT1, nullptr, false);
			UINT iYCount = GetDlgItemInt(hDlg, IDC_EDIT2, nullptr, false);

			CGameObject* gameObj = CGameObjectManager::GetInst()->GetFocusObj();
			if (nullptr == gameObj)
			{
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
				
			gameObj->ChangeSize(Vec2((float)iXCount, (float)iYCount));


			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}


//
// Offset Window Proc
//
INT_PTR CALLBACK SetOffsetProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			int Offset = GetDlgItemInt(hDlg, IDC_OFFSET_EDIT1, nullptr, false);

			CGameObject* gameObj = CGameObjectManager::GetInst()->GetFocusObj();
			if (nullptr == gameObj)
			{
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}

			gameObj->SetOffset(Offset);

			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}


/// 
/// ListBoxProc
///
int index = 0;
SpawnObj spawnList[] =
{
	{TEXT("Player"),GROUP_TYPE::PLAYER,MON_TYPE::NONE},
	{TEXT("Nomal"),GROUP_TYPE::MONSTER,MON_TYPE::NORMAL},
	{TEXT("Slime"),GROUP_TYPE::BOSS,MON_TYPE::SLIME},
	{TEXT("Ollie Bulb"),GROUP_TYPE::BOSS,MON_TYPE::OLLIE},
	{TEXT("Chauncey Chantenay"),GROUP_TYPE::BOSS,MON_TYPE::CHAUNCEY},
	{TEXT("Sal Spudder"),GROUP_TYPE::BOSS,MON_TYPE::SAL},

};
INT_PTR CALLBACK ListBoxExampleProc(HWND hDlg, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	

	switch (message)
	{
	case WM_INITDIALOG:
	{
		// Add items to list. 
		HWND hwndList = GetDlgItem(hDlg, IDC_SPAWN_OBJ_LIST);
		for (int i = 0; i < ARRAYSIZE(spawnList); i++)
		{
			int pos = (int)SendMessage(hwndList, LB_ADDSTRING, 0,
				(LPARAM)spawnList[i].objName);
			// Set the array index of the player as item data.
			// This enables us to retrieve the item from the array
			// even after the items are sorted by the list box.
			SendMessage(hwndList, LB_SETITEMDATA, pos, (LPARAM)i);
		}
		// Set input focus to the list box.
		SetFocus(hwndList);
		return TRUE;
	}

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			CGameObject* gameObj = CGameObjectManager::GetInst()->GetFocusObj();

			CSpawnObject* spawnObj = static_cast<CSpawnObject*>(gameObj);

			if (nullptr == spawnObj)
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
				
			spawnObj->SetMonType(spawnList[index].mon_type);
			spawnObj->SetGroupType(spawnList[index].group);
			spawnObj->Start();
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		case IDCANCEL:
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;

		case IDC_SPAWN_OBJ_LIST:
		{
			switch (HIWORD(wParam))
			{
			case LBN_SELCHANGE:
			{
				HWND hwndList = GetDlgItem(hDlg, IDC_SPAWN_OBJ_LIST);

				// Get selected index.
				int lbItem = (int)SendMessage(hwndList, LB_GETCURSEL, 0, 0);

				// Get item data.
				index = (int)SendMessage(hwndList, LB_GETITEMDATA, lbItem, 0);

				
				
				return TRUE;
			}
			}
		}
		return TRUE;
		}
	}
	return FALSE;
}


void LoadMapData()
{
	OPENFILENAME ofn = {};
	//file name
	wchar_t szFile[256] = {};
	wstring strTileFolder = CPathManager::GetInst()->GetContentPath();
	strTileFolder += L"tile";
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = CCore::GetInst()->GetMainHwnd();
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = L"All\0*.*\0Tile\0*.tile\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = strTileFolder.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;


	if (GetOpenFileName(&ofn))
	{
		wstring relativePath = CPathManager::GetInst()->GetRelativePath(szFile);
		CScene* curScene = CSceneManager::GetInst()->GetCurrentScene();
		curScene->LoadMap(relativePath);
		MessageBox(CCore::GetInst()->GetMainHwnd(), L"맵을 불러왔습니다.", L"불러오기 확인", MB_OK);
	}
}


void SaveMapData()
{
	OPENFILENAME ofn = {};
	//file name
	wchar_t szFile[256] = {};
	wstring strTileFolder = CPathManager::GetInst()->GetContentPath();
	strTileFolder += L"tile";
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = CCore::GetInst()->GetMainHwnd();
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = L"All\0*.*\0Tile\0*.tile\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = strTileFolder.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;


	if (GetSaveFileName(&ofn))
	{
		CScene* curScene = CSceneManager::GetInst()->GetCurrentScene();
		CScene_Tool* toolScene = static_cast<CScene_Tool*>(curScene);

		toolScene->SaveMap(szFile);
		MessageBox(CCore::GetInst()->GetMainHwnd(), L"맵을 저장했습니다.", L"저장 확인", MB_OK);
	}


}