//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/15
// <file>			CreateRay.h
// <概要>			ray作成用
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"pch.h"

namespace NakashiLib
{
	class CreateRay
	{
	private:
		// Rayのポジション用
		DirectX::SimpleMath::Vector3 m_rayPosition;

		// Ray
		DirectX::SimpleMath::Ray m_ray;

		// Ｙ軸方向の伸ばす長さ
		float m_length;

		// プリミティブバッチ
		std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_primitiveBatch;

	public:
		// コンストラクタとデストラクタ
		CreateRay();
		~CreateRay();

		// 初期化、更新、描画処理
		void Initialize(ID3D11DeviceContext* context, const float length);
		void Update( const DirectX::SimpleMath::Vector3& newPosition);
		void Render();

		// プロパティ
		// Ray取得
		const DirectX::SimpleMath::Ray GetRay() const { return m_ray; }
		// 長さ変更
		void SetLength(const float length) { m_length = length; }

	private:
		//　Rayを計算する
		void CalculateRay(const DirectX::SimpleMath::Vector3& position );
		
	};
}