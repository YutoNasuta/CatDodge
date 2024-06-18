//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/01/28
// <file>			DebugString.h
// <�T�v>			�f�o�b�O�p������̕`��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"pch.h"
#include<SpriteFont.h>
#include<vector>
#include<string>

namespace NakashiLib
{
	class DebugString
	{
	private:
		// �f�[�^�����o
		std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
		std::unique_ptr<DirectX::SpriteFont> m_spriteFont;
		std::vector<std::string> m_strings;
		float m_fontHeight;
		DirectX::SimpleMath::Color m_color;

	public:
		// �R���X�g���N�^
		DebugString(
			ID3D11Device* device,
			ID3D11DeviceContext* context,
			const wchar_t* fontFilePath
		);
		
		// �f�X�g���N�^
		~DebugString() = default;

		// �`�敶����̓o�^
		void AddString(const char* format, ...);

		// �f�o�b�O�������`��
		void Render(DirectX::CommonStates* states);

		// �`�悷�镶����̐F���w�肷��
		void SetColor(DirectX::FXMVECTOR color = DirectX::Colors::White)
		{
			m_color = color;
		}
	};
}