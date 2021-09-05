#pragma once
#include "CScene.h"

class CMonsterDebugPanel;
class CStageScene_02 :
    public CScene
{
public:
    CStageScene_02();
    ~CStageScene_02();
public:
    // CScene��(��) ���� ��ӵ�
    virtual void Enter() override;
    virtual void Update() override;
    virtual void Exit() override;

private:
	CObject* m_currentBoss;
    CMonsterDebugPanel* m_debugPanel;
	wstring m_prevBossName;
};

