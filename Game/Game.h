//
// Game.h
//

#pragma once

#include "Framework/DeviceResources.h"
#include "Framework/StepTimer.h"

// ��include�̒ǋL��
#include "Game/CommonResources.h"
#include "Interface/IScene.h"
#include "Game/Scene/SceneManager.h"
#include "Libraries/NakashiLib/DebugString.h"
#include "Libraries/NakashiLib/InputManager.h"
#include"Libraries/NakashiLib/ResourcesManager.h"

// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game final : public DX::IDeviceNotify
{
public:

    Game() noexcept(false);
    ~Game() = default;

    Game(Game&&) = default;
    Game& operator= (Game&&) = default;

    Game(Game const&) = delete;
    Game& operator= (Game const&) = delete;

    // Initialization and management
    void Initialize(HWND window, int width, int height);

    // Basic game loop
    void Tick();

    // IDeviceNotify
    void OnDeviceLost() override;
    void OnDeviceRestored() override;

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowMoved();
    void OnDisplayChange();
    void OnWindowSizeChanged(int width, int height);

    // Properties
    void GetDefaultSize( int& width, int& height ) const noexcept;

private:

    void Update(DX::StepTimer const& timer);
    void Render();

    void Clear();

    void CreateDeviceDependentResources();
    void CreateWindowSizeDependentResources();

    // Device resources.
    std::unique_ptr<DX::DeviceResources>    m_deviceResources;

    // Rendering loop timer.
    DX::StepTimer                           m_timer;


    // ���ǋL�R�R���火������

    // �R�����X�e�[�g
    std::unique_ptr<DirectX::CommonStates>  m_commonStates;

    // �R�������\�[�X
    CommonResources*                        m_commonResources;

    // �f�o�b�O�X�g�����O
    std::unique_ptr<NakashiLib::DebugString>     m_debugString;

    // ���̓}�l�[�W��
    std::unique_ptr<NakashiLib::InputManager>    m_inputManager;

    // �V�[���}�l�[�W��
    std::unique_ptr<SceneManager>           m_sceneManager;

    // ���\�[�X�}�l�[�W���[
    std::unique_ptr<NakashiLib::ResourcesManager> m_resourceManager;

   

    // ���ǋL�R�R�܂Ł�������
};
