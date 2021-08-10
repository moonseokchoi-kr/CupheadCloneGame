#include "pch.h"
#include "CScene_Tool.h"
#include "CTile.h"
#include "CPanelUI.h"
#include "CButtonUI.h"
#include "CTileButtonUI.h"
#include "CBackGround.h"

#include "CKeyManager.h"
#include "CPathManager.h"
#include "CCore.h"
#include "CCamera.h"
#include "CSceneManager.h"
#include "CResourceManager.h"
#include "CBackGroundManager.h"
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
/// 1. 오브젝트 선택해서 배경 나타나게 하기
/// 2. 각각에 항목 표시하는 글씨 적기
/// 3. 게임 오브젝트(비, 플랫폼, 번개 제작)
/// 4. 게임 오브젝트 드래그앤 드랍으로 배치하기
/// 5. 구름 오브젝트 제작


CScene_Tool::CScene_Tool()
	:m_cilckedImageIdx(0)
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
		SetTileIdx();
	}
	
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
	if (!CBackGroundManager::GetInst()->GetFocusBack())
	{
		if (KEY_TAP(KEY::MOUSE_LBUTTON))
		{
			CreateBackGround();
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

void CScene_Tool::SetTileIdx()
{
	if (KEY_HOLD(KEY::MOUSE_LBUTTON))
	{
		Vec2 mousePos = MOUSE_POS;

		mousePos = CCamera::GetInst()->GetRealPos(mousePos);

		int tileX = GetTileX();
		int tileY = GetTileY();

		int col = (int)mousePos.x / TILE_SIZE;
		int row = (int)mousePos.y / TILE_SIZE;

		if (mousePos.x < 0 || tileX <= col || mousePos.y < 0 || tileY <= row)
		{
			return;
		}

		UINT idx = row * tileX + col;

		const vector<CObject*>& tiles = GetObjWithType(GROUP_TYPE::TILE);

		((CTile*)tiles[idx])->SetImageIdx(m_cilckedImageIdx);

	}
	if (KEY_HOLD(KEY::MOUSE_RBUTTON))
	{
		Vec2 mousePos = MOUSE_POS;

		mousePos = CCamera::GetInst()->GetRealPos(mousePos);

		int tileX = GetTileX();
		int tileY = GetTileY();

		int col = (int)mousePos.x / TILE_SIZE;
		int row = (int)mousePos.y / TILE_SIZE;

		if (mousePos.x < 0 || tileX <= col || mousePos.y < 0 || tileY <= row)
		{
			return;
		}

		UINT idx = row * tileX + col;

		const vector<CObject*>& tiles = GetObjWithType(GROUP_TYPE::TILE);

		((CTile*)tiles[idx])->SetImageIdx(-1);
	}
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

void CScene_Tool::GoNextTable()
{
	int idx = 16;

	const vector<CObject*>& UIs = GetObjWithType(GROUP_TYPE::UI);
	
	for (CObject* UI : UIs)
	{
		if (UI->GetName() == L"TilePanelUI")
		{
			const vector<CUI*>& children =  ((CUI*)UI)->GetChilds();
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

void CScene_Tool::GoBackTable()
{
	int idx = 0;

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

void CScene_Tool::GoIdxTable(int _idx)
{
	int idx = 16*_idx;

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

void CScene_Tool::CreateBackGround()
{
	CBackGround* backObj = new CBackGround;
	backObj->SetPos(MOUSE_POS);
	backObj->SetType((BACKGROUND_TYPE)m_cilckedImageIdx);
	AddObject(backObj, GROUP_TYPE::BACK_GROUND);
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

			CScene* pCurScene = CSceneManager::GetInst()->GetCurrentScene();
			CScene_Tool* pScene = dynamic_cast<CScene_Tool*>(pCurScene);
			assert(pScene);

			pScene->DeleteGroup(GROUP_TYPE::TILE);

			pScene->CreateTile(iXCount, iYCount);
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