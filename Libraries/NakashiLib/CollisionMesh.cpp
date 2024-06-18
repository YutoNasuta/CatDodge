//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/13
// <file>			MousePoint.cpp
// <概要>			メッシュの当たり判定用
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include "pch.h"
#include "CollisionMesh.h"
#include <iostream>
#include <fstream>
#include <sstream>

// VertexPositionTexture の定義


/// <summary>
/// コンストラクタ
/// </summary>
NakashiLib::CollisionMesh::CollisionMesh()
	:
	m_position{},
	m_rotation{},
	m_vertices{},
	m_indices{},
	m_triangles{},
	m_inputLayout{},
	m_basicEffect{},
	m_primitiveBatch{},
	m_basicEffectTexture{},
	m_texture{},
	m_verticesTexture{},
	m_inputLayoutTexture{},
	m_primitiveBatchTexture{},
	m_context{}
{

}

/// <summary>
/// 初期化する
/// </summary>
void NakashiLib::CollisionMesh::InitializeObject(
	ID3D11Device* device,
	ID3D11DeviceContext* context,
	const std::wstring& objName
)
{
	assert(device);
	assert(context);
	m_context = context;

	// objファイルのよみこみ
	LoadObjFile(objName);

	// ポリゴン配列の作成
	for (size_t i = 0; i < m_indices.size() / 3; i++)
	{
		AddTriangle(
			m_vertices[m_indices[i * 3 + 0]].position,
			m_vertices[m_indices[i * 3 + 1]].position,
			m_vertices[m_indices[i * 3 + 2]].position
		);
	}

	// 描画オブジェクトを準備する
	m_basicEffect = std::make_unique<DirectX::BasicEffect>(device);

	DX::ThrowIfFailed(
		DirectX::CreateInputLayoutFromEffect<DirectX::VertexPosition>(
			device,
			m_basicEffect.get(),
			m_inputLayout.ReleaseAndGetAddressOf()
		)
	);
	
	
	m_primitiveBatch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPosition>> (m_context);
}

/// <summary>
/// メッシュ情報の初期化
/// </summary>
/// <param name="device">デバイス</param>
/// <param name="context">コンテキスト</param>
/// <param name="vertices">頂点情報</param>
/// <param name="indices">インデックス</param>
void NakashiLib::CollisionMesh::InitializeVertexMesh(
	ID3D11Device* device,
	ID3D11DeviceContext* context,
	const std::vector<DirectX::VertexPosition>& vertices,
	const std::vector<uint16_t>& indices
)
{
	m_context = context;
	// 描画オブジェクトを準備する(ワイヤーフレーム)
	m_basicEffect = std::make_unique<DirectX::BasicEffect>(device);

	DX::ThrowIfFailed(
		DirectX::CreateInputLayoutFromEffect<DirectX::VertexPosition>(
			device,
			m_basicEffect.get(),
			m_inputLayout.ReleaseAndGetAddressOf()
		)
	);

	m_primitiveBatch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPosition>>(m_context);
	

	m_vertices = vertices;
	m_indices = indices;

	for (size_t i = 0; i < m_indices.size() / 3; i++)
	{
		AddTriangle(
			m_vertices[m_indices[i * 3 + 0]].position,
			m_vertices[m_indices[i * 3 + 1]].position,
			m_vertices[m_indices[i * 3 + 2]].position
		);
	}


}

/// <summary>
/// テクスチャの描画
/// </summary>
/// <param name="device">デバイス</param>
/// <param name="context">コンテキスト</param>
/// <param name="vertices">頂点情報</param>
/// <param name="indices">インデックス</param>
void NakashiLib::CollisionMesh::InitializeVertexMeshTexture(
	ID3D11Device* device,
	ID3D11DeviceContext* context,
	const std::vector<DirectX::VertexPositionTexture>& vertices,
	const std::vector<uint16_t>& indices
) {
	m_context = context;
	// テクスチャ用オブジェクト準備
	m_basicEffectTexture = std::make_unique<DirectX::BasicEffect>(device);
	m_basicEffectTexture->SetTextureEnabled(true);

	DX::ThrowIfFailed(
		DirectX::CreateInputLayoutFromEffect<DirectX::VertexPositionTexture>(
			device,
			m_basicEffectTexture.get(),
			m_inputLayoutTexture.ReleaseAndGetAddressOf()
		)
	);

	m_primitiveBatchTexture =
		std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>>(m_context);

	m_verticesTexture = vertices;
	m_indices = indices;

	for (size_t i = 0; i < m_indices.size() / 3; i++) {
		AddTriangle(
			m_verticesTexture[m_indices[i * 3 + 0]].position,
			m_verticesTexture[m_indices[i * 3 + 1]].position,
			m_verticesTexture[m_indices[i * 3 + 2]].position
		);
	}

	// 画像のロード
	HRESULT hr = DirectX::CreateWICTextureFromFile(
		device,
		L"Resources/Textures/Ground.png",
		nullptr,
		m_texture.ReleaseAndGetAddressOf()
	);
	if (FAILED(hr)) {
		OutputDebugStringA("Failed to load texture\n");
	}
}

/// <summary>
/// ワイヤーフレームの描画
/// </summary>
/// <param name="context">デバイス</param>
/// <param name="states">初期</param>
/// <param name="view">カメラのビュー</param>
/// <param name="projection">投影</param>
void NakashiLib::CollisionMesh::DrawMesh(
	DirectX::CommonStates* states,
	const DirectX::SimpleMath::Matrix& view,
	const DirectX::SimpleMath::Matrix& projection
)
{
	assert(states);

	// デバイスコンテキストのパラメータを設定
	m_context->OMSetBlendState(states->AlphaBlend(), nullptr, 0xFFFFF);	// ブレンドステート
	m_context->OMSetDepthStencilState(states->DepthRead(), 0);			// 深度バッファ/ステンシルバッファ
	m_context->RSSetState(states->Wireframe());							// カリング
	m_context->IASetInputLayout(m_inputLayout.Get());						// 入力レイアウト


	// ワールド行列を計算する
	DirectX::SimpleMath::Matrix rotation = DirectX::SimpleMath::Matrix::CreateFromQuaternion(m_rotation);	
	DirectX::SimpleMath::Matrix translation = DirectX::SimpleMath::Matrix::CreateTranslation(m_position);
	DirectX::SimpleMath::Matrix world = rotation * translation;

	//ベーシックエフェクトのパラメータを設定する
	m_basicEffect->SetWorld(world);					
	m_basicEffect->SetView(view);
	m_basicEffect->SetProjection(projection);
	m_basicEffect->Apply(m_context);

	// テクスチャを描画
	m_primitiveBatch->Begin();
	m_primitiveBatch->DrawIndexed(
		D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
		&m_indices[0], m_indices.size(),
		&m_vertices[0], m_vertices.size()
	);
	m_primitiveBatch->End();
}

/// <summary>
///  テクスチャを張った描画
/// </summary>
/// <param name="context">デバイス</param>
/// <param name="states">初期</param>
/// <param name="view">カメラのビュー</param>
/// <param name="projection">投影</param>
void NakashiLib::CollisionMesh::DrawMeshTexture(
	DirectX::CommonStates* states,
	const DirectX::SimpleMath::Matrix& view,
	const DirectX::SimpleMath::Matrix& projection
) {
	assert(states);

	// デバイスコンテキストのパラメータを設定
	m_context->OMSetBlendState(states->AlphaBlend(), nullptr, 0xFFFFF);        // ブレンドステート
	m_context->OMSetDepthStencilState(states->DepthDefault(), 0);                // 深度バッファ/ステンシルバッファ
	m_context->RSSetState(states->CullNone());                                // カリング
	m_context->IASetInputLayout(m_inputLayoutTexture.Get());                  // 入力レイアウト

	// ワールド行列を計算する
	DirectX::SimpleMath::Matrix rotation = DirectX::SimpleMath::Matrix::CreateFromQuaternion(m_rotation);
	DirectX::SimpleMath::Matrix translation = DirectX::SimpleMath::Matrix::CreateTranslation(m_position);
	DirectX::SimpleMath::Matrix world = rotation * translation;

	// ベーシックエフェクトのパラメータを設定する
	m_basicEffectTexture->SetWorld(world);                    // ワールド行列
	m_basicEffectTexture->SetView(view);                    // ビュー行列
	m_basicEffectTexture->SetProjection(projection);        // 射影行列
	m_basicEffectTexture->SetTexture(m_texture.Get());        // テクスチャ
	m_basicEffectTexture->Apply(m_context);                    // ベーシックエフェクトを更新する

	// メッシュを描画
	m_primitiveBatchTexture->Begin();
	m_primitiveBatchTexture->DrawIndexed(
		D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
		&m_indices[0],
		m_indices.size(),
		&m_verticesTexture[0],
		m_verticesTexture.size()
	);
	m_primitiveBatchTexture->End();
}

/// <summary>
/// メッシュとRayの衝突判定
/// </summary>
bool NakashiLib::CollisionMesh::IntersectRay(
	const DirectX::SimpleMath::Ray& ray,
	DirectX::SimpleMath::Vector3* hitPosition,
	DirectX::SimpleMath::Vector3* normal,
	int* polygonNo
)
{
	assert(hitPosition);
	assert(normal);
	// コリジョンメッシュの回転や座標情報から、worldの逆行列を求める
	DirectX::SimpleMath::Matrix rotation = DirectX::SimpleMath::Matrix::CreateFromQuaternion(m_rotation);
	DirectX::SimpleMath::Matrix transration = DirectX::SimpleMath::Matrix::CreateTranslation(m_position);
	DirectX::SimpleMath::Matrix world = rotation * transration;
	DirectX::SimpleMath::Matrix invertWorld = world.Invert();

	// レイにコリジョンメッシュの逆行列をかける
	// →レイをコリジョンメッシュのローカル座標系に持っていく
	DirectX::SimpleMath::Ray unitRay{};
	unitRay.position = DirectX::SimpleMath::Vector3::Transform(ray.position, invertWorld);
	unitRay.direction = DirectX::SimpleMath::Vector3::Transform(ray.direction, invertWorld);

	// レイと衝突点までの距離
 	float distance = 0.0f;

	// 衝突判定
	for (int i = 0; i < m_triangles.size(); i++)
	{
		//** ToDo::明らかに衝突しない場合は早期リターンするように変更する

		// レイとポリゴンの衝突判定をとる
		if (unitRay.Intersects(
			m_triangles[i].triangle[0],
			m_triangles[i].triangle[1],
			m_triangles[i].triangle[2],
			distance
		)
	)
		{
			// 衝突点の座標を計算する
			*hitPosition = DirectX::SimpleMath::Vector3{ unitRay.position + unitRay.direction * distance };

			// 衝突点をワールド座標に変換する
			*hitPosition = DirectX::SimpleMath::Vector3::Transform(*hitPosition, world);

			// ポリゴンの法線にコリジョンメッシュの回転情報を加味する
			*normal = DirectX::SimpleMath::Vector3::Transform(m_triangles[i].normal, m_rotation);

			// 衝突したポリゴン番号
			*polygonNo = i;

			return true;
		}
	}
	// 衝突しなかった
	return false;
}

/// <summary>
/// 当たったポリゴンの番号を取得する
/// </summary>
/// <param name="hitPolygonNo">ポリゴンの番号</param>
/// <returns></returns>
std::vector<DirectX::SimpleMath::Vector3> NakashiLib::CollisionMesh::GetHitPolygon(unsigned int hitPolygonNo)
{
	std::vector<DirectX::SimpleMath::Vector3> hitPolygon;
	hitPolygon.push_back(m_triangles[hitPolygonNo].triangle[0]);
	hitPolygon.push_back(m_triangles[hitPolygonNo].triangle[1]);
	hitPolygon.push_back(m_triangles[hitPolygonNo].triangle[2]);
	
	return hitPolygon;
}

/// <summary>
/// オブジェ形式のファイルをロードする
/// </summary>
/// <param name="objName">オブジェクトの名前</param>
void NakashiLib::CollisionMesh::LoadObjFile(const std::wstring& objName)
{
	// Obj形式のファイルを開く
	std::wstring fileName = L"Resources/Models/" + objName + L".obj";
	std::ifstream ifs(fileName);

	assert(ifs && ".objファイルが読み込めませんでした");

	// 1行ごとに処理する
	std::string line;
	while (getline(ifs, line))
	{
		// 読み取った１行分のデータをストリングストリームで扱う
		std::stringstream iss(line);
		std::string type;

		// 先頭要素を受け取る
		iss >> type;

		// 頂点データを作成する
		// ※Objデータにvt,vnが入る時もあるので注意する
		if (type.compare("v") == 0)
		{
			DirectX::SimpleMath::Vector3 vec;
			iss >> vec.x >> vec.y >> vec.z;
			m_vertices.emplace_back(vec);
		}
		// インデックスデータを作成する
		else if (type.compare("f") == 0)
		{
			int a, b, c;
			iss >> a >> b >> c;

			// 三角形の頂点インデックス番号が同じ物を含む場合は無視する：３点が異なる点を指している
			if (a != b && a != c && b != c)
			{
				m_indices.emplace_back(static_cast<uint16_t>(a - 1));
				m_indices.emplace_back(static_cast<uint16_t>(b - 1));
				m_indices.emplace_back(static_cast<uint16_t>(c - 1));
			}
		}
	}

	// 開いたファイルを閉じる
	ifs.close();
}

/// <summary>
/// 三角形ポリゴンを作成し、配列に登録する
/// </summary>
/// <param name="a">三角形の頂点１つめ</param>
/// <param name="b">三角形の頂点２つめ</param>
/// <param name="c">三角形の頂点３つめ</param>
void NakashiLib::CollisionMesh::AddTriangle(
	DirectX::SimpleMath::Vector3 a,
	DirectX::SimpleMath::Vector3 b,
	DirectX::SimpleMath::Vector3 c
)
{
	m_triangles.emplace_back(Triangle(a, b, c));
}