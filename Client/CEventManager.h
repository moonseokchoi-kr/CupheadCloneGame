#pragma once
/// <summary>
/// ���ӳ� �̺�Ʈ�� �ѹ��� ����ó���ϴ� �Ŵ���Ŭ����
/// </summary>
/// 
/// �ۼ���: �ֹ���
/// 
/// �ۼ��Ͻ�: 2021-07-10
/// 
/// ����
/// 
/// 1.0 - �⺻���� �̺�Ʈ ó������ �ۼ�

/// <summary>
/// �̺�Ʈ�� ������ ����ü
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

