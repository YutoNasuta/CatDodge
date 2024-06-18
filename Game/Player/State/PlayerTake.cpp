//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/01
// <file>			PlayerTake.cpp
// <概要>		　　プレイヤーの受け取るステート
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"PlayerTake.h"
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
PlayerTake::PlayerTake(
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
PlayerTake::~PlayerTake()
{
}

/// <summary>
/// このステートに入った時
/// </summary>
void PlayerTake::OnEnter()
{
	m_player->SetVelocity(m_player->GetVelocity());
	m_player->SetAngle(m_player->GetQuaternion());
}

/// <summary>
/// このステートを抜けた時
/// </summary>
void PlayerTake::OnExit()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void PlayerTake::Initialize()
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="keyboardStateTracker">キーボード</param>
void PlayerTake::Update()
{
	auto keyboardStateTracker = m_commonResources->GetInputManager()->GetKeyboardState();

	//プレイヤー移動
	m_player->SetPosition(m_player->GetPosition() + m_player->GetVelocity());
	m_player->SetVelocity(m_player->GetVelocity() * m_player->GetFriction());

	MoveChild();
	if (keyboardStateTracker.G)
	{
		BallTakeMove();									// ボールを取った状態にする処理	
	}
	
	ChangeStateKey(keyboardStateTracker);			// キーの変更でステート変更する処理
	ChangeDirection(keyboardStateTracker);			// 向きの補正をする
}

/// <summary>
/// 描画処理
/// </summary>
void PlayerTake::Render()
{
}

/// <summary>
/// 終了処理
/// </summary>
void PlayerTake::Finalize()
{

}

/// <summary>
/// ステートを変更する
/// </summary>
/// <param name="keyboardStateTracker">キーボード</param>
void PlayerTake::ChangeStateKey(
	const DirectX::Keyboard::State& keyboardStateTracker
)
{
	const auto& mouseState = m_commonResources->GetInputManager()->GetMouseState();
	if (mouseState.rightButton == 0)
	{
		m_player->ChangeState(m_player->GetStanding());				//マウスの開放でスタンディング状態に移行
	}
}

/// <summary>
/// ボールを取る動き
/// </summary>
void PlayerTake::BallTakeMove()
{
	m_player->SetBallTakeFlag(true);	
}

/// <summary>
/// 向きの変更
/// </summary>
/// <param name="keyboardStateTracker">キーボード</param>
void PlayerTake::ChangeDirection(
	const DirectX::Keyboard::State& keyboardStateTracker
)
{
	DirectX::SimpleMath::Vector3 direction = DirectX::SimpleMath::Vector3::Zero;	// 停止処理

	direction +=															
		DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3::Forward, m_player->GetCameraQuaternion());	//カメラの方向に向く
	
	direction.y = 0.0f;			//y軸成分をなくす

	direction.Normalize();		// 移動量の正規化

	SlarpRotate(direction);		//プレイヤーの移動と角度から補完をする

}

/// <summary>
/// 向きの補完
/// </summary>
/// <param name="direction">向き</param>
void PlayerTake::SlarpRotate(
	DirectX::SimpleMath::Vector3 direction
)
{
	if (direction.LengthSquared() < 1e-2f) { return; }	// 移動量がほとんどないなら計算しない( 1の10-2乗以下 )

	DirectX::SimpleMath::Quaternion targetRotation =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(atan2f(direction.x, direction.z), 0.0f, 0.0f);		// 移動方向ベクトルから目標のクォータニオンを計算

	DirectX::SimpleMath::Quaternion slerpRotation = 
		DirectX::SimpleMath::Quaternion::Slerp(m_player->GetQuaternion(), targetRotation, 0.2f);			// 線形補完する
	slerpRotation.Normalize();

	m_player->SetAngle(slerpRotation);		// 現在の角度をプレイヤーのクォータニオンにいれる
}
void PlayerTake::MoveChild()
{
	MoveHand();
	MoveTail();
}

/// <summary>
/// 腕の動き
/// </summary>
void PlayerTake::MoveHand()
{
	auto rightHand = m_player->GetBody()->GetRightHand();		// 右手取得
	auto leftHand = m_player->GetBody()->GetLeftHand();			// 左手取得

	DirectX::SimpleMath::Quaternion TakePointRightQuaternion = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(0.5f,5.0f,0.5f);
	DirectX::SimpleMath::Quaternion TakePointLeftQuaternion = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(-0.5f, 5.0f, -0.5f);
		DirectX::SimpleMath::Quaternion slerpRotationRight =
		DirectX::SimpleMath::Quaternion::Slerp(rightHand->GetAddQUaternion(), TakePointRightQuaternion, 0.2f);
	DirectX::SimpleMath::Quaternion slerpRotationLeft =
		DirectX::SimpleMath::Quaternion::Slerp(leftHand->GetAddQUaternion(), TakePointLeftQuaternion, 0.2f);// 線形補完する

	rightHand->SetAddQuaternion(slerpRotationRight);
	leftHand->SetAddQuaternion(slerpRotationLeft);

}

/// <summary>
/// しっぽの動き
/// </summary>
void PlayerTake::MoveTail()
{
	auto tail = m_player->GetBody()->GetTail();
	// 振りモーションのパラメーター
	float swingSpeed = 1.0f;
	float swingAmount = 0.6f;

	// 振りモーションを追加
	float swing = sin(m_player->GetTotalTime() * swingSpeed) * swingAmount;
	auto swingQuaternion = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(0.0f, 0.0f, swing);


	tail->SetAddQuaternion(swingQuaternion);
}