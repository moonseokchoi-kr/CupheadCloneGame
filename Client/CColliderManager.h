#pragma once

/// <summary>
/// CColliderManager
/// 
/// 콜라이더간의 충돌을 감지하고 처리를 담당하는 클래스 
/// 게임내에 오직하나만 존재가능하다
/// </summary>
/// 
/// 작성자 : 최문석
/// 작성일시 : 2021-07-10
/// 버전
/// 1.0 - 충돌 구조및 관리 기능 작성

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
	/// 현재 체크된 그룹을 전부 언체크한 상태로 돌리는 함수
	/// </summary>
	void Reset() { m_collCheckArray.fill(0); }
private:
	void collisionGroupUpdate(GROUP_TYPE _left, GROUP_TYPE _right);
	bool isCollision(CCollider* _leftCol, CCollider* _rightCol);
private:
	//충돌체 간의 충돌정보를 저장
	unordered_map<ULONGLONG, bool> m_mapCollInfo;
	//그룹간의 충돌을 체크
	array<UINT, TYPE_NUMBER(GROUP_TYPE::END)> m_collCheckArray;
};

