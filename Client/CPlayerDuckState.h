#pragma once
#include "CPlayerState.h"
class CPlayerDuckState :
    public CPlayerState
{
public:
	CPlayerDuckState();
	~CPlayerDuckState();
public:
	// CPlayerState��(��) ���� ��ӵ�
	virtual void Enter() override;

	virtual void Exit() override;

	virtual void Update() override;

protected:
	virtual void updateSubState();
	virtual void updateAnimation();
private:
	PLAYER_STATE m_subState;
};

