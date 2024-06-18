//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/15
// <file>			CreateRay.cpp
// <概要>			ray作成用
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"CreateRay.h"
#include "Libraries/NakashiLib/DrawVarious.h"

/// <summary>
/// コンストラクタ
/// </summary>
NakashiLib::CreateRay::CreateRay()
	:
	m_rayPosition{},
	m_ray{},
	m_length{}
{

}

/// <summary>
/// デストラクタ
/// </summary>
NakashiLib::CreateRay::~CreateRay()
{

}

/// <summary>
/// 初期化
/// </summary>
/// <param name="context">デバイスコンテキスト</param>
/// <param name="length">長さ</param>
void NakashiLib::CreateRay::Initialize(ID3D11DeviceContext* context, const float length)
{
	m_primitiveBatch = 
		std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>>(context);
	m_length = length;

}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="newPosition">ポジション設定</param>
void NakashiLib::CreateRay::Update(const DirectX::SimpleMath::Vector3& newPosition)
{
	// ポジションを変更させる
	m_rayPosition.x = newPosition.x;
	m_rayPosition.z = newPosition.z;

	// Rayのポジションを変更させる用
	 m_rayPosition.y += m_length;

	// Rayの計算をする
	CalculateRay(m_rayPosition);
}

/// <summary>
/// 描画
/// </summary>
void NakashiLib::CreateRay::Render()
{
	m_primitiveBatch->Begin();
	auto draw = std::make_unique<NakashiLib::DrawVarious>();
		draw->DrawVector(
		m_primitiveBatch.get(),
			DirectX::SimpleMath::Vector3(m_rayPosition.x , m_length , m_rayPosition.z),
		DirectX::SimpleMath::Vector3(m_rayPosition.x, -m_length, m_rayPosition.z),
		DirectX::Colors::Red);
	m_primitiveBatch->End();
}

/// <summary>
/// Rayの計算
/// </summary>
/// <param name="position">Rayの位置</param>
void NakashiLib::CreateRay::CalculateRay(const DirectX::SimpleMath::Vector3& position)
{
	m_ray = DirectX::SimpleMath::Ray{ position , DirectX::SimpleMath::Vector3::Down };
}
