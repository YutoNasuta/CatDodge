//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/05/18
// <file>			ResourcesManager.h
// <�T�v>			���\�[�X�}�l�[�W���[�N���X
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"ResourcesManager.h"
#include"Game/CommonResources.h"
#include"Framework/DeviceResources.h"
/// <summary>
/// �R���X�g���N�^
/// </summary>
NakashiLib::ResourcesManager::ResourcesManager()
	:
	m_models{},
	m_srvs{}
{
	m_commonResources = CommonResources::GetInstance();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
NakashiLib::ResourcesManager::~ResourcesManager()
{
	DeleteAllResources();
}

/// <summary>
/// ���ׂẴ��\�[�X������
/// </summary>
void NakashiLib::ResourcesManager::DeleteAllResources()
{
	m_models.clear();
	m_srvs.clear();
}

/// <summary>
/// �w�肵�����f���̍폜
/// </summary>
/// <param name="id">ID</param>
void NakashiLib::ResourcesManager::DeleteModel(const std::wstring& id)
{
	m_models.erase(id);
}

/// <summary>
/// �w�肵���摜�I�u�W�F�N�g�̍폜
/// </summary>
/// <param name="id">ID</param>
void NakashiLib::ResourcesManager::DeleteSRV(const std::wstring& id)
{
	m_srvs.erase(id);
}

/// <summary>
/// ���f���̓o�^
/// </summary>
/// <param name="id">ID</param>
/// <param name="fileName">�t�@�C���̖��O</param>
void NakashiLib::ResourcesManager::CreateModel(const std::wstring& id, const std::wstring& fileName)
{
	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();

	// ���f����ǂݍ��ޏ���
	std::unique_ptr<DirectX::EffectFactory> fx =
		std::make_unique<DirectX::EffectFactory>(device);

	fx->SetDirectory(L"Resources/Models");

	// ���f���̓ǂݍ���
	std::wstring path = L"Resources/Models/" + fileName;
	m_models[id] = DirectX::Model::CreateFromCMO(device, path.c_str(), *fx);
}

/// <summary>
/// �摜�̓o�^
/// </summary>
/// <param name="id">ID</param>
/// <param name="fileName">�t�@�C���̖��O</param>
void NakashiLib::ResourcesManager::CreateSRV(const std::wstring& id, const std::wstring& fileName)
{
	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> srv;

	std::wstring path = L"Resources/Textures/" + fileName;

	// �摜�̃��[�h
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
/// ���f���̎擾
/// </summary>
/// <param name="id">�o�^ID</param>
/// <returns></returns>
DirectX::Model* NakashiLib::ResourcesManager::GetModel(const std::wstring& id) const
{
	DirectX::Model* model = m_models.at(id).get();

	assert(model);
	return model;
}

/// <summary>
/// �摜�̃|�C���^�擾
/// </summary>
/// <param name="id"></param>
/// <returns></returns>
ID3D11ShaderResourceView* NakashiLib::ResourcesManager::GetSRV(const std::wstring& id)const
{
	ID3D11ShaderResourceView* srv = m_srvs.at(id).Get();

	assert(srv);
	return srv;
}