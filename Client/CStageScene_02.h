#pragma once
#include "CScene.h"
class CStageScene_02 :
    public CScene
{
public:
    CStageScene_02();
    ~CStageScene_02();
public:
    // CScene��(��) ���� ��ӵ�
    virtual void Enter() override;

    virtual void Exit() override;

};

