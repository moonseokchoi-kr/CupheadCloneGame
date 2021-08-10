#pragma once
#include "CObject.h"

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
class CBackGroundManager;



class CBackGround :
    public CObject
{
public:
    CBackGround();
    ~CBackGround();
    CLONE(CBackGround);
public:
    virtual void Update() override;
    virtual void FinalUpdate() override;
    virtual void Render(HDC _dc) override;
public:
    bool IsMouseOn() { return m_mouseOn; }
    bool IsLButtonDown() { return m_lbuttonDown; }
    bool IsLButtonUp() { return m_lbuttonUp; }

    void SetType(BACKGROUND_TYPE _type) { m_type = _type; setTexture(); }
public:
    void MouseOn();
    void MouseLButtonDown();
    void MouseLButtonUp();
    void MouseOnCheck();
private:
    void setTexture();
private:
    CTexture* m_currentTex;        //배경 텍스쳐
    BACKGROUND_TYPE m_type;

    Vec2  m_dragStart;      //드래그를 시작한 포지션
    Vec2 m_currentMousePos; //현재 마우스 포지션


    array<const wchar_t*, TYPE_NUMBER(BACKGROUND_TYPE::END)> m_backGroundArray;

    bool m_lbuttonDown;
    bool m_lbuttonUp;
    bool m_mouseOn;


    friend class CBackGroundManager;

};

