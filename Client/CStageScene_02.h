#pragma once
#include "CScene.h"
class CStageScene_02 :
    public CScene
{
public:
    CStageScene_02();
    ~CStageScene_02();
public:
    // CScene을(를) 통해 상속됨
    virtual void Enter() override;
    virtual void Update() override;
    virtual void Exit() override;
private:
	CObject* m_currentBoss;
	wstring m_prevBossName;
};

