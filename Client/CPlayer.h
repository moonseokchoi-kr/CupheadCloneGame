#pragma once
#include "CObject.h"
#include "CTexture.h"


/// <summary>
/// 게임 플레이어 캐릭터 클래스
/// </summary>
/// 
/// 작성자 최문석
/// 
/// 버전 :
/// 1.0 - 기본 구조 작성
/// 1.1 - 콜라이더 추가
/// 1.2 - 애니메이션 추가
/// 1.3 - 상태 추가
/// 
///
// 2021-08-04
// TODO : 플레이어 상태 머신 작성


struct playerInfo
{
	float moveSpeed;
	Vec2 prevMoveDir;
    float attackSpeed;
    float jupAccTime = 0.15f;
    float dashtime = 0.15f;
    float dashDist = 300.f;
    Vec2  shootDir;
    float infiniteTime = 0.3f;
    int health;
};

class CPlayerStateMachine;
class CAttackBox;

class CPlayer :
    public CObject
{
public:
    CPlayer();
    ~CPlayer();
public:
    virtual void Start();
    // CObject을(를) 통해 상속됨
    virtual void Update() override;

    virtual void Render(HDC _dc);

    virtual void OnCollisionEnter(CCollider* _col);
    virtual void OnCollision(CCollider* _col);
    virtual void OnCollisionExit(CCollider* _col);
    virtual void FinalUpdate();
    CLONE(CPlayer);

public:
    void UpdateMove();

    bool IsAir() { return m_isAir; }
    void SetAir(bool _b) { m_isAir = _b; }
    playerInfo GetInfo() { return m_info; }
    void SetInfo(playerInfo _info) { m_info = _info; }
    void SetAi(CPlayerStateMachine* _ai);
    CAttackBox* GetAttackBox() { return m_attackBox; }


    void CreateAttackBox();
private:
    void fire();
private:

    float m_animateTime;
    bool m_attack;
    bool m_isAir;
    UINT m_weaponMode;

    CAttackBox* m_attackBox;
    playerInfo m_info;

    CPlayerStateMachine* m_ai;

    PLAYER_STATE m_curState;
    PLAYER_STATE m_prevState;
};
