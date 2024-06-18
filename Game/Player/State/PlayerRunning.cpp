//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/01
// <file>			PlayerRunning.cpp
// <�T�v>		�@�@�v���C���[�̑���X�e�[�g
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"PlayerRunning.h"
#include"Game/Player/Player.h"
#include"Game/CommonResources.h"
#include"framework/DeviceResources.h"
#include"Libraries/NakashiLib/InputManager.h"
#include"Game/Player/PlayerPart/PlayerBody.h"
#include"Game/Player/PlayerPart/PlayerRightHand.h"
#include"Game/Player/PlayerPart/PlayerLeftHand.h"
#include"Game/Player/PlayerPart/PlayerTail.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="player">�v���C���[</param>
/// <param name="resource">���ʃ��\�[�X</param>
PlayerRunning::PlayerRunning(
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
PlayerRunning::~PlayerRunning()
{
}

/// <summary>
/// ���̃X�e�[�g�ɓ�������
/// </summary>
void PlayerRunning::OnEnter()
{
	m_player->SetVelocity(m_player->GetVelocity());	//velocity�����킹��
	m_player->SetAngle(m_player->GetQuaternion());	//�N�H�[�^�j�I�������킹��
}

/// <summary>
/// ���̃X�e�[�g���o���Ƃ�
/// </summary>
void PlayerRunning::OnExit()
{
	m_player->SetAngle(m_player->GetQuaternion());	//�N�H�[�^�j�I�������킹��
}

/// <summary>
/// ����������
/// </summary>
void PlayerRunning::Initialize()
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="keyboardStateTracker">�L�[�{�[�h</param>
void PlayerRunning::Update()
{
	auto keyboardStateTracker = m_commonResources->GetInputManager()->GetKeyboardState();

	Moving(keyboardStateTracker);				// �v���C���[�̈ړ�
	MoveChild();
	ChangeStateKey(keyboardStateTracker);		// �L�[���͂�State�J��
}

/// <summary>
/// �`��
/// </summary>
void PlayerRunning::Render()
{
}

/// <summary>
/// �㏈��
/// </summary>
void PlayerRunning::Finalize()
{
}

/// <summary>
/// �v���C���[�̓���
/// </summary>
/// <param name="keyboardStateTracker">�L�[�{�[�h</param>
void PlayerRunning::Moving(
	const DirectX::Keyboard::State& keyboardStateTracker
)
{
	DirectX::SimpleMath::Vector3 direction = m_player->GetVelocity();		// ��~����
	
	// �v���C���[�̈ړ�
	// �J�����̕�����O�Ƃ��Ċp�x���܂߂��ړ�
	if (keyboardStateTracker.IsKeyDown(DirectX::Keyboard::Keys::W))
	{ direction += DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3::Forward, m_player->GetCameraQuaternion());}
	if (keyboardStateTracker.IsKeyDown(DirectX::Keyboard::Keys::D))
	{ direction += DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3::Right,   m_player->GetCameraQuaternion());}
	if (keyboardStateTracker.IsKeyDown(DirectX::Keyboard::Keys::A))
	{ direction += DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3::Left,	  m_player->GetCameraQuaternion());}
	if (keyboardStateTracker.IsKeyDown(DirectX::Keyboard::Keys::S))
	{ direction += DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3::Backward,m_player->GetCameraQuaternion());}
 
	direction.y = 0.0f;			// y���������[����

	direction.Normalize();		// �ړ��ʂ̐��K��

	SlerpRotate(direction);		//�v���C���[�̈ړ��Ɗp�x����⊮������

	DirectX::SimpleMath::Vector3 velocity = direction ;	// �ړ��ʂ̕␳

	m_player->SetPosition(m_player->GetPosition() + m_player->GetVelocity());		//�|�W�V�����̕ύX
	m_player->SetVelocity(velocity * m_player->GetFriction() * 0.25f);				//���x�̕ύX

}

/// <summary>
/// �����̕␳
/// </summary>
/// <param name="direction">����</param>
void PlayerRunning::SlerpRotate(
	DirectX::SimpleMath::Vector3 direction
)
{
	if (direction.LengthSquared() < 1e-2f) { return; }			// �ړ��ʂ��قƂ�ǂȂ��Ȃ�v�Z���Ȃ�( 1��10-2��ȉ� )

	DirectX::SimpleMath::Quaternion targetRotation = 
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(atan2f(direction.x, direction.z), 0.0f, 0.0f);	// �ړ������x�N�g������ڕW�̃N�H�[�^�j�I�����v�Z

	DirectX::SimpleMath::Quaternion slerpRotation  = 
		DirectX::SimpleMath::Quaternion::Slerp(m_player->GetQuaternion(), targetRotation, 0.2f);			// ���`�⊮����

	slerpRotation.Normalize();				//�m�[�}���C�Y����

	m_player->SetAngle(slerpRotation);			// ���݂̊p�x���v���C���[�̃N�H�[�^�j�I���ɂ����
}

/// <summary>
/// �X�e�[�g�̕ύX
/// </summary>
/// <param name="keyboardStateTracker"></param>
void PlayerRunning::ChangeStateKey(
	const DirectX::Keyboard::State& keyboardStateTracker
)
{
	if (keyboardStateTracker.IsKeyUp(DirectX::Keyboard::Keys::D) && keyboardStateTracker.IsKeyUp(DirectX::Keyboard::Keys::A) &&
		keyboardStateTracker.IsKeyUp(DirectX::Keyboard::Keys::W) && keyboardStateTracker.IsKeyUp(DirectX::Keyboard::Keys::S))			// �L�[�̊J���ŁAStanding�ɑJ��
	{
		m_player->ChangeState(m_player->GetStanding());
	}
	if (keyboardStateTracker.IsKeyDown(DirectX::Keyboard::Keys::Space))					// �X�y�[�X�L�[�ŃW�����v�ɑJ��
	{
		m_player->ChangeState(m_player->GetJumping());
	}
	const auto& mouseState = m_commonResources->GetInputManager()->GetMouseState();		//�}�E�X�̏��擾
	if (mouseState.rightButton == 1 && m_player->GetBallTakeFlag() == false)			// �󂯏�ԂɕύX	
	{
		m_player->ChangeState(m_player->GetTake());
	}
	if (mouseState.leftButton == 1 && m_player->GetBallTakeFlag() == true)				// ������ԂɕύX
	{
		m_player->ChangeState(m_player->GetThrow());
	}
}


/// <summary>
/// �v���C���[�̎q�p�[�c�𓮂�������
/// </summary>
void PlayerRunning::MoveChild()
{
	MoveHand();
	MoveTail();
	MoveBody();
}

/// <summary>
/// ��̓���
/// </summary>
void PlayerRunning::MoveHand()
{
	auto rightHand = m_player->GetBody()->GetRightHand();		// �E��擾
	auto leftHand = m_player->GetBody()->GetLeftHand();			// ����擾

	// �U�胂�[�V�����̃p�����[�^�[
	float swingSpeed = 10.0f;
	float swingAmount = 0.8f;

	// �U�胂�[�V������ǉ�
	float swing = sin(m_player->GetTotalTime() * swingSpeed) * swingAmount;

	// �v���C���[�̉E��̈ʒu���v�Z
	auto rightQuaternion =  DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(0.0f, swing, 0.0f);
	auto leftQuaternion = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(0.0f, -swing, 0.0f);

	rightHand->SetAddQuaternion(rightQuaternion);
	leftHand->SetAddQuaternion(leftQuaternion);
}

/// <summary>
/// ���̂̓���
/// </summary>
void PlayerRunning::MoveBody()
{



}

/// <summary>
/// �����ۂ̓���
/// </summary>
void PlayerRunning::MoveTail()
{
	auto tail = m_player->GetBody()->GetTail();
	// �U�胂�[�V�����̃p�����[�^�[
	float swingSpeed = 7.0f;
	float swingAmount = 0.6f;

	// �U�胂�[�V������ǉ�
	float swing = sin(m_player->GetTotalTime() * swingSpeed) * swingAmount;
	auto swingQuaternion = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(0.0f, 0.0f, swing);

	tail->SetAddQuaternion(swingQuaternion);

}