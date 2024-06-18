#pragma once
#include"pch.h"
#include"SimpleMath.h"
#include"VertexTypes.h"
#include "DirectXHelpers.h"
#include "GeometricPrimitive.h"
#include "PrimitiveBatch.h"
#include "Effects.h"
#include "CommonStates.h"

class DisplayCollision
{
private:
	// �\���\�ȃR���W�����̍ő吔�i�f�t�H���g�j
	static const uint32_t DISPLAY_COLLISION_MAX = 10000;

	// �\���\�ȃR���W�����̍ő吔
	uint32_t m_collisionMax;

	// ���C���̕\��
	bool m_lineActive;

	// ���f���̕\��
	bool m_modelActive;


	// �����̏��
	struct LineSegment
	{
		DirectX::SimpleMath::Vector3 a;			// �n�_
		DirectX::SimpleMath::Vector3 b;			// �I�_
		DirectX::SimpleMath::Color lineColor;	// �F

		constexpr LineSegment(
			const DirectX::SimpleMath::Vector3& a,
			const DirectX::SimpleMath::Vector3& b,
			DirectX::SimpleMath::Color lineColor)
			noexcept :
			a(a) , b(b) , lineColor(lineColor){}
	};


	// ������Collision���
	std::vector<LineSegment> m_lineSegments;

	// �v���~�e�B�u�o�b�`�i���C���p�j
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_primitiveBatch;

	// �G�t�F�N�g	(���C���p�j
	std::unique_ptr<DirectX::BasicEffect> m_lineEffect;

	// ���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_lineInputLayout;

	// ���b�V���̏��
	struct Mesh
	{
		const std::vector<DirectX::VertexPosition>& vertexes;	// ���_�o�b�t�@
		const std::vector<uint16_t>& indexes;			// �C���f�b�N�X�o�b�t�@
		DirectX::SimpleMath::Vector3 position;			// �ړ�
		DirectX::SimpleMath::Quaternion rotate;			// ��]
		DirectX::SimpleMath::Color lineColor;			// �F�i���C���p�j

		constexpr Mesh(
			const std::vector<DirectX::VertexPosition>& vertexes,
			const std::vector<uint16_t>& indexes,
			const DirectX::SimpleMath::Vector3& position,
			const DirectX::SimpleMath::Quaternion& rotate,
			DirectX::SimpleMath::Color lineColor) noexcept
			: vertexes(vertexes), indexes(indexes), position(position), rotate(rotate), lineColor(lineColor) {}
	};

	// ���b�V���̃R���W�������
	std::vector<Mesh> m_meshes;

	// �G�t�F�N�g�i���b�V���p�j
	std::unique_ptr<DirectX::BasicEffect> m_meshEffect;

	// ���̓��C�A�E�g�i���b�V���p�j
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_meshInputLayout;

	// �v���~�e�B�u�o�b�`�i���b�V���p�j
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPosition>> m_meshBatch;



	// ���̏��
	struct Sphere
	{
		DirectX::SimpleMath::Vector3 center;	// ���S
		float radius;							// ���a
		DirectX::SimpleMath::Color lineColor;	// �F�i���C���p�j

		constexpr Sphere(
			const DirectX::SimpleMath::Vector3& center,
			float radius,
			DirectX::SimpleMath::Color lineColor) noexcept
			: center(center), radius(radius), lineColor(lineColor) {}
	};

	// �{�b�N�X�̏��
	struct Box
	{
		DirectX::SimpleMath::Vector3 center;	// ���S
		DirectX::SimpleMath::Vector3 extents;	// �e�ʂ̒��S����̋���.
		DirectX::SimpleMath::Quaternion rotate;	// ��]
		DirectX::SimpleMath::Color lineColor;	// �F�i���C���p�j

		constexpr Box(
			const DirectX::SimpleMath::Vector3& center,
			const DirectX::SimpleMath::Vector3& extents,
			const DirectX::SimpleMath::Quaternion& rotate,
			DirectX::SimpleMath::Color lineColor) noexcept
			: center(center), extents(extents), rotate(rotate), lineColor(lineColor) {}
	};

	// ���̃R���W�������
	std::vector<Sphere> m_spheres;

	// �{�b�N�X�̃R���W�������
	std::vector<Box> m_boxes;

	// ���̃��f��
	std::unique_ptr<DirectX::GeometricPrimitive> m_modelSphere;

	// �{�b�N�X�̃��f��
	std::unique_ptr<DirectX::GeometricPrimitive> m_modelBox;

	// �G�t�F�N�g�i���f���p�j
	std::unique_ptr<DirectX::NormalMapEffect> m_modelEffect;

	// ���̓��C�A�E�g�i���f���p�j
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_modelInputLayout;


	// �C���X�^���X�p���_�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_instancedVB;

private:

	// �R���W�������f���̕`��֐�
	void DrawCollisionModel(
		ID3D11DeviceContext* context,
		DirectX::CommonStates* states,
		const DirectX::SimpleMath::Matrix& view,
		const DirectX::SimpleMath::Matrix& proj,
		DirectX::FXMVECTOR color
	);

	// �R���W�������C���̕`��֐�
	void DrawCollisionLine(
		ID3D11DeviceContext* context,
		DirectX::CommonStates* states,
		const DirectX::SimpleMath::Matrix& view,
		const DirectX::SimpleMath::Matrix& proj,
		DirectX::FXMVECTOR color
	);

public:

	// �R���X�g���N�^
	DisplayCollision(
		ID3D11Device* device,
		ID3D11DeviceContext* context,
		bool modelActive = true,
		bool lineActive = true,
		uint32_t collisionMax = DISPLAY_COLLISION_MAX
	);

	// �o�^���ꂽ�R���W�����̕`��֐�
	void DrawCollision(
		ID3D11DeviceContext* context,
		DirectX::CommonStates* states,
		const DirectX::SimpleMath::Matrix& view,
		const DirectX::SimpleMath::Matrix& proj,
		DirectX::FXMVECTOR baseColor = DirectX::Colors::White,
		DirectX::FXMVECTOR lineColor = DirectX::XMVECTORF32{ 0.0f,0.0f,0.0f,0.0f },
		float alpha = 0.5f
	);

	// ������o�^����֐�
	void AddLineSegment(
		DirectX::SimpleMath::Vector3 a,
		DirectX::SimpleMath::Vector3 b,
		DirectX::FXMVECTOR lineColor = DirectX::XMVECTORF32{ 0.0f,0.0f,0.0f,0.0f })
	{
		m_lineSegments.push_back(LineSegment(a, b, lineColor));
	}

	// ���b�V���̃R���W������o�^����֐�
	void AddBoundingVolume(
		const std::vector<DirectX::VertexPosition>& vertexes,
		const std::vector<uint16_t>& indexes,
		DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Quaternion rotate,
		DirectX::FXMVECTOR lineColor = DirectX::XMVECTORF32{ 0.0f, 0.0f, 0.0f, 0.0f }
	)
	{
		m_meshes.push_back(Mesh(vertexes, indexes, position, rotate, lineColor));
	}

	// ���̃R���W������o�^����֐�
	void AddBoundingVolume(
		DirectX::BoundingSphere shpere,
		DirectX::FXMVECTOR lineColor = DirectX::XMVECTORF32{ 0.0f, 0.0f, 0.0f, 0.0f })
	{
		DirectX::XMFLOAT3 center = shpere.Center;
		m_spheres.push_back(Sphere(center, shpere.Radius, lineColor));
	}

	// �{�b�N�X�̃R���W������o�^����֐�
	void AddBoundingVolume(
		DirectX::BoundingBox box,
		DirectX::FXMVECTOR lineColor = DirectX::XMVECTORF32{ 0.0f, 0.0f, 0.0f, 0.0f })
	{
		m_boxes.push_back(Box(box.Center, box.Extents, DirectX::SimpleMath::Quaternion(), lineColor));
	}

	// ��]�����{�b�N�X�̃R���W������o�^����֐�
	void AddBoundingVolume(
		DirectX::BoundingOrientedBox box,
		DirectX::FXMVECTOR lineColor = DirectX::XMVECTORF32{ 0.0f, 0.0f, 0.0f, 0.0f })
	{
		m_boxes.push_back(Box(box.Center, box.Extents, DirectX::SimpleMath::Quaternion(box.Orientation), lineColor));
	}

	// �R���W�������C���̕\�� (ON/OFF)
	void SetLineActive(bool active) { m_lineActive = active; }

	// �R���W�������f���̕\���iON/OFF)
	void SetModelActive(bool active) { m_modelActive = active; }

};
