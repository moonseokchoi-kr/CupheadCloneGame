#pragma once
#include "CScene.h"
class CStartScene :
    public CScene
{
public:
    CStartScene();
    ~CStartScene();
public:
    // CScene��(��) ���� ��ӵ�
    virtual void Enter() override;

    virtual void Update() override;

    virtual void Exit() override;

public:

private:


};

