#pragma once
#include "CGameObject.h"

/// <summary>
/// ���� �� ����� ����ϴ� ������Ʈ Ŭ����
/// 
/// �ۼ��� �ֹ���
/// 
/// ����
/// 
/// 1.0 - ��� Ŭ������ �⺻���� ���� �ۼ� 2021-08-09
/// 1.1 - ���� ���� �߰� 2021-08-10
/// </summary>


class CTexture;

class CBackGround :
    public CGameObject
{
public:
    CBackGround();
    ~CBackGround();
    CLONE(CBackGround);
public:
    virtual void Update() override;
    virtual void Render(HDC _dc) override;

    virtual void Save(FILE* _file);
    virtual void Load(FILE* _file);
public:
    void SetType(BACKGROUND_TYPE _type) { m_type = _type; setTexture(); }
private:
    void setTexture();
private:
    CTexture* m_currentTex;        //��� �ؽ���
    BACKGROUND_TYPE m_type;

    


    array<const wchar_t*, TYPE_NUMBER(BACKGROUND_TYPE::END)> m_backGroundArray;
};

