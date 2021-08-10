#pragma once
#include "CObject.h"
#include "CMonsterFactory.h"

/// <summary>
/// 앞으로 만들어질 모든 장면의 부모클래스로 상속을 받아서 이용한다.
/// </summary>
/// 
/// 작성자: 최문석
///  
/// 버전: 
/// 1.0 - 기본 클래스구조 구현 2021-06-30
/// 1.1 - CreateTile함수 추가 2021-07-19
/// 1.2 - ChangeFocusUI함수 추가 2021-07-22

class CUI;
class CPlayer;

class CScene
{
public:	
	CScene();
	virtual ~CScene();
public:

	virtual void Update();
	virtual void Render(HDC _dc);
	virtual void FinalUpdate() final;
	virtual void Enter() = 0;
	virtual void Exit() = 0;
public:
	
	void AddObject(CObject* _obj, GROUP_TYPE _state)
	{
		m_arrObj[(UINT)_state].push_back(_obj);
	}
	void ChangeFocus(vector<CObject*>::const_iterator iter, CObject* _focusUI, GROUP_TYPE _group)
	{
		m_arrObj[TYPE_NUMBER(_group)].erase(iter);
		m_arrObj[TYPE_NUMBER(_group)].push_back(_focusUI);
	}
	CPlayer* GetPlayer()
	{
		return (CPlayer*)m_arrObj[TYPE_NUMBER(GROUP_TYPE::PLAYER)][0];
	}
	const vector<CObject*>& GetObjWithType(GROUP_TYPE _state)
	{
		return m_arrObj[(UINT)_state];
	}
	wstring GetSceneName()
	{
		return m_strName;
	}
	void SetSceneName(wstring _strName)
	{
		m_strName = _strName;
	}
	UINT GetTileX() { return m_TileXCount; }
	UINT GetTileY() { return m_TileYCount; }

public:
	void DeleteAll();
	void DeleteGroup(GROUP_TYPE _target);
	void CreateTile(UINT _xCount, UINT _yCount);
	void LoadTile(const wstring& _relativePath);
private:
	void render_tile(HDC _dc);
private:
	array<vector<CObject*>, (UINT)GROUP_TYPE::END> m_arrObj;
	wstring m_strName;

	UINT m_TileXCount;
	UINT m_TileYCount;
};

