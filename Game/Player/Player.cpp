//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/01
// <file>			Player.cpp
// <�T�v>		�@�@�v���C���[�̒��S�j
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"Player.h"
#include"Game/Player/PlayerPart/PlayerBody.h"
#include"Game/CommonResources.h"
#include"Libraries/NakashiLib/InputManager.h"
#include"Framework/DeviceResources.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="parent">�e</param>
/// <param name="position">�ʒu</param>
/// <param name="quaternion">��]</param>
Player::Player(
	IComponent* parent, 
	const DirectX::SimpleMath::Vector3& position, 
	const DirectX::SimpleMath::Quaternion& quaternion
)
	:
	PlayerBase(parent , position , quaternion),
	m_commonResources{},
	m_partID{PlayerBase::PartID::ROOT} ,
	m_position{position},
	m_velocity{},
	m_quaternion{quaternion},
	m_mass{},
	m_worldMatrix{},
	m_acceleration{ 0.0f,-0.4f,0.0f },
	m_gravity{ 0.0f,-0.098f , 0.0f },
	m_friction{ 0.8f ,0.0f,0.8f },
	m_ground{},
	m_cameraProjection{},
	m_cameraView{},
	m_cameraQuaternion{},
	m_ballTaking{false},
	m_forceCharge{},
	m_body{},
	m_standing{},
	m_currentState{},
	m_jumping{},
	m_runnning{},
	m_throw{},
	m_taking{},
	m_totalTime{},
	m_nodeNumber(0)
{
	m_commonResources = CommonResources::GetInstance();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Player::~Player()
{

}

/// <summary>
/// ����������
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
void Player::Initialize()
{					

	PlayerBase::Initialize();				// �x�[�X�̏��������Ă�

	auto body = std::make_unique<PlayerBody>(				// �v���C���[�{�f�B���쐬
		this,
		DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f),
		DirectX::SimpleMath::Quaternion::Identity
	);
	m_body = body.get();									// �Ăяo���pbody�Ɋi�[
	SetChild(std::move(body));					// �v���C���[�̎q��body��ݒ�
	
	m_standing = std::make_unique<PlayerStanding>(this);		// �������
	m_jumping = std::make_unique<PlayerJumping>(this);		// �W�����v���
	m_runnning = std::make_unique<PlayerRunning>(this);		// �ړ����
	m_taking = std::make_unique<PlayerTake>(this);			// �����
	m_throw = std::make_unique<PlayerThrow>(this);			// �������

	m_currentState = m_standing.get();			// �����̏�Ԃ͗������
	m_currentState->OnEnter();					// �ŏ��̃X�e�[�g��ԂɈڍs
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="timer">����</param>
/// <param name="position">�ʒu</param>
/// <param name="quaternion">��]</param>
void Player::Update(
	const DX::StepTimer& timer, 
	const DirectX::SimpleMath::Vector3& position,
	const DirectX::SimpleMath::Quaternion& quaternion
)
{
	UNREFERENCED_PARAMETER(timer);

	m_totalTime += timer.GetElapsedSeconds();

	m_currentState->Update();											// �X�e�[�g�p�^�[������

	PlayerBase::Update(														// �x�[�X�̍X�V
		timer,
		m_position + GetInitialPosition(),
		m_quaternion
	);
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="view">�J�����̃r���[</param>
/// <param name="projection">�J�����̓��e</param>
void Player::Render(
	const DirectX::SimpleMath::Matrix& view ,
	const DirectX::SimpleMath::Matrix& projection
)
{
	// �p�[�c��`��
 	PlayerBase::Render(view , projection);
}

/// <summary>
/// �X�e�[�g�p�^�[���̕ύX
/// </summary>
/// <param name="currentState">�X�e�[�g�̏��</param>
void Player::ChangeState(
	IState* currentState
)
{
	m_currentState->OnExit();		// ���݂̃X�e�[�g���o��
	m_currentState = currentState;	// �X�e�[�g�ύX
	m_currentState->OnEnter();		// ���̃X�e�[�g�ɓ���
}

