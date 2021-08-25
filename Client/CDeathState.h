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
	// CState을(를) 통해 상속됨
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void Update() override;

private:
	wstring m_animName;//재생할 애니메이션 이름
	wstring m_animName1;
};

