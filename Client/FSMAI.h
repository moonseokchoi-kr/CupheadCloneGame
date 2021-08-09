#pragma once


/// <summary>
/// ���ѻ��¸ӽ��� ����� ���� AIŬ����
/// 
/// 1.0- ���� ���¸ӽ� �⺻ ���� �ۼ� 2021-08-01
/// </summary>
/// 

class CState;
class CMonster;


class FSMAI
{
public:	
	FSMAI();
	~FSMAI();
public:
	void Update();
public:
	void AddState(CState* _state);
	CState* GetState(MON_STATE _state);
	CMonster* GetOwner() { return m_owner; }
	void SetCurrentState(MON_STATE _state);
	void ChangeState(MON_STATE _nextState);
private:
	unordered_map<MON_STATE, CState*> m_StateMap;
	CMonster* m_owner;
	CState* m_currentState;
	CState* m_prevState;

	friend class CMonster;
};

