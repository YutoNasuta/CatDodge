//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/01/28
// <file>			DebugString.h
// <概要>			デバッグ用文字列の描画
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"DebugString.h"
#include<cstdarg>
#include<cassert>

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="device">デバイス</param>
/// <param name="context">コンテキスト</param>
/// <param name="fontFilePath">フォント</param>
NakashiLib::DebugString::DebugString(
	ID3D11Device* device,
	ID3D11DeviceContext* context,
	const wchar_t* fontFilePath
)
	:
	m_strings{}
{
	assert(device);
	assert(context);

	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(context);
	m_spriteFont = std::make_unique<DirectX::SpriteFont>(device, fontFilePath);

	m_fontHeight = m_spriteFont->GetLineSpacing();
	m_color = DirectX::Colors::White;
}

/// <summary>
/// 描画する文字列を登録
/// </summary>
/// <param name="format"フォーマット></param>
/// <param name="">表示文字</param>
void NakashiLib::DebugString::AddString(const char* format, ...)
{
	// 可変長配列を扱う
	va_list args;

	// 登録する文字列の長さを求める
	va_start(args, format);
	int length = vsnprintf(nullptr, 0, format, args);
	va_end(args);

	// 登録する文字列の大きさを調整
	std::string appendString;
	appendString.resize(length + 1);

	// 登録する文字列の作成
	va_start(args, format);
	vsnprintf(&appendString[0], length + 1, format, args);
	va_end(args);

	// 作成した文字列を文字列配列に登録する
	m_strings.push_back(appendString);
}

void NakashiLib::DebugString::Render(DirectX::CommonStates* states)
{
	UNREFERENCED_PARAMETER(states);	// Beginのパラメータ設定用

	m_spriteBatch->Begin();

	// 文字列の描画位置
	DirectX::SimpleMath::Vector2 pos{ DirectX::SimpleMath::Vector2::Zero };

	for (unsigned int i = 0; i < m_strings.size(); i++)
	{
		// 表示する行の高さを計算する
		pos.y = m_fontHeight * i;

		// 描画する
		m_spriteFont->DrawString(
			m_spriteBatch.get(),
			m_strings[i].c_str(),
			pos,
			m_color
		);
	}

	m_spriteBatch->End();

	// 描画後、文字列配列をクリアする
	m_strings.clear();
}