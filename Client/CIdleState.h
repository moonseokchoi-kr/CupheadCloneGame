#pragma once
#include "CState.h"
class CIdleState :
    public CState
{
public:
    CIdleState(wstring _anim);
    ~CIdleState();
public:
    // CState��(��) ���� ��ӵ�
    virtual void Enter() override;
    virtual void Exit() override;
    virtual void Update() override;

private:
    float m_accTime; //���� �ð����� �ʱ�ȭ
    wstring m_animName;//���̵鿡�� ����� �ִϸ��̼� �̸�
};

