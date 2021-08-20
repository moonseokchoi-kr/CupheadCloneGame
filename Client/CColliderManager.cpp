#include "pch.h"
#include "CColliderManager.h"
#include "CCollider.h"
#include "CSceneManager.h"
#include "CScene.h"
#include "CObject.h"

CColliderManager::CColliderManager()
{

}
CColliderManager::~CColliderManager()
{

}

void CColliderManager::Init()
{

}

void CColliderManager::Update()
{
	for (UINT row = 0; row < TYPE_NUMBER(GROUP_TYPE::END); ++row)
		for (UINT col = row; col < m_collCheckArray.size(); ++col)
		{
			if (m_collCheckArray[row] & (1 << col))
			{
				//체크된 비트를 확인해 그룹을 갱신한다
				collisionGroupUpdate((GROUP_TYPE)row, (GROUP_TYPE)col);
			}
		}
}
/// <summary>
/// 콜라이더 그룹간의 체크를 하는 함수
/// </summary>
/// <param name="_eLeft">체크 할 그룹</param>
/// <param name="_eRight">체크 할 그룹</param>
void CColliderManager::CheckGroup(GROUP_TYPE _left, GROUP_TYPE _right)
{
	//더 작은값을 그룸 타입을 행으로,
	//큰값을 열(비트)로 사용
	 
	UINT row = TYPE_NUMBER(_left);
	UINT col = TYPE_NUMBER(_right);

	if (row > col)
	{
		row = TYPE_NUMBER(_right);
		col = TYPE_NUMBER(_left);
	}
	

	if (m_collCheckArray[row] & (1 << col))
	{
		m_collCheckArray[row] &= ~(1 << col);
	}
	else
	{
		//비트시프트로 열만큼 밀어서 집어넣음
		m_collCheckArray[row] |= (1 << col);
	}

}
/// <summary>
/// 두 그룹의 충돌체의 충돌타입에 따라 업데이트를 진행하는 함수
/// </summary>
/// <param name="_eLeft">오브젝트 그룹타입</param>
/// <param name="_eRight">오브젝트 그룹타입</param>
void CColliderManager::collisionGroupUpdate(GROUP_TYPE _left, GROUP_TYPE _right)
{
	CScene* currentScene = CSceneManager::GetInst()->GetCurrentScene();

	const vector<CObject*>& vecLeft = currentScene->GetObjWithType(_left);
	const vector<CObject*>& vecRight = currentScene->GetObjWithType(_right);

	unordered_map<ULONGLONG, bool>::iterator iter;

	for (size_t i = 0; i < vecLeft.size(); ++i)
	{
		if (nullptr == vecLeft[i]->GetCollider())
		{
			continue;
		}

		for (size_t j = 0; j < vecRight.size(); ++j)
		{
			//충돌체가 없거나 자기 자신과의 충돌
			if (nullptr == vecRight[j]->GetCollider() || vecLeft[i] == vecRight[j])
			{
				continue;
			}

			CCollider* leftCol = vecLeft[i]->GetCollider();
			CCollider* rightCol = vecRight[j]->GetCollider();
			if (!leftCol->CanCollide() || !rightCol->CanCollide())
				return;

			COLLIDER_ID ID;
	
			ID.left_id = leftCol->GetID();
			ID.right_id = rightCol->GetID();

			iter = m_mapCollInfo.find(ID.id);

			//아직 충돌정보가 미등록일때
			if (m_mapCollInfo.end() == iter)
			{
				m_mapCollInfo.insert(make_pair(ID.id, false));
				iter = m_mapCollInfo.find(ID.id);
			}
			

			if (isCollision(leftCol, rightCol))
			{
				if (iter->second)
				{
					//이전에도 충돌하고 있을때(OnCollision)
					if (vecLeft[i]->IsDead() || vecRight[j]->IsDead())
					{
						//둘중 하나가 삭제 예정이라면 충돌을 해제
						leftCol->OnCollisionExit(rightCol);
						rightCol->OnCollisionExit(leftCol);
						iter->second = false;
					}
					else
					{
						leftCol->OnCollision(rightCol);
						rightCol->OnCollision(leftCol);
					}
				}

				else
				{
					//이제 막 충돌했을경우
					//근데 둘중 누가 삭제예정이라면 충돌시키지 않음
					if (!vecLeft[i]->IsDead() && !vecRight[j]->IsDead())
					{
						leftCol->OnCollisionEnter(rightCol);
						rightCol->OnCollisionEnter(leftCol);
						iter->second = true;
					}
				}

			}
			else
			{
				//현재 충돌하고 있지 않다.

				if (iter->second)
				{
					leftCol->OnCollisionExit(rightCol);
					rightCol->OnCollisionExit(leftCol);
					iter->second = false;
				}
			}
			
		}
	}
}
/// <summary>
/// 충돌체 끼리의 충돌을 체크하는 함수
/// </summary>
/// <param name="_pLeftCol">충돌체 </param>
/// <param name="_pRightCol">충돌체</param>
bool CColliderManager::isCollision(CCollider* _leftCol, CCollider* _rightCol)
{
	Vec2 leftPos = _leftCol->GetFinalPos();
	Vec2 leftSize = _leftCol->GetScale();

	Vec2 rightPos = _rightCol->GetFinalPos();
	Vec2 rightSize = _rightCol->GetScale();

	if (abs(rightPos.x - leftPos.x) <= (leftSize.x + rightSize.x) / 2.f && abs(rightPos.y - leftPos.y) <= (leftSize.y + rightSize.y) / 2.f)
	{
		return true;
	}
	return false;
}

