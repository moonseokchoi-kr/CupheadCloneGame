#pragma once
#include "CState.h"
class CIdleState :
    public CState
{
public:
    CIdleState(wstring _anim);
    ~CIdleState();
public:
    // CState을(를) 통해 상속됨
    virtual void Enter() override;
    virtual void Exit() override;
    virtual void Update() override;

private:
    float m_accTime; //일정 시간마다 초기화
    wstring m_animName;//아이들에서 재생할 애니메이션 이름
};

