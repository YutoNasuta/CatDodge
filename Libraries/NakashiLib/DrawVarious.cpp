//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/02/04
// <file>			DrawVarious.h
// <�T�v>			�l�X�ȕ`����@
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include"pch.h"
#include"DrawVarious.h"
#include<cassert>

/// <summary>
/// �O�p�`�̕`��
/// </summary>
/// <param name="batch">�v���~�e�B�u�o�b�`�擾</param>
/// <param name="v1">���_</param>
/// <param name="v2">���_</param>
/// <param name="v3">���_</param>
/// <param name="color">�F</param>
void NakashiLib::DrawVarious::DrawTriangle(
	DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* batch,
	const DirectX::SimpleMath::Vector3& v1,
	const DirectX::SimpleMath::Vector3& v2,
	const DirectX::SimpleMath::Vector3& v3,
	const DirectX::XMVECTOR& color
)
{
	assert(batch);

	batch->DrawLine(DirectX::VertexPositionColor(v1, color), DirectX::VertexPositionColor(v2, color));
	batch->DrawLine(DirectX::VertexPositionColor(v2, color), DirectX::VertexPositionColor(v3, color));
	batch->DrawLine(DirectX::VertexPositionColor(v3, color), DirectX::VertexPositionColor(v1, color));

}

/// <summary>
/// �_�̕`��
/// </summary>
/// <param name="batch">�v���~�e�B�u�o�b�`</param>
/// <param name="center">�^��</param>
/// <param name="color">�F</param>
void NakashiLib::DrawVarious::DrawPoint(
	DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* batch,
	const DirectX::SimpleMath::Vector3& center,
	const DirectX::XMVECTOR& color
)
{
	assert(batch);

	const int   DIVS = 16;					// ������
	const int   NUM_VERTICES = DIVS + 1;	// ���_��
	const float POINT_SIZE = 0.1f;			// �_�̑傫��    

	DirectX::VertexPositionColor vertices[NUM_VERTICES];	// ���_�o�b�t�@
	uint16_t indices[DIVS * 3];					// �C���f�b�N�X�o�b�t�@


	// �C���f�b�N�X�e�[�u��
	for (uint16_t i = 0; i < DIVS; i++)
	{
		indices[i * 3 + 0] = 0;		// ��ɒ��S�_
		indices[i * 3 + 1] = i + 2;	// �A CullCounterClockwise
		indices[i * 3 + 2] = i + 1;
	}
	indices[(DIVS - 1) * 3 + 1] = indices[2];	// �A CullCounterClockwise



	// ���S�_�̐ݒ�
	XMStoreFloat3(&vertices[0].position, center);
	XMStoreFloat4(&vertices[0].color, color);

	// �O���̒��_�̐ݒ�
	for (int i = 1; i < NUM_VERTICES; i++)
	{
		vertices[i].position.x = center.x + POINT_SIZE * cosf(DirectX::XM_2PI / DIVS * i);
		vertices[i].position.y = center.y + POINT_SIZE * sinf(DirectX::XM_2PI / DIVS * i);
		vertices[i].position.z = 0.0f;
		XMStoreFloat4(&vertices[i].color, color);
	}

	batch->DrawIndexed(
		D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
		indices,
		DIVS * 3,
		vertices,
		NUM_VERTICES
	);


}
/// <summary>
/// ���̕`��
/// </summary>
/// <param name="batch">�v���~�e�B�u�o�b�`</param>
/// <param name="start">�n�_</param>
/// <param name="end">�I�_</param>
/// <param name="color">�F</param>
void NakashiLib::DrawVarious::DrawLine(
	DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* batch,
	const DirectX::SimpleMath::Vector3& start,
	const DirectX::SimpleMath::Vector3& end,
	const DirectX::XMVECTOR& color
)
{
	assert(batch);
	batch->DrawLine(DirectX::VertexPositionColor(start, color),
		DirectX::VertexPositionColor(end, color));
}

/// <summary>
/// �x�N�g���̕`��
/// </summary>
/// <param name="batch">�v���~�e�B�u�o�b�`</param>
/// <param name="start">�n�_</param>
/// <param name="end">�I�_</param>
/// <param name="color">�F</param>
void NakashiLib::DrawVarious::DrawVector(
	DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* batch,
	const DirectX::SimpleMath::Vector3& start,
	const DirectX::SimpleMath::Vector3& end,
	const DirectX::FXMVECTOR& color
)
{
	assert(batch);

	// ���[�J���ϐ����`����
	DirectX::SimpleMath::Matrix mat;
	DirectX::SimpleMath::Vector3 v1, v2, vec;	// �H�̏I�_�A�H�̎n�_�A�H

	// start�x�N�g�����u-end�v���s�ړ�����
	mat = DirectX::SimpleMath::Matrix::CreateTranslation(-end);
	v1 = DirectX::SimpleMath::Vector3::Transform(start, mat);

	// end�x�N�g�������_�Ɉړ�����
	mat = DirectX::SimpleMath::Matrix::CreateTranslation(-end);
	v2 = DirectX::SimpleMath::Vector3::Transform(end, mat);

	// �x�N�g���̉H�ɂȂ镔���̌��^���쐬����Fend����start�Ɍ������x�N�g��
	vec = v1 - v2;
	// �H�̌��^�����𐳋K������
	vec.Normalize();

	// �H�̑傫�������߂�
	vec *= 0.5f;

	// �E�̉H�����
	mat = DirectX::SimpleMath::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(30.0f));
	DirectX::SimpleMath::Vector3 right = DirectX::SimpleMath::Vector3::Transform(vec, mat);

	// �E�̉H�𐳂����ʒu�ɔz�u����
	mat = DirectX::SimpleMath::Matrix::CreateTranslation(end);
	right = DirectX::SimpleMath::Vector3::Transform(right, mat);

	// ���̉H�����
	mat = DirectX::SimpleMath::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(-30.0f));
	DirectX::SimpleMath::Vector3 left = DirectX::SimpleMath::Vector3::Transform(vec, mat);

	// ���̉H�𐳂����ʒu�ɔz�u����
	mat = DirectX::SimpleMath::Matrix::CreateTranslation(end);
	left = DirectX::SimpleMath::Vector3::Transform(left, mat);

	// �x�N�g����`�悷��
	DrawLine(batch, end, right, color);	// �E�̉H
	DrawLine(batch, end, left, color);	// ���̉H
	DrawLine(batch, start, end, color);	// ���S��
}

/// <summary>
/// �~�̕`��
/// </summary>
/// <param name="batch">�v���~�e�B�u�o�b�`</param>
/// <param name="center">����</param>
/// <param name="radius">���a</param>
/// <param name="color">�F</param>
/// <param name="divs">����</param>
void NakashiLib::DrawVarious::DrawCircle(
	DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* batch,
	const DirectX::SimpleMath::Vector3& center,
	float radius,
	const DirectX::FXMVECTOR& color,
	int divs
)
{
	assert(batch);

	DirectX::SimpleMath::Vector3 pos[2];	// [0]�F�n�_�A[1]�F�I�_
	float angle = 0.0f;

	pos[1] = DirectX::SimpleMath::Vector3(cosf(angle), sinf(angle), 0.0f) * radius + center;
	for (int i = 0; i < divs; i++)
	{
		pos[0] = pos[1];
		angle += DirectX::XM_2PI / static_cast<float>(divs);
		pos[1] = DirectX::SimpleMath::Vector3(cosf(angle), sinf(angle), 0.0f) * radius + center;
		DrawLine(batch, pos[0], pos[1], color);
	}
}