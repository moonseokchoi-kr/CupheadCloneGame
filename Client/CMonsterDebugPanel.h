#pragma once
#include "CPanelUI.h"

class CMonster;
class CTextUI;
class CTextButtonUI;
class CMonsterDebugPanel :
    public CPanelUI
{

public:
    CMonsterDebugPanel();
    ~CMonsterDebugPanel();
    CLONE(CMonsterDebugPanel);
public:
    virtual void Update();
    virtual void Render(HDC _dc);
    void SetOwner(CMonster* _owner) { m_owner = _owner; }
private:

    CTextUI* m_monsterName;
    CTextUI* m_monsterHP;
    CTextUI* m_currnetPatt;
    CMonster* m_owner;
};

