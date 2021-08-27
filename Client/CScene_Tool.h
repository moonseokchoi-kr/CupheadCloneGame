#pragma once
#include "CScene.h"


struct SpawnObj
{
    TCHAR objName[255];
    GROUP_TYPE group;
    MON_TYPE mon_type;
};


/// <summary>
/// �� ������ �ϴ� �� ȭ�� Ŭ����
/// 
/// �ۼ���: �ֹ���
/// 
/// ����
/// 1.0 - �� ȭ�� ���� 2021-07-19
/// 1.1 - ���� ����� �ε����߰�
/// </summary>
/// 
/// 
/// �� ��� 
/// 
/// ��� ��ġ
/// ������Ʈ ��ġ
/// 
/// 
class CTextUI;

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
    void SaveMap(const wstring& _path);
    void SaveMapData();
    void LoadMapData();
    void GetTileUIidx(int _idx);
    void CreateGameObject();
    void DeleteGameObject();
private:

    int m_cilckedImageIdx;

    CTextUI* m_focusPos;
    CTextUI* m_focusScale;
    CTextUI* m_focusObjText;

};

