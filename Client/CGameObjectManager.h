#pragma once

class CGameObject;
/// <summary>
/// background ������Ʈ�� �ϰ� �����ϴ� Ŭ����
/// </summary>
class CGameObjectManager
{
	SINGLE(CGameObjectManager);

public:
	void Update();
public:
	CGameObject* GetFocusObj() { return m_focusObj; }
	void SetFocusedObj(CGameObject* _obj);
	void SetCurrnetGroup(GROUP_TYPE _group) { m_currentType = _group; }
	GROUP_TYPE GetCurrentGroup() { return m_currentType; }
private:
	CGameObject* getFocusedObj();
	
private:
	CGameObject* m_focusObj;
	CGameObject* m_prevTargetObj;
	GROUP_TYPE m_currentType;
};

