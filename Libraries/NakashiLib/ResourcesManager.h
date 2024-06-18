//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/05/18
// <file>			ResourcesManager.h
// <概要>			リソースマネージャークラス
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include<unordered_map>
#include<string>

// 前方宣言
class CommonResources;

namespace NakashiLib
{
	class ResourcesManager
	{
	private:
		// リソース
		CommonResources* m_commonResources;
		
		// モデル配列
		std::unordered_map<std::wstring, std::unique_ptr<DirectX::Model>> m_models;
		std::unordered_map<std::wstring, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_srvs;

	public:
		ResourcesManager();
		~ResourcesManager();

		// リソースの削除
		void DeleteAllResources();
		void DeleteModel(const std::wstring& id);
		void DeleteSRV(const std::wstring& id);

		// リソースの登録関数
		void CreateModel(const std::wstring& id, const std::wstring& fileName);
		void CreateSRV(const std::wstring& id, const std::wstring& fileName);

		// 取得
		DirectX::Model* GetModel(const std::wstring& id) const;
		ID3D11ShaderResourceView* GetSRV(const std::wstring& id) const;
	};
}
