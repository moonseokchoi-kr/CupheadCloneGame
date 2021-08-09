#include "pch.h"
#include "CScene.h"
#include "CTexture.h"
#include "CTile.h"


#include "CPathManager.h"
#include "CResourceManager.h"
#include "CCore.h"
#include "CCamera.h"


CScene::CScene()
	:m_TileXCount(0)
	,m_TileYCount(0)
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
/// <summary>
/// 씬안에 있는 오브젝트들의 update를 진행하는 함수
/// </summary>
void CScene::Update()
{
	for (int i = 0; i < m_arrObj.size(); ++i)
	{
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
		if (TYPE_NUMBER(GROUP_TYPE::TILE) == i)
		{
			render_tile(_dc);
			continue;
		}
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
		for (int j = 0; j < m_arrObj[i].size(); ++j)
		{
			m_arrObj[i][j]->FinalUpdate();
		}
	}
}

void CScene::DeleteAll()
{
	for (UINT i = 0; i < TYPE_NUMBER(GROUP_TYPE::END); ++i)
	{
		DeleteGroup((GROUP_TYPE)i);
	}
}

void CScene::DeleteGroup(GROUP_TYPE _target)
{
	Safe_Delete_Vec(m_arrObj[TYPE_NUMBER(_target)]);
}

void CScene::CreateTile(UINT _xCount, UINT _yCount)
{
	CTexture* tile = CResourceManager::GetInst()->LoadTexture(L"Tile", L"texture\\tile\\TILE.bmp");
	m_TileXCount = _xCount;
	m_TileYCount = _yCount;

	for (int i = 0; i < _yCount; ++i)
	{
		for (int j = 0; j < _xCount; ++j)\
		{
			CTile* pTile = new CTile;
			pTile->SetPos(Vec2((float)(j * TILE_SIZE), (float)(i * TILE_SIZE)));
			pTile->SetTexture(tile);
			AddObject(pTile, GROUP_TYPE::TILE);
		}
	}
}

void CScene::LoadTile(const wstring& _relativePath)
{
	FILE* file = nullptr;

	wstring path = CPathManager::GetInst()->GetContentPath();
	path += _relativePath;
	_wfopen_s(&file, path.c_str(), L"rb");
	
	assert(file);

	UINT xCount = GetTileX();
	UINT yCount = GetTileY();

	fread(&xCount, sizeof(UINT), 1, file);
	fread(&yCount, sizeof(UINT), 1, file);

	const vector<CObject*> tiles = GetObjWithType(GROUP_TYPE::TILE);
	for (CObject* tile : tiles)
	{
		((CTile*)tile)->Load(file);
	}

	fclose(file);
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
