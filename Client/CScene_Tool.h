#pragma once
#include "CScene.h"

/// <summary>
/// �� ������ �ϴ� �� ȭ�� Ŭ����
/// 
/// �ۼ���: �ֹ���
/// 
/// ����
/// 1.0 - �� ȭ�� ���� 2021-07-19
/// 1.1 - ���� ����� �ε����߰�
/// </summary>
class CScene_Tool :
    public CScene
{
public:
    CScene_Tool();
    ~CScene_Tool();
public:
    virtual void Update();
    // CScene��(��) ���� ��ӵ�
    virtual void Enter() override;
    virtual void Exit() override;

public:
    void SetTileIdx();
    void SaveTile(const wstring& _path);
    void SaveTileData();
    void LoadTileData();
    void GoNextTable();
    void GoBackTable();
    void GetTileUIidx(int _idx);
private:

    int m_cilckedImageIdx;

};

