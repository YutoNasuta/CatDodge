//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/01
// <file>			PlayerJumping.cpp
// <概要>		　　プレイヤーのジャンプステート
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"PlayerJumping.h"
#include"Game/Player/Player.h"
#include"Framework/DeviceResources.h"
#include"Game/CommonResources.h"
#include"Libraries/NakashiLib/InputManager.h"
#include"Game/Player/PlayerPart/PlayerBody.h"
#include"Game/Player/PlayerPart/PlayerLeftHand.h"
#include"Game/Player/PlayerPart/PlayerRightHand.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="player">プレイヤー</param>
/// <param name="resource">共通リソース</param>
PlayerJumping::PlayerJumping(
	Player* player
)
:
	m_player(player)
{
	m_commonResources = CommonResources::GetInstance();
}

/// <summary>
/// デストラクタ
/// </summary>
PlayerJumping::~PlayerJumping()
{
}

/// <summary>
/// このステートに入った時
/// </summary>
void PlayerJumping::OnEnter()
{
	m_player->SetVelocity(DirectX::SimpleMath::Vector3(m_player->GetVelocity().x, m_player->GetVelocity().y + 1.1f, m_player->GetVelocity().z));
	m_player->SetAngle(m_player->GetQuaternion());
}

/// <summary>
/// このステートを出た時
/// </summary>
void PlayerJumping::OnExit()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void PlayerJumping::Initialize()
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="keyboardStateTracker">キーボード</param>
void PlayerJumping::Update()
{
	auto keyboardStateTracker = m_commonResources->GetInputManager()->GetKeyboardState();

	m_player->SetVelocity(m_player->GetVelocity() + m_player->GetGravity());					// 速度に重力を加算
	m_player->SetPosition(m_player->GetPosition() + m_player->GetVelocity());		// 位置に速度を加算

	MoveChild();

	// 地面より下にいった時
	if (m_player->GetPosition().y < m_player->GetGround().y)
	{
		DirectX::SimpleMath::Vector3 position = m_player->GetPosition();				// 位置を取得

		position.y = m_player->GetGround().y;							// 地面の高さを設定する

		m_player->SetPosition(position);				// 位置を設定する
		
		DirectX::SimpleMath::Vector3 velocity = m_player->GetVelocity();			// 速度を設定する
		
		velocity.y = 0.0f;					// 速度を設定
		
		m_player->SetVelocity(velocity);			// 速度を設定する
	}

	// 地面に着地したとき
	if (m_player->GetPosition().y == m_player->GetGround().y)
	{
		ChangeStateKey(keyboardStateTracker);				//ステート変更
	}
}

/// <summary>
/// 描画処理
/// </summary>
void PlayerJumping::Render()
{

}

/// <summary>
/// 後処理
/// </summary>
void PlayerJumping::Finalize()
{
}

/// <summary>
/// ステート変更
/// </summary>
/// <param name="keyboardStateTracker">キーボード</param>
void PlayerJumping::ChangeStateKey(
	const DirectX::Keyboard::State& keyboardStateTracker
)
{
	const auto& mouseState = m_commonResources->GetInputManager()->GetMouseState(); 
	 if(mouseState.rightButton)
	{
		m_player->ChangeState(m_player->GetTake());		// 受け状態に遷移
	}
	m_player->ChangeState(m_player->GetStanding());		// 立ち状態に遷移する
}

/// <summary>
/// 子の動き
/// </summary>
void PlayerJumping::MoveChild()
{
	MoveHand();
}

/// <summary>
/// 手の動き
/// </summary>
void PlayerJumping::MoveHand()
{
	auto rightHand = m_player->GetBody()->GetRightHand();		//右手取得
	auto leftHand = m_player->GetBody()->GetLeftHand();

	// 振りモーションのパラメーター
	float swingSpeed = 10.0f;
	float swingAmount = 0.8f;

	// 振りモーションを追加
	float swing = sin(m_player->GetTotalTime() * swingSpeed) * swingAmount;

	// プレイヤーの右手の位置を計算
	auto rightQuaternion = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(0.0f, swing, 0.0f);
	auto leftQuaternion = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(0.0f, -swing, 0.0f);

	rightHand->SetAddQuaternion(rightQuaternion);
	leftHand->SetAddQuaternion(leftQuaternion);
}