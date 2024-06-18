//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/05/27
// <file>			BallThrow.cpp
// <�T�v>			�{�[���̓����i�ʏ��ԁj
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"Game/Ball/BallMove.h"
#include"Framework/DeviceResources.h"
#include"Game/CommonResources.h"
#include"Libraries/NakashiLib/InputManager.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="ball">�{�[��</param>
/// <param name="resources">���ʃ��\�[�X</param>
BallMove::BallMove(
	Ball* ball
)
:
	m_ball(ball)
{
	m_commonResources = CommonResources::GetInstance();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BallMove::~BallMove()
{

}

/// <summary>
/// ���̃X�e�[�g�ɓ�������
/// </summary>
void BallMove::OnEnter()
{
	m_ball->SetAcceleration(DirectX::SimpleMath::Vector3(0.0f, Ball::GRAVITATION_ACCELERATION, 0.0f));		// �����x
	m_ball->SetVelocity(m_ball->GetVelocity());
}

/// <summary>
/// ���̃X�e�[�g�𔲂����Ƃ�
/// </summary>
void BallMove::OnExit()
{

}

/// <summary>
/// ����������
/// </summary>
void BallMove::Initialize()
{

}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="keyboardStateTracker">�L�[�{�[�h</param>
void BallMove::Update()
{
	auto keyboardStateTracker = m_commonResources->GetInputManager()->GetKeyboardState();
	ChangeState();

	if (keyboardStateTracker.IsKeyDown(DirectX::Keyboard::Keys::I))
	{
		m_ball->SetDebugLog(2);
	}
	if (keyboardStateTracker.IsKeyDown(DirectX::Keyboard::Keys::Up))
	{
		m_ball->SetVelocity(DirectX::SimpleMath::Vector3::Forward);
	}
	if (keyboardStateTracker.IsKeyDown(DirectX::Keyboard::Keys::Down))
	{
		m_ball->SetVelocity(DirectX::SimpleMath::Vector3::Backward);
	}
	if (keyboardStateTracker.IsKeyDown(DirectX::Keyboard::Keys::Left))
	{
		m_ball->SetVelocity(DirectX::SimpleMath::Vector3::Left);
	}
	if (keyboardStateTracker.IsKeyDown(DirectX::Keyboard::Keys::Right))
	{
		m_ball->SetVelocity(DirectX::SimpleMath::Vector3::Right);
	}

	//  �d�͉����x���ݒ肳��Ă��Ȃ��ꍇ�͍X�V���Ȃ�
	if (m_ball->GetAcceleration().y == 0.0f)
		return;			


	// ���x�̌v�Z
	m_ball->SetVelocity(m_ball->GetVelocity() + m_ball->GetAcceleration());
	// �����̐ݒ�
	DirectX::SimpleMath::Vector3 heading = m_ball->GetVelocity();
	// ��C��R�ɂ�茸��
	/*m_ball->SetVelocity(heading * Ball::AIR_RESISTANCE);*/
	// �ʒu���v�Z
	m_ball->SetPosition(m_ball->GetPosition() + m_ball->GetVelocity());

	// �{�[���̉�]����ݒ�
	DirectX::SimpleMath::Vector3 axis = DirectX::SimpleMath::Vector3(heading.y, 0.0f, -heading.x);
	if (m_ball->GetVelocity().Length())
	{
		// ��]�p���v�Z
		float angle = (m_ball->GetVelocity().Length() / m_ball->GetRadius()) * 0.006f;
		// �N�H�[�^�j�I���𐶐�
		m_ball->SetQuaternion(m_ball->GetQuaternion() * DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(axis, angle));
	}

	// �{�[����e�܂���
	if (m_ball->GetPosition().y <= m_ball->GetGround().y)
	{
		// �ʒu��␳����
		m_ball->SetPosition(DirectX::SimpleMath::Vector3(m_ball->GetPosition().x, m_ball->GetGround().y, m_ball->GetPosition().z));
		// ���x�̔��]
		m_ball->SetVelocity(DirectX::SimpleMath::Vector3(m_ball->GetVelocity().x, -m_ball->GetVelocity().y, m_ball->GetVelocity().z));
		// �������i�W�T���j��K�p
		m_ball->SetVelocity(m_ball->GetVelocity() * 0.85f);
	}
	// ���x���Ȃ��Ȃ��Ă�����
	if (m_ball->GetVelocity().Length() < 0.1f)
	{
		// �ʒu�̐ݒ�
		m_ball->SetPosition(m_ball->GetPosition());
		// �����x�̏�����
		m_ball->SetAcceleration(DirectX::SimpleMath::Vector3::Zero);
		// ���x�̏�����
		m_ball->SetVelocity(DirectX::SimpleMath::Vector3::Zero);
	}
	


	
}

/// <summary>
/// �`�揈��
/// </summary>
void BallMove::Render()
{
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();

	DirectX::SimpleMath::Matrix world =
		DirectX::SimpleMath::Matrix::CreateFromQuaternion(m_ball->GetQuaternion());
	world *= DirectX::SimpleMath::Matrix::CreateTranslation(m_ball->GetPosition());

	// �r���[�s����擾����
	m_ball->GetBallModel()->Draw(
		context, *states,
		world,
		m_ball->GetView(),
		m_ball->GetProj()
	);

}

/// <summary>
/// �㏈��
/// </summary>
void BallMove::Finalize()
{

}

/// <summary>
/// �X�e�[�g�ύX
/// </summary>
/// <param name="keyboardStateTracker"></param>
void BallMove::ChangeState()
{
	if (m_ball->GetPlayer()->GetBallTakeFlag() == true)
	{
		// �󂯏�ԂɕύX
		m_ball->ChangeState(m_ball->GetThrow());
	}
}

