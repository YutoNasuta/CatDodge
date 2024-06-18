//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/02/04
// <file>			DrawVarious.h
// <概要>			様々な描画方法
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include"pch.h"
#include"DrawVarious.h"
#include<cassert>

/// <summary>
/// 三角形の描画
/// </summary>
/// <param name="batch">プリミティブバッチ取得</param>
/// <param name="v1">頂点</param>
/// <param name="v2">頂点</param>
/// <param name="v3">頂点</param>
/// <param name="color">色</param>
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
/// 点の描画
/// </summary>
/// <param name="batch">プリミティブバッチ</param>
/// <param name="center">真ん中</param>
/// <param name="color">色</param>
void NakashiLib::DrawVarious::DrawPoint(
	DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* batch,
	const DirectX::SimpleMath::Vector3& center,
	const DirectX::XMVECTOR& color
)
{
	assert(batch);

	const int   DIVS = 16;					// 分割数
	const int   NUM_VERTICES = DIVS + 1;	// 頂点数
	const float POINT_SIZE = 0.1f;			// 点の大きさ    

	DirectX::VertexPositionColor vertices[NUM_VERTICES];	// 頂点バッファ
	uint16_t indices[DIVS * 3];					// インデックスバッファ


	// インデックステーブル
	for (uint16_t i = 0; i < DIVS; i++)
	{
		indices[i * 3 + 0] = 0;		// 常に中心点
		indices[i * 3 + 1] = i + 2;	// ② CullCounterClockwise
		indices[i * 3 + 2] = i + 1;
	}
	indices[(DIVS - 1) * 3 + 1] = indices[2];	// ② CullCounterClockwise



	// 中心点の設定
	XMStoreFloat3(&vertices[0].position, center);
	XMStoreFloat4(&vertices[0].color, color);

	// 外周の頂点の設定
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
/// 線の描画
/// </summary>
/// <param name="batch">プリミティブバッチ</param>
/// <param name="start">始点</param>
/// <param name="end">終点</param>
/// <param name="color">色</param>
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
/// ベクトルの描画
/// </summary>
/// <param name="batch">プリミティブバッチ</param>
/// <param name="start">始点</param>
/// <param name="end">終点</param>
/// <param name="color">色</param>
void NakashiLib::DrawVarious::DrawVector(
	DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* batch,
	const DirectX::SimpleMath::Vector3& start,
	const DirectX::SimpleMath::Vector3& end,
	const DirectX::FXMVECTOR& color
)
{
	assert(batch);

	// ローカル変数を定義する
	DirectX::SimpleMath::Matrix mat;
	DirectX::SimpleMath::Vector3 v1, v2, vec;	// 羽の終点、羽の始点、羽

	// startベクトルを「-end」平行移動する
	mat = DirectX::SimpleMath::Matrix::CreateTranslation(-end);
	v1 = DirectX::SimpleMath::Vector3::Transform(start, mat);

	// endベクトルを原点に移動する
	mat = DirectX::SimpleMath::Matrix::CreateTranslation(-end);
	v2 = DirectX::SimpleMath::Vector3::Transform(end, mat);

	// ベクトルの羽になる部分の原型を作成する：endからstartに向かうベクトル
	vec = v1 - v2;
	// 羽の原型部分を正規化する
	vec.Normalize();

	// 羽の大きさを決める
	vec *= 0.5f;

	// 右の羽を作る
	mat = DirectX::SimpleMath::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(30.0f));
	DirectX::SimpleMath::Vector3 right = DirectX::SimpleMath::Vector3::Transform(vec, mat);

	// 右の羽を正しい位置に配置する
	mat = DirectX::SimpleMath::Matrix::CreateTranslation(end);
	right = DirectX::SimpleMath::Vector3::Transform(right, mat);

	// 左の羽を作る
	mat = DirectX::SimpleMath::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(-30.0f));
	DirectX::SimpleMath::Vector3 left = DirectX::SimpleMath::Vector3::Transform(vec, mat);

	// 左の羽を正しい位置に配置する
	mat = DirectX::SimpleMath::Matrix::CreateTranslation(end);
	left = DirectX::SimpleMath::Vector3::Transform(left, mat);

	// ベクトルを描画する
	DrawLine(batch, end, right, color);	// 右の羽
	DrawLine(batch, end, left, color);	// 左の羽
	DrawLine(batch, start, end, color);	// 中心線
}

/// <summary>
/// 円の描画
/// </summary>
/// <param name="batch">プリミティブバッチ</param>
/// <param name="center">中央</param>
/// <param name="radius">半径</param>
/// <param name="color">色</param>
/// <param name="divs">分割</param>
void NakashiLib::DrawVarious::DrawCircle(
	DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* batch,
	const DirectX::SimpleMath::Vector3& center,
	float radius,
	const DirectX::FXMVECTOR& color,
	int divs
)
{
	assert(batch);

	DirectX::SimpleMath::Vector3 pos[2];	// [0]：始点、[1]：終点
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