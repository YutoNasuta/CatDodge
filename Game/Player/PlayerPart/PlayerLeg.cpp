//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/01
// <file>			PlayerLeg.cpp
// <�T�v>		�@�@�v���C���[�̑��p�[�c
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"PlayerLeg.h"
#include"Interface/IComponent.h"
#include"Libraries/NakashiLib/ResourcesManager.h"
#include"Game/CommonResources.h"
#include"Game/Player/PlayerPart/PlayerHead.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="parent">�e</param>
/// <param name="position">�ʒu</param>
/// <param name="quaternion">��]</param>
PlayerLeg::PlayerLeg(
	IComponent* parent, 
	const DirectX::SimpleMath::Vector3& position,
	const DirectX::SimpleMath::Quaternion& quaternion
)
	: PlayerBase(parent , position ,quaternion),
	m_commonResources{},
	m_partID{PlayerBase::PartID::LEG},
	m_model{},
	m_position{},
	m_velocity{},
	m_quaternion{},
	m_mass{},
	m_worldMatrix{},
	m_nodeNumber{0}
{
	m_commonResources = CommonResources::GetInstance();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayerLeg::~PlayerLeg()
{
}

/// <summary>
/// ����������
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
void PlayerLeg::Initialize()
{
	m_model = m_commonResources->GetResourcesManager()->GetModel(L"PlayerLeg");


	// ���N���X��Initialize�Ăяo��
	PlayerBase::Initialize(m_nodeNumber , m_model);
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="timer">����</param>
/// <param name="position">�ʒu</param>
/// <param name="quaternion">��]</param>
void PlayerLeg::Update(
	const DX::StepTimer& timer, 
	const DirectX::SimpleMath::Vector3& position , 
	const DirectX::SimpleMath::Quaternion& quaternion)
{
	UNREFERENCED_PARAMETER(timer);

	DirectX::SimpleMath::Vector3 localPosition = position;
	DirectX::SimpleMath::Quaternion localQuaternion = m_quaternion;

	localPosition += m_velocity;
	m_position = localPosition;

	m_quaternion = quaternion;			// ���݂̉�]�p���X�V����

	PlayerBase::Update(
		timer,
		m_position,
		m_quaternion);

	m_worldMatrix = DirectX::SimpleMath::Matrix::CreateFromQuaternion(m_quaternion)
		* DirectX::SimpleMath::Matrix::CreateTranslation(m_position)
		* DirectX::SimpleMath::Matrix::CreateFromQuaternion(GetInitialQuaternion())
		* DirectX::SimpleMath::Matrix::CreateTranslation(GetInitialPosition());

}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="view">�J�����̃r���[</param>
/// <param name="projection">�J�����̓��e</param>
void PlayerLeg::Render(
const DirectX::SimpleMath::Matrix& view ,
const DirectX::SimpleMath::Matrix& projection
)
{
	PlayerBase::Render(m_worldMatrix, view, projection);
}

/// <summary>
/// �㏈��
/// </summary>
void PlayerLeg::Finalize()
{
}