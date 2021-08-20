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
				//üũ�� ��Ʈ�� Ȯ���� �׷��� �����Ѵ�
				collisionGroupUpdate((GROUP_TYPE)row, (GROUP_TYPE)col);
			}
		}
}
/// <summary>
/// �ݶ��̴� �׷찣�� üũ�� �ϴ� �Լ�
/// </summary>
/// <param name="_eLeft">üũ �� �׷�</param>
/// <param name="_eRight">üũ �� �׷�</param>
void CColliderManager::CheckGroup(GROUP_TYPE _left, GROUP_TYPE _right)
{
	//�� �������� �׷� Ÿ���� ������,
	//ū���� ��(��Ʈ)�� ���
	 
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
		//��Ʈ����Ʈ�� ����ŭ �о �������
		m_collCheckArray[row] |= (1 << col);
	}

}
/// <summary>
/// �� �׷��� �浹ü�� �浹Ÿ�Կ� ���� ������Ʈ�� �����ϴ� �Լ�
/// </summary>
/// <param name="_eLeft">������Ʈ �׷�Ÿ��</param>
/// <param name="_eRight">������Ʈ �׷�Ÿ��</param>
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
			//�浹ü�� ���ų� �ڱ� �ڽŰ��� �浹
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

			//���� �浹������ �̵���϶�
			if (m_mapCollInfo.end() == iter)
			{
				m_mapCollInfo.insert(make_pair(ID.id, false));
				iter = m_mapCollInfo.find(ID.id);
			}
			

			if (isCollision(leftCol, rightCol))
			{
				if (iter->second)
				{
					//�������� �浹�ϰ� ������(OnCollision)
					if (vecLeft[i]->IsDead() || vecRight[j]->IsDead())
					{
						//���� �ϳ��� ���� �����̶�� �浹�� ����
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
					//���� �� �浹�������
					//�ٵ� ���� ���� ���������̶�� �浹��Ű�� ����
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
				//���� �浹�ϰ� ���� �ʴ�.

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
/// �浹ü ������ �浹�� üũ�ϴ� �Լ�
/// </summary>
/// <param name="_pLeftCol">�浹ü </param>
/// <param name="_pRightCol">�浹ü</param>
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

