#pragma once
#include "CObject.h"

/// <summary>
/// ���� �� ����� ����ϴ� ������Ʈ Ŭ����
/// 
/// �ۼ��� �ֹ���
/// 
/// ����
/// 
/// 1.0 - ��� Ŭ������ �⺻���� ���� �ۼ�
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
public:
    void MouseOn();
    void MouseLButtonDown();
    void MouseLButtonUp();
    void MouseOnCheck();
private:
    CTexture* m_tex;        //��� �ؽ���

    Vec2  m_dragStart;      //�巡�׸� ������ ������
    Vec2 m_currentMousePos; //���� ���콺 ������

    bool m_lbuttonDown;
    bool m_lbuttonUp;
    bool m_mouseOn;

    int m_imgIdx;

    friend class CBackGroundManager;

};

