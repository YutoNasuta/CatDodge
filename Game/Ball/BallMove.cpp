//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/05/27
// <file>			BallThrow.cpp
// <概要>			ボールの動き（通常状態）
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"Game/Ball/BallMove.h"
#include"Framework/DeviceResources.h"
#include"Game/CommonResources.h"
#include"Libraries/NakashiLib/InputManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="ball">ボール</param>
/// <param name="resources">共通リソース</param>
BallMove::BallMove(
	Ball* ball
)
:
	m_ball(ball)
{
	m_commonResources = CommonResources::GetInstance();
}

/// <summary>
/// デストラクタ
/// </summary>
BallMove::~BallMove()
{

}

/// <summary>
/// このステートに入った時
/// </summary>
void BallMove::OnEnter()
{
	m_ball->SetAcceleration(DirectX::SimpleMath::Vector3(0.0f, Ball::GRAVITATION_ACCELERATION, 0.0f));		// 加速度
	m_ball->SetVelocity(m_ball->GetVelocity());
}

/// <summary>
/// このステートを抜けたとき
/// </summary>
void BallMove::OnExit()
{

}

/// <summary>
/// 初期化処理
/// </summary>
void BallMove::Initialize()
{

}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="keyboardStateTracker">キーボード</param>
void BallMove::Update()
{
	auto keyboardStateTracker = m_commonResources->GetInputManager()->GetKeyboardState();
	ChangeState();

	if (keyboardStateTracker.IsKeyDown(DirectX::Keyboard::Keys::I))
	{
		m_ball->SetDebugLog(2);
	}
	if (keyboardStateTracker.IsKeyDown(DirectX::Keyboard::Keys::Up))
	{
		m_ball->SetVelocity(DirectX::SimpleMath::Vector3::Forward);
	}
	if (keyboardStateTracker.IsKeyDown(DirectX::Keyboard::Keys::Down))
	{
		m_ball->SetVelocity(DirectX::SimpleMath::Vector3::Backward);
	}
	if (keyboardStateTracker.IsKeyDown(DirectX::Keyboard::Keys::Left))
	{
		m_ball->SetVelocity(DirectX::SimpleMath::Vector3::Left);
	}
	if (keyboardStateTracker.IsKeyDown(DirectX::Keyboard::Keys::Right))
	{
		m_ball->SetVelocity(DirectX::SimpleMath::Vector3::Right);
	}

	//  重力加速度が設定されていない場合は更新しない
	if (m_ball->GetAcceleration().y == 0.0f)
		return;			


	// 速度の計算
	m_ball->SetVelocity(m_ball->GetVelocity() + m_ball->GetAcceleration());
	// 向きの設定
	DirectX::SimpleMath::Vector3 heading = m_ball->GetVelocity();
	// 空気抵抗により減速
	/*m_ball->SetVelocity(heading * Ball::AIR_RESISTANCE);*/
	// 位置を計算
	m_ball->SetPosition(m_ball->GetPosition() + m_ball->GetVelocity());

	// ボールの回転軸を設定
	DirectX::SimpleMath::Vector3 axis = DirectX::SimpleMath::Vector3(heading.y, 0.0f, -heading.x);
	if (m_ball->GetVelocity().Length())
	{
		// 回転角を計算
		float angle = (m_ball->GetVelocity().Length() / m_ball->GetRadius()) * 0.006f;
		// クォータニオンを生成
		m_ball->SetQuaternion(m_ball->GetQuaternion() * DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(axis, angle));
	}

	// ボールを弾ませる
	if (m_ball->GetPosition().y <= m_ball->GetGround().y)
	{
		// 位置を補正する
		m_ball->SetPosition(DirectX::SimpleMath::Vector3(m_ball->GetPosition().x, m_ball->GetGround().y, m_ball->GetPosition().z));
		// 速度の反転
		m_ball->SetVelocity(DirectX::SimpleMath::Vector3(m_ball->GetVelocity().x, -m_ball->GetVelocity().y, m_ball->GetVelocity().z));
		// 減速率（８５％）を適用
		m_ball->SetVelocity(m_ball->GetVelocity() * 0.85f);
	}
	// 速度がなくなってきたら
	if (m_ball->GetVelocity().Length() < 0.1f)
	{
		// 位置の設定
		m_ball->SetPosition(m_ball->GetPosition());
		// 加速度の初期化
		m_ball->SetAcceleration(DirectX::SimpleMath::Vector3::Zero);
		// 速度の初期化
		m_ball->SetVelocity(DirectX::SimpleMath::Vector3::Zero);
	}
	


	
}

/// <summary>
/// 描画処理
/// </summary>
void BallMove::Render()
{
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();

	DirectX::SimpleMath::Matrix world =
		DirectX::SimpleMath::Matrix::CreateFromQuaternion(m_ball->GetQuaternion());
	world *= DirectX::SimpleMath::Matrix::CreateTranslation(m_ball->GetPosition());

	// ビュー行列を取得する
	m_ball->GetBallModel()->Draw(
		context, *states,
		world,
		m_ball->GetView(),
		m_ball->GetProj()
	);

}

/// <summary>
/// 後処理
/// </summary>
void BallMove::Finalize()
{

}

/// <summary>
/// ステート変更
/// </summary>
/// <param name="keyboardStateTracker"></param>
void BallMove::ChangeState()
{
	if (m_ball->GetPlayer()->GetBallTakeFlag() == true)
	{
		// 受け状態に変更
		m_ball->ChangeState(m_ball->GetThrow());
	}
}

