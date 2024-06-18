//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/01
// <file>			PlayerBase.cpp
// <�T�v>		�@�@�v���C���[�̃x�[�X
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"PlayerBase.h"
#include"Game/CommonResources.h"
#include"Framework/DeviceResources.h"
#include "Libraries/Microsoft/DebugDraw.h"
#include "Game/Team/Team.h"

/// <summary>
///  �R���X�g���N�^
/// </summary>
/// <param name="parent">�e</param>
/// <param name="position">�ʒu</param>
/// <param name="quaternion">��]</param>
PlayerBase::PlayerBase(
	IComponent* parent,
	const DirectX::SimpleMath::Vector3& position, 
	const DirectX::SimpleMath::Quaternion& quaternion
)
	:
	m_teamNumber(0),
	m_commonResources{},
	m_model{},
	m_parent{parent},
	m_initialPosition{position},
	m_initialQuaternion{quaternion},
	m_mass{},
	m_playerParts{},
	m_worldMatrix{},
	m_collision{}
{
	m_commonResources = CommonResources::GetInstance();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayerBase::~PlayerBase()
{

}

/// <summary>
/// ������
/// </summary>
void PlayerBase::Initialize() 
{
}

/// <summary>
/// ������
/// </summary>
/// <param name="model">���f���̎擾</param>
void PlayerBase::Initialize(
	int nodeNumber,
	DirectX::Model* model
)
{
	// ���f����ݒ�
	m_model = model;
	m_teamNumber = Team::GetTeamNumberForNodeNumber(nodeNumber);
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="timer">����</param>
/// <param name="position">�ʒu</param>
/// <param name="quaternion">��]</param>
void PlayerBase::Update(
	const DX::StepTimer& timer, 
	const DirectX::SimpleMath::Vector3& position, 
	const DirectX::SimpleMath::Quaternion& quaternion
)
{
	// �p�[�c�̍X�V
	for (auto& Part : m_playerParts)
	{
		Part->Update(timer, position, quaternion);
	
	}

	
}

/// <summary>
/// �q��ݒ肷��
/// </summary>
/// <param name="playerPart">�v���C���[�̃p�[�c</param>
/// <param name="resources">���ʃ��\�[�X</param>
void PlayerBase::SetChild(
	std::unique_ptr<IComponent> playerPart
)
{
	// ������
	playerPart->Initialize();
	// �p�[�c�̒ǉ�
	m_playerParts.emplace_back(std::move(playerPart));
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="view">�J�����̃r���[</param>
/// <param name="projection">�J�����̓��e</param>
void PlayerBase::Render(
	const DirectX::SimpleMath::Matrix& view ,
	const DirectX::SimpleMath::Matrix& projection
)
{
	// �p�[�c�̕`��
	for (auto& playerPart : m_playerParts)
	{
		// �p�[�c��`��
		playerPart->Render(view , projection);
	}
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
/// <param name="matrix">�s��</param>
/// <param name="view">�J�����̃r���[</param>
/// <param name="projection">�J�����̓��e</param>
void PlayerBase::Render(
	const DirectX::SimpleMath::Matrix& matrix ,
	const DirectX::SimpleMath::Matrix& view ,
	const DirectX::SimpleMath::Matrix& projection
)
{
	// ���f���̕`��
	DrawModel( matrix , view , projection);

#ifdef _DEBUG
	//���E�{�b�N�X�̕`��
	DrawBoundingBox(matrix, view, projection);
#endif

	// �p�[�c��`�悷��
	for (auto& playerPart : m_playerParts)
	{
		playerPart->Render(view , projection);
	}

}

/// <summary>
/// ���f���̕`��
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
/// <param name="matrix">�s��</param>
/// <param name="view">�J�����̃r���[</param>
/// <param name="projection">�J�����̓��e</param>
void PlayerBase::DrawModel(
	const DirectX::SimpleMath::Matrix& matrix,
	const DirectX::SimpleMath::Matrix& view,
	const DirectX::SimpleMath::Matrix& projection
)
{
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();

	// ���f���̕`��
	m_model->Draw(context, *states, matrix, view, projection);
}

/// <summary>
/// ���E�{�b�N�X�̕`��
/// </summary>
/// <param name="matrix">�s��</param>
/// <param name="commonResources">���ʃ��\�[�X</param>
/// <param name="view">�J�����̃r���[</param>
/// <param name="projection">�J�����̓��e</param>
void PlayerBase::DrawBoundingBox(
	const DirectX::SimpleMath::Matrix& matrix,
	const DirectX::SimpleMath::Matrix& view,
	const DirectX::SimpleMath::Matrix& projection
)
{
	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();

	auto m_batch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>>(context);
	auto m_effect = std::make_unique<DirectX::BasicEffect>(device);
	m_effect->SetVertexColorEnabled(true);
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_layout;

	// ���̓��C�A�E�g���쐬����
	DX::ThrowIfFailed(
		DirectX::CreateInputLayoutFromEffect<DirectX::VertexPositionColor>(
			device,
			m_effect.get(),
			m_layout.ReleaseAndGetAddressOf()
		)
	);

	// �f�o�b�O�h���[�p�̐ݒ�
	m_effect->SetView(view);
	m_effect->SetProjection(projection);
	m_effect->Apply(context);

	//�o�E���f�B���O�{�b�N�X�̐ݒ�
	context->OMSetBlendState(states->Opaque(), nullptr, 0xFFFFFFFF);	// ���߂��Ȃ�
	context->OMSetDepthStencilState(states->DepthDefault(), 0);			// �y�o�b�t�@���g�p����
	context->RSSetState(states->CullNone());							// �|���S���̗��ʂ�`�悷��
	context->IASetInputLayout(m_layout.Get());

	DirectX::BoundingBox boundingBox;
	// ���E�{�b�N�X�̃g�����X�t�H�[��
	m_boundingBox.Transform(boundingBox, matrix);
	// �v���~�e�B�u�`��̊J�n
	m_batch->Begin();

	DX::Draw(m_batch.get(), boundingBox, DirectX::Colors::White);

	m_batch->End();

}