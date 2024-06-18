
#include "pch.h"
#include "Result.h"
#include "Game/Screen.h"
#include "Game/CommonResources.h"
#include "framework/DeviceResources.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include "Libraries/NakashiLib/InputManager.h"
#include <cassert>

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
ResultScene::ResultScene()
	:
	m_commonResources{},
	m_spriteBatch{},
	m_spriteFont{},
	m_texture{},
	m_texCenter{},
	m_isChangeScene{}
{
	m_commonResources = CommonResources::GetInstance();
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
ResultScene::~ResultScene()
{
	// do nothing.
}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void ResultScene::Initialize()
{


	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();

	// スプライトバッチを作成する
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(context);

	// スプライトフォントを作成する
	m_spriteFont = std::make_unique<DirectX::SpriteFont>(
		device,
		L"Resources/Fonts/SegoeUI_18.spritefont"
	);

	// 画像をロードする
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(
			device,
			L"Resources/Textures/TridentLogo.png",
			nullptr,
			m_texture.ReleaseAndGetAddressOf()
		)
	);


	// 以下、テクスチャの大きさを求める→テクスチャの中心座標を計算する

	// 一時的な変数の宣言
	Microsoft::WRL::ComPtr<ID3D11Resource> resource;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> tex2D;
	D3D11_TEXTURE2D_DESC desc;
	Vector2 texSize;

	// テクスチャの情報を取得する================================
	// テクスチャをID3D11Resourceとして見る
	m_texture->GetResource(resource.GetAddressOf());
	// ID3D11ResourceをID3D11Texture2Dとして見る
	resource.As(&tex2D);
	// テクスチャ情報を取得する
	tex2D->GetDesc(&desc);

	// テクスチャサイズを取得し、float型に変換する
	texSize.x = static_cast<float>(desc.Width);
	texSize.y = static_cast<float>(desc.Height);

	// テクスチャの中心位置を計算する
	m_texCenter = texSize / 2.0f;


	// シーン変更フラグを初期化する
	m_isChangeScene = false;
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void ResultScene::Update(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	// キーボードステートトラッカーを取得する
	const auto& kbTracker = m_commonResources->GetInputManager()->GetKeyboardTracker();

	// スペースキーが押されたら
	if (kbTracker->IsKeyPressed(Keyboard::Space))
	{
		m_isChangeScene = true;
	}
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void ResultScene::Render()
{
	auto states = m_commonResources->GetCommonStates();

	// スプライトバッチの開始：オプションでソートモード、ブレンドステートを指定する
	m_spriteBatch->Begin(SpriteSortMode_Deferred, states->NonPremultiplied());

	//// TRIDENTロゴの描画位置を決める
	RECT rect = m_commonResources->GetDeviceResources()->GetOutputSize();
	Vector2 pos(rect.right / 2.0f - m_texCenter.x, rect.bottom / 2.0f - m_texCenter.y);

	// TRIDENTロゴを描画する
	m_spriteBatch->Draw(m_texture.Get(), pos);

	// スプライトフォントで文字列を描画する
	m_spriteFont->DrawString(m_spriteBatch.get(), L"ResultScene", Vector2(10, 40));

	// スプライトバッチの終わり
	m_spriteBatch->End();
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void ResultScene::Finalize()
{
	// do nothing.
}

//---------------------------------------------------------
// 次のシーンIDを取得する
//---------------------------------------------------------
IScene::SceneID ResultScene::GetNextSceneID() const
{
	// シーン変更がある場合
	if (m_isChangeScene)
	{
		return IScene::SceneID::TITLE;
	}

	// シーン変更がない場合
	return IScene::SceneID::NONE;
}