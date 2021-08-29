#include "pch.h"
#include "CSlimAttackState.h"
#include "CSlimeAttackBox.h"
#include "CSlime.h"
#include "CCollider.h"
#include "CRigidBody.h"
#include "CGravity.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CScene.h"
#include "CMonsterHitBox.h"
#include "CSceneManager.h"
CSlimAttackState::CSlimAttackState()
	:m_accTime(0)
	, m_jumpCount(0)
	, m_maxJumpCount(5)
	, m_isAttack(false)
	,m_currSubState(SLIME_SUB_STATE::GROUND)
	,m_currentPatt(ATTACK_PATT::PATT1)
{
}

CSlimAttackState::~CSlimAttackState()
{
}

void CSlimAttackState::Enter()
{
	GetMonster()->GetRigidBody()->SetActive(true);
	GetMonster()->GetHitBox()->GetCollider()->SetAvaCollide(true);
	CSlime* slime = static_cast<CSlime*>(GetMonster());
	getTargetDiff();
	randomPatt();
}

void CSlimAttackState::Exit()
{
	//������ 1���� ������2 �� �ٲ� ���
	m_jumpCount = 0;
}

void CSlimAttackState::Update()
{
	CSlime* slime = static_cast<CSlime*>(GetMonster());
	CSlimeAttackBox* slimeAttackBox = static_cast<CSlimeAttackBox*>(GetMonster()->GetAttackBox());
	if (!slime)
		return;
	if (!slimeAttackBox)
		return;
	updateSubState();
	updateAnimation();
	//����� ���� �ִϸ��̼� ��Ī ����
	//���ݹ����� ���ʿ� �����ɶ� �ѹ��� ����
}

void CSlimAttackState::updateAnimation()
{
	CSlime* slime = static_cast<CSlime*>(GetMonster());
	CSlimeAttackBox* slimeAttackBox = static_cast<CSlimeAttackBox*>(GetMonster()->GetAttackBox());
	Vec2 moveDir = slime->GetMoveDir();
	switch (m_currentPatt)
	{
	case ATTACK_PATT::PATT1:
	{
		//������ 1 ���� ����
		//5���� �۶����� 3��°���� ���� ���̷� �ڴ�.
		//������ �̵������� �޶����� �� �ִϸ��̼� ����
		if (m_jumpCount <= m_maxJumpCount)
		{
			switch (m_currSubState)
			{
			case SLIME_SUB_STATE::GROUND:
			{
				
				if (moveDir.x < 0)
				{
					
					slime->GetAnimator()->Play(L"SLIME_JUMP_LEFT", false);
				}
				else
				{
					slime->GetAnimator()->Play(L"SLIME_JUMP_RIGHT", false);
				}
				
				if (slime->GetAnimator()->GetCurrentAnim()->IsFinish())
				{
					slime->GetAnimator()->GetCurrentAnim()->SetFrame(0);
					slime->GetRigidBody()->SetMaxVelocity(1500.f);
					slime->GetRigidBody()->SetVelocity(Vec2(moveDir.x * 400.f, -1000.f));
					slime->GetRigidBody()->AddForce(Vec2(moveDir.x * 400.f, -1000.f));
					m_prevSubState = m_currSubState;
					m_currSubState = SLIME_SUB_STATE::AIR;
					++m_jumpCount;

				}
			}
				break;
			case SLIME_SUB_STATE::AIR:
			{
				if (moveDir.x < 0)
				{
					if (moveDir.y < 0)
					{
						slime->GetAnimator()->Play(L"SLIME_AIR_UP_LEFT", true);
					}
					else
					{
						slime->GetAnimator()->Play(L"SLIME_AIR_DOWN_LEFT", true);
					}
					
				}
				else
				{
					if (moveDir.y < 0)
					{
						slime->GetAnimator()->Play(L"SLIME_AIR_UP_RIGHT", true);
					}
					else
					{
						slime->GetAnimator()->Play(L"SLIME_AIR_DOWN_RIGHT", true);
					}

				}
			}
				break;
			case SLIME_SUB_STATE::TURN:
				break;
			case SLIME_SUB_STATE::AIR_TURN:
			{
				if (slime->GetPrevMoveDir().x < 0)
				{
					if (moveDir.y < 0)
					{
						slime->GetAnimator()->Play(L"SLIME_AIR_UP_TURN_LEFT", true);
					}
					else
					{
						slime->GetAnimator()->Play(L"SLIME_AIR_DOWN_TURN_LEFT", true);
					}
				}
				else
				{
					if (moveDir.y < 0)
					{
						slime->GetAnimator()->Play(L"SLIME_AIR_UP_TURN_RIGHT", true);
					}
					else
					{
						slime->GetAnimator()->Play(L"SLIME_AIR_DOWN_TURN_RIGHT", true);
					}
				}
			}
				break;
			default:
				break;
			}
		}
		else
		{
			if (slime->GetGravity()->IsGround())
			{
				m_jumpCount = 0;
				getTargetDiff();
				randomPatt();
			}
		}
	}
	break;
	case ATTACK_PATT::PATT2:
	{
		//���� ������ �ָ� ����
		//�ѹ��� ����
		switch (m_currSubState)
		{
		case SLIME_SUB_STATE::GROUND:
		{
			
			if (moveDir.x < 0)
			{
				slimeAttackBox->SetOffset(Vec2(-300.f, -100.f));
				slimeAttackBox->GetCollider()->SetScale(Vec2(500.f, 300.f));
				if (slime->GetAnimator()->GetCurrentAnim()->GetName() == L"SLIME_PUNCH_TURN_LEFT")
				{
					if (slime->GetAnimator()->GetCurrentAnim()->IsFinish())
					{
						slime->GetAnimator()->Play(L"SLIME_PUNCH_LEFT", false);
						slime->GetAnimator()->GetCurrentAnim()->SetFrame(7);
					}
					else
					{
						return;
					}
				}
				else
				{
					
					slime->GetAnimator()->Play(L"SLIME_PUNCH_LEFT", false);
				}
				
			}
			else
			{
				slimeAttackBox->SetOffset(Vec2(300.f, -100.f));
				slimeAttackBox->GetCollider()->SetScale(Vec2(500.f, 300.f));
				if (slime->GetAnimator()->GetCurrentAnim()->GetName() == L"SLIME_PUNCH_TURN_RIGHT")
				{
					if (slime->GetAnimator()->GetCurrentAnim()->IsFinish())
					{
						slime->GetAnimator()->Play(L"SLIME_PUNCH_RIGHT", false);
						slime->GetAnimator()->GetCurrentAnim()->SetFrame(7);
					}
					else
					{
						return;
					}
				}
				else
				{
					slime->GetAnimator()->Play(L"SLIME_PUNCH_RIGHT", false);
				}

			}
			if (slime->GetAnimator()->GetCurrentAnim()->GetCurrentFrame() >8 && slime->GetAnimator()->GetCurrentAnim()->GetCurrentFrame()<11 )
			{
				slimeAttackBox->GetCollider()->SetAvaCollide(true);
			}
			else
			{
				slimeAttackBox->GetCollider()->SetAvaCollide(false);
			}


			if (slime->GetAnimator()->GetCurrentAnim()->IsFinish())
			{
				randomPatt();
				getTargetDiff();
				slime->GetAnimator()->GetCurrentAnim()->SetFrame(0);
			}
		}
			break;
		case SLIME_SUB_STATE::TURN:
		{
			if (slime->GetPrevMoveDir().x < 0)
			{
				slime->GetAnimator()->Play(L"SLIME_PUNCH_TURN_RIGHT", false);
			}
			else
			{
				slime->GetAnimator()->Play(L"SLIME_PUNCH_TURN_LEFT", false);
			}
		}
			break;
		default:
			break;
		}
	}
		break;
	case ATTACK_PATT::PATT3:
	{
		//������ 1 ���� ����
		//5���� �۶����� 3��°���� ���� ���̷� �ڴ�.
		//������ �̵������� �޶����� �� �ִϸ��̼� ����
		if (m_jumpCount <= m_maxJumpCount)
		{
			switch (m_currSubState)
			{
			case SLIME_SUB_STATE::GROUND:
			{

				if (moveDir.x < 0)
				{

					slime->GetAnimator()->Play(L"LG_SLIME_JUMP_LEFT", false);
				}
				else
				{
					slime->GetAnimator()->Play(L"LG_SLIME_JUMP_RIGHT", false);
				}

				if (slime->GetAnimator()->GetCurrentAnim()->IsFinish())
				{
					slime->GetAnimator()->GetCurrentAnim()->SetFrame(0);
					slime->GetRigidBody()->SetMaxVelocity(1200.f);
					slime->GetRigidBody()->SetVelocity(Vec2(moveDir.x * 400.f, -2000.f));
					slime->GetRigidBody()->AddForce(Vec2(moveDir.x * 400.f, -2000.f));
					m_prevSubState = m_currSubState;
					m_currSubState = SLIME_SUB_STATE::AIR;
					++m_jumpCount;

				}
			}
			break;
			case SLIME_SUB_STATE::AIR:
			{
				if (moveDir.x < 0)
				{
					if (moveDir.y < 0)
					{
						slime->GetAnimator()->Play(L"LG_SLIME_AIR_UP_LEFT", true);
					}
					else
					{
						slime->GetAnimator()->Play(L"LG_SLIME_AIR_DOWN_LEFT", true);
					}

				}
				else
				{
					if (moveDir.y < 0)
					{
						slime->GetAnimator()->Play(L"LG_SLIME_AIR_UP_RIGHT", true);
					}
					else
					{
						slime->GetAnimator()->Play(L"LG_SLIME_AIR_DOWN_RIGHT", true);
					}

				}
			}
			break;
			case SLIME_SUB_STATE::TURN:
				break;
			case SLIME_SUB_STATE::AIR_TURN:
			{
				if (slime->GetPrevMoveDir().x < 0)
				{
					if (moveDir.y < 0)
					{
						slime->GetAnimator()->Play(L"LG_SLIME_AIR_UP_TURN_LEFT", true);
					}
					else
					{
						slime->GetAnimator()->Play(L"LG_SLIME_AIR_DOWN_TURN_LEFT", true);
					}
				}
				else
				{
					if (moveDir.y < 0)
					{
						slime->GetAnimator()->Play(L"LG_SLIME_AIR_UP_TURN_RIGHT", true);
					}
					else
					{
						slime->GetAnimator()->Play(L"LG_SLIME_AIR_DOWN_TURN_RIGHT", true);
					}
				}
			}
			break;
			default:
				break;
			}
		}
		else
		{
			if (slime->GetGravity()->IsGround())
			{
				m_jumpCount = 0;
				getTargetDiff();
				randomPatt();
			}
		}
	}
		break;
	case ATTACK_PATT::PATT4:
	{
		//���� ������ �ָ� ����
		//�ѹ��� ����
		switch (m_currSubState)
		{
		case SLIME_SUB_STATE::GROUND:
		{
			if (moveDir.x < 0)
			{
				slimeAttackBox->SetOffset(Vec2(-300.f, 0.f));
				slimeAttackBox->GetCollider()->SetScale(Vec2(500.f, 100.f));
				if (slime->GetAnimator()->GetCurrentAnim()->GetName() == L"LG_SLIME_PUNCH_TURN_LEFT")
				{
					if (slime->GetAnimator()->GetCurrentAnim()->IsFinish())
					{
						slime->GetAnimator()->Play(L"LG_SLIME_PUNCH_LEFT", false);
						slime->GetAnimator()->GetCurrentAnim()->SetFrame(7);
					}
					else
					{
						return;
					}
				}
				else
				{
					slime->GetAnimator()->Play(L"LG_SLIME_PUNCH_LEFT", false);
				}

			}
			else
			{
				slimeAttackBox->SetOffset(Vec2(300.f, 0.f));
				slimeAttackBox->GetCollider()->SetScale(Vec2(500.f, 100.f));
				if (slime->GetAnimator()->GetCurrentAnim()->GetName() == L"LG_SLIME_PUNCH_TURN_RIGHT")
				{
					if (slime->GetAnimator()->GetCurrentAnim()->IsFinish())
					{
						slime->GetAnimator()->Play(L"LG_SLIME_PUNCH_RIGHT", false);
						slime->GetAnimator()->GetCurrentAnim()->SetFrame(7);
					}
					else
					{
						return;
					}
				}
				else
				{
					slime->GetAnimator()->Play(L"LG_SLIME_PUNCH_RIGHT", false);
				}

			}
			if (slime->GetAnimator()->GetCurrentAnim()->GetCurrentFrame() > 14 && slime->GetAnimator()->GetCurrentAnim()->GetCurrentFrame() < 18)
			{
				slimeAttackBox->GetCollider()->SetAvaCollide(true);
			}
			else
			{
				slimeAttackBox->GetCollider()->SetAvaCollide(false);
			}

			if (slime->GetAnimator()->GetCurrentAnim()->IsFinish())
			{
				slime->GetAnimator()->GetCurrentAnim()->SetFrame(0);
				ChangeAIState(GetAI(), MON_STATE::IDLE);
			}
		}
		break;
		case SLIME_SUB_STATE::TURN:
		{
			if (slime->GetPrevMoveDir().x < 0)
			{
				slime->GetAnimator()->Play(L"LG_SLIME_PUNCH_TURN_RIGHT", false);
			}
			else
			{
				slime->GetAnimator()->Play(L"LG_SLIME_PUNCH_TURN_LEFT", false);
			}
		}
		break;
		default:
			break;
		}
	}
		break;
	case ATTACK_PATT::END:
		break;
	default:
		break;
	}
}

void CSlimAttackState::updateSubState()
{
	CSlime* slime = static_cast<CSlime*>(GetMonster());
	if (slime->GetGravity()->IsGround())
	{
		if (slime->GetMoveDir().x != slime->GetPrevMoveDir().x)
		{
			m_prevSubState = m_currSubState;
			m_currSubState = SLIME_SUB_STATE::TURN;
		}

		if (slime->GetMoveDir().y == 0)
		{
			if(SLIME_SUB_STATE::AIR == m_prevSubState)
				slime->GetRigidBody()->SetVelocity(Vec2(0, 0));
			m_prevSubState = m_currSubState;
			m_currSubState = SLIME_SUB_STATE::GROUND;

		}
	}
	else
	{
		if (slime->GetMoveDir().x != slime->GetPrevMoveDir().x)
		{
			m_prevSubState = m_currSubState;
			m_currSubState = SLIME_SUB_STATE::AIR_TURN;
		}
		else
		{
			m_currSubState = SLIME_SUB_STATE::AIR;
		}
	}
	
}

void CSlimAttackState::getTargetDiff()
{
	CSlime* slime = static_cast<CSlime*>(GetMonster());
	CObject* target = CSceneManager::GetInst()->GetCurrentScene()->GetTarget(GROUP_TYPE::PLAYER_HITBOX, L"PlayerHitBox");
	m_diff = target->GetPos() - slime->GetPos();
	m_diff.Normalize();
	slime->SetMoveDir(m_diff.x, slime->GetMoveDir().y);
}

void CSlimAttackState::randomPatt()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(0, 1000);
	float percent = dis(gen) / 1000.f;
	m_prevPatt = m_currentPatt;
	CSlime* slime = static_cast<CSlime*>(GetMonster());
	if (0 < percent && percent <= 0.5f)
	{
		if (slime->GetCurrentPhase() == PHASE::PHASE1)
		{
			
			m_currentPatt = ATTACK_PATT::PATT1;
		}
		else
		{
			
			m_currentPatt = ATTACK_PATT::PATT3;
		}
		
	}
	else
	{
		if (slime->GetCurrentPhase() == PHASE::PHASE1 && m_prevPatt != ATTACK_PATT::PATT2)
		{
			
			m_currentPatt = ATTACK_PATT::PATT2;
		}
		else if (slime->GetCurrentPhase() == PHASE::PHASE1 && m_prevPatt == ATTACK_PATT::PATT2)
		{
		
			m_currentPatt = ATTACK_PATT::PATT1;

		}
		else if (slime->GetCurrentPhase() == PHASE::PHASE2 && m_prevPatt != ATTACK_PATT::PATT4)
		{
			m_currentPatt = ATTACK_PATT::PATT4;
		}
		else
		{
			m_currentPatt = ATTACK_PATT::PATT3;
		}
	}


}
