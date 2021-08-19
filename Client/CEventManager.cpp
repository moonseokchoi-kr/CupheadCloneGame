#include "pch.h"

#include "CEventManager.h"
#include "CSceneManager.h"

#include "CScene.h"
#include "CObject.h"

#include "FSMAI.h"
#include "CPlayerStateMachine.h"
CEventManager::CEventManager()
{

}

CEventManager::~CEventManager()
{

}

void CEventManager::Update()
{
	//������������ ������ ������Ʈ ����
	for (size_t i = 0; i < m_deadObjects.size(); ++i)
	{
		delete m_deadObjects[i];
	}
	m_deadObjects.clear();
	for (size_t i = 0; i < m_events.size(); ++i)
	{
		excute(m_events[i]);
	}
	m_events.clear();
}

void CEventManager::excute(const event& _event)
{
	switch (_event.event_type)
	{
		
	case EVENT_TYPE::CREATE_OBJECT:
	{
		//lParam : Object
		//wParam : GROUPTYPE
		CObject* object = (CObject*)_event.lParam;
		GROUP_TYPE group = (GROUP_TYPE)_event.wParam;

		CSceneManager::GetInst()->GetCurrentScene()->AddObject(object,group);
	}
		break;
	case EVENT_TYPE::DELETE_OBJECT:
	{
		//lParam : Object
		//wParam : None
		//Object�� Dead���·� ����
		//��������������Ʈ���� ��Ƶд�.
		CObject* object = (CObject*)_event.lParam;

		if (!object->IsDead())
			object->SetDead();

		m_deadObjects.push_back(object);

	}
		break;
	case EVENT_TYPE::SCENE_CHANGE:
	{
		SCENE_TYPE scene_type = (SCENE_TYPE)_event.lParam;

		CSceneManager::GetInst()->ChangeScene(scene_type);

	}
		break;
	case EVENT_TYPE::STATE_CHANGE:
	{
		//1Param: ai
		//wParam: next state

		FSMAI* ai = (FSMAI*)_event.lParam;
		MON_STATE nextState = (MON_STATE)_event.wParam;

		ai->ChangeState(nextState);
	}
	break;
	case EVENT_TYPE::PLAYER_STATE_CHANGE:
	{

		//1Param: ai
		//wParam: next state
		CPlayerStateMachine* ai = (CPlayerStateMachine*)_event.lParam;
		PLAYER_STATE nextState = (PLAYER_STATE)_event.wParam;
		ai->ChangeState(nextState);
	}
	break;
	default:
		break;
	}
}
