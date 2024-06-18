//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/05/27
// <file>			Ball.cpp
// <概要>			ボールの中心クラス
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"Ball.h"
#include"Game/CommonResources.h"
#include"Libraries/NakashiLib/ResourcesManager.h"
#include"Framework/DeviceResources.h"

// SI単位系を適用する
// 重力加速度 m/s^2
const float Ball::GRAVITATION_ACCELERATION = -0.0980665f;
// 質量 kg
const float Ball::MASS = 0.00450f;
// 半径 m
const float Ball::RADIUS = 0.0011f;
// 直径 m
const float Ball::DIAMETER = 0.0022f;
// 空気抵抗係数(Cd)
const float Ball::DRAG_COEFFICIENT = 0.002f;
// 空気密度(ρ) kg/m^3
const float Ball::AIR_DENSITY = 0.0122f;
//サッカーボール直径断面積 m^2
const float Ball::CROSS_SECTION = (0.25f * DirectX::XM_PI) * DIAMETER * DIAMETER;
// 空気抵抗係数(k)
// ボールに働く空気抵抗はボールの速度の二乗に比例する
const float Ball::AIR_RESISTANCE = -0.5f * AIR_DENSITY * CROSS_SECTION * DRAG_COEFFICIENT;
// 摩擦係数
const float Ball::FRICTION = -0.0004f;
// 交差判定距離
const float Ball::INTERSECT_JUDGEMENT_DISTANCE = 10.0f;

/// <summary>
/// コンストラクタ
/// </summary>
Ball::Ball()
	:
	m_commonResources{},
	m_position{},
	m_velocity{},
	m_friction{},
	m_ballModel{},
	m_rotate{},
	m_horizontal{},
	m_forward{},
	m_speed{},
	m_ballMove{},
	m_currentState{},
	m_ballThrow{},
	m_player{},
	m_acceleration{},
	m_radius{RADIUS}
{
	m_commonResources = CommonResources::GetInstance();
}

/// <summary>
/// デストラクタ
/// </summary>
Ball::~Ball()
{

}

/// <summary>
/// 初期化処理
/// </summary>
/// <param name="resources">共通リソース</param>
/// <param name="player">プレイヤー取得</param>
void Ball::Initialize(Player* player)
{

	m_player = player;


	m_commonResources->GetResourcesManager()->CreateModel(L"Ball", L"Ball.cmo");		// Resourcesにモデルを作成

	m_ballMove = std::make_unique<BallMove>(this);		// 立ち状態取得

	m_ballThrow = std::make_unique<BallThrow>(this);		// 投げ状態取得

	m_currentState = m_ballMove.get();
	m_currentState->OnEnter();

}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="keyboardStateTracke">キーボード</param>
/// <param name="elapsedTime">時間</param>
void Ball::Update(float elapsedTime)
{

	m_currentState->Update();
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="view">カメラのビュー</param>
/// <param name="proj">カメラの投影</param>
void Ball::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{
	m_view = view;
	m_projection = proj;
	m_currentState->Render();

}

/// <summary>
/// 後処理
/// </summary>
void Ball::Finalize()
{

}

/// <summary>
/// ボールのモデルを取得
/// </summary>
/// <returns></returns>
DirectX::Model* Ball::GetBallModel()
{
	return m_commonResources->GetResourcesManager()->GetModel(L"Ball");
}

/// <summary>
/// ステートの変更
/// </summary>
/// <param name="currentState">ステートの状態</param>
void Ball::ChangeState(IState* currentState)
{
	m_currentState->OnExit();		// 現在のステートを出る
	m_currentState = currentState;	// ステート変更
	m_currentState->OnEnter();		// 次のステートに入る
}