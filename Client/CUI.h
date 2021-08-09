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

	// CObject을(를) 통해 상속됨
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
    vector<CUI*> m_childUIs;        //자식 UI
    CUI* m_parentUI;                //부모 UI nullptr이면 최상위
    Vec2 m_finalPos;                //최종위치

    bool m_cameraAffected;          //카메라 영향을 받는지
    bool m_mouseOn;                 //마우스가 올라가있는지
    bool m_lButtonDown;             //마우스왼쪽버튼을 클릭했는지
    bool m_select;                  //선택이 되었는지

    friend class CUIManager;
};

