//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/05/27
// <file>			BallThrow.cpp
// <概要>			ボールが投げられた状態
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"Game/Ball/BallThrow.h"
#include"Framework/DeviceResources.h"
#include"Game/CommonResources.h"
#include"Libraries/NakashiLib/InputManager.h"
#include"Game/Player/PlayerPart/PlayerBody.h"
#include"Game/Player/PlayerPart/PlayerRightHand.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="ball">ボール</param>
/// <param name="resources">共通リソース</param>
BallThrow::BallThrow(
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
BallThrow::~BallThrow()
{

}

/// <summary>
/// このステートに入った時
/// </summary>
void BallThrow::OnEnter()
{
	m_ball->SetPosition(m_ball->GetPlayer()->GetBody()->GetRightHand()->GetPosition());
}

/// <summary>
/// このステートを抜けたとき
/// </summary>
void BallThrow::OnExit()
{
	// 向き取得
	DirectX::SimpleMath::Vector3 direction(0.0f,0.0f,-1.0f);	// 前方向の成分

	DirectX::SimpleMath::Matrix rotationZ =
		DirectX::SimpleMath::Matrix::CreateFromQuaternion(m_ball->GetPlayer()->GetCameraQuaternion());			// Z軸周りの回転行列を生成する
	 rotationZ._32 =  0.1f;

	// 上下方向を計算する
	direction = DirectX::SimpleMath::Vector3::Transform(direction * m_ball->GetPlayer()->GetForceCharge(), rotationZ);
	m_ball->SetVelocity(direction);				//速度設定 
}

/// <summary>
/// 初期化処理
/// </summary>
void BallThrow::Initialize()
{

}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="keyboardStateTracker">キーボード</param>
void BallThrow::Update()
{

	ToFollow();
	ChangeState();
}

/// <summary>
/// 描画処理
/// </summary>
void BallThrow::Render()
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
void BallThrow::Finalize()
{

}

/// <summary>
/// ステートの変更
/// </summary>
/// <param name="keyboardStateTracker"></param>
void BallThrow::ChangeState()
{
	if (m_ball->GetPlayer()->GetBallTakeFlag() == false)
	{
		m_ball->ChangeState(m_ball->GetMove());
	}
}

/// <summary>
/// プレイヤーに追従する
/// </summary>
void BallThrow::ToFollow()
{
	DirectX::SimpleMath::Matrix handWorldMatrix = m_ball->GetPlayer()->GetBody()->GetRightHand()->GetWorldMatrix();
	DirectX::SimpleMath::Vector3 ballPos = handWorldMatrix.Translation(); // ワールド行列から位置を取得

	m_ball->SetPosition(ballPos);

}