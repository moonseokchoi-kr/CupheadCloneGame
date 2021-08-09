#pragma once
/// <summary>
/// 게임내 이벤트를 한번에 지연처리하는 매니저클래스
/// </summary>
/// 
/// 작성자: 최문석
/// 
/// 작성일시: 2021-07-10
/// 
/// 버전
/// 
/// 1.0 - 기본적인 이벤트 처리구조 작성

/// <summary>
/// 이벤트를 저장할 구조체
/// </summary>
/// 
struct event
{
	EVENT_TYPE event_type;
	DWORD_PTR lParam;
	DWORD_PTR wParam;
};

class CObject;

class CEventManager
{
	SINGLE(CEventManager);
public:
	void Update();
	
public:
	void AddEvent(const event& _event) { m_events.push_back(_event); }

private:
	void excute(const event& _event);
private:
	vector<event> m_events;
	vector<CObject*> m_deadObjects;
};

