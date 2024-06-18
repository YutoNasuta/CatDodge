//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/15
// <file>			CreateRay.cpp
// <�T�v>			ray�쐬�p
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"CreateRay.h"
#include "Libraries/NakashiLib/DrawVarious.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
NakashiLib::CreateRay::CreateRay()
	:
	m_rayPosition{},
	m_ray{},
	m_length{}
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
NakashiLib::CreateRay::~CreateRay()
{

}

/// <summary>
/// ������
/// </summary>
/// <param name="context">�f�o�C�X�R���e�L�X�g</param>
/// <param name="length">����</param>
void NakashiLib::CreateRay::Initialize(ID3D11DeviceContext* context, const float length)
{
	m_primitiveBatch = 
		std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>>(context);
	m_length = length;

}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="newPosition">�|�W�V�����ݒ�</param>
void NakashiLib::CreateRay::Update(const DirectX::SimpleMath::Vector3& newPosition)
{
	// �|�W�V������ύX������
	m_rayPosition.x = newPosition.x;
	m_rayPosition.z = newPosition.z;

	// Ray�̃|�W�V������ύX������p
	 m_rayPosition.y += m_length;

	// Ray�̌v�Z������
	CalculateRay(m_rayPosition);
}

/// <summary>
/// �`��
/// </summary>
void NakashiLib::CreateRay::Render()
{
	m_primitiveBatch->Begin();
	auto draw = std::make_unique<NakashiLib::DrawVarious>();
		draw->DrawVector(
		m_primitiveBatch.get(),
			DirectX::SimpleMath::Vector3(m_rayPosition.x , m_length , m_rayPosition.z),
		DirectX::SimpleMath::Vector3(m_rayPosition.x, -m_length, m_rayPosition.z),
		DirectX::Colors::Red);
	m_primitiveBatch->End();
}

/// <summary>
/// Ray�̌v�Z
/// </summary>
/// <param name="position">Ray�̈ʒu</param>
void NakashiLib::CreateRay::CalculateRay(const DirectX::SimpleMath::Vector3& position)
{
	m_ray = DirectX::SimpleMath::Ray{ position , DirectX::SimpleMath::Vector3::Down };
}
