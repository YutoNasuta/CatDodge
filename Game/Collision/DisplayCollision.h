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
	// 表示可能なコリジョンの最大数（デフォルト）
	static const uint32_t DISPLAY_COLLISION_MAX = 10000;

	// 表示可能なコリジョンの最大数
	uint32_t m_collisionMax;

	// ラインの表示
	bool m_lineActive;

	// モデルの表示
	bool m_modelActive;


	// 線分の情報
	struct LineSegment
	{
		DirectX::SimpleMath::Vector3 a;			// 始点
		DirectX::SimpleMath::Vector3 b;			// 終点
		DirectX::SimpleMath::Color lineColor;	// 色

		constexpr LineSegment(
			const DirectX::SimpleMath::Vector3& a,
			const DirectX::SimpleMath::Vector3& b,
			DirectX::SimpleMath::Color lineColor)
			noexcept :
			a(a) , b(b) , lineColor(lineColor){}
	};


	// 線分のCollision情報
	std::vector<LineSegment> m_lineSegments;

	// プリミティブバッチ（ライン用）
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_primitiveBatch;

	// エフェクト	(ライン用）
	std::unique_ptr<DirectX::BasicEffect> m_lineEffect;

	// 入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_lineInputLayout;

	// メッシュの情報
	struct Mesh
	{
		const std::vector<DirectX::VertexPosition>& vertexes;	// 頂点バッファ
		const std::vector<uint16_t>& indexes;			// インデックスバッファ
		DirectX::SimpleMath::Vector3 position;			// 移動
		DirectX::SimpleMath::Quaternion rotate;			// 回転
		DirectX::SimpleMath::Color lineColor;			// 色（ライン用）

		constexpr Mesh(
			const std::vector<DirectX::VertexPosition>& vertexes,
			const std::vector<uint16_t>& indexes,
			const DirectX::SimpleMath::Vector3& position,
			const DirectX::SimpleMath::Quaternion& rotate,
			DirectX::SimpleMath::Color lineColor) noexcept
			: vertexes(vertexes), indexes(indexes), position(position), rotate(rotate), lineColor(lineColor) {}
	};

	// メッシュのコリジョン情報
	std::vector<Mesh> m_meshes;

	// エフェクト（メッシュ用）
	std::unique_ptr<DirectX::BasicEffect> m_meshEffect;

	// 入力レイアウト（メッシュ用）
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_meshInputLayout;

	// プリミティブバッチ（メッシュ用）
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPosition>> m_meshBatch;



	// 球の情報
	struct Sphere
	{
		DirectX::SimpleMath::Vector3 center;	// 中心
		float radius;							// 半径
		DirectX::SimpleMath::Color lineColor;	// 色（ライン用）

		constexpr Sphere(
			const DirectX::SimpleMath::Vector3& center,
			float radius,
			DirectX::SimpleMath::Color lineColor) noexcept
			: center(center), radius(radius), lineColor(lineColor) {}
	};

	// ボックスの情報
	struct Box
	{
		DirectX::SimpleMath::Vector3 center;	// 中心
		DirectX::SimpleMath::Vector3 extents;	// 各面の中心からの距離.
		DirectX::SimpleMath::Quaternion rotate;	// 回転
		DirectX::SimpleMath::Color lineColor;	// 色（ライン用）

		constexpr Box(
			const DirectX::SimpleMath::Vector3& center,
			const DirectX::SimpleMath::Vector3& extents,
			const DirectX::SimpleMath::Quaternion& rotate,
			DirectX::SimpleMath::Color lineColor) noexcept
			: center(center), extents(extents), rotate(rotate), lineColor(lineColor) {}
	};

	// 球のコリジョン情報
	std::vector<Sphere> m_spheres;

	// ボックスのコリジョン情報
	std::vector<Box> m_boxes;

	// 球のモデル
	std::unique_ptr<DirectX::GeometricPrimitive> m_modelSphere;

	// ボックスのモデル
	std::unique_ptr<DirectX::GeometricPrimitive> m_modelBox;

	// エフェクト（モデル用）
	std::unique_ptr<DirectX::NormalMapEffect> m_modelEffect;

	// 入力レイアウト（モデル用）
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_modelInputLayout;


	// インスタンス用頂点バッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_instancedVB;

private:

	// コリジョンモデルの描画関数
	void DrawCollisionModel(
		ID3D11DeviceContext* context,
		DirectX::CommonStates* states,
		const DirectX::SimpleMath::Matrix& view,
		const DirectX::SimpleMath::Matrix& proj,
		DirectX::FXMVECTOR color
	);

	// コリジョンラインの描画関数
	void DrawCollisionLine(
		ID3D11DeviceContext* context,
		DirectX::CommonStates* states,
		const DirectX::SimpleMath::Matrix& view,
		const DirectX::SimpleMath::Matrix& proj,
		DirectX::FXMVECTOR color
	);

public:

	// コンストラクタ
	DisplayCollision(
		ID3D11Device* device,
		ID3D11DeviceContext* context,
		bool modelActive = true,
		bool lineActive = true,
		uint32_t collisionMax = DISPLAY_COLLISION_MAX
	);

	// 登録されたコリジョンの描画関数
	void DrawCollision(
		ID3D11DeviceContext* context,
		DirectX::CommonStates* states,
		const DirectX::SimpleMath::Matrix& view,
		const DirectX::SimpleMath::Matrix& proj,
		DirectX::FXMVECTOR baseColor = DirectX::Colors::White,
		DirectX::FXMVECTOR lineColor = DirectX::XMVECTORF32{ 0.0f,0.0f,0.0f,0.0f },
		float alpha = 0.5f
	);

	// 線分を登録する関数
	void AddLineSegment(
		DirectX::SimpleMath::Vector3 a,
		DirectX::SimpleMath::Vector3 b,
		DirectX::FXMVECTOR lineColor = DirectX::XMVECTORF32{ 0.0f,0.0f,0.0f,0.0f })
	{
		m_lineSegments.push_back(LineSegment(a, b, lineColor));
	}

	// メッシュのコリジョンを登録する関数
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

	// 球のコリジョンを登録する関数
	void AddBoundingVolume(
		DirectX::BoundingSphere shpere,
		DirectX::FXMVECTOR lineColor = DirectX::XMVECTORF32{ 0.0f, 0.0f, 0.0f, 0.0f })
	{
		DirectX::XMFLOAT3 center = shpere.Center;
		m_spheres.push_back(Sphere(center, shpere.Radius, lineColor));
	}

	// ボックスのコリジョンを登録する関数
	void AddBoundingVolume(
		DirectX::BoundingBox box,
		DirectX::FXMVECTOR lineColor = DirectX::XMVECTORF32{ 0.0f, 0.0f, 0.0f, 0.0f })
	{
		m_boxes.push_back(Box(box.Center, box.Extents, DirectX::SimpleMath::Quaternion(), lineColor));
	}

	// 回転したボックスのコリジョンを登録する関数
	void AddBoundingVolume(
		DirectX::BoundingOrientedBox box,
		DirectX::FXMVECTOR lineColor = DirectX::XMVECTORF32{ 0.0f, 0.0f, 0.0f, 0.0f })
	{
		m_boxes.push_back(Box(box.Center, box.Extents, DirectX::SimpleMath::Quaternion(box.Orientation), lineColor));
	}

	// コリジョンラインの表示 (ON/OFF)
	void SetLineActive(bool active) { m_lineActive = active; }

	// コリジョンモデルの表示（ON/OFF)
	void SetModelActive(bool active) { m_modelActive = active; }

};
