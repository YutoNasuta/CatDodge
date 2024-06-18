//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/16
// <file>			InputManager.h
// <概要>			マウス、キーボードの入力
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"pch.h"

namespace NakashiLib
{
	class InputManager
	{
	private:
		// マウス
		std::unique_ptr<DirectX::Mouse> m_mouse;
		std::unique_ptr<DirectX::Mouse::ButtonStateTracker> m_mouseTracker;
		DirectX::Mouse::State m_mouseState;

		// キーボード
		std::unique_ptr<DirectX::Keyboard> m_keyboard;
		std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker> m_keyboardTracker;
		DirectX::Keyboard::State m_keyboardState;

	public:
		InputManager(const HWND& window);
		~InputManager() = default;

		void Update();

		// キーボードステートを取得
		const DirectX::Keyboard::State& GetKeyboardState() const
		{
			return m_keyboardState;
		}
		// キーボードのステートトラッカー取得
		const std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker>& GetKeyboardTracker() const
		{
			return m_keyboardTracker;
		}
		// マウスステートの取得
		const DirectX::Mouse::State& GetMouseState() const
		{
			return m_mouseState;
		}
		// マウスのボタンステートトラッカーを取得
		const std::unique_ptr<DirectX::Mouse::ButtonStateTracker>& GetMouseTracker() const
		{
			return m_mouseTracker;
		}
		
	};
}