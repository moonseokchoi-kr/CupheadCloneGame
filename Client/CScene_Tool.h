#pragma once
#include "CScene.h"

/// <summary>
/// 맵 제작을 하는 툴 화면 클래스
/// 
/// 작성자: 최문석
/// 
/// 버전
/// 1.0 - 툴 화면 구성 2021-07-19
/// 1.1 - 파일 저장과 로드기능추가
/// </summary>
class CScene_Tool :
    public CScene
{
public:
    CScene_Tool();
    ~CScene_Tool();
public:
    virtual void Update();
    // CScene을(를) 통해 상속됨
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

