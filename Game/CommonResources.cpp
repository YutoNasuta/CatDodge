//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/05/21
// <file>			CommonResources.cpp
// <概要>			シーンへ渡す、ゲーム内で使用する共通リソース
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "pch.h"
#include "CommonResources.h"
#include <cassert>

// 外部で初期化
std::unique_ptr<CommonResources> CommonResources::m_commonResources = nullptr;

CommonResources* const CommonResources::GetInstance()
{
	// 最初だけの処理
	if (m_commonResources == nullptr)
	{
		m_commonResources.reset(new CommonResources());
	}
	// コモンリソースのインスタンスを返す
	return m_commonResources.get();
}

//---------------------------------------------------------
// コンストラクタ
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
// 初期化する
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
