#pragma once
#include "CObject.h"


class CTexture;

enum class TILE_TYPE
{
    NONE,
    GROUND,
    PLATFORM,
    STOP,
};
/// <summary>
/// 화면의 맵을 그리기 위해 사용하는 Tile클래스
/// 
/// 작성자: 최문석
/// 
/// 버전
/// 1.0 - 기본 클래스 구조 작성 2021-07-19
/// </summary>
class CTile :
    public CObject
{
public:
    CTile();
    ~CTile();
public:
    // CObject을(를) 통해 상속됨
    virtual void Update() override;
    virtual void Render(HDC _dc);
    virtual void FinalUpdate();
    CLONE(CTile);
public:
    void SetType(TILE_TYPE _type) { m_tileType = _type; }
    TILE_TYPE GetType() { return m_tileType; }
    void Save(FILE* _file);
    void Load(FILE* _file);
private:
    TILE_TYPE m_tileType;;
};

