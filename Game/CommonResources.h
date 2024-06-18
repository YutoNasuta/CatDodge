//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/05/21
// <file>			CommonResources.h
// <�T�v>			�V�[���֓n���A�Q�[�����Ŏg�p���鋤�ʃ��\�[�X
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once

// �O���錾
namespace DX
{
	class StepTimer;
	class DeviceResources;
}

namespace NakashiLib
{
	class ResourcesManager;
	class InputManager;
	class DebugString;
}

// ���ʃ��\�[�X
class CommonResources
{
public:
	// CommonResources�N���X�̃C���X�^���X�擾
	static CommonResources* const GetInstance();
private:
	// �R�������\�[�X
	static std::unique_ptr<CommonResources> m_commonResources;

	// �󂯓n�����郊�\�[�X�ꗗ
	DX::StepTimer* m_stepTimer;

	DX::DeviceResources* m_deviceResources;

	DirectX::CommonStates* m_commonStates;

	NakashiLib::DebugString* m_debugString;

	NakashiLib::InputManager* m_inputManager;

	NakashiLib::ResourcesManager* m_resourceManager;


private:
	// �R���X�g���N�^
	CommonResources();
	// �C���X�^���X�R�s�[�̋֎~�ƃ��[�u�̋֎~
	void operator=(const CommonResources&) = delete;
	CommonResources& operator = (CommonResources&&) = delete;
	// �R�s�[�R���X�g���N�^�A���[�u�R���X�g���N�^�̋֎~
	CommonResources(const CommonResources&) = delete;
	CommonResources(CommonResources&&) = delete;
public:

	~CommonResources() = default;

	void Initialize(
		DX::StepTimer* timer,
		DX::DeviceResources* dr,
		DirectX::CommonStates* commonStates,
		NakashiLib::DebugString* debugString,
		NakashiLib::InputManager* inputManager,
		NakashiLib::ResourcesManager* resourcesManager
	);

	// getter
	DX::StepTimer* GetStepTimer() const
	{
		return m_stepTimer;
	}

	DX::DeviceResources* GetDeviceResources() const
	{
		return m_deviceResources;
	}

	DirectX::CommonStates* GetCommonStates() const
	{
		return m_commonStates;
	}

	NakashiLib::DebugString* GetDebugString() const
	{
		return m_debugString;
	}

	NakashiLib::InputManager* GetInputManager() const
	{
		return m_inputManager;
	}

	NakashiLib::ResourcesManager* GetResourcesManager() const
	{
		return m_resourceManager;
	}
	
};
