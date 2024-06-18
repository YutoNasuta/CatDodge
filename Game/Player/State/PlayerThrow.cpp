//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/01
// <file>			PlayerThrow.cpp
// <�T�v>		�@�@�v���C���[�̓�����X�e�[�g
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include"pch.h"
#include"PlayerThrow.h"
#include"Game/CommonResources.h"
#include"framework/DeviceResources.h"
#include"Libraries/NakashiLib/InputManager.h"
#include"Game/Player/PlayerPart/PlayerBody.h"
#include"Game/Player/PlayerPart/PlayerLeftHand.h"
#include"Game/Player/PlayerPart/PlayerRightHand.h"
#include"Game/Player/PlayerPart/PlayerTail.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="player">�v���C���[</param>
/// <param name="resources">���ʃ��\�[�X</param>
PlayerThrow::PlayerThrow(
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
PlayerThrow::~PlayerThrow()
{

}

/// <summary>
/// ���̃X�e�[�g�p�^�[���ɓ�������
/// </summary>
void PlayerThrow::OnEnter()
{
	m_player->SetVelocity(m_player->GetVelocity());
	m_player->SetAngle(m_player->GetQuaternion());
	m_player->SetForceCharge(0.0f);
	
}

/// <summary>
/// ���̃X�e�[�g�p�^�[���𔲂�����
/// </summary>
void PlayerThrow::OnExit()
{
	m_player->SetBallTakeFlag(false);
}

/// <summary>
/// ����������
/// </summary>
void PlayerThrow::Initialize()
{

}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="keyboardStateTracker">�L�[�{�[�h</param>
void PlayerThrow::Update()
{
	auto keyboardStateTracker = m_commonResources->GetInputManager()->GetKeyboardState();
	//�v���C���[�ړ�
	m_player->SetPosition(m_player->GetPosition() + m_player->GetVelocity());
	m_player->SetVelocity(m_player->GetVelocity() * m_player->GetFriction());
	// ���Ɏ����Ă���Ȃ炱�̃X�e�[�g�𔲂��A������ԂɈڂ�

	MoveChild();

	AddForce();

	ChangeStateKey(keyboardStateTracker);
	ChangeDirectionMove(keyboardStateTracker);
}

/// <summary>
/// �`�揈��
/// </summary>
void PlayerThrow::Render()
{
}

/// <summary>
/// �I������
/// </summary>
void PlayerThrow::Finalize()
{

}

/// <summary>
/// �L�[�̕ύX�ɂ��X�e�[�g��ύX����
/// </summary>
/// <param name="keyboardStateTracker">�L�[�{�[�h</param>
void PlayerThrow::ChangeStateKey(
	const DirectX::Keyboard::State& keyboardStateTracker
)
{
	const auto& mouseState = m_commonResources->GetInputManager()->GetMouseState();
	if (mouseState.leftButton == 0)
	{
		m_player->ChangeState(m_player->GetStanding());			//������ԂɕύX
	}
}

/// <summary>
/// �v���C���[�̌����ύX
/// </summary>
/// <param name="keyboardStateTracker">�L�[�{�[�h</param>
void PlayerThrow::ChangeDirectionMove(
	const DirectX::Keyboard::State& keyboardStateTracker
)
{
	DirectX::SimpleMath::Vector3 direction = DirectX::SimpleMath::Vector3::Zero;				// ��~����

	// �v���C���[�̈ړ�	  �J�����̕�����O�Ƃ��Ċp�x���܂߂��ړ�
	if (keyboardStateTracker.IsKeyDown(DirectX::Keyboard::Keys::W)) { direction += DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3::Forward, m_player->GetCameraQuaternion()); }
	if (keyboardStateTracker.IsKeyDown(DirectX::Keyboard::Keys::D)) { direction += DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3::Right, m_player->GetCameraQuaternion()); }
	if (keyboardStateTracker.IsKeyDown(DirectX::Keyboard::Keys::A)) { direction += DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3::Left, m_player->GetCameraQuaternion()); }
	if (keyboardStateTracker.IsKeyDown(DirectX::Keyboard::Keys::S)) { direction += DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3::Backward, m_player->GetCameraQuaternion()); }

	direction.y = 0.0f;						// y���̐������Ȃ���

	direction.Normalize();					// �ړ��ʂ̐��K��

	SlarpRotate(direction);					//�v���C���[�̈ړ��Ɗp�x����⊮������

	DirectX::SimpleMath::Vector3 velocity = direction * 0.1f;	// �ړ��ʂ̕␳

	m_player->SetVelocity(velocity);		// ���ۂɈړ�������
}

/// <summary>
/// �����ύX���̕␳
/// </summary>
/// <param name="direction">����</param>
void PlayerThrow::SlarpRotate(
	DirectX::SimpleMath::Vector3 direction
)
{
	if (direction.LengthSquared() < 1e-2f) { return; }				// �ړ��ʂ��قƂ�ǂȂ��Ȃ�v�Z���Ȃ�( 1��10-2��ȉ� )

	DirectX::SimpleMath::Quaternion targetRotation = 
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(atan2f(direction.x, direction.z), 0.0f, 0.0f);	// �ړ������x�N�g������ڕW�̃N�H�[�^�j�I�����v�Z

	DirectX::SimpleMath::Quaternion slerpRotation = 
		DirectX::SimpleMath::Quaternion::Slerp(m_player->GetQuaternion(), targetRotation, 0.2f);		// ���`�⊮����

	slerpRotation.Normalize();							//�m�[�}���C�Y������

	m_player->SetAngle(slerpRotation);		// ���݂̊p�x���v���C���[�̃N�H�[�^�j�I���ɂ����
}

/// <summary>
/// �͂������鏈��
/// </summary>
void PlayerThrow::AddForce()
{
	const auto& mouseState = m_commonResources->GetInputManager()->GetMouseState();
	if (mouseState.leftButton == 1)
	{
		float force = 0.02f;
		if (m_player->GetForceCharge() <= 4.0f)
			m_player->SetForceCharge(m_player->GetForceCharge() + force);	//�͂��{����
	}
}

/// <summary>
/// �q�p�[�c�̓���
/// </summary>
void PlayerThrow::MoveChild()
{
	MoveHand();
}

/// <summary>
/// ��̓���
/// </summary>
void PlayerThrow::MoveHand()
{
	auto rightHand = m_player->GetBody()->GetRightHand();
	auto leftHand = m_player->GetBody()->GetLeftHand();

	DirectX::SimpleMath::Quaternion TakePointRightQuaternion = 
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(1.5f, -2.0f, 1.0f);

	DirectX::SimpleMath::Quaternion TakePointLeftQuaternion = 
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(1.0f, 1.0f, -1.0f);

	DirectX::SimpleMath::Quaternion slerpRotationRight =
		DirectX::SimpleMath::Quaternion::Slerp(rightHand->GetAddQUaternion(), TakePointRightQuaternion, 0.2f);
	DirectX::SimpleMath::Quaternion slerpRotationLeft =
		DirectX::SimpleMath::Quaternion::Slerp(leftHand->GetAddQUaternion(), TakePointLeftQuaternion, 0.2f);// ���`�⊮����

	rightHand->SetAddQuaternion(slerpRotationRight);
	leftHand->SetAddQuaternion(slerpRotationLeft);
}

void PlayerThrow::MoveTail()
{
}