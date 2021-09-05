#pragma once
#include "CScene.h"

class CObject;
class CMonsterDebugPanel;
class CStageScene_01 :
    public CScene
{
public:
    CStageScene_01();
    ~CStageScene_01();
public:
    // CScene을(를) 통해 상속됨
    virtual void Enter() override;

    virtual void Update() override;

    virtual void Exit() override;

private:
    CObject* m_currentBoss;
    CMonsterDebugPanel* m_debugPanel;
    wstring m_prevBossName;
};

