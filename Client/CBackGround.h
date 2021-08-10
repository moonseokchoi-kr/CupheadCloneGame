#pragma once
#include "CObject.h"

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
    CTexture* m_currentTex;        //��� �ؽ���
    BACKGROUND_TYPE m_type;

    Vec2  m_dragStart;      //�巡�׸� ������ ������
    Vec2 m_currentMousePos; //���� ���콺 ������


    array<const wchar_t*, TYPE_NUMBER(BACKGROUND_TYPE::END)> m_backGroundArray;

    bool m_lbuttonDown;
    bool m_lbuttonUp;
    bool m_mouseOn;


    friend class CBackGroundManager;

};

