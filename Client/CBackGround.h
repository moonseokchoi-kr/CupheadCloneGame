#pragma once
#include "CGameObject.h"

/// <summary>
/// 게임 내 배경을 담당하는 오브젝트 클래스
/// 
/// 작성자 최문석
/// 
/// 버전
/// 
/// 1.0 - 배경 클래스의 기본적인 구조 작성 2021-08-09
/// 1.1 - 알파 블렌딩 추가 2021-08-10
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
    CTexture* m_currentTex;        //배경 텍스쳐
    BACKGROUND_TYPE m_type;

    


    array<const wchar_t*, TYPE_NUMBER(BACKGROUND_TYPE::END)> m_backGroundArray;
};

