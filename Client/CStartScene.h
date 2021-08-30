#pragma once
#include "CScene.h"
class CStartScene :
    public CScene
{
public:
    CStartScene();
    ~CStartScene();
public:
    // CScene을(를) 통해 상속됨
    virtual void Enter() override;

    virtual void Update() override;

    virtual void Exit() override;

public:

private:


};

