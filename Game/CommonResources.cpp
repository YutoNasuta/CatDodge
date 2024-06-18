//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/05/21
// <file>			CommonResources.cpp
// <�T�v>			�V�[���֓n���A�Q�[�����Ŏg�p���鋤�ʃ��\�[�X
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "pch.h"
#include "CommonResources.h"
#include <cassert>

// �O���ŏ�����
std::unique_ptr<CommonResources> CommonResources::m_commonResources = nullptr;

CommonResources* const CommonResources::GetInstance()
{
	// �ŏ������̏���
	if (m_commonResources == nullptr)
	{
		m_commonResources.reset(new CommonResources());
	}
	// �R�������\�[�X�̃C���X�^���X��Ԃ�
	return m_commonResources.get();
}

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
CommonResources::CommonResources()
	:
	m_stepTimer{ nullptr },
	m_deviceResources{ nullptr },
	m_commonStates{ nullptr },
	m_debugString{ nullptr },
	m_inputManager{ nullptr },
	m_resourceManager{ nullptr }
{
}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void CommonResources::Initialize(
	DX::StepTimer* timer,
	DX::DeviceResources* dr,
	DirectX::CommonStates* commonStates,
	NakashiLib::DebugString* debugString,
	NakashiLib::InputManager* inputManager,
	NakashiLib::ResourcesManager* resourcesManager
)
{
	assert(timer);
	assert(dr);
	assert(commonStates);
	assert(debugString);
	assert(inputManager);
	assert(resourcesManager);

	m_stepTimer = timer;
	m_deviceResources = dr;
	m_commonStates = commonStates;
	m_debugString = debugString;
	m_inputManager = inputManager;
	m_resourceManager = resourcesManager;
}
