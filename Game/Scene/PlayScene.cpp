/*
	@file	PlayScene.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "PlayScene.h"
#include "Game/CommonResources.h"
#include "framework/DeviceResources.h"

#include"Game/Resources.h"

#include "Libraries/NakashiLib/DebugString.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/NakashiLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>

#include"Game/Player/Player.h"
#include"Game/Player/PlayerPart/PlayerBody.h"
#include"Game/Player/PlayerPart/PlayerLeftHand.h"
#include"Game/Player/PlayerPart/PlayerRightHand.h"
#include"Game/Enemy/Enemy.h"

#include"Game/Stage/GenerateStage.h"
#include"Libraries/NakashiLib/CollisionMesh.h"
#include"Libraries/NakashiLib/CreateRay.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
PlayScene::PlayScene()
	:
	m_commonResources{},
	m_gridFloor{},
	m_projection{},
	m_isChangeScene{},
	m_angle{},
	/*m_player{},*/
	m_ground{},
	m_ball{},
	m_tpsCamera{},
	m_stage{}
{
	m_commonResources = CommonResources::GetInstance();
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
PlayScene::~PlayScene()
{
	// do nothing.
}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void PlayScene::Initialize()
{


	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();


	m_resources = std::make_unique<NakashiLib::Resources>();
	


	// グリッド床を作成する
	m_gridFloor = std::make_unique<mylib::GridFloor>(device, context, states);

	// デバッグカメラを作成する
	RECT rect = m_commonResources->GetDeviceResources()->GetOutputSize();
	//m_debugCamera = std::make_unique<mylib::DebugCamera>();
	//m_debugCamera->Initialize(rect.right, rect.bottom);

	// 射影行列を作成する
	m_projection = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		DirectX::XMConvertToRadians(45.0f),
		static_cast<float>(rect.right) / static_cast<float>(rect.bottom),
		0.1f, 100.0f
	);


	



	// 回転角を初期化する（度）
	m_angle = 0;

	// シーン変更フラグを初期化する
	m_isChangeScene = false;

	// プレイヤーオブジェクトの生成
	/*m_player = std::make_unique<Player>(this);
	m_player->Initialize(m_commonResources);*/

	

	m_ground = DirectX::SimpleMath::Vector3::Zero;

	

	

	// プレイヤー生成
	m_player = std::make_unique<Player>(
		nullptr,
		DirectX::SimpleMath::Vector3(0.0f, 0.5f, 0.0f),
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(0.0f)));
	
	m_player->Initialize();
	// tpsカメラを作る
	m_tpsCamera = std::make_unique<TPSCamera>(m_player->GetPosition());

	m_ball = std::make_unique<Ball>();
	m_ball->Initialize(m_player.get());

	m_enemy = std::make_unique<Enemy>(
		nullptr,
		DirectX::SimpleMath::Vector3(0.0f, 0.5f, 0.0f),
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(0.0f)));

	m_enemy->Initialize();

	m_stage = std::make_unique<GenerateStage>();
	m_stage->Initialize(device , context);

	m_ray = std::make_unique<NakashiLib::CreateRay>();
	m_ray->Initialize(context , 1.0f);

}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void PlayScene::Update(float elapsedTime)
{

	UNREFERENCED_PARAMETER(elapsedTime);

	// デバッグカメラを更新する
	//m_debugCamera->Update(m_commonResources->GetInputManager());




	m_rayPosition.x = m_player->GetPosition().x;
	m_rayPosition.z = m_player->GetPosition().z;

	m_ballRayPosition.x = m_ball->GetPosition().x;
	m_ballRayPosition.y = m_ball->GetPosition().y;


	// キーボードステートトラッカーを取得する
	const auto& kbTracker = m_commonResources->GetInputManager()->GetKeyboardTracker();

	if (kbTracker->IsKeyPressed(DirectX::Keyboard::Keys::K))
	{
		m_isChangeScene = true;
	}

	// スペースキーが押されたら
	/*if (kbTracker->IsKeyPressed(DirectX::Keyboard::Space))
	{
		m_isChangeScene = true;
	}*/
	// プレイヤーのアップデートを回す
	//m_player->Update(m_commonResources->GetInputManager()->GetKeyboardState(), m_tpsCamera->GetCameraRotate());



		// 線分表示用
	//DirectX::SimpleMath::Vector3 startVec = m_rayPosition;
	//startVec.y += 10.0f;
	//DirectX::SimpleMath::Vector3 endVec = m_rayPosition;
	//endVec.y -= 2.0f;
	//// 線分表示用
	//DirectX::SimpleMath::Vector3 startVec2 = m_ballRayPosition;
	//startVec2.y += 10.0f;
	//DirectX::SimpleMath::Vector3 endVec2 = m_ballRayPosition;
	//endVec2.y -= 10.0f;


	//DirectX::SimpleMath::Ray ray{ startVec , DirectX::SimpleMath::Vector3::Down };
	//DirectX::SimpleMath::Ray Ballray{ startVec2 , DirectX::SimpleMath::Vector3::Down };

	m_ray->Update(m_player->GetPosition());

	DirectX::SimpleMath::Vector3 hitposition;
	DirectX::SimpleMath::Vector3 normal;
	int number;
	int ishit;

	/*DirectX::SimpleMath::Vector3 hitposition2;
	DirectX::SimpleMath::Vector3 normal2;
	int number2;
	int ishit2;*/

	
	ishit = m_stage->GetCollisionMesh()->IntersectRay(m_ray->GetRay(), &hitposition, &normal, &number);

	if (ishit)
	{
		m_ground.y = hitposition.y;
		m_player->SetGround(m_ground);
		if(m_player->GetNowState() != m_player->GetJumping())
		m_player->SetPosition(hitposition + DirectX::SimpleMath::Vector3(0.0f,0.4f,0.0f));
	}

	/*ishit2 = m_stage->GetCollisionMesh()->IntersectRay(Ballray, &hitposition2, &normal2, &number2);

	if (ishit2)
	{
		
		m_ball->SetGround(hitposition2);
	}*/

	//	ステップタイマーの取得
	const DX::StepTimer& stepTimer = *(m_commonResources->GetStepTimer());
	DirectX::SimpleMath::Vector3 position = DirectX::SimpleMath::Vector3::Zero;
	DirectX::SimpleMath::Quaternion quaternion = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(0.0f));
	
	m_tpsCamera->Update(m_player->GetBody()->GetPosition());
	m_player->SetCameraQuaternion(m_tpsCamera->GetCameraRotate());
	m_player->Update(stepTimer, position, quaternion);
	
	m_ball->Update(elapsedTime);

	m_enemy->Update(stepTimer, position, quaternion);
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void PlayScene::Render()
{
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();

#ifdef _DEBUG
	// デバッグ情報を表示する
	auto debugString = m_commonResources->GetDebugString();
	debugString->AddString("Play Scene");
	debugString->AddString("P:Body:Pos: x =%f, y=%f, z=%f", m_player->GetBody()->GetPosition().x, m_player->GetBody()->GetPosition().y, m_player->GetBody()->GetPosition().z);
	debugString->AddString("P:RightHand:Pos: x=%f, y=%f, z=%f", m_player->GetBody()->GetRightHand()->GetPosition().x, m_player->GetBody()->GetRightHand()->GetPosition().y, m_player->GetBody()->GetRightHand()->GetPosition().z);
	debugString->AddString("P:LeftHand:Pos: x=%f, y=%f, z=%f", m_player->GetBody()->GetLeftHand()->GetPosition().x, m_player->GetBody()->GetLeftHand()->GetPosition().y, m_player->GetBody()->GetLeftHand()->GetPosition().z);
	debugString->AddString("P:Acceleration: x = %f , y = %f , z = %f", m_player->GetAcceleration().x, m_player->GetAcceleration().y, m_player->GetAcceleration().z);
	debugString->AddString("P:Friction: x = %f , y = %f , z = %f", m_player->GetFriction().x, m_player->GetFriction().y, m_player->GetFriction().z);
	debugString->AddString("CQuaternion: x=%f, y=%f, z=%f, w=%f", m_tpsCamera->GetCameraRotate().x, m_tpsCamera->GetCameraRotate().y, m_tpsCamera->GetCameraRotate().z, m_tpsCamera->GetCameraRotate().w);
	debugString->AddString("Ground: x=%f, y=%f, z=%f", m_player->GetGround().x, m_player->GetGround().y, m_player->GetGround().z);
	/*debugString->AddString("BallPosition: x=%f, y=%f, z=%f, w=%f", m_ball->GetPosition().x , m_ball->GetPosition().y , m_ball->GetPosition().z);
	debugString->AddString("BallQuaternion: x = %f, y = %f, z =%f, w = %f", m_ball->GetQuaternion().x, m_ball->GetQuaternion().y, m_ball->GetQuaternion().z, m_ball->GetQuaternion().w);*/
	debugString->AddString("BallTake %f", m_player->GetBallTakeFlag());


	if (m_player->GetNowState() == m_player->GetStanding()) { debugString->AddString("P::standing"); }
	else if (m_player->GetNowState() == m_player->GetJumping()) { debugString->AddString("P::Jumping"); }
	else if (m_player->GetNowState() == m_player->GetRunning()) { debugString->AddString("P::Runnning"); }
	else if (m_player->GetNowState() == m_player->GetTake()) { debugString->AddString("P::Take"); }
	else if (m_player->GetNowState() == m_player->GetThrow()) { debugString->AddString("P::Throw"); }


	if (m_ball->GetNowState() == m_ball->GetMove()) { debugString->AddString("B::Move"); }
	else if (m_ball->GetNowState() == m_ball->GetThrow()) { debugString->AddString("B::Throw"); }

	debugString->AddString("PlayerForce:: %f", m_player->GetForceCharge());
	debugString->AddString("EnemyDebug:: %f", m_enemy->GetDebug());
	debugString->AddString("EnemyNumber:: %f", m_enemy->GetNumber());
	//debugString->AddString("ballDebug:: %f", m_ball->GetDebugLog());
	//m_ray->Render();
#endif

	m_ball->Render(m_tpsCamera->GetViewMatrix(), m_tpsCamera->GetProjectionMatrix());
	//m_player->Render(m_tpsCamera->GetViewMatrix() , m_tpsCamera->GetProjectionMatrix());

	
	m_player->Render(m_tpsCamera->GetViewMatrix(), m_tpsCamera->GetProjectionMatrix());

	m_enemy->Render(m_tpsCamera->GetViewMatrix(), m_tpsCamera->GetProjectionMatrix());


	//	デバイスコンテキストの取得
	auto device = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();

	m_stage->Render(states, m_tpsCamera->GetViewMatrix(), m_tpsCamera->GetProjectionMatrix());
	

	m_gridFloor->Render(device, m_tpsCamera->GetViewMatrix(), m_tpsCamera->GetProjectionMatrix());

	
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void PlayScene::Finalize()
{
	// do nothing.
}

//---------------------------------------------------------
// 次のシーンIDを取得する
//---------------------------------------------------------
IScene::SceneID PlayScene::GetNextSceneID() const
{
	// シーン変更がある場合
	if (m_isChangeScene)
	{
		return IScene::SceneID::RESULT;
	}

	// シーン変更がない場合
	return IScene::SceneID::NONE;
}


