#pragma once
#include "CObject.h"


class CGameObject :
	public CObject
{
public:
	CGameObject();
	~CGameObject();
	CLONE(CGameObject);
public:
	virtual void Start();
	virtual void Update();
	virtual void FinalUpdate();
	virtual void Render(HDC _dc);

public:
	void MouseOnCheck();
	void ChangeSize(Vec2 _size);

	void SetType(GAMEOBJECT_TYPE _type) { m_type = _type; }
	GAMEOBJECT_TYPE GetType() { return m_type; }
	bool IsMouseOn() { return m_mouseOn; }
	bool IsLButtonDown() { return m_lButtonDown; }
	bool IsSelect() { return m_select; }
	void SetMouseOn(bool _b) { m_mouseOn = _b; }
	void SetLButtonDown(bool _b) { m_lButtonDown = _b; }
	void SetSelect(bool _b) { m_select = _b; }

	CGameObject* GetParent() { return m_parentObejct; }
	const vector<CGameObject*>& GetChilds() { return m_childObejcts; }

	void AddChild(CGameObject* _child) { _child->m_parentObejct = this;  m_childObejcts.push_back(_child); }
public:
	virtual void MouseOn();
	virtual void MouseLButtonDown();
	virtual void MouseLButtonUp();

	virtual void Save(FILE* _file);
	virtual void Load(FILE* _file);
private:
    array<const wchar_t*, TYPE_NUMBER(GAMEOBJECT_TYPE::END)> m_gameObjectArray;


	bool m_mouseOn;                 //���콺�� �ö��ִ���
	bool m_lButtonDown;             //���콺���ʹ�ư�� Ŭ���ߴ���
	bool m_select;                  //������ �Ǿ�����

	Vec2  m_dragStart;      //�巡�׸� ������ ������
	Vec2 m_currentMousePos; //���� ���콺 ������


	Vec2 m_finalPos;

	GAMEOBJECT_TYPE m_type;

	CGameObject* m_parentObejct;
	vector<CGameObject*> m_childObejcts;
	friend class CGameObjectManager;
};

