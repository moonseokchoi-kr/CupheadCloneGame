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
	float prevMoveDir;
	float moveDir;
    float attackSpeed;

    float dashtime = 0.15f;

    Vec2  shootDir;

    int health;
};

class CPlayerStateMachine;


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
    virtual void FinalUpdate();
    CLONE(CPlayer);

public:
    void UpdateMove();

    playerInfo GetInfo() { return m_info; }
    void SetInfo(playerInfo _info) { m_info = _info; }
    void SetAi(CPlayerStateMachine* _ai);
private:
    void fire();

private:


    bool m_attack;

    UINT m_weaponMode;

    Vec2 m_prevPos;

    playerInfo m_info;

    CPlayerStateMachine* m_ai;

    PLAYER_STATE m_curState;
    PLAYER_STATE m_prevState;
};
