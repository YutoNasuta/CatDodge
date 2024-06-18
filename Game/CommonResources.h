//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/05/21
// <file>			CommonResources.h
// <概要>			シーンへ渡す、ゲーム内で使用する共通リソース
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once

// 前方宣言
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

// 共通リソース
class CommonResources
{
public:
	// CommonResourcesクラスのインスタンス取得
	static CommonResources* const GetInstance();
private:
	// コモンリソース
	static std::unique_ptr<CommonResources> m_commonResources;

	// 受け渡しするリソース一覧
	DX::StepTimer* m_stepTimer;

	DX::DeviceResources* m_deviceResources;

	DirectX::CommonStates* m_commonStates;

	NakashiLib::DebugString* m_debugString;

	NakashiLib::InputManager* m_inputManager;

	NakashiLib::ResourcesManager* m_resourceManager;


private:
	// コンストラクタ
	CommonResources();
	// インスタンスコピーの禁止とムーブの禁止
	void operator=(const CommonResources&) = delete;
	CommonResources& operator = (CommonResources&&) = delete;
	// コピーコンストラクタ、ムーブコンストラクタの禁止
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
