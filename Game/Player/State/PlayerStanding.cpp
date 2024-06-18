//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/01
// <file>			PlayerStanding.cpp
// <�T�v>		�@�@�v���C���[�̓����Ă��Ȃ��X�e�[�g
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"PlayerStanding.h"
#include"Game/Player/Player.h"
#include"framework/DeviceResources.h"
#include"Game/CommonResources.h"
#include"Libraries/NakashiLib/InputManager.h"
#include"Game/Player/PlayerPart/PlayerBody.h"
#include"Game/Player/PlayerPart/PlayerLeftHand.h"
#include"Game/Player/PlayerPart/PlayerRightHand.h"
#include"Game/Player/PlayerPart/PlayerTail.h"
/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="player">�v���C���[</param>
/// <param name="resource">���ʃ��\�[�X</param>
PlayerStanding::PlayerStanding(
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
PlayerStanding::~PlayerStanding()
{
}

/// <summary>
/// ���̃X�e�[�g�ɓ�������
/// </summary>
void PlayerStanding::OnEnter()
{
	m_player->SetAngle(m_player->GetQuaternion());	//�N�H�[�^�j�I�������킹��
}

/// <summary>
/// ���̃X�e�[�g�𔲂����Ƃ�
/// </summary>
void PlayerStanding::OnExit()
{
}

/// <summary>
/// ����������
/// </summary>
void PlayerStanding::Initialize()
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="keyboardStateTracker">�L�[�{�[�h</param>
void PlayerStanding::Update()
{
	auto keyboardStateTracker = m_commonResources->GetInputManager()->GetKeyboardState();

	m_player->SetVelocity(m_player->GetVelocity() * m_player->GetFriction());				// ���x�ɖ��C������
	m_player->SetPosition(m_player->GetPosition() + m_player->GetVelocity());	// �ʒu�̍X�V

	MoveChild();
	ChangeStateKey(keyboardStateTracker);																		//�X�e�[�g�ύX
}

/// <summary>
/// �`�揈��
/// </summary>
void PlayerStanding::Render()
{
}

/// <summary>
/// �X�e�[�g�ύX����
/// </summary>
/// <param name="keyboardStateTracker">�L�[�{�[�h</param>
void PlayerStanding::ChangeStateKey(
	const DirectX::Keyboard::State& keyboardStateTracker
)
{
	if (keyboardStateTracker.IsKeyDown(DirectX::Keyboard::Space))	 //�X�y�[�X�L�[���������Ƃ�
	{
		m_player->ChangeState(m_player->GetJumping());			// �W�����v��ԂɑJ�ڂ���
	}
	if (keyboardStateTracker.IsKeyDown(DirectX::Keyboard::Keys::D) || keyboardStateTracker.IsKeyDown(DirectX::Keyboard::Keys::A) ||
		keyboardStateTracker.IsKeyDown(DirectX::Keyboard::Keys::W) || keyboardStateTracker.IsKeyDown(DirectX::Keyboard::Keys::S))			// WASD�̂ǂꂩ���������Ƃ�
	{
		m_player->ChangeState(m_player->GetRunning());			// �v���C���̏�Ԃ��u�����j���O�v��ԂɑJ�ڂ���
	}
	const auto& mouseState = m_commonResources->GetInputManager()->GetMouseState();		// �}�E�X�̏�Ԏ擾
	if (mouseState.rightButton == 1 && m_player->GetBallTakeFlag() == false)			// �E�{�^���������ꂽ�@���@�{�[���������Ă��Ȃ�
	{
		m_player->ChangeState(m_player->GetTake());				// �󂯏�ԂɕύX
	}
	if (mouseState.leftButton == 1 && m_player->GetBallTakeFlag() == true)				// ���{�^���������ꂽ�@���@�{�[���������Ă���
	{
		m_player->ChangeState(m_player->GetThrow());			// ������ԂɕύX
	}
}

/// <summary>
/// �㏈��
/// </summary>
void PlayerStanding::Finalize()
{
}

void PlayerStanding::MoveChild()
{
	MoveHand();
	MoveTail();
}

/// <summary>
/// ��̓���
/// </summary>
void PlayerStanding::MoveHand()
{
	auto rightHand = m_player->GetBody()->GetRightHand();
	auto leftHand = m_player->GetBody()->GetLeftHand();
	auto m_normalQuaternion = DirectX::SimpleMath::Quaternion::Identity;
	// �E��̐U�胂�[�V�����̃p�����[�^�[
	float swingSpeed = 1.0f;
	float swingAmount = 0.1f;

	// �U�胂�[�V������ǉ�
	float swing = sin(m_player->GetTotalTime() * swingSpeed) * swingAmount;


	DirectX::SimpleMath::Quaternion slerpRotationRight =
		DirectX::SimpleMath::Quaternion::Slerp(rightHand->GetAddQUaternion(), m_normalQuaternion, 0.2f);
	DirectX::SimpleMath::Quaternion slerpRotationLeft =
		DirectX::SimpleMath::Quaternion::Slerp(leftHand->GetAddQUaternion(), m_normalQuaternion, 0.2f);// ���`�⊮����

	rightHand->SetVelocity(DirectX::SimpleMath::Vector3(0.0f, swing, 0.0f));
	rightHand->SetAddQuaternion(slerpRotationRight);
	leftHand->SetVelocity(DirectX::SimpleMath::Vector3(0.0f, swing, 0.0f));
	leftHand->SetAddQuaternion(slerpRotationLeft);
}

/// <summary>
/// �����ۂ̓���
/// </summary>
void PlayerStanding::MoveTail()
{
	auto tail = m_player->GetBody()->GetTail();
	// �U�胂�[�V�����̃p�����[�^�[
	float swingSpeed = 1.0f;
	float swingAmount = 0.6f;

	// �U�胂�[�V������ǉ�
	float swing = sin(m_player->GetTotalTime() * swingSpeed) * swingAmount;
	auto swingQuaternion = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(0.0f, 0.0f, swing);


	tail->SetAddQuaternion(swingQuaternion);
}