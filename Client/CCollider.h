#pragma once
class CObject;


/// <summary>
/// 충돌체 컴포넌트 클래스 물체간의 충돌을 정의한다.
/// </summary>
/// 
/// 작성자: 최문석
/// 작성일시: 2021-07-10
/// 
/// 버전
/// 1.0 - 기본 구조 작성
/// 1.1 - 충돌 이벤트 처리 작성
/// 1.2 - 렌더링 구조 변경


//2021-08-04
//TODO: 콜라이더가 있는 물체끼리 통과되지 않게 설정
class CCollider
{
	friend class CObject;
public:
	CCollider();
	CCollider(const CCollider& _origin);
	~CCollider();
public:
	void SetOffsetPos(Vec2 offset) { m_offset = offset; }
	void SetScale(Vec2 scale) { m_scale = scale; }
	bool CanCollide() { return m_avaliableCollide; }
	void SetAvaCollide(bool _b) { m_avaliableCollide = _b; }
	Vec2 GetFinalPos() { return m_finalPos; }
	Vec2 GetPrevFinalPos() { return m_prevFinalPos; }
	Vec2 GetOffsetPos() { return m_offset; }
	Vec2 GetScale() { return m_scale; }
	CObject* GetOwner() { return m_owner; }
	UINT GetID() { return m_id; }
public:
	void FinalUpdate();
	void Render(HDC _dc);

public:
	void OnCollision(CCollider* _col);
	void OnCollisionEnter(CCollider* _col);
	void OnCollisionExit(CCollider* _col);

	//대입을 막아버림
	CCollider& operator = (const CCollider* _col) = delete;
private:
	static UINT g_nextId;

	UINT m_id;
	//현재 충돌중인 콜라이더 수
	int m_col;

	bool m_avaliableCollide;
	CObject* m_owner;
	Vec2 m_offset;
	Vec2 m_finalPos;
	Vec2 m_scale;
	Vec2 m_prevFinalPos;
};

