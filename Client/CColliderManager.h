#pragma once

/// <summary>
/// CColliderManager
/// 
/// �ݶ��̴����� �浹�� �����ϰ� ó���� ����ϴ� Ŭ���� 
/// ���ӳ��� �����ϳ��� ���簡���ϴ�
/// </summary>
/// 
/// �ۼ��� : �ֹ���
/// �ۼ��Ͻ� : 2021-07-10
/// ����
/// 1.0 - �浹 ������ ���� ��� �ۼ�

union COLLIDER_ID
{
	struct
	{
		UINT left_id;
		UINT right_id;
	};

	ULONGLONG id;
}; 


class CCollider;

class CColliderManager
{
	SINGLE(CColliderManager);

public:
	void Init();
	void Update();
	void CheckGroup(GROUP_TYPE _left, GROUP_TYPE _right);

	/// <summary>
	/// ���� üũ�� �׷��� ���� ��üũ�� ���·� ������ �Լ�
	/// </summary>
	void Reset() { m_collCheckArray.fill(0); }
private:
	void collisionGroupUpdate(GROUP_TYPE _left, GROUP_TYPE _right);
	bool isCollision(CCollider* _leftCol, CCollider* _rightCol);
private:
	//�浹ü ���� �浹������ ����
	unordered_map<ULONGLONG, bool> m_mapCollInfo;
	//�׷찣�� �浹�� üũ
	array<UINT, TYPE_NUMBER(GROUP_TYPE::END)> m_collCheckArray;
};

