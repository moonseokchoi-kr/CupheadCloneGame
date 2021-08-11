#include "pch.h"
#include "CScene_Tool.h"
#include "CTile.h"
#include "CPanelUI.h"
#include "CButtonUI.h"
#include "CTileButtonUI.h"
#include "CBackGround.h"
#include "CGameObject.h"
#include "CGround.h"


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
	


	if (!CUIManager::GetInst()->GetFocusedUI())
	{
		if(m_cilckedImageIdx > -1 && !CGameObjectManager::GetInst()->GetFocusObj())
			CreateGameObject();
	}
	
	if (KEY_TAP(KEY::DELT) && CGameObjectManager::GetInst()->GetFocusObj())
		DeleteGameObject();


	if (KEY_HOLD(KEY::LCTRL))
	{
		if (KEY_TAP(KEY::S))
		{
			SaveTileData();
		}
		else if(KEY_TAP(KEY::O))
		{
			LoadTileData();
		}
		
	}
}
	

void CScene_Tool::Enter()
{
	CCore::GetInst()->DockMenu();
	Vec2 resolution = RESOLUTION;

	/*CreateTile(5, 5);*/

	CUI* parentUI = new CPanelUI(false);
	parentUI->SetScale(Vec2(400.f, 550.f));
	parentUI->SetPos(Vec2(resolution.x - parentUI->GetScale().x, 100.f));
	parentUI->SetName(L"TilePanelUI");
	//타일 UI설정
	CTileButtonUI* tileUI = new CTileButtonUI(false);


	
	int row = 4;
	int col = 2;
	float yTerm = (parentUI->GetScale().y - 60.f) / (col+2);
	float xTerm = (parentUI->GetScale().x - 60.f) / (row+1);
	for (int i = 0; i <col; ++i)
	{
		for (int j = 0; j < row; ++j)
		{
			CTileButtonUI* newChild = tileUI->Clone();
			newChild->SetPos(Vec2(xTerm*(j+1), yTerm * (i + 1)));
			newChild->SetTileidx(i+j*row);
			newChild->SetName(L"TileButtonUI");
			newChild->SetClickedCallBack(this, (SCENE_MEM_FUNC)&CScene_Tool::GetTileUIidx);
			parentUI->AddChild(newChild);
		}
	}
	//탭 전환 버튼 설정
	row = 3;
	xTerm = (parentUI->GetScale().x - 60.f) / (row+2);
	CButtonUI* tabButton = new CButtonUI(false);
	
	tabButton->SetScale(Vec2(100.f, 60.f));
	
	for (int j = 0; j < row; ++j)
	{
		CButtonUI* newTabButton = tabButton->Clone();
		newTabButton->SetPos(Vec2(xTerm * (j + 1) + 30.f * j, 400.f));
		newTabButton->SetName(L"TabButtonUI");
		newTabButton->SetClickedCallBack(this, (SCENE_MEM_FUNC_INT)&CScene_Tool::GoIdxTable, (DWORD_PTR)j);
		parentUI->AddChild(newTabButton);
	}

	AddObject(parentUI, GROUP_TYPE::UI);

	CBackGround* back_obj = new CBackGround;

	
	back_obj->SetScale(Vec2(400, 300));
	back_obj->SetPos(resolution/2.f-Vec2(300.f,100.f));
	back_obj->SetType(BACKGROUND_TYPE::BLUE_SKY);
	AddObject(back_obj, GROUP_TYPE::BACK_GROUND);



	CCamera::GetInst()->SetLookAt(resolution / 2.f);
	CCamera::GetInst()->SetType(CAMERA_TYPE::DEFALT);
}

void CScene_Tool::Exit()
{
	CCore::GetInst()->UnDockMenu();
	DeleteAll();
}


void CScene_Tool::SaveTile(const wstring& _path)
{
	FILE* file = nullptr;

	_wfopen_s(&file, _path.c_str(), L"wb");
	
	assert(file);

	UINT xCount = GetTileX();
	UINT yCount = GetTileY();

	fwrite(&xCount, sizeof(UINT), 1, file);
	fwrite(&yCount, sizeof(UINT), 1, file);

	const vector<CObject*> tiles = GetObjWithType(GROUP_TYPE::TILE);
	for (CObject* tile : tiles)
	{
		((CTile*)tile)->Save(file);
	}

	fclose(file);
}

void CScene_Tool::SaveTileData()
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
		SaveTile(szFile);
	}
}

void CScene_Tool::LoadTileData()
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
		LoadTile(relativePath);
	}
}


void CScene_Tool::GoIdxTable(int _idx)
{
	int idx = 8*_idx;

	switch (_idx)
	{
	case 0:
		CGameObjectManager::GetInst()->SetCurrnetGroup(GROUP_TYPE::BACK_GROUND);
		break;
	case 1:
		CGameObjectManager::GetInst()->SetCurrnetGroup(GROUP_TYPE::BACK_GROUND);
		break;
	case 2:
		CGameObjectManager::GetInst()->SetCurrnetGroup(GROUP_TYPE::GAME_OBJECT);
	default:
		break;
	}

	const vector<CObject*>& UIs = GetObjWithType(GROUP_TYPE::UI);

	for (CObject* UI : UIs)
	{
		if (UI->GetName() == L"TilePanelUI")
		{
			const vector<CUI*>& children = ((CUI*)UI)->GetChilds();
			for (CUI* child : children)
			{
				if (child->GetName() == L"TileButtonUI")
				{
					((CTileButtonUI*)child)->SetTileidx(idx++);
				}
			}
			break;
		}
	}
}

void CScene_Tool::GetTileUIidx(int _idx)
{
	m_cilckedImageIdx = _idx;
}

void CScene_Tool::CreateGameObject()
{
	
	if (KEY_TAP(KEY::MOUSE_LBUTTON))
	{
		CGameObject* gameObj = nullptr;
		switch (CGameObjectManager::GetInst()->GetCurrentGroup())
		{
			
		case GROUP_TYPE::BACK_GROUND:
		{
			gameObj = new CBackGround;
			gameObj->SetPos(MOUSE_POS);
			((CBackGround*)gameObj)->SetType((BACKGROUND_TYPE)m_cilckedImageIdx);
			AddObject(gameObj, GROUP_TYPE::BACK_GROUND);
			m_cilckedImageIdx = -1;
		}
		break;
		case GROUP_TYPE::FORE_GROUND:
		{
		}
		break;
		case GROUP_TYPE::GAME_OBJECT:
		{
			
			switch ((GAMEOBJECT_TYPE)m_cilckedImageIdx)
			{
			case GAMEOBJECT_TYPE::FLOWER_PLATFORM:
				break;
			case GAMEOBJECT_TYPE::DARK_TOWER:
				break;
			case GAMEOBJECT_TYPE::NOMAL_TOWER:
				break;
			case GAMEOBJECT_TYPE::GROUND:
			{
				gameObj = new CGround;
				gameObj->SetPos(MOUSE_POS);
				AddObject(gameObj, GROUP_TYPE::GAME_OBJECT);
				m_cilckedImageIdx = -1;
			}
				break;
			case GAMEOBJECT_TYPE::END:
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
		}
	}
}



//
// Tile Count Window Proc
//
INT_PTR CALLBACK TileCountProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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