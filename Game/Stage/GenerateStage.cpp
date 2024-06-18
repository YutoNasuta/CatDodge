#include"pch.h"
#include"GenerateStage.h"
#include"Libraries/NakashiLib/PerlinNoise.h"
#include"Libraries/NakashiLib/CollisionMesh.h"
GenerateStage::GenerateStage()
	:
	m_correction{15.0f},
	m_correctionHeight{9},
	m_correctionNoise{100},
	m_octaves{ 80},
	m_normalHeight{1.5f},
	m_scale{ 5 },
	m_landScape{}
{
}

GenerateStage::~GenerateStage()
{

}

void GenerateStage::Initialize(
	ID3D11Device* device,
	ID3D11DeviceContext* context)
{
	m_collisionMesh = std::make_unique<NakashiLib::CollisionMesh>();
	// パーリンノイズのインスタンス化
	std::random_device rd; //完全ランダム
	auto pPerlinNoise = std::make_unique<NakashiLib::PerlinNoise>(rd());

	for (int y = 0; y < LAND_HEIGHT; y++)
	{
		for (int x = 0; x < LAND_WIDTH; x++)
		{

			int m_NoiseValue = (int)(pPerlinNoise->GetNoise(m_octaves, (float)x / m_correctionNoise, (float)y / m_correctionNoise) * m_correction);

			m_landScape[y][x] = (float)m_NoiseValue * m_normalHeight;
		}
	}
	
	// 衝突メッシュの初期化
	std::vector<DirectX::VertexPosition> vertices;
	std::vector<DirectX::VertexPositionTexture> verticesTexture;
	std::vector<uint16_t> indices;

	for (int y = 0; y < LAND_HEIGHT - 1; y++)
	{
		for (int x = 0; x < LAND_WIDTH - 1; x++)
		{
			// 頂点座標を作成
			float scaledX = (float)x * m_scale;
			float scaledY = (float)y * m_scale;
			float scaledX1 = (float)(x + 1) * m_scale;
			float scaledY1 = (float)(y + 1) * m_scale;

			vertices.emplace_back(DirectX::VertexPosition{ DirectX::SimpleMath::Vector3{ scaledX, m_landScape[y][x] - m_correctionHeight, scaledY } });
			vertices.emplace_back(DirectX::VertexPosition{ DirectX::SimpleMath::Vector3{ scaledX1, m_landScape[y][x + 1] - m_correctionHeight, scaledY } });
			vertices.emplace_back(DirectX::VertexPosition{ DirectX::SimpleMath::Vector3{ scaledX, m_landScape[y + 1][x] - m_correctionHeight, scaledY1 } });
			vertices.emplace_back(DirectX::VertexPosition{ DirectX::SimpleMath::Vector3{ scaledX1, m_landScape[y + 1][x + 1] - m_correctionHeight, scaledY1 } });

			verticesTexture.emplace_back(DirectX::VertexPositionTexture{ DirectX::SimpleMath::Vector3{ scaledX, m_landScape[y][x] - m_correctionHeight, scaledY }  , DirectX::SimpleMath::Vector2{0.0f,0.0f} });
			verticesTexture.emplace_back(DirectX::VertexPositionTexture{ DirectX::SimpleMath::Vector3{ scaledX1, m_landScape[y][x + 1] - m_correctionHeight, scaledY } , DirectX::SimpleMath::Vector2{1.0f,0.0f} });
			verticesTexture.emplace_back(DirectX::VertexPositionTexture{ DirectX::SimpleMath::Vector3{ scaledX, m_landScape[y + 1][x] - m_correctionHeight, scaledY1 } , DirectX::SimpleMath::Vector2{0.0f,1.0f} });
			verticesTexture.emplace_back(DirectX::VertexPositionTexture{ DirectX::SimpleMath::Vector3{ scaledX1, m_landScape[y + 1][x + 1] - m_correctionHeight, scaledY1 }, DirectX::SimpleMath::Vector2{1.0f,1.0f} });


			// インデックスの作成
			uint16_t baseIndex = static_cast<uint16_t>((y * (LAND_WIDTH - 1) + x) * 4);
			indices.push_back(baseIndex + 0);
			indices.push_back(baseIndex + 1);
			indices.push_back(baseIndex + 2);

			indices.push_back(baseIndex + 2);
			indices.push_back(baseIndex + 1);
			indices.push_back(baseIndex + 3);
		}
	}

	m_collisionMesh->InitializeVertexMesh(device , context ,vertices, indices);
	m_collisionMesh->InitializeVertexMeshTexture(device, context, verticesTexture, indices);



}

void GenerateStage::Render( DirectX::CommonStates* states, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	m_collisionMesh->DrawMesh(states, view, projection);

	m_collisionMesh->DrawMeshTexture(states, view, projection);
}