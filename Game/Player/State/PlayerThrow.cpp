//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/01
// <file>			PlayerThrow.cpp
// <概要>		　　プレイヤーの投げるステート
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include"pch.h"
#include"PlayerThrow.h"
#include"Game/CommonResources.h"
#include"framework/DeviceResources.h"
#include"Libraries/NakashiLib/InputManager.h"
#include"Game/Player/PlayerPart/PlayerBody.h"
#include"Game/Player/PlayerPart/PlayerLeftHand.h"
#include"Game/Player/PlayerPart/PlayerRightHand.h"
#include"Game/Player/PlayerPart/PlayerTail.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="player">プレイヤー</param>
/// <param name="resources">共通リソース</param>
PlayerThrow::PlayerThrow(
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
PlayerThrow::~PlayerThrow()
{

}

/// <summary>
/// このステートパターンに入った時
/// </summary>
void PlayerThrow::OnEnter()
{
	m_player->SetVelocity(m_player->GetVelocity());
	m_player->SetAngle(m_player->GetQuaternion());
	m_player->SetForceCharge(0.0f);
	
}

/// <summary>
/// このステートパターンを抜けた時
/// </summary>
void PlayerThrow::OnExit()
{
	m_player->SetBallTakeFlag(false);
}

/// <summary>
/// 初期化処理
/// </summary>
void PlayerThrow::Initialize()
{

}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="keyboardStateTracker">キーボード</param>
void PlayerThrow::Update()
{
	auto keyboardStateTracker = m_commonResources->GetInputManager()->GetKeyboardState();
	//プレイヤー移動
	m_player->SetPosition(m_player->GetPosition() + m_player->GetVelocity());
	m_player->SetVelocity(m_player->GetVelocity() * m_player->GetFriction());
	// 既に持っているならこのステートを抜け、立ち状態に移る

	MoveChild();

	AddForce();

	ChangeStateKey(keyboardStateTracker);
	ChangeDirectionMove(keyboardStateTracker);
}

/// <summary>
/// 描画処理
/// </summary>
void PlayerThrow::Render()
{
}

/// <summary>
/// 終了処理
/// </summary>
void PlayerThrow::Finalize()
{

}

/// <summary>
/// キーの変更によりステートを変更する
/// </summary>
/// <param name="keyboardStateTracker">キーボード</param>
void PlayerThrow::ChangeStateKey(
	const DirectX::Keyboard::State& keyboardStateTracker
)
{
	const auto& mouseState = m_commonResources->GetInputManager()->GetMouseState();
	if (mouseState.leftButton == 0)
	{
		m_player->ChangeState(m_player->GetStanding());			//立ち状態に変更
	}
}

/// <summary>
/// プレイヤーの向き変更
/// </summary>
/// <param name="keyboardStateTracker">キーボード</param>
void PlayerThrow::ChangeDirectionMove(
	const DirectX::Keyboard::State& keyboardStateTracker
)
{
	DirectX::SimpleMath::Vector3 direction = DirectX::SimpleMath::Vector3::Zero;				// 停止処理

	// プレイヤーの移動	  カメラの方向を前として角度を含めた移動
	if (keyboardStateTracker.IsKeyDown(DirectX::Keyboard::Keys::W)) { direction += DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3::Forward, m_player->GetCameraQuaternion()); }
	if (keyboardStateTracker.IsKeyDown(DirectX::Keyboard::Keys::D)) { direction += DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3::Right, m_player->GetCameraQuaternion()); }
	if (keyboardStateTracker.IsKeyDown(DirectX::Keyboard::Keys::A)) { direction += DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3::Left, m_player->GetCameraQuaternion()); }
	if (keyboardStateTracker.IsKeyDown(DirectX::Keyboard::Keys::S)) { direction += DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3::Backward, m_player->GetCameraQuaternion()); }

	direction.y = 0.0f;						// y軸の成分をなくす

	direction.Normalize();					// 移動量の正規化

	SlarpRotate(direction);					//プレイヤーの移動と角度から補完をする

	DirectX::SimpleMath::Vector3 velocity = direction * 0.1f;	// 移動量の補正

	m_player->SetVelocity(velocity);		// 実際に移動させる
}

/// <summary>
/// 向き変更時の補正
/// </summary>
/// <param name="direction">向き</param>
void PlayerThrow::SlarpRotate(
	DirectX::SimpleMath::Vector3 direction
)
{
	if (direction.LengthSquared() < 1e-2f) { return; }				// 移動量がほとんどないなら計算しない( 1の10-2乗以下 )

	DirectX::SimpleMath::Quaternion targetRotation = 
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(atan2f(direction.x, direction.z), 0.0f, 0.0f);	// 移動方向ベクトルから目標のクォータニオンを計算

	DirectX::SimpleMath::Quaternion slerpRotation = 
		DirectX::SimpleMath::Quaternion::Slerp(m_player->GetQuaternion(), targetRotation, 0.2f);		// 線形補完する

	slerpRotation.Normalize();							//ノーマライズさせる

	m_player->SetAngle(slerpRotation);		// 現在の角度をプレイヤーのクォータニオンにいれる
}

/// <summary>
/// 力を加える処理
/// </summary>
void PlayerThrow::AddForce()
{
	const auto& mouseState = m_commonResources->GetInputManager()->GetMouseState();
	if (mouseState.leftButton == 1)
	{
		float force = 0.02f;
		if (m_player->GetForceCharge() <= 4.0f)
			m_player->SetForceCharge(m_player->GetForceCharge() + force);	//力を＋する
	}
}

/// <summary>
/// 子パーツの動き
/// </summary>
void PlayerThrow::MoveChild()
{
	MoveHand();
}

/// <summary>
/// 手の動き
/// </summary>
void PlayerThrow::MoveHand()
{
	auto rightHand = m_player->GetBody()->GetRightHand();
	auto leftHand = m_player->GetBody()->GetLeftHand();

	DirectX::SimpleMath::Quaternion TakePointRightQuaternion = 
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(1.5f, -2.0f, 1.0f);

	DirectX::SimpleMath::Quaternion TakePointLeftQuaternion = 
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(1.0f, 1.0f, -1.0f);

	DirectX::SimpleMath::Quaternion slerpRotationRight =
		DirectX::SimpleMath::Quaternion::Slerp(rightHand->GetAddQUaternion(), TakePointRightQuaternion, 0.2f);
	DirectX::SimpleMath::Quaternion slerpRotationLeft =
		DirectX::SimpleMath::Quaternion::Slerp(leftHand->GetAddQUaternion(), TakePointLeftQuaternion, 0.2f);// 線形補完する

	rightHand->SetAddQuaternion(slerpRotationRight);
	leftHand->SetAddQuaternion(slerpRotationLeft);
}

void PlayerThrow::MoveTail()
{
}