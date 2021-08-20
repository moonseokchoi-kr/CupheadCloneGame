#pragma once
#include "CMonster.h"

/// <summary>
/// 당근 보스 클래스
/// 
/// 공격 패턴은 빔 공격과, 유도미사일 공격 2가지를 날리며,
/// 유도 미사일은 플레이어 위치를 한번만지정하여 쫓는다.
/// 
/// 스테이트
/// intro
/// idle
/// attack
/// Death
/// </summary>
class CChauncey :
    public CMonster
{
public:
    CChauncey();
    ~CChauncey();
    CLONE(CChauncey);
public:
    virtual void Update();
    virtual void Render(HDC _dc);
public:
    void CreateAttackBox();
};

