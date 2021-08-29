#pragma once
#include "CMonster.h"

enum class PHASE
{
    PHASE1,
    PHASE2,
};

class CSlime :
    public CMonster
{
public:
    CSlime();
    ~CSlime();
    CLONE(CSlime);
public:
    virtual void Start();
    virtual void Update();
    virtual void Render(HDC _dc);
    
public:
    PHASE GetCurrentPhase() { return m_currentPhase; }
    void SetCurrentPhase(PHASE _p) { m_currentPhase = _p; }
    Vec2 GetPrevMoveDir() { return m_prevMoveDir; }

protected:
    virtual void CreateAttackBox();

private:
    PHASE m_currentPhase;
    Vec2 m_prevMoveDir;
};

