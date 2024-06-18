//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/13
// <file>			MousePoint.cpp
// <�T�v>			���b�V���̓����蔻��p
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include "pch.h"
#include "CollisionMesh.h"
#include <iostream>
#include <fstream>
#include <sstream>

// VertexPositionTexture �̒�`


/// <summary>
/// �R���X�g���N�^
/// </summary>
NakashiLib::CollisionMesh::CollisionMesh()
	:
	m_position{},
	m_rotation{},
	m_vertices{},
	m_indices{},
	m_triangles{},
	m_inputLayout{},
	m_basicEffect{},
	m_primitiveBatch{},
	m_basicEffectTexture{},
	m_texture{},
	m_verticesTexture{},
	m_inputLayoutTexture{},
	m_primitiveBatchTexture{},
	m_context{}
{

}

/// <summary>
/// ����������
/// </summary>
void NakashiLib::CollisionMesh::InitializeObject(
	ID3D11Device* device,
	ID3D11DeviceContext* context,
	const std::wstring& objName
)
{
	assert(device);
	assert(context);
	m_context = context;

	// obj�t�@�C���̂�݂���
	LoadObjFile(objName);

	// �|���S���z��̍쐬
	for (size_t i = 0; i < m_indices.size() / 3; i++)
	{
		AddTriangle(
			m_vertices[m_indices[i * 3 + 0]].position,
			m_vertices[m_indices[i * 3 + 1]].position,
			m_vertices[m_indices[i * 3 + 2]].position
		);
	}

	// �`��I�u�W�F�N�g����������
	m_basicEffect = std::make_unique<DirectX::BasicEffect>(device);

	DX::ThrowIfFailed(
		DirectX::CreateInputLayoutFromEffect<DirectX::VertexPosition>(
			device,
			m_basicEffect.get(),
			m_inputLayout.ReleaseAndGetAddressOf()
		)
	);
	
	
	m_primitiveBatch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPosition>> (m_context);
}

/// <summary>
/// ���b�V�����̏�����
/// </summary>
/// <param name="device">�f�o�C�X</param>
/// <param name="context">�R���e�L�X�g</param>
/// <param name="vertices">���_���</param>
/// <param name="indices">�C���f�b�N�X</param>
void NakashiLib::CollisionMesh::InitializeVertexMesh(
	ID3D11Device* device,
	ID3D11DeviceContext* context,
	const std::vector<DirectX::VertexPosition>& vertices,
	const std::vector<uint16_t>& indices
)
{
	m_context = context;
	// �`��I�u�W�F�N�g����������(���C���[�t���[��)
	m_basicEffect = std::make_unique<DirectX::BasicEffect>(device);

	DX::ThrowIfFailed(
		DirectX::CreateInputLayoutFromEffect<DirectX::VertexPosition>(
			device,
			m_basicEffect.get(),
			m_inputLayout.ReleaseAndGetAddressOf()
		)
	);

	m_primitiveBatch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPosition>>(m_context);
	

	m_vertices = vertices;
	m_indices = indices;

	for (size_t i = 0; i < m_indices.size() / 3; i++)
	{
		AddTriangle(
			m_vertices[m_indices[i * 3 + 0]].position,
			m_vertices[m_indices[i * 3 + 1]].position,
			m_vertices[m_indices[i * 3 + 2]].position
		);
	}


}

/// <summary>
/// �e�N�X�`���̕`��
/// </summary>
/// <param name="device">�f�o�C�X</param>
/// <param name="context">�R���e�L�X�g</param>
/// <param name="vertices">���_���</param>
/// <param name="indices">�C���f�b�N�X</param>
void NakashiLib::CollisionMesh::InitializeVertexMeshTexture(
	ID3D11Device* device,
	ID3D11DeviceContext* context,
	const std::vector<DirectX::VertexPositionTexture>& vertices,
	const std::vector<uint16_t>& indices
) {
	m_context = context;
	// �e�N�X�`���p�I�u�W�F�N�g����
	m_basicEffectTexture = std::make_unique<DirectX::BasicEffect>(device);
	m_basicEffectTexture->SetTextureEnabled(true);

	DX::ThrowIfFailed(
		DirectX::CreateInputLayoutFromEffect<DirectX::VertexPositionTexture>(
			device,
			m_basicEffectTexture.get(),
			m_inputLayoutTexture.ReleaseAndGetAddressOf()
		)
	);

	m_primitiveBatchTexture =
		std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>>(m_context);

	m_verticesTexture = vertices;
	m_indices = indices;

	for (size_t i = 0; i < m_indices.size() / 3; i++) {
		AddTriangle(
			m_verticesTexture[m_indices[i * 3 + 0]].position,
			m_verticesTexture[m_indices[i * 3 + 1]].position,
			m_verticesTexture[m_indices[i * 3 + 2]].position
		);
	}

	// �摜�̃��[�h
	HRESULT hr = DirectX::CreateWICTextureFromFile(
		device,
		L"Resources/Textures/Ground.png",
		nullptr,
		m_texture.ReleaseAndGetAddressOf()
	);
	if (FAILED(hr)) {
		OutputDebugStringA("Failed to load texture\n");
	}
}

/// <summary>
/// ���C���[�t���[���̕`��
/// </summary>
/// <param name="context">�f�o�C�X</param>
/// <param name="states">����</param>
/// <param name="view">�J�����̃r���[</param>
/// <param name="projection">���e</param>
void NakashiLib::CollisionMesh::DrawMesh(
	DirectX::CommonStates* states,
	const DirectX::SimpleMath::Matrix& view,
	const DirectX::SimpleMath::Matrix& projection
)
{
	assert(states);

	// �f�o�C�X�R���e�L�X�g�̃p�����[�^��ݒ�
	m_context->OMSetBlendState(states->AlphaBlend(), nullptr, 0xFFFFF);	// �u�����h�X�e�[�g
	m_context->OMSetDepthStencilState(states->DepthRead(), 0);			// �[�x�o�b�t�@/�X�e���V���o�b�t�@
	m_context->RSSetState(states->Wireframe());							// �J�����O
	m_context->IASetInputLayout(m_inputLayout.Get());						// ���̓��C�A�E�g


	// ���[���h�s����v�Z����
	DirectX::SimpleMath::Matrix rotation = DirectX::SimpleMath::Matrix::CreateFromQuaternion(m_rotation);	
	DirectX::SimpleMath::Matrix translation = DirectX::SimpleMath::Matrix::CreateTranslation(m_position);
	DirectX::SimpleMath::Matrix world = rotation * translation;

	//�x�[�V�b�N�G�t�F�N�g�̃p�����[�^��ݒ肷��
	m_basicEffect->SetWorld(world);					
	m_basicEffect->SetView(view);
	m_basicEffect->SetProjection(projection);
	m_basicEffect->Apply(m_context);

	// �e�N�X�`����`��
	m_primitiveBatch->Begin();
	m_primitiveBatch->DrawIndexed(
		D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
		&m_indices[0], m_indices.size(),
		&m_vertices[0], m_vertices.size()
	);
	m_primitiveBatch->End();
}

/// <summary>
///  �e�N�X�`���𒣂����`��
/// </summary>
/// <param name="context">�f�o�C�X</param>
/// <param name="states">����</param>
/// <param name="view">�J�����̃r���[</param>
/// <param name="projection">���e</param>
void NakashiLib::CollisionMesh::DrawMeshTexture(
	DirectX::CommonStates* states,
	const DirectX::SimpleMath::Matrix& view,
	const DirectX::SimpleMath::Matrix& projection
) {
	assert(states);

	// �f�o�C�X�R���e�L�X�g�̃p�����[�^��ݒ�
	m_context->OMSetBlendState(states->AlphaBlend(), nullptr, 0xFFFFF);        // �u�����h�X�e�[�g
	m_context->OMSetDepthStencilState(states->DepthDefault(), 0);                // �[�x�o�b�t�@/�X�e���V���o�b�t�@
	m_context->RSSetState(states->CullNone());                                // �J�����O
	m_context->IASetInputLayout(m_inputLayoutTexture.Get());                  // ���̓��C�A�E�g

	// ���[���h�s����v�Z����
	DirectX::SimpleMath::Matrix rotation = DirectX::SimpleMath::Matrix::CreateFromQuaternion(m_rotation);
	DirectX::SimpleMath::Matrix translation = DirectX::SimpleMath::Matrix::CreateTranslation(m_position);
	DirectX::SimpleMath::Matrix world = rotation * translation;

	// �x�[�V�b�N�G�t�F�N�g�̃p�����[�^��ݒ肷��
	m_basicEffectTexture->SetWorld(world);                    // ���[���h�s��
	m_basicEffectTexture->SetView(view);                    // �r���[�s��
	m_basicEffectTexture->SetProjection(projection);        // �ˉe�s��
	m_basicEffectTexture->SetTexture(m_texture.Get());        // �e�N�X�`��
	m_basicEffectTexture->Apply(m_context);                    // �x�[�V�b�N�G�t�F�N�g���X�V����

	// ���b�V����`��
	m_primitiveBatchTexture->Begin();
	m_primitiveBatchTexture->DrawIndexed(
		D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
		&m_indices[0],
		m_indices.size(),
		&m_verticesTexture[0],
		m_verticesTexture.size()
	);
	m_primitiveBatchTexture->End();
}

/// <summary>
/// ���b�V����Ray�̏Փ˔���
/// </summary>
bool NakashiLib::CollisionMesh::IntersectRay(
	const DirectX::SimpleMath::Ray& ray,
	DirectX::SimpleMath::Vector3* hitPosition,
	DirectX::SimpleMath::Vector3* normal,
	int* polygonNo
)
{
	assert(hitPosition);
	assert(normal);
	// �R���W�������b�V���̉�]����W��񂩂�Aworld�̋t�s������߂�
	DirectX::SimpleMath::Matrix rotation = DirectX::SimpleMath::Matrix::CreateFromQuaternion(m_rotation);
	DirectX::SimpleMath::Matrix transration = DirectX::SimpleMath::Matrix::CreateTranslation(m_position);
	DirectX::SimpleMath::Matrix world = rotation * transration;
	DirectX::SimpleMath::Matrix invertWorld = world.Invert();

	// ���C�ɃR���W�������b�V���̋t�s���������
	// �����C���R���W�������b�V���̃��[�J�����W�n�Ɏ����Ă���
	DirectX::SimpleMath::Ray unitRay{};
	unitRay.position = DirectX::SimpleMath::Vector3::Transform(ray.position, invertWorld);
	unitRay.direction = DirectX::SimpleMath::Vector3::Transform(ray.direction, invertWorld);

	// ���C�ƏՓ˓_�܂ł̋���
 	float distance = 0.0f;

	// �Փ˔���
	for (int i = 0; i < m_triangles.size(); i++)
	{
		//** ToDo::���炩�ɏՓ˂��Ȃ��ꍇ�͑������^�[������悤�ɕύX����

		// ���C�ƃ|���S���̏Փ˔�����Ƃ�
		if (unitRay.Intersects(
			m_triangles[i].triangle[0],
			m_triangles[i].triangle[1],
			m_triangles[i].triangle[2],
			distance
		)
	)
		{
			// �Փ˓_�̍��W���v�Z����
			*hitPosition = DirectX::SimpleMath::Vector3{ unitRay.position + unitRay.direction * distance };

			// �Փ˓_�����[���h���W�ɕϊ�����
			*hitPosition = DirectX::SimpleMath::Vector3::Transform(*hitPosition, world);

			// �|���S���̖@���ɃR���W�������b�V���̉�]������������
			*normal = DirectX::SimpleMath::Vector3::Transform(m_triangles[i].normal, m_rotation);

			// �Փ˂����|���S���ԍ�
			*polygonNo = i;

			return true;
		}
	}
	// �Փ˂��Ȃ�����
	return false;
}

/// <summary>
/// ���������|���S���̔ԍ����擾����
/// </summary>
/// <param name="hitPolygonNo">�|���S���̔ԍ�</param>
/// <returns></returns>
std::vector<DirectX::SimpleMath::Vector3> NakashiLib::CollisionMesh::GetHitPolygon(unsigned int hitPolygonNo)
{
	std::vector<DirectX::SimpleMath::Vector3> hitPolygon;
	hitPolygon.push_back(m_triangles[hitPolygonNo].triangle[0]);
	hitPolygon.push_back(m_triangles[hitPolygonNo].triangle[1]);
	hitPolygon.push_back(m_triangles[hitPolygonNo].triangle[2]);
	
	return hitPolygon;
}

/// <summary>
/// �I�u�W�F�`���̃t�@�C�������[�h����
/// </summary>
/// <param name="objName">�I�u�W�F�N�g�̖��O</param>
void NakashiLib::CollisionMesh::LoadObjFile(const std::wstring& objName)
{
	// Obj�`���̃t�@�C�����J��
	std::wstring fileName = L"Resources/Models/" + objName + L".obj";
	std::ifstream ifs(fileName);

	assert(ifs && ".obj�t�@�C�����ǂݍ��߂܂���ł���");

	// 1�s���Ƃɏ�������
	std::string line;
	while (getline(ifs, line))
	{
		// �ǂݎ�����P�s���̃f�[�^���X�g�����O�X�g���[���ň���
		std::stringstream iss(line);
		std::string type;

		// �擪�v�f���󂯎��
		iss >> type;

		// ���_�f�[�^���쐬����
		// ��Obj�f�[�^��vt,vn�����鎞������̂Œ��ӂ���
		if (type.compare("v") == 0)
		{
			DirectX::SimpleMath::Vector3 vec;
			iss >> vec.x >> vec.y >> vec.z;
			m_vertices.emplace_back(vec);
		}
		// �C���f�b�N�X�f�[�^���쐬����
		else if (type.compare("f") == 0)
		{
			int a, b, c;
			iss >> a >> b >> c;

			// �O�p�`�̒��_�C���f�b�N�X�ԍ������������܂ޏꍇ�͖�������F�R�_���قȂ�_���w���Ă���
			if (a != b && a != c && b != c)
			{
				m_indices.emplace_back(static_cast<uint16_t>(a - 1));
				m_indices.emplace_back(static_cast<uint16_t>(b - 1));
				m_indices.emplace_back(static_cast<uint16_t>(c - 1));
			}
		}
	}

	// �J�����t�@�C�������
	ifs.close();
}

/// <summary>
/// �O�p�`�|���S�����쐬���A�z��ɓo�^����
/// </summary>
/// <param name="a">�O�p�`�̒��_�P��</param>
/// <param name="b">�O�p�`�̒��_�Q��</param>
/// <param name="c">�O�p�`�̒��_�R��</param>
void NakashiLib::CollisionMesh::AddTriangle(
	DirectX::SimpleMath::Vector3 a,
	DirectX::SimpleMath::Vector3 b,
	DirectX::SimpleMath::Vector3 c
)
{
	m_triangles.emplace_back(Triangle(a, b, c));
}