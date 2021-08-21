#pragma once
#include "CCamera.h"
/// <summary>
/// 앞으로 만들어질 모든 오브젝트의 부모클래스로 상속을 받아서 이용한다.
/// </summary>
/// 
/// 작성자: 최문석
///
/// 버전: 
/// 1.0- 기본적인 구조 작성				2021-06-30
/// 1.1- 충돌체 이벤트 추가				2021-07-10
/// 1.2- 애니메이터 추가				2021-07-11
/// 1.3- Clone함수 추가 복사생성자 추가 2021-07-17
/// 1.4- rigidbody 추가					2021-08-03
/// 1.5- 중력 추가						2021-08-16
class CCollider;
class CAnimator;
class CEventManager;
class CRigidBody;
class CGravity;

class CObject
{
public:
	CObject();
	CObject(const CObject& _origin);
	virtual ~CObject();
public:
	Vec2 GetPos() { return m_objPos; }
	Vec2 GetPrevPos() { return m_objPrevPos; }
	void SetPrevPos(Vec2 _v) { m_objPrevPos = _v; }
	Vec2 GetMoveDir()
	{
		return m_moveDir;
	}
	void SetMoveDir(float x, float y)
	{
		m_moveDir = Vec2(x, y);
	}
	Vec2 GetScale() { return m_objScale; }
	void SetPos(const Vec2& v) { m_objPos = v; }
	void SetScale(const Vec2& v) { m_objScale = v; }
	


	const wstring& GetName() { return m_objName; }
	void SetName(const wstring& _str) { m_objName = _str; }

	bool IsDead() { return m_dead; }
	
	void SetOffset(int offset) { m_renderingOffSet = offset; }
	int GetOffset() { return m_renderingOffSet; }

	CAnimator* GetAnimator() { return m_animator; }
	CCollider* GetCollider() { return m_collider; }
	CRigidBody* GetRigidBody() { return m_rigidBody; }
	CGravity* GetGravity() { return m_gravity; }

public:
	void CreateCollider();
	void CreateAnimator();
	void CreateRigidBody();
	void CreateGravity();
public:
	virtual void Start() {};
	virtual void Update() = 0;
	virtual void Render(HDC _dc);
	virtual void FinalUpdate();

	virtual CObject* Clone() = 0;
	/// <summary>
	/// 컴포넌트를 렌더링하는 함수
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

protected:
	void calMoveDir()
	{
		if (m_objPos == m_objPrevPos)
			return;
		m_moveDir = m_objPos - m_objPrevPos;
		m_moveDir.Normalize();
	}
private:
	void SetDead() { m_dead = true; }

private:
	Vec2 m_objPos;			//물체의 위치
	Vec2 m_objPrevPos;		//물체의 이전 위치
	Vec2 m_objScale;		//물체의 크기

	Vec2 m_moveDir;			//이동방향

	CCollider* m_collider;	//충돌체
	CAnimator* m_animator;	//애니메이터
	CRigidBody* m_rigidBody; //강체
	CGravity* m_gravity;

	wstring m_objName;		//물체의 이름
	bool m_dead;			//죽었는지 여부

	int m_renderingOffSet;

	friend class CEventManager;
	
};

