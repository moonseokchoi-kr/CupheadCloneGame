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
	float moveSpeed = 0.f;
	Vec2 prevMoveDir;
    float attackSpeed = 0.f;
	float jupAccTime = 0.f;
	float dashtime = 0.f;
	float dashDist = 0.f;
    Vec2  shootDir;
    float infiniteTime =0.f;
    int health = 0;
};

class CPlayerStateMachine;
class CPlayerHpUI;
class CPlayerAttackBox;
class CPlayerHitBox;

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
    virtual void OnCollision(CCollider* _col);
    virtual void OnCollisionExit(CCollider* _col);
    virtual void FinalUpdate();
    CLONE(CPlayer);

public:
    void UpdateMove();

    bool IsAir() { return m_isAir; }
    bool IsHit() { return m_hit; }
    bool IsInfinite() { return m_infinite; }
    void SetAir(bool _b) { m_isAir = _b; }
    void SetHit(bool _b) { m_hit = _b; }
    playerInfo GetInfo() { return m_info; }
    void SetInfo(playerInfo _info) { m_info = _info; }
    void SetAi(CPlayerStateMachine* _ai);
    CPlayerStateMachine* GetAi() { return m_ai; }
    CPlayerAttackBox* GetAttackBox() { return m_attackBox; }
    CPlayerHitBox* GetHitBox() { return m_hitBox; }

    void CreateAttackBox();
    void CreateHitBox();
    void CreatehpUI();
private:

    float m_animateTime;
    bool m_hit;
    bool m_infinite;
    bool m_isAir;
    bool m_renderToggle;
    float m_accTime;
    UINT m_weaponMode;

    CPlayerAttackBox* m_attackBox;
    CPlayerHitBox* m_hitBox;
    playerInfo m_info;

    CPlayerStateMachine* m_ai;

    PLAYER_STATE m_curState;
    PLAYER_STATE m_prevState;

    CPlayerHpUI* m_hpUI;
};
