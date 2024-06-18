#pragma once
#include"pch.h"
#include"Game/Collision/Collision.h"
#include"Game/Collision/DisplayCollision.h"

class ObjMeshCollision
{
private:

	// �ʒu
	DirectX::SimpleMath::Vector3 m_position;

	// ��]
	DirectX::SimpleMath::Quaternion m_rotation;

private:

	// ���_���
	std::vector<DirectX::VertexPosition> m_vertexes;

	// �C���f�b�N�X���
	std::vector<uint16_t> m_indexes;

	// �R���W�����p�O�p�`�f�[�^
	std::vector<Collision::Triangle> m_triangles;

	// �R���W�����p�O�p�`�f�[�^�̒ǉ��֐�
	void AddTriangle(DirectX::XMFLOAT3 a, DirectX::XMFLOAT3 b, DirectX::XMFLOAT3 c);

public:

	// �R���X�g���N�^
	ObjMeshCollision(const wchar_t* filename);

	// �R���W�������̍X�V
	void UpdateBoundingInfo(const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& rotate);

	// �����Ƃ̌�������֐�
	bool IntersectLineSegment(
		DirectX::SimpleMath::Vector3 a,
		DirectX::SimpleMath::Vector3 b,
		DirectX::SimpleMath::Vector3* hitPosition,
		DirectX::SimpleMath::Vector3* normal = nullptr
	);

	// �Փ˔���̕\���ɓo�^����֐�
	void AddDisplayCollision(DisplayCollision* displayCollision, DirectX::FXMVECTOR lineColor = DirectX::XMVECTORF32{ 0.0f, 0.0f, 0.0f, 0.0f }) const;
};