#pragma once
class CObject;


/// <summary>
/// �浹ü ������Ʈ Ŭ���� ��ü���� �浹�� �����Ѵ�.
/// </summary>
/// 
/// �ۼ���: �ֹ���
/// �ۼ��Ͻ�: 2021-07-10
/// 
/// ����
/// 1.0 - �⺻ ���� �ۼ�
/// 1.1 - �浹 �̺�Ʈ ó�� �ۼ�
/// 1.2 - ������ ���� ����


//2021-08-04
//TODO: �ݶ��̴��� �ִ� ��ü���� ������� �ʰ� ����
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

	//������ ���ƹ���
	CCollider& operator = (const CCollider* _col) = delete;
private:
	static UINT g_nextId;

	UINT m_id;
	//���� �浹���� �ݶ��̴� ��
	int m_col;

	bool m_avaliableCollide;
	CObject* m_owner;
	Vec2 m_offset;
	Vec2 m_finalPos;
	Vec2 m_scale;
	Vec2 m_prevFinalPos;
};

