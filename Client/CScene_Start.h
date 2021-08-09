#pragma once
#include "CScene.h"
class CTexture;

class CScene_Start :
    public CScene
{
public:
    CScene_Start();
    ~CScene_Start();
public:
    // CScene��(��) ���� ��ӵ�
    virtual void Enter() override;
    virtual void Exit() override;
    virtual void Update();
    virtual void Render(HDC _dc);
private:
    CTexture* m_background;
    static int nX;
};

