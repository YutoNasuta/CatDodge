//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/05/18
// <file>			ResourcesManager.h
// <概要>			リソースマネージャークラス
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"ResourcesManager.h"
#include"Game/CommonResources.h"
#include"Framework/DeviceResources.h"
/// <summary>
/// コンストラクタ
/// </summary>
NakashiLib::ResourcesManager::ResourcesManager()
	:
	m_models{},
	m_srvs{}
{
	m_commonResources = CommonResources::GetInstance();
}

/// <summary>
/// デストラクタ
/// </summary>
NakashiLib::ResourcesManager::~ResourcesManager()
{
	DeleteAllResources();
}

/// <summary>
/// すべてのリソースを消す
/// </summary>
void NakashiLib::ResourcesManager::DeleteAllResources()
{
	m_models.clear();
	m_srvs.clear();
}

/// <summary>
/// 指定したモデルの削除
/// </summary>
/// <param name="id">ID</param>
void NakashiLib::ResourcesManager::DeleteModel(const std::wstring& id)
{
	m_models.erase(id);
}

/// <summary>
/// 指定した画像オブジェクトの削除
/// </summary>
/// <param name="id">ID</param>
void NakashiLib::ResourcesManager::DeleteSRV(const std::wstring& id)
{
	m_srvs.erase(id);
}

/// <summary>
/// モデルの登録
/// </summary>
/// <param name="id">ID</param>
/// <param name="fileName">ファイルの名前</param>
void NakashiLib::ResourcesManager::CreateModel(const std::wstring& id, const std::wstring& fileName)
{
	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();

	// モデルを読み込む準備
	std::unique_ptr<DirectX::EffectFactory> fx =
		std::make_unique<DirectX::EffectFactory>(device);

	fx->SetDirectory(L"Resources/Models");

	// モデルの読み込み
	std::wstring path = L"Resources/Models/" + fileName;
	m_models[id] = DirectX::Model::CreateFromCMO(device, path.c_str(), *fx);
}

/// <summary>
/// 画像の登録
/// </summary>
/// <param name="id">ID</param>
/// <param name="fileName">ファイルの名前</param>
void NakashiLib::ResourcesManager::CreateSRV(const std::wstring& id, const std::wstring& fileName)
{
	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> srv;

	std::wstring path = L"Resources/Textures/" + fileName;

	// 画像のロード
	DX::ThrowIfFailed(
		DirectX::CreateWICTextureFromFile(
			device,
			path.c_str(),
			nullptr,
			srv.ReleaseAndGetAddressOf()
		)
	);

	m_srvs[id] = srv;
}

/// <summary>
/// モデルの取得
/// </summary>
/// <param name="id">登録ID</param>
/// <returns></returns>
DirectX::Model* NakashiLib::ResourcesManager::GetModel(const std::wstring& id) const
{
	DirectX::Model* model = m_models.at(id).get();

	assert(model);
	return model;
}

/// <summary>
/// 画像のポインタ取得
/// </summary>
/// <param name="id"></param>
/// <returns></returns>
ID3D11ShaderResourceView* NakashiLib::ResourcesManager::GetSRV(const std::wstring& id)const
{
	ID3D11ShaderResourceView* srv = m_srvs.at(id).Get();

	assert(srv);
	return srv;
}