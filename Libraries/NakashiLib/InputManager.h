//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/16
// <file>			InputManager.h
// <�T�v>			�}�E�X�A�L�[�{�[�h�̓���
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"pch.h"

namespace NakashiLib
{
	class InputManager
	{
	private:
		// �}�E�X
		std::unique_ptr<DirectX::Mouse> m_mouse;
		std::unique_ptr<DirectX::Mouse::ButtonStateTracker> m_mouseTracker;
		DirectX::Mouse::State m_mouseState;

		// �L�[�{�[�h
		std::unique_ptr<DirectX::Keyboard> m_keyboard;
		std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker> m_keyboardTracker;
		DirectX::Keyboard::State m_keyboardState;

	public:
		InputManager(const HWND& window);
		~InputManager() = default;

		void Update();

		// �L�[�{�[�h�X�e�[�g���擾
		const DirectX::Keyboard::State& GetKeyboardState() const
		{
			return m_keyboardState;
		}
		// �L�[�{�[�h�̃X�e�[�g�g���b�J�[�擾
		const std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker>& GetKeyboardTracker() const
		{
			return m_keyboardTracker;
		}
		// �}�E�X�X�e�[�g�̎擾
		const DirectX::Mouse::State& GetMouseState() const
		{
			return m_mouseState;
		}
		// �}�E�X�̃{�^���X�e�[�g�g���b�J�[���擾
		const std::unique_ptr<DirectX::Mouse::ButtonStateTracker>& GetMouseTracker() const
		{
			return m_mouseTracker;
		}
		
	};
}