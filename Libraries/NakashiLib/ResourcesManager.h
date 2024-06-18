//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/05/18
// <file>			ResourcesManager.h
// <�T�v>			���\�[�X�}�l�[�W���[�N���X
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include<unordered_map>
#include<string>

// �O���錾
class CommonResources;

namespace NakashiLib
{
	class ResourcesManager
	{
	private:
		// ���\�[�X
		CommonResources* m_commonResources;
		
		// ���f���z��
		std::unordered_map<std::wstring, std::unique_ptr<DirectX::Model>> m_models;
		std::unordered_map<std::wstring, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_srvs;

	public:
		ResourcesManager();
		~ResourcesManager();

		// ���\�[�X�̍폜
		void DeleteAllResources();
		void DeleteModel(const std::wstring& id);
		void DeleteSRV(const std::wstring& id);

		// ���\�[�X�̓o�^�֐�
		void CreateModel(const std::wstring& id, const std::wstring& fileName);
		void CreateSRV(const std::wstring& id, const std::wstring& fileName);

		// �擾
		DirectX::Model* GetModel(const std::wstring& id) const;
		ID3D11ShaderResourceView* GetSRV(const std::wstring& id) const;
	};
}
