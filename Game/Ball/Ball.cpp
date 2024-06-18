//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/05/27
// <file>			Ball.cpp
// <�T�v>			�{�[���̒��S�N���X
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"Ball.h"
#include"Game/CommonResources.h"
#include"Libraries/NakashiLib/ResourcesManager.h"
#include"Framework/DeviceResources.h"

// SI�P�ʌn��K�p����
// �d�͉����x m/s^2
const float Ball::GRAVITATION_ACCELERATION = -0.0980665f;
// ���� kg
const float Ball::MASS = 0.00450f;
// ���a m
const float Ball::RADIUS = 0.0011f;
// ���a m
const float Ball::DIAMETER = 0.0022f;
// ��C��R�W��(Cd)
const float Ball::DRAG_COEFFICIENT = 0.002f;
// ��C���x(��) kg/m^3
const float Ball::AIR_DENSITY = 0.0122f;
//�T�b�J�[�{�[�����a�f�ʐ� m^2
const float Ball::CROSS_SECTION = (0.25f * DirectX::XM_PI) * DIAMETER * DIAMETER;
// ��C��R�W��(k)
// �{�[���ɓ�����C��R�̓{�[���̑��x�̓��ɔ�Ⴗ��
const float Ball::AIR_RESISTANCE = -0.5f * AIR_DENSITY * CROSS_SECTION * DRAG_COEFFICIENT;
// ���C�W��
const float Ball::FRICTION = -0.0004f;
// �������苗��
const float Ball::INTERSECT_JUDGEMENT_DISTANCE = 10.0f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Ball::Ball()
	:
	m_commonResources{},
	m_position{},
	m_velocity{},
	m_friction{},
	m_ballModel{},
	m_rotate{},
	m_horizontal{},
	m_forward{},
	m_speed{},
	m_ballMove{},
	m_currentState{},
	m_ballThrow{},
	m_player{},
	m_acceleration{},
	m_radius{RADIUS}
{
	m_commonResources = CommonResources::GetInstance();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Ball::~Ball()
{

}

/// <summary>
/// ����������
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
/// <param name="player">�v���C���[�擾</param>
void Ball::Initialize(Player* player)
{

	m_player = player;


	m_commonResources->GetResourcesManager()->CreateModel(L"Ball", L"Ball.cmo");		// Resources�Ƀ��f�����쐬

	m_ballMove = std::make_unique<BallMove>(this);		// ������Ԏ擾

	m_ballThrow = std::make_unique<BallThrow>(this);		// ������Ԏ擾

	m_currentState = m_ballMove.get();
	m_currentState->OnEnter();

}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="keyboardStateTracke">�L�[�{�[�h</param>
/// <param name="elapsedTime">����</param>
void Ball::Update(float elapsedTime)
{

	m_currentState->Update();
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="view">�J�����̃r���[</param>
/// <param name="proj">�J�����̓��e</param>
void Ball::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{
	m_view = view;
	m_projection = proj;
	m_currentState->Render();

}

/// <summary>
/// �㏈��
/// </summary>
void Ball::Finalize()
{

}

/// <summary>
/// �{�[���̃��f�����擾
/// </summary>
/// <returns></returns>
DirectX::Model* Ball::GetBallModel()
{
	return m_commonResources->GetResourcesManager()->GetModel(L"Ball");
}

/// <summary>
/// �X�e�[�g�̕ύX
/// </summary>
/// <param name="currentState">�X�e�[�g�̏��</param>
void Ball::ChangeState(IState* currentState)
{
	m_currentState->OnExit();		// ���݂̃X�e�[�g���o��
	m_currentState = currentState;	// �X�e�[�g�ύX
	m_currentState->OnEnter();		// ���̃X�e�[�g�ɓ���
}