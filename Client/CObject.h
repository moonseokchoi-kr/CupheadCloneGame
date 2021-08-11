#pragma once
#include "UpdateInterface.h"
/// <summary>
/// ������ ������� ��� ������Ʈ�� �θ�Ŭ������ ����� �޾Ƽ� �̿��Ѵ�.
/// </summary>
/// 
/// �ۼ���: �ֹ���
///
/// ����: 
/// 1.0- �⺻���� ���� �ۼ�				2021-06-30
/// 1.1- �浹ü �̺�Ʈ �߰�				2021-07-10
/// 1.2- �ִϸ����� �߰�				2021-07-11
/// 1.3- Clone�Լ� �߰� ��������� �߰� 2021-07-17
/// 1.4- rigidbody �߰�					2021-08-03
class CCollider;
class CAnimator;
class CEventManager;
class CRigidBody;

class CObject
{
public:
	CObject();
	CObject(const CObject& _origin);
	virtual ~CObject();
public:
	Vec2 GetPos() { return m_objPos; }
	Vec2 GetScale() { return m_objScale; }
	void SetPos(const Vec2& v) { m_objPos = v; }
	void SetScale(const Vec2& v) { m_objScale = v; }
	


	const wstring& GetName() { return m_objName; }
	void SetName(const wstring& _str) { m_objName = _str; }

	bool IsDead() { return m_dead; }
	

	CAnimator* GetAnimator() { return m_animator; }
	CCollider* GetCollider() { return m_collider; }
	CRigidBody* GetRigidBody() { return m_rigidBody; }

public:
	void CreateCollider();
	void CreateAnimator();
	void CreateRigidBody();
public:
	virtual void Start() {};
	virtual void Update() = 0;
	virtual void Render(HDC _dc);
	virtual void FinalUpdate();

	virtual CObject* Clone() = 0;
	/// <summary>
	/// ������Ʈ�� �������ϴ� �Լ�
	/// </summary>
	/// <param name="_dc"></param>
	void ComponentRender(HDC _dc);

	virtual void OnCollision(CCollider* _col) {}
	virtual void OnCollisionEnter(CCollider* _col) {}
	virtual void OnCollisionExit(CCollider* _col) {}

	virtual void MouseOn() {}
	virtual void MouseLButtonDown(){}
	virtual void MouseLButtonUp(){}
	virtual void MouseLButtonClicked(){}

private:
	void SetDead() { m_dead = true; }
private:
	Vec2 m_objPos;			//��ü�� ��ġ
	Vec2 m_objScale;		//��ü�� ũ��

	CCollider* m_collider;	//�浹ü
	CAnimator* m_animator;	//�ִϸ�����
	CRigidBody* m_rigidBody; //��ü

	wstring m_objName;		//��ü�� �̸�
	bool m_dead;			//�׾����� ����



	friend class CEventManager;
	
};

