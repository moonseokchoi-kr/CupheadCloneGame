#pragma once
#include "CPanelUI.h"

class CMonster;
class CMonsterDebugPanel :
    public CPanelUI
{

public:
    CMonsterDebugPanel();
    ~CMonsterDebugPanel();
    CLONE(CMonsterDebugPanel);
public:
    virtual void Render(HDC _dc);
    void SetOwner(CMonster* _owner) { m_owner = _owner; }
private:
    CMonster* m_owner;
};

