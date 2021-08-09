#pragma once
#include "CObject.h"


class CTexture;

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
    void SetTexture(CTexture* _tex) { m_tex = _tex; }
    void SetImageIdx(int _idx) { m_imgIdx = _idx; }
    void AddImgIndex() { ++m_imgIdx; }
    void Save(FILE* _file);
    void Load(FILE* _file);
private:
    CTexture* m_tex;
    int m_imgIdx;
};

