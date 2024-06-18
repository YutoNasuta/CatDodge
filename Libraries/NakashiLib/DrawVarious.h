//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/02/04
// <file>			DrawVarious.h
// <概要>			様々な描画方法
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"pch.h"

namespace NakashiLib
{
	class DrawVarious
	{
	public:
		// 三角形を描く
		void DrawTriangle(
			DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* batch,
			const DirectX::SimpleMath::Vector3& v1,
			const DirectX::SimpleMath::Vector3& v2,
			const DirectX::SimpleMath::Vector3& v3,
			const DirectX::XMVECTOR& color = DirectX::Colors::White
		);

		// 点を描画する
		void DrawPoint(
			DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* batch,
			const DirectX::SimpleMath::Vector3& center,
			const DirectX::XMVECTOR& color = DirectX::Colors::White
		);

		// 線を引く
		void DrawLine(
			DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* batch,
			const DirectX::SimpleMath::Vector3& v1,
			const DirectX::SimpleMath::Vector3& v2,
			const DirectX::XMVECTOR& color = DirectX::Colors::White
		);

		// ベクトルを描く
		void DrawVector(
			DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* batch,
			const DirectX::SimpleMath::Vector3& start,
			const DirectX::SimpleMath::Vector3& end,
			const DirectX::FXMVECTOR& color = DirectX::Colors::White
		);

		// 円を描く
		void DrawCircle(
			DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* batch,
			const DirectX::SimpleMath::Vector3& center,
			float radius,
			const DirectX::FXMVECTOR& color = DirectX::Colors::White,
			int divs = 32
		);

	};
}