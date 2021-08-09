#pragma once
#include "CObject.h"
#include "CTexture.h"

class PlayerSubweapon;
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
/// 
/// 
///
// 2021-08-04
// TODO : 플레이어 상태 머신 작성
class CPlayer :
    public CObject
{
public:
    CPlayer();
    ~CPlayer();
public:
    // CObject을(를) 통해 상속됨
    virtual void Update() override;

    virtual void Render(HDC _dc);

    virtual void OnCollisionEnter(CCollider* _col);
    virtual void FinalUpdate();
    CLONE(CPlayer);
private:
    void fire();
   
private:
    PlayerSubweapon* m_subweapon;
    float m_moveSpeed;
    float m_moveDir;
    Vec2  m_shootDir;
    UINT m_weaponMode;
    float m_health;
    friend class PlayerSubweapon;
};
