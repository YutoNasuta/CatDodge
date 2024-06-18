//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/13
// <file>			MousePoint.cpp
// <概要>			メッシュの当たり判定用
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"pch.h"

namespace NakashiLib
{
	class CollisionMesh
	{
	public:
		// 線分と三角形の交差判定用
		struct Triangle
		{
			DirectX::SimpleMath::Vector3 triangle[3];	// 頂点座標
			DirectX::SimpleMath::Vector3 normal;		// 法線

			Triangle(
				DirectX::SimpleMath::Vector3 a,
				DirectX::SimpleMath::Vector3 b,
				DirectX::SimpleMath::Vector3 c
			)
			{
				// ポリゴン
				triangle[0] = a;
				triangle[1] = b;
				triangle[2] = c;

				// 法線
				DirectX::SimpleMath::Vector3 ab = triangle[1] - triangle[0];
				DirectX::SimpleMath::Vector3 ac = triangle[2] - triangle[0];
				normal = ab.Cross(ac);	// 右手座標系でポリゴンの頂点が反時計回りの時
			}

			//文献
			// 平面計算サイト
			//https://keisan.casio.jp/exec/system/1202458197#:~:text=%EF%BC%93%E7%82%B9A%E3%80%81B%E3%80%81C,d%3D0%20%E3%82%92%E6%B1%82%E3%82%81%E3%81%BE%E3%81%99%E3%80%82&text=%E3%83%99%E3%82%AF%E3%83%88%E3%83%ABAB%E3%81%A8%E3%83%99%E3%82%AF%E3%83%88%E3%83%ABAC,%E5%AE%9A%E6%95%B0%E9%83%A8%E5%88%86%E3%81%8C%E5%B0%8E%E5%87%BA%E3%81%A7%E3%81%8D%E3%82%8B%E3%80%82&text=%E5%BA%83%E7%BE%A9%E5%9B%BA%E6%9C%89%E7%A9%BA%E9%96%93%E3%82%92%E6%B1%82%E3%82%81%E3%82%8B%E3%81%9F%E3%82%81%E3%80%82
			// 法線ベクトルとスムージング角
			//http://tegetegeosprey.g1.xrea.com/opengl/opengl_normalvecotr.htm

		};

	private:
		// 座標、回転、頂点情報配列、頂点インデックス配列、ポリゴン配列
		DirectX::SimpleMath::Vector3 m_position;
		DirectX::SimpleMath::Quaternion m_rotation;
		std::vector<DirectX::VertexPosition> m_vertices;
		std::vector<DirectX::VertexPositionTexture> m_verticesTexture;
		std::vector<uint16_t> m_indices;
		std::vector<Triangle> m_triangles;
		ID3D11DeviceContext* m_context;

		// メッシュ描画用オブジェクト
		Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
		std::unique_ptr<DirectX::BasicEffect> m_basicEffect;
		std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPosition>> m_primitiveBatch;

		// テクスチャ描画用オブジェクト
		Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayoutTexture;
		std::unique_ptr<DirectX::BasicEffect> m_basicEffectTexture;
		std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>> m_primitiveBatchTexture;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;

	public:
		CollisionMesh();
		~CollisionMesh() = default;

		// メッシュオブジェクトを作成
		void InitializeObject(
			ID3D11Device* devie,
			ID3D11DeviceContext* context,
			const std::wstring& objName);

		// 頂点情報のワイヤーフレーム初期化
		void InitializeVertexMesh(
			ID3D11Device* device,
			ID3D11DeviceContext* context,
			const std::vector<DirectX::VertexPosition>& vertices,
			const std::vector<uint16_t>& indices
		);
		// テクスチャ用の初期化
		void InitializeVertexMeshTexture(
			ID3D11Device* device,
			ID3D11DeviceContext* context,
			const std::vector<DirectX::VertexPositionTexture>& vertices,
			const std::vector<uint16_t>& indices
		);

		// メッシュデータをワイヤーフレームで描画
		void DrawMesh(
			DirectX::CommonStates* states,
			const DirectX::SimpleMath::Matrix& view,
			const DirectX::SimpleMath::Matrix& projection);

		// テクスチャを貼った状態で描画
		void DrawMeshTexture(
			DirectX::CommonStates* states,
			const DirectX::SimpleMath::Matrix& view,
			const DirectX::SimpleMath::Matrix& projection);

		// メッシュとRayの衝突判定
		bool IntersectRay(
			const DirectX::SimpleMath::Ray& ray,
			DirectX::SimpleMath::Vector3* hitPosition,
			DirectX::SimpleMath::Vector3* normal,
			int* polygonNo);

		// 衝突したポリゴンの頂点情報を返す
		std::vector<DirectX::SimpleMath::Vector3> GetHitPolygon(unsigned int hitPolygonNo);

	private:
		// objファイルをロードする
		void LoadObjFile(const std::wstring& objName);

		// ポリゴンを作り配列に登録
		void AddTriangle(
			DirectX::SimpleMath::Vector3 a,
			DirectX::SimpleMath::Vector3 b,
			DirectX::SimpleMath::Vector3 c
		);
	};
}