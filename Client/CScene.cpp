#include "pch.h"
#include "CScene.h"
#include "CTexture.h"
#include "CTile.h"
#include "CMonster.h"
#include "FSMAI.h"

#include "CPathManager.h"
#include "CResourceManager.h"
#include "CCore.h"
#include "CCamera.h"
#include "CBackGround.h"
#include "CSpawnObject.h"
#include "CGround.h"
#include "CForeGround.h"
#include "CMenuPanel.h"
#include "CMenuButtonUI.h"
#include "CSceneManager.h"
#include "CGameObjectManager.h"

int  CScene::m_playerhp = 0;
CScene::CScene()
	:m_TileXCount(0)
	,m_TileYCount(0)
	,m_currentState(SCENE_STATE::START)
	,m_prevState(SCENE_STATE::START)
{
	
}

CScene::~CScene()
{
	for (int i = 0; i < m_arrObj.size(); ++i)
	{
		for (int j = 0; j < m_arrObj[i].size(); ++j)
		{
			delete m_arrObj[i][j];
		}
	}
}
void CScene::Start()
{
	for (int i = 0; i < m_arrObj.size(); ++i)
	{
		for (int j = 0; j < m_arrObj[i].size(); ++j)
		{
			if (!m_arrObj[i][j]->IsDead())
			{
				m_arrObj[i][j]->Start();
			}

		}
	}
}
/// <summary>
/// 씬안에 있는 오브젝트들의 update를 진행하는 함수
/// </summary>
void CScene::Update()
{

	for (int i = 0; i < m_arrObj.size(); ++i)
	{
		if (TYPE_NUMBER(GROUP_TYPE::BACK_GROUND) == i)
		{
			offset_change();
		}
		if (m_currentState == SCENE_STATE::PAUSE)
		{
			if (TYPE_NUMBER(GROUP_TYPE::UI) == i)
			{
				for (int j = 0; j < m_arrObj[i].size(); ++j)
				{
					if (!m_arrObj[i][j]->IsDead())
					{
						m_arrObj[i][j]->Update();
					}

				}
			}
			continue;
		}

		for (int j = 0; j < m_arrObj[i].size(); ++j)
		{
			if (!m_arrObj[i][j]->IsDead())
			{
				m_arrObj[i][j]->Update();
			}

		}
		
	}
}
/// <summary>
/// 씬에 존재하는 오브젝트들을 렌더링하는 함수
/// </summary>
/// <param name="_dc">렌더링 데이터를 집어넣을 Device Context</param>
void CScene::Render(HDC _dc)
{
	for (int i = 0; i < m_arrObj.size(); ++i)
	{
		vector<CObject*>::iterator iter = m_arrObj[i].begin();
		for (;iter != m_arrObj[i].end();)
		{
			if (!(*iter)->IsDead())
			{
				(*iter)->Render(_dc);
				++iter;
			}
			else
			{
				iter = m_arrObj[i].erase(iter);
			}
		}

		
	}
}

void CScene::FinalUpdate()
{
	for (int i = 0; i < m_arrObj.size(); ++i)
	{
	
		if (m_currentState == SCENE_STATE::PAUSE)
		{
			if (TYPE_NUMBER(GROUP_TYPE::UI) == i)
			{
				for (int j = 0; j < m_arrObj[i].size(); ++j)
				{
					m_arrObj[i][j]->FinalUpdate();
				}
			}
			continue;
		}
		for (int j = 0; j < m_arrObj[i].size(); ++j)
		{
			m_arrObj[i][j]->FinalUpdate();
		}


	}
}

void CScene::Restart()
{
	Exit();
	Enter();
}

void CScene::SetDeadState(CMonster* _boss)
{
	ChangeAIState(_boss->GetAi(), MON_STATE::DEAD);
}

void CScene::SetDebug()
{
	if (CCore::GetInst()->IsDebug())
	{
		CCore::GetInst()->SetDebug(false);
		return;
	}
	else
	{
		CCore::GetInst()->SetDebug(true);
	}
	
}

void CScene::DeleteAll()
{
	for (UINT i = 0; i < TYPE_NUMBER(GROUP_TYPE::END); ++i)
	{
		if (m_strName == L"Tool Scene" && (TYPE_NUMBER(GROUP_TYPE::MONSTER_HITBOX) == i || TYPE_NUMBER(GROUP_TYPE::MONSTER_ATTACKBOX) == i || TYPE_NUMBER(GROUP_TYPE::PLAYER_HITBOX) == i))
			continue;
		DeleteGroup((GROUP_TYPE)i);
	}
}

void CScene::DeleteGroup(GROUP_TYPE _target)
{
	Safe_Delete_Vec(m_arrObj[TYPE_NUMBER(_target)]);
}


void CScene::LoadMap(const wstring& _relativePath)
{
	FILE* file = nullptr;

	wstring path = CPathManager::GetInst()->GetContentPath();
	path += _relativePath;
	_wfopen_s(&file, path.c_str(), L"rb");
	
	assert(file);
	char buffer[20] = { 0, };

	CGameObject* gameObj = nullptr;
	DeleteGroup(GROUP_TYPE::GAME_OBJ);
	DeleteGroup(GROUP_TYPE::BACK_GROUND);
	DeleteGroup(GROUP_TYPE::SPAWN_OBJ);
	DeleteGroup(GROUP_TYPE::GROUND);
	DeleteGroup(GROUP_TYPE::FORE_GROUND);
	DeleteGroup(GROUP_TYPE::MONSTER);
	DeleteGroup(GROUP_TYPE::PLAYER);
	DeleteGroup(GROUP_TYPE::PLATFORM_OBJ);
	while ('E' != buffer[0])
	{
		fgets(buffer,sizeof(buffer),file);
		
		if ('B' == buffer[0])
		{
			gameObj = new CBackGround;
			((CBackGround*)gameObj)->Load(file);
			AddObject(gameObj, GROUP_TYPE::BACK_GROUND);
		}
		
		else if ('S' == buffer[0])
		{
			
			gameObj = new CSpawnObject;
			((CSpawnObject*)gameObj)->Load(file);
			((CSpawnObject*)gameObj)->Start();
			if (CSceneManager::GetInst()->GetCurrentScene()->GetSceneName() == L"Tool Scene")
			{
				((CGround*)gameObj)->SetType(GAMEOBJECT_TYPE::SPAWN);
				AddObject(gameObj, GROUP_TYPE::GAME_OBJ);
			}
			else
			{
				AddObject(gameObj, GROUP_TYPE::SPAWN_OBJ);
			}
				
		}

		else if ('G' == buffer[0])
		{
			gameObj = new CGround;
			((CGround*)gameObj)->Load(file);
			((CGround*)gameObj)->Start();
			if (CSceneManager::GetInst()->GetCurrentScene()->GetSceneName() == L"Tool Scene")
			{
				
				AddObject(gameObj, GROUP_TYPE::GAME_OBJ);
			}
			else
				AddObject(gameObj, GROUP_TYPE::GROUND);
		}

		else if ('P' == buffer[0])
		{
			gameObj = new CGround;
			((CGround*)gameObj)->Load(file);
			((CGround*)gameObj)->Start();
			if (CSceneManager::GetInst()->GetCurrentScene()->GetSceneName() == L"Tool Scene")
				AddObject(gameObj, GROUP_TYPE::GAME_OBJ);
			else
				AddObject(gameObj, GROUP_TYPE::PLATFORM_OBJ);
		}
		

		else if ('F' == buffer[0])
		{
			gameObj = new CForeGround;
			((CForeGround*)gameObj)->Load(file);
			AddObject(gameObj, GROUP_TYPE::FORE_GROUND);
		}
	}
	fclose(file);
}

CObject* CScene::GetTarget(GROUP_TYPE _group, const wstring& _objName)
{
	for (CObject* _obj : m_arrObj[TYPE_NUMBER(_group)])
	{
		if (_obj->GetName() == _objName)
			return _obj;
	}
	return nullptr;
}

void CScene::ShowPauseUI()
{
	if (nullptr == m_pauseUI)
		return;
	Vec2 resolution = CCore::GetInst()->GetResolution();
	if (m_pauseUI->IsShow())
	{
		m_pauseUI->SetShow(false);
		m_pauseUI->SetScale(Vec2(0.f, 0.f));
		m_prevState = m_currentState;
		m_currentState = SCENE_STATE::PLAY;
	}
	else
	{
		m_currentState = SCENE_STATE::PAUSE;
		m_pauseUI->SetShow(true);
		m_pauseUI->SetScale(Vec2(resolution));
		m_prevState = m_currentState;
	}
}

void CScene::CreatePauseUI()
{
	Vec2 resolution = CCore::GetInst()->GetResolution();
	m_pauseUI = new CMenuPanel;
	m_pauseUI->UsePauseUI();
	m_pauseUI->SetPos(Vec2(resolution / 2.f));
	CMenuButtonUI* resumeButton = new CMenuButtonUI;
	resumeButton->SetScale(Vec2(320.f, 78.f));
	resumeButton->SetPos(Vec2(-170.f, -138.f));
	resumeButton->SetIndex(5);
	resumeButton->SetClickedCallBack(this, (SCENE_MEM_FUNC_VOID)&CScene::ShowPauseUI);
	CMenuButtonUI* restartButton = new CMenuButtonUI;
	restartButton->SetScale(Vec2(320.f, 78.f));
	restartButton->SetPos(Vec2(-170.f, -60.f));
	restartButton->SetIndex(0);
	restartButton->SetClickedCallBack(this, (SCENE_MEM_FUNC_VOID)&CScene::Restart);
	CMenuButtonUI* returnButton = new CMenuButtonUI;
	returnButton->SetScale(Vec2(320.f, 78.f));
	returnButton->SetPos(Vec2(-170.f, 20.f));
	returnButton->SetIndex(1);
	returnButton->SetClickedCallBack((SCENE_MEM_FUNC_SCENE_TYPE)&ChangeScene, (DWORD_PTR)SCENE_TYPE::START);
	m_pauseUI->AddChild(resumeButton);
	m_pauseUI->AddChild(restartButton);
	m_pauseUI->AddChild(returnButton);
	CreateObject(m_pauseUI, GROUP_TYPE::UI);
}


void CScene::render_tile(HDC _dc)
{
	const vector<CObject*>& tiles = GetObjWithType(GROUP_TYPE::TILE);

	Vec2 camLook = CCamera::GetInst()->GetLookAt();
	Vec2 resolution = CCore::GetInst()->GetResolution();

	Vec2 leftTop = camLook - resolution / 2.f;

	int tileSize = TILE_SIZE;

	int ltCol = (int)leftTop.x / tileSize;
	int ltRow = (int)leftTop.y / tileSize;

	int camWidthTileCount = ((int)resolution.x / tileSize)+1;
	int camHeightTileCount = ((int)resolution.y / tileSize)+1;

	for (int curRow = ltRow; curRow < (ltRow + camHeightTileCount); ++curRow)
	{
		for (int curCol = ltCol; curCol < (ltCol + camWidthTileCount); ++curCol)
		{
			if(curCol<0||m_TileXCount<=curCol||curRow<0||m_TileYCount<=curRow)
				continue;

			int idx = m_TileXCount * curRow + curCol;

			tiles[idx]->Render(_dc);

		}
	}
}

bool comp(CObject* a, CObject* b);

/// <summary>
/// 오프셋에 따라 렌더링 순서를 재정렬한다.
/// </summary>
void CScene::offset_change()
{
	
	//화면에 렌더링을 오프셋에 따라 순서를 결정하여 진행
	//정렬 알고리즘을 이용해 진행
	sort(m_arrObj[TYPE_NUMBER(GROUP_TYPE::BACK_GROUND)].begin(), m_arrObj[TYPE_NUMBER(GROUP_TYPE::BACK_GROUND)].end(), comp);

}

bool comp(CObject* a, CObject* b)
{
	return a->GetOffset()>b->GetOffset();
}
