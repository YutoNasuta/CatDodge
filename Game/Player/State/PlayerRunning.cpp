//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/01
// <file>			PlayerRunning.cpp
// <概要>		　　プレイヤーの走りステート
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"PlayerRunning.h"
#include"Game/Player/Player.h"
#include"Game/CommonResources.h"
#include"framework/DeviceResources.h"
#include"Libraries/NakashiLib/InputManager.h"
#include"Game/Player/PlayerPart/PlayerBody.h"
#include"Game/Player/PlayerPart/PlayerRightHand.h"
#include"Game/Player/PlayerPart/PlayerLeftHand.h"
#include"Game/Player/PlayerPart/PlayerTail.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="player">プレイヤー</param>
/// <param name="resource">共通リソース</param>
PlayerRunning::PlayerRunning(
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
PlayerRunning::~PlayerRunning()
{
}

/// <summary>
/// このステートに入った時
/// </summary>
void PlayerRunning::OnEnter()
{
	m_player->SetVelocity(m_player->GetVelocity());	//velocityを合わせる
	m_player->SetAngle(m_player->GetQuaternion());	//クォータニオンを合わせる
}

/// <summary>
/// このステートを出たとき
/// </summary>
void PlayerRunning::OnExit()
{
	m_player->SetAngle(m_player->GetQuaternion());	//クォータニオンを合わせる
}

/// <summary>
/// 初期化処理
/// </summary>
void PlayerRunning::Initialize()
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="keyboardStateTracker">キーボード</param>
void PlayerRunning::Update()
{
	auto keyboardStateTracker = m_commonResources->GetInputManager()->GetKeyboardState();

	Moving(keyboardStateTracker);				// プレイヤーの移動
	MoveChild();
	ChangeStateKey(keyboardStateTracker);		// キー入力でState遷移
}

/// <summary>
/// 描画
/// </summary>
void PlayerRunning::Render()
{
}

/// <summary>
/// 後処理
/// </summary>
void PlayerRunning::Finalize()
{
}

/// <summary>
/// プレイヤーの動き
/// </summary>
/// <param name="keyboardStateTracker">キーボード</param>
void PlayerRunning::Moving(
	const DirectX::Keyboard::State& keyboardStateTracker
)
{
	DirectX::SimpleMath::Vector3 direction = m_player->GetVelocity();		// 停止処理
	
	// プレイヤーの移動
	// カメラの方向を前として角度を含めた移動
	if (keyboardStateTracker.IsKeyDown(DirectX::Keyboard::Keys::W))
	{ direction += DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3::Forward, m_player->GetCameraQuaternion());}
	if (keyboardStateTracker.IsKeyDown(DirectX::Keyboard::Keys::D))
	{ direction += DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3::Right,   m_player->GetCameraQuaternion());}
	if (keyboardStateTracker.IsKeyDown(DirectX::Keyboard::Keys::A))
	{ direction += DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3::Left,	  m_player->GetCameraQuaternion());}
	if (keyboardStateTracker.IsKeyDown(DirectX::Keyboard::Keys::S))
	{ direction += DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3::Backward,m_player->GetCameraQuaternion());}
 
	direction.y = 0.0f;			// y軸成分をゼロに

	direction.Normalize();		// 移動量の正規化

	SlerpRotate(direction);		//プレイヤーの移動と角度から補完をする

	DirectX::SimpleMath::Vector3 velocity = direction ;	// 移動量の補正

	m_player->SetPosition(m_player->GetPosition() + m_player->GetVelocity());		//ポジションの変更
	m_player->SetVelocity(velocity * m_player->GetFriction() * 0.25f);				//速度の変更

}

/// <summary>
/// 向きの補正
/// </summary>
/// <param name="direction">向き</param>
void PlayerRunning::SlerpRotate(
	DirectX::SimpleMath::Vector3 direction
)
{
	if (direction.LengthSquared() < 1e-2f) { return; }			// 移動量がほとんどないなら計算しない( 1の10-2乗以下 )

	DirectX::SimpleMath::Quaternion targetRotation = 
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(atan2f(direction.x, direction.z), 0.0f, 0.0f);	// 移動方向ベクトルから目標のクォータニオンを計算

	DirectX::SimpleMath::Quaternion slerpRotation  = 
		DirectX::SimpleMath::Quaternion::Slerp(m_player->GetQuaternion(), targetRotation, 0.2f);			// 線形補完する

	slerpRotation.Normalize();				//ノーマライズする

	m_player->SetAngle(slerpRotation);			// 現在の角度をプレイヤーのクォータニオンにいれる
}

/// <summary>
/// ステートの変更
/// </summary>
/// <param name="keyboardStateTracker"></param>
void PlayerRunning::ChangeStateKey(
	const DirectX::Keyboard::State& keyboardStateTracker
)
{
	if (keyboardStateTracker.IsKeyUp(DirectX::Keyboard::Keys::D) && keyboardStateTracker.IsKeyUp(DirectX::Keyboard::Keys::A) &&
		keyboardStateTracker.IsKeyUp(DirectX::Keyboard::Keys::W) && keyboardStateTracker.IsKeyUp(DirectX::Keyboard::Keys::S))			// キーの開放で、Standingに遷移
	{
		m_player->ChangeState(m_player->GetStanding());
	}
	if (keyboardStateTracker.IsKeyDown(DirectX::Keyboard::Keys::Space))					// スペースキーでジャンプに遷移
	{
		m_player->ChangeState(m_player->GetJumping());
	}
	const auto& mouseState = m_commonResources->GetInputManager()->GetMouseState();		//マウスの情報取得
	if (mouseState.rightButton == 1 && m_player->GetBallTakeFlag() == false)			// 受け状態に変更	
	{
		m_player->ChangeState(m_player->GetTake());
	}
	if (mouseState.leftButton == 1 && m_player->GetBallTakeFlag() == true)				// 投げ状態に変更
	{
		m_player->ChangeState(m_player->GetThrow());
	}
}


/// <summary>
/// プレイヤーの子パーツを動かす処理
/// </summary>
void PlayerRunning::MoveChild()
{
	MoveHand();
	MoveTail();
	MoveBody();
}

/// <summary>
/// 手の動き
/// </summary>
void PlayerRunning::MoveHand()
{
	auto rightHand = m_player->GetBody()->GetRightHand();		// 右手取得
	auto leftHand = m_player->GetBody()->GetLeftHand();			// 左手取得

	// 振りモーションのパラメーター
	float swingSpeed = 10.0f;
	float swingAmount = 0.8f;

	// 振りモーションを追加
	float swing = sin(m_player->GetTotalTime() * swingSpeed) * swingAmount;

	// プレイヤーの右手の位置を計算
	auto rightQuaternion =  DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(0.0f, swing, 0.0f);
	auto leftQuaternion = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(0.0f, -swing, 0.0f);

	rightHand->SetAddQuaternion(rightQuaternion);
	leftHand->SetAddQuaternion(leftQuaternion);
}

/// <summary>
/// 胴体の動き
/// </summary>
void PlayerRunning::MoveBody()
{



}

/// <summary>
/// しっぽの動き
/// </summary>
void PlayerRunning::MoveTail()
{
	auto tail = m_player->GetBody()->GetTail();
	// 振りモーションのパラメーター
	float swingSpeed = 7.0f;
	float swingAmount = 0.6f;

	// 振りモーションを追加
	float swing = sin(m_player->GetTotalTime() * swingSpeed) * swingAmount;
	auto swingQuaternion = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(0.0f, 0.0f, swing);

	tail->SetAddQuaternion(swingQuaternion);

}