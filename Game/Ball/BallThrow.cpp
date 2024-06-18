//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/05/27
// <file>			BallThrow.cpp
// <�T�v>			�{�[����������ꂽ���
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"Game/Ball/BallThrow.h"
#include"Framework/DeviceResources.h"
#include"Game/CommonResources.h"
#include"Libraries/NakashiLib/InputManager.h"
#include"Game/Player/PlayerPart/PlayerBody.h"
#include"Game/Player/PlayerPart/PlayerRightHand.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="ball">�{�[��</param>
/// <param name="resources">���ʃ��\�[�X</param>
BallThrow::BallThrow(
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
BallThrow::~BallThrow()
{

}

/// <summary>
/// ���̃X�e�[�g�ɓ�������
/// </summary>
void BallThrow::OnEnter()
{
	m_ball->SetPosition(m_ball->GetPlayer()->GetBody()->GetRightHand()->GetPosition());
}

/// <summary>
/// ���̃X�e�[�g�𔲂����Ƃ�
/// </summary>
void BallThrow::OnExit()
{
	// �����擾
	DirectX::SimpleMath::Vector3 direction(0.0f,0.0f,-1.0f);	// �O�����̐���

	DirectX::SimpleMath::Matrix rotationZ =
		DirectX::SimpleMath::Matrix::CreateFromQuaternion(m_ball->GetPlayer()->GetCameraQuaternion());			// Z������̉�]�s��𐶐�����
	 rotationZ._32 =  0.1f;

	// �㉺�������v�Z����
	direction = DirectX::SimpleMath::Vector3::Transform(direction * m_ball->GetPlayer()->GetForceCharge(), rotationZ);
	m_ball->SetVelocity(direction);				//���x�ݒ� 
}

/// <summary>
/// ����������
/// </summary>
void BallThrow::Initialize()
{

}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="keyboardStateTracker">�L�[�{�[�h</param>
void BallThrow::Update()
{

	ToFollow();
	ChangeState();
}

/// <summary>
/// �`�揈��
/// </summary>
void BallThrow::Render()
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
void BallThrow::Finalize()
{

}

/// <summary>
/// �X�e�[�g�̕ύX
/// </summary>
/// <param name="keyboardStateTracker"></param>
void BallThrow::ChangeState()
{
	if (m_ball->GetPlayer()->GetBallTakeFlag() == false)
	{
		m_ball->ChangeState(m_ball->GetMove());
	}
}

/// <summary>
/// �v���C���[�ɒǏ]����
/// </summary>
void BallThrow::ToFollow()
{
	DirectX::SimpleMath::Matrix handWorldMatrix = m_ball->GetPlayer()->GetBody()->GetRightHand()->GetWorldMatrix();
	DirectX::SimpleMath::Vector3 ballPos = handWorldMatrix.Translation(); // ���[���h�s�񂩂�ʒu���擾

	m_ball->SetPosition(ballPos);

}