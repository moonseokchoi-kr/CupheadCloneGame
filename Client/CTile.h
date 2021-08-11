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
/// ȭ���� ���� �׸��� ���� ����ϴ� TileŬ����
/// 
/// �ۼ���: �ֹ���
/// 
/// ����
/// 1.0 - �⺻ Ŭ���� ���� �ۼ� 2021-07-19
/// </summary>
class CTile :
    public CObject
{
public:
    CTile();
    ~CTile();
public:
    // CObject��(��) ���� ��ӵ�
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

