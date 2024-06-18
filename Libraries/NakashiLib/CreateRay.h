//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/15
// <file>			CreateRay.h
// <�T�v>			ray�쐬�p
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"pch.h"

namespace NakashiLib
{
	class CreateRay
	{
	private:
		// Ray�̃|�W�V�����p
		DirectX::SimpleMath::Vector3 m_rayPosition;

		// Ray
		DirectX::SimpleMath::Ray m_ray;

		// �x�������̐L�΂�����
		float m_length;

		// �v���~�e�B�u�o�b�`
		std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_primitiveBatch;

	public:
		// �R���X�g���N�^�ƃf�X�g���N�^
		CreateRay();
		~CreateRay();

		// �������A�X�V�A�`�揈��
		void Initialize(ID3D11DeviceContext* context, const float length);
		void Update( const DirectX::SimpleMath::Vector3& newPosition);
		void Render();

		// �v���p�e�B
		// Ray�擾
		const DirectX::SimpleMath::Ray GetRay() const { return m_ray; }
		// �����ύX
		void SetLength(const float length) { m_length = length; }

	private:
		//�@Ray���v�Z����
		void CalculateRay(const DirectX::SimpleMath::Vector3& position );
		
	};
}