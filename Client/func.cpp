#include "pch.h"
#include "func.h"

#include "CEventManager.h"
#include "CObject.h"
#include "FSMAI.h"


void CreateObject(CObject* _object, GROUP_TYPE _group, Vec2 _pos, Vec2 _scale)
{
	_object->SetPos(_pos);
	_object->SetScale(_scale);
	event evn = { };
	evn.event_type = EVENT_TYPE::CREATE_OBJECT;
	evn.lParam = (DWORD_PTR)_object;
	evn.wParam = (DWORD_PTR)_group;
	CEventManager::GetInst()->AddEvent(evn);
}

void CreateObject(CObject* _object, GROUP_TYPE _group)
{
	event evn = { };
	evn.event_type = EVENT_TYPE::CREATE_OBJECT;
	evn.lParam = (DWORD_PTR)_object;
	evn.wParam = (DWORD_PTR)_group;
	CEventManager::GetInst()->AddEvent(evn);
}

void DeleteObject(CObject* _object)
{
	event evn = {};
	evn.event_type = EVENT_TYPE::DELETE_OBJECT;
	evn.lParam = (DWORD_PTR)_object;

	CEventManager::GetInst()->AddEvent(evn);
}

void ChangeScene(SCENE_TYPE _type)
{
	event evn = {};
	evn.event_type = EVENT_TYPE::SCENE_CHANGE;
	evn.lParam = (DWORD_PTR)_type;

	CEventManager::GetInst()->AddEvent(evn);
}

void ChangeAIState(FSMAI* _ai, MON_STATE _nextState)
{
	event evn = {};
	evn.event_type = EVENT_TYPE::STATE_CHANGE;
	evn.lParam = (DWORD_PTR)_ai;
	evn.wParam = (DWORD_PTR)_nextState;

	CEventManager::GetInst()->AddEvent(evn);
}

void ChangePlayerState(CPlayerStateMachine* _ai, PLAYER_STATE _nextState)
{
	event evn = {};
	evn.event_type = EVENT_TYPE::PLAYER_STATE_CHANGE;
	evn.lParam = (DWORD_PTR)_ai;
	evn.wParam = (DWORD_PTR)_nextState;

	CEventManager::GetInst()->AddEvent(evn);
}
