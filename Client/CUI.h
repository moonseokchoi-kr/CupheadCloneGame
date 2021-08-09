#pragma once
#include "CObject.h"
class CUI :
    public CObject
{
public:   
    CUI(bool _cameraAffeted);
    CUI(const CUI& _origin);
    ~CUI();
public:   

	// CObject��(��) ���� ��ӵ�
	virtual void Update() override;
    virtual void Render(HDC _dc);
    virtual void FinalUpdate();

    virtual void MouseOn();
    virtual void MouseLButtonDown();
    virtual void MouseLButtonUp();
    virtual void MouseLButtonClicked();

public:
    const vector<CUI*>& GetChilds() { return m_childUIs; }
    CUI* GetParent() { return m_parentUI; }
    Vec2 GetFinalPos() { return m_finalPos; }
    bool IsCameraAffed() { return m_cameraAffected; }
    bool IsMouseOn() { return m_mouseOn; }
    bool IsLButtonDown() { return m_lButtonDown; }
    bool IsSelect() { return m_select; }
    void MouseOnCheck();
    void AddChild(CUI* _childUI) { m_childUIs.push_back(_childUI); _childUI->m_parentUI = this; }

    virtual CUI* Clone() = 0;
private:
    void renderChild(HDC _dc);
    void updateChild();
    void finalUpdateChild();
private:
    vector<CUI*> m_childUIs;        //�ڽ� UI
    CUI* m_parentUI;                //�θ� UI nullptr�̸� �ֻ���
    Vec2 m_finalPos;                //������ġ

    bool m_cameraAffected;          //ī�޶� ������ �޴���
    bool m_mouseOn;                 //���콺�� �ö��ִ���
    bool m_lButtonDown;             //���콺���ʹ�ư�� Ŭ���ߴ���
    bool m_select;                  //������ �Ǿ�����

    friend class CUIManager;
};

