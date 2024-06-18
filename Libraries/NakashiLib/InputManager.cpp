//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/16
// <file>			InputManager.cpp
// <概要>			マウス、キーボードの入力
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include"pch.h"
#include"InputManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="window">ウィンドウ</param>
NakashiLib::InputManager::InputManager(const HWND& window)
:
	m_mouseState{},
	m_keyboardState{}
{
	// マウスを使用できる状態にする
	m_mouse = std::make_unique<DirectX::Mouse>();
	m_mouse->SetWindow(window);
	m_mouseTracker = std::make_unique<DirectX::Mouse::ButtonStateTracker>();

	// キーボードを使用できる状態にする
	m_keyboard = std::make_unique<DirectX::Keyboard>();
	m_keyboardTracker = std::make_unique<DirectX::Keyboard::KeyboardStateTracker>();
}

/// <summary>
/// リソースの更新
/// </summary>
void NakashiLib::InputManager::Update()
{
	// マウスの情報を更新
	m_mouseState = m_mouse->GetState();
	m_mouseTracker->Update(m_mouseState);

	// キーボードの情報を更新する
	m_keyboardState = m_keyboard->GetState();
	m_keyboardTracker->Update(m_keyboardState);
}