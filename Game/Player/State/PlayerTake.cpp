//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/01
// <file>			PlayerTake.cpp
// <�T�v>		�@�@�v���C���[�̎󂯎��X�e�[�g
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"PlayerTake.h"
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
PlayerTake::PlayerTake(
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
PlayerTake::~PlayerTake()
{
}

/// <summary>
/// ���̃X�e�[�g�ɓ�������
/// </summary>
void PlayerTake::OnEnter()
{
	m_player->SetVelocity(m_player->GetVelocity());
	m_player->SetAngle(m_player->GetQuaternion());
}

/// <summary>
/// ���̃X�e�[�g�𔲂�����
/// </summary>
void PlayerTake::OnExit()
{
}

/// <summary>
/// ����������
/// </summary>
void PlayerTake::Initialize()
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="keyboardStateTracker">�L�[�{�[�h</param>
void PlayerTake::Update()
{
	auto keyboardStateTracker = m_commonResources->GetInputManager()->GetKeyboardState();

	//�v���C���[�ړ�
	m_player->SetPosition(m_player->GetPosition() + m_player->GetVelocity());
	m_player->SetVelocity(m_player->GetVelocity() * m_player->GetFriction());

	MoveChild();
	if (keyboardStateTracker.G)
	{
		BallTakeMove();									// �{�[�����������Ԃɂ��鏈��	
	}
	
	ChangeStateKey(keyboardStateTracker);			// �L�[�̕ύX�ŃX�e�[�g�ύX���鏈��
	ChangeDirection(keyboardStateTracker);			// �����̕␳������
}

/// <summary>
/// �`�揈��
/// </summary>
void PlayerTake::Render()
{
}

/// <summary>
/// �I������
/// </summary>
void PlayerTake::Finalize()
{

}

/// <summary>
/// �X�e�[�g��ύX����
/// </summary>
/// <param name="keyboardStateTracker">�L�[�{�[�h</param>
void PlayerTake::ChangeStateKey(
	const DirectX::Keyboard::State& keyboardStateTracker
)
{
	const auto& mouseState = m_commonResources->GetInputManager()->GetMouseState();
	if (mouseState.rightButton == 0)
	{
		m_player->ChangeState(m_player->GetStanding());				//�}�E�X�̊J���ŃX�^���f�B���O��ԂɈڍs
	}
}

/// <summary>
/// �{�[������铮��
/// </summary>
void PlayerTake::BallTakeMove()
{
	m_player->SetBallTakeFlag(true);	
}

/// <summary>
/// �����̕ύX
/// </summary>
/// <param name="keyboardStateTracker">�L�[�{�[�h</param>
void PlayerTake::ChangeDirection(
	const DirectX::Keyboard::State& keyboardStateTracker
)
{
	DirectX::SimpleMath::Vector3 direction = DirectX::SimpleMath::Vector3::Zero;	// ��~����

	direction +=															
		DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3::Forward, m_player->GetCameraQuaternion());	//�J�����̕����Ɍ���
	
	direction.y = 0.0f;			//y���������Ȃ���

	direction.Normalize();		// �ړ��ʂ̐��K��

	SlarpRotate(direction);		//�v���C���[�̈ړ��Ɗp�x����⊮������

}

/// <summary>
/// �����̕⊮
/// </summary>
/// <param name="direction">����</param>
void PlayerTake::SlarpRotate(
	DirectX::SimpleMath::Vector3 direction
)
{
	if (direction.LengthSquared() < 1e-2f) { return; }	// �ړ��ʂ��قƂ�ǂȂ��Ȃ�v�Z���Ȃ�( 1��10-2��ȉ� )

	DirectX::SimpleMath::Quaternion targetRotation =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(atan2f(direction.x, direction.z), 0.0f, 0.0f);		// �ړ������x�N�g������ڕW�̃N�H�[�^�j�I�����v�Z

	DirectX::SimpleMath::Quaternion slerpRotation = 
		DirectX::SimpleMath::Quaternion::Slerp(m_player->GetQuaternion(), targetRotation, 0.2f);			// ���`�⊮����
	slerpRotation.Normalize();

	m_player->SetAngle(slerpRotation);		// ���݂̊p�x���v���C���[�̃N�H�[�^�j�I���ɂ����
}
void PlayerTake::MoveChild()
{
	MoveHand();
	MoveTail();
}

/// <summary>
/// �r�̓���
/// </summary>
void PlayerTake::MoveHand()
{
	auto rightHand = m_player->GetBody()->GetRightHand();		// �E��擾
	auto leftHand = m_player->GetBody()->GetLeftHand();			// ����擾

	DirectX::SimpleMath::Quaternion TakePointRightQuaternion = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(0.5f,5.0f,0.5f);
	DirectX::SimpleMath::Quaternion TakePointLeftQuaternion = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(-0.5f, 5.0f, -0.5f);
		DirectX::SimpleMath::Quaternion slerpRotationRight =
		DirectX::SimpleMath::Quaternion::Slerp(rightHand->GetAddQUaternion(), TakePointRightQuaternion, 0.2f);
	DirectX::SimpleMath::Quaternion slerpRotationLeft =
		DirectX::SimpleMath::Quaternion::Slerp(leftHand->GetAddQUaternion(), TakePointLeftQuaternion, 0.2f);// ���`�⊮����

	rightHand->SetAddQuaternion(slerpRotationRight);
	leftHand->SetAddQuaternion(slerpRotationLeft);

}

/// <summary>
/// �����ۂ̓���
/// </summary>
void PlayerTake::MoveTail()
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