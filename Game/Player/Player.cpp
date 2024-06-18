//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/01
// <file>			Player.cpp
// <概要>		　　プレイヤーの中心核
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"Player.h"
#include"Game/Player/PlayerPart/PlayerBody.h"
#include"Game/CommonResources.h"
#include"Libraries/NakashiLib/InputManager.h"
#include"Framework/DeviceResources.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="parent">親</param>
/// <param name="position">位置</param>
/// <param name="quaternion">回転</param>
Player::Player(
	IComponent* parent, 
	const DirectX::SimpleMath::Vector3& position, 
	const DirectX::SimpleMath::Quaternion& quaternion
)
	:
	PlayerBase(parent , position , quaternion),
	m_commonResources{},
	m_partID{PlayerBase::PartID::ROOT} ,
	m_position{position},
	m_velocity{},
	m_quaternion{quaternion},
	m_mass{},
	m_worldMatrix{},
	m_acceleration{ 0.0f,-0.4f,0.0f },
	m_gravity{ 0.0f,-0.098f , 0.0f },
	m_friction{ 0.8f ,0.0f,0.8f },
	m_ground{},
	m_cameraProjection{},
	m_cameraView{},
	m_cameraQuaternion{},
	m_ballTaking{false},
	m_forceCharge{},
	m_body{},
	m_standing{},
	m_currentState{},
	m_jumping{},
	m_runnning{},
	m_throw{},
	m_taking{},
	m_totalTime{},
	m_nodeNumber(0)
{
	m_commonResources = CommonResources::GetInstance();
}

/// <summary>
/// デストラクタ
/// </summary>
Player::~Player()
{

}

/// <summary>
/// 初期化処理
/// </summary>
/// <param name="resources">共通リソース</param>
void Player::Initialize()
{					

	PlayerBase::Initialize();				// ベースの初期化を呼ぶ

	auto body = std::make_unique<PlayerBody>(				// プレイヤーボディを作成
		this,
		DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f),
		DirectX::SimpleMath::Quaternion::Identity
	);
	m_body = body.get();									// 呼び出し用bodyに格納
	SetChild(std::move(body));					// プレイヤーの子にbodyを設定
	
	m_standing = std::make_unique<PlayerStanding>(this);		// 立ち状態
	m_jumping = std::make_unique<PlayerJumping>(this);		// ジャンプ状態
	m_runnning = std::make_unique<PlayerRunning>(this);		// 移動状態
	m_taking = std::make_unique<PlayerTake>(this);			// 取る状態
	m_throw = std::make_unique<PlayerThrow>(this);			// 投げ状態

	m_currentState = m_standing.get();			// 初期の状態は立ち状態
	m_currentState->OnEnter();					// 最初のステート状態に移行
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="timer">時間</param>
/// <param name="position">位置</param>
/// <param name="quaternion">回転</param>
void Player::Update(
	const DX::StepTimer& timer, 
	const DirectX::SimpleMath::Vector3& position,
	const DirectX::SimpleMath::Quaternion& quaternion
)
{
	UNREFERENCED_PARAMETER(timer);

	m_totalTime += timer.GetElapsedSeconds();

	m_currentState->Update();											// ステートパターンを回す

	PlayerBase::Update(														// ベースの更新
		timer,
		m_position + GetInitialPosition(),
		m_quaternion
	);
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="view">カメラのビュー</param>
/// <param name="projection">カメラの投影</param>
void Player::Render(
	const DirectX::SimpleMath::Matrix& view ,
	const DirectX::SimpleMath::Matrix& projection
)
{
	// パーツを描画
 	PlayerBase::Render(view , projection);
}

/// <summary>
/// ステートパターンの変更
/// </summary>
/// <param name="currentState">ステートの状態</param>
void Player::ChangeState(
	IState* currentState
)
{
	m_currentState->OnExit();		// 現在のステートを出る
	m_currentState = currentState;	// ステート変更
	m_currentState->OnEnter();		// 次のステートに入る
}

