#pragma once
#include "CState.h"
class CDeathState :
    public CState
{
public:
	CDeathState(const wstring& _anim);
	CDeathState(const wstring& _anim, const wstring& _anim1);
	virtual ~CDeathState();
public:
	// CState��(��) ���� ��ӵ�
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void Update() override;

private:
	wstring m_animName;//����� �ִϸ��̼� �̸�
	wstring m_animName1;
};

