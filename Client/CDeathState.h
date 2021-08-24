#pragma once
#include "CState.h"
class CDeathState :
    public CState
{
public:
	CDeathState(const wstring& _anim);
	virtual ~CDeathState();
public:
	// CState��(��) ���� ��ӵ�
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void Update() override;

private:
	wstring m_animName;//���̵鿡�� ����� �ִϸ��̼� �̸�
};

