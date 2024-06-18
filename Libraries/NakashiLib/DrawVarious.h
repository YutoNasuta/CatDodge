//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/02/04
// <file>			DrawVarious.h
// <�T�v>			�l�X�ȕ`����@
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"pch.h"

namespace NakashiLib
{
	class DrawVarious
	{
	public:
		// �O�p�`��`��
		void DrawTriangle(
			DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* batch,
			const DirectX::SimpleMath::Vector3& v1,
			const DirectX::SimpleMath::Vector3& v2,
			const DirectX::SimpleMath::Vector3& v3,
			const DirectX::XMVECTOR& color = DirectX::Colors::White
		);

		// �_��`�悷��
		void DrawPoint(
			DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* batch,
			const DirectX::SimpleMath::Vector3& center,
			const DirectX::XMVECTOR& color = DirectX::Colors::White
		);

		// ��������
		void DrawLine(
			DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* batch,
			const DirectX::SimpleMath::Vector3& v1,
			const DirectX::SimpleMath::Vector3& v2,
			const DirectX::XMVECTOR& color = DirectX::Colors::White
		);

		// �x�N�g����`��
		void DrawVector(
			DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* batch,
			const DirectX::SimpleMath::Vector3& start,
			const DirectX::SimpleMath::Vector3& end,
			const DirectX::FXMVECTOR& color = DirectX::Colors::White
		);

		// �~��`��
		void DrawCircle(
			DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* batch,
			const DirectX::SimpleMath::Vector3& center,
			float radius,
			const DirectX::FXMVECTOR& color = DirectX::Colors::White,
			int divs = 32
		);

	};
}