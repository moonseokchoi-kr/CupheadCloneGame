#pragma once
#include "CObject.h"
#include "CTexture.h"


/// <summary>
/// ���� �÷��̾� ĳ���� Ŭ����
/// </summary>
/// 
/// �ۼ��� �ֹ���
/// 
/// ���� :
/// 1.0 - �⺻ ���� �ۼ�
/// 1.1 - �ݶ��̴� �߰�
/// 1.2 - �ִϸ��̼� �߰�
/// 1.3 - ���� �߰�
/// 
///
// 2021-08-04
// TODO : �÷��̾� ���� �ӽ� �ۼ�


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
    // CObject��(��) ���� ��ӵ�
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
