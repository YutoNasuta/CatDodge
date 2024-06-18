//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/01
// <file>			PlayerJumping.cpp
// <�T�v>		�@�@�v���C���[�̃W�����v�X�e�[�g
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"PlayerJumping.h"
#include"Game/Player/Player.h"
#include"Framework/DeviceResources.h"
#include"Game/CommonResources.h"
#include"Libraries/NakashiLib/InputManager.h"
#include"Game/Player/PlayerPart/PlayerBody.h"
#include"Game/Player/PlayerPart/PlayerLeftHand.h"
#include"Game/Player/PlayerPart/PlayerRightHand.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="player">�v���C���[</param>
/// <param name="resource">���ʃ��\�[�X</param>
PlayerJumping::PlayerJumping(
	Player* player
)
:
	m_player(player)
{
	m_commonResources = CommonResources::GetInstance();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayerJumping::~PlayerJumping()
{
}

/// <summary>
/// ���̃X�e�[�g�ɓ�������
/// </summary>
void PlayerJumping::OnEnter()
{
	m_player->SetVelocity(DirectX::SimpleMath::Vector3(m_player->GetVelocity().x, m_player->GetVelocity().y + 1.1f, m_player->GetVelocity().z));
	m_player->SetAngle(m_player->GetQuaternion());
}

/// <summary>
/// ���̃X�e�[�g���o����
/// </summary>
void PlayerJumping::OnExit()
{
}

/// <summary>
/// ����������
/// </summary>
void PlayerJumping::Initialize()
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="keyboardStateTracker">�L�[�{�[�h</param>
void PlayerJumping::Update()
{
	auto keyboardStateTracker = m_commonResources->GetInputManager()->GetKeyboardState();

	m_player->SetVelocity(m_player->GetVelocity() + m_player->GetGravity());					// ���x�ɏd�͂����Z
	m_player->SetPosition(m_player->GetPosition() + m_player->GetVelocity());		// �ʒu�ɑ��x�����Z

	MoveChild();

	// �n�ʂ�艺�ɂ�������
	if (m_player->GetPosition().y < m_player->GetGround().y)
	{
		DirectX::SimpleMath::Vector3 position = m_player->GetPosition();				// �ʒu���擾

		position.y = m_player->GetGround().y;							// �n�ʂ̍�����ݒ肷��

		m_player->SetPosition(position);				// �ʒu��ݒ肷��
		
		DirectX::SimpleMath::Vector3 velocity = m_player->GetVelocity();			// ���x��ݒ肷��
		
		velocity.y = 0.0f;					// ���x��ݒ�
		
		m_player->SetVelocity(velocity);			// ���x��ݒ肷��
	}

	// �n�ʂɒ��n�����Ƃ�
	if (m_player->GetPosition().y == m_player->GetGround().y)
	{
		ChangeStateKey(keyboardStateTracker);				//�X�e�[�g�ύX
	}
}

/// <summary>
/// �`�揈��
/// </summary>
void PlayerJumping::Render()
{

}

/// <summary>
/// �㏈��
/// </summary>
void PlayerJumping::Finalize()
{
}

/// <summary>
/// �X�e�[�g�ύX
/// </summary>
/// <param name="keyboardStateTracker">�L�[�{�[�h</param>
void PlayerJumping::ChangeStateKey(
	const DirectX::Keyboard::State& keyboardStateTracker
)
{
	const auto& mouseState = m_commonResources->GetInputManager()->GetMouseState(); 
	 if(mouseState.rightButton)
	{
		m_player->ChangeState(m_player->GetTake());		// �󂯏�ԂɑJ��
	}
	m_player->ChangeState(m_player->GetStanding());		// ������ԂɑJ�ڂ���
}

/// <summary>
/// �q�̓���
/// </summary>
void PlayerJumping::MoveChild()
{
	MoveHand();
}

/// <summary>
/// ��̓���
/// </summary>
void PlayerJumping::MoveHand()
{
	auto rightHand = m_player->GetBody()->GetRightHand();		//�E��擾
	auto leftHand = m_player->GetBody()->GetLeftHand();

	// �U�胂�[�V�����̃p�����[�^�[
	float swingSpeed = 10.0f;
	float swingAmount = 0.8f;

	// �U�胂�[�V������ǉ�
	float swing = sin(m_player->GetTotalTime() * swingSpeed) * swingAmount;

	// �v���C���[�̉E��̈ʒu���v�Z
	auto rightQuaternion = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(0.0f, swing, 0.0f);
	auto leftQuaternion = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(0.0f, -swing, 0.0f);

	rightHand->SetAddQuaternion(rightQuaternion);
	leftHand->SetAddQuaternion(leftQuaternion);
}