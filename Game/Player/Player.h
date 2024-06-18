//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/01
// <file>			Player.h
// <概要>		　　プレイヤーの中心核
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"pch.h"
#include"Interface/IComponent.h"
#include"Interface/IState.h"
#include"Game/Player/PlayerBase.h"
#include"Game/Player/State/PlayerStanding.h"
#include"State/PlayerJumping.h"
#include"State/PlayerRunning.h"
#include"State/PlayerTake.h"
#include"State/PlayerThrow.h"

// 前方宣言
class CommonResources;
class PlayerStanding;
class PlayerJumping;
class PlayerRunning;
class PlayerTake;
class PlayerThrow;

class PlayerBody;

class Player : public PlayerBase
{
public:
	// インタフェース用++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	DirectX::SimpleMath::Vector3 GetPosition() const override { return m_position; }						// 現在の位置を取得する
	void SetPosition(const DirectX::SimpleMath::Vector3& position) override{ m_position = position; }		// 現在の位置を設定する

	DirectX::SimpleMath::Quaternion GetQuaternion() const override { return m_quaternion; }						//  現在の回転角を取得する
	void SetAngle(const DirectX::SimpleMath::Quaternion& quaternion)override { m_quaternion = quaternion; }		// 現在の回転角を設定する

	float GetMass() const override { return m_mass; }				// 質量を設定
	void SetMass(const float& mass) override { m_mass = mass; }		// 質量を設定

	// ステート用++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	PlayerStanding* GetStanding() { return m_standing.get(); }		// 立ち状態取得
	PlayerJumping* GetJumping() { return m_jumping.get(); }			// ジャンプ状態取得
	PlayerRunning* GetRunning() { return m_runnning.get(); }		// 走る状態取得
	PlayerTake* GetTake() { return m_taking.get(); }				// 取る状態取得
	PlayerThrow* GetThrow() { return m_throw.get(); }				// 投げ状態取得

	void ChangeState(IState* currentState);							// 状態を遷移する
	IState* GetNowState() const { return m_currentState; }			// 現在のステート情報を取得

	// プロパティ（取得と設定）++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	DirectX::SimpleMath::Vector3 GetVelocity() const { return m_velocity; }						// 速度取得
	void SetVelocity(const DirectX::SimpleMath::Vector3& velocity) { m_velocity = velocity; }	// 速度設定

	DirectX::SimpleMath::Vector3 GetAcceleration() const { return m_acceleration; }								// 加速度取得
	void SetAcceleration(const DirectX::SimpleMath::Vector3& acceleration) { m_acceleration = acceleration; }	// 加速度設定

	DirectX::SimpleMath::Vector3 GetGravity() const { return m_gravity; }		// 重力取得

	DirectX::SimpleMath::Vector3 GetFriction() const { return m_friction; }		// 摩擦取得

	DirectX::SimpleMath::Matrix GetWorld() const { return m_worldMatrix; }		//ワールド行列取得
	void SetWorld(const DirectX::SimpleMath::Matrix& world) { m_worldMatrix = world; }

	DirectX::SimpleMath::Matrix GetCameraView() const { return m_cameraView; }					// カメラのビューを取得
	DirectX::SimpleMath::Matrix GetProjection() const { return m_cameraProjection; }			// カメラのプロジェクション取得
	DirectX::SimpleMath::Quaternion GetCameraQuaternion() const { return m_cameraQuaternion; }	// カメラの回転を取得
	void SetCameraQuaternion(const DirectX::SimpleMath::Quaternion& quaternion) { m_cameraQuaternion = quaternion; }

	bool GetBallTakeFlag() const { return m_ballTaking; }			// ボール持ち状態取得
	void SetBallTakeFlag(const bool& flag) { m_ballTaking = flag; }	// ボール持ち状態設定

	float GetForceCharge() const { return m_forceCharge; }				// ボールに加える力取得
	void SetForceCharge(const float& force) { m_forceCharge = force; }	// ボールに加える力設定

	PlayerBody* GetBody() const { return m_body; }

	DirectX::SimpleMath::Vector3 GetGround() const { return m_ground; }
	void SetGround(const DirectX::SimpleMath::Vector3& ground) { m_ground = ground; }

	float GetTotalTime() const { return m_totalTime; }
	
	int GetNodeNumber() const { return m_nodeNumber; }
	
public:
	// コンストラクタ
	Player(
		IComponent* parent,
		const DirectX::SimpleMath::Vector3& position, 
		const DirectX::SimpleMath::Quaternion& quaternion);
	// デストラクタ
	~Player();
	// 初期化する
	void Initialize() override;
	// 更新する
	void Update(
		const DX::StepTimer& timer, 
		const DirectX::SimpleMath::Vector3& position, 
		const DirectX::SimpleMath::Quaternion& quaternion) override;
	// 描画する
	void Render(
		const DirectX::SimpleMath::Matrix& view , 
		const DirectX::SimpleMath::Matrix& projection) override;


private:
	// 共通リソース
	CommonResources* m_commonResources;
	// 地面位置用
	DirectX::SimpleMath::Vector3 m_ground;
	// 時間
	float m_totalTime;
	// ノード番号
	int m_nodeNumber;
	
	//　ステート用+++++++++++++++++++++++++++++++++++++++++++++++
	IState* m_currentState;						// 現在の状態
	std::unique_ptr<PlayerStanding> m_standing;	// 立ち状態
	std::unique_ptr<PlayerJumping> m_jumping;	// ジャンプ状態
	std::unique_ptr<PlayerRunning> m_runnning;	// 走り状態
	std::unique_ptr<PlayerTake> m_taking;		// 取る状態
	std::unique_ptr<PlayerThrow> m_throw;		// 投げ状態

	//  プレイヤーの情報+++++++++++++++++++++++++++++++++++++++++++
	int m_partID;								 //ID
	DirectX::SimpleMath::Vector3 m_position;	 //  現在の位置
	DirectX::SimpleMath::Vector3 m_velocity;	 //  現在の速度
	DirectX::SimpleMath::Quaternion m_quaternion;//  現在の回転角
	DirectX::SimpleMath::Matrix m_worldMatrix;   //  ワールド行列 
	DirectX::SimpleMath::Vector3 m_friction;	 //　摩擦
	float m_mass;								 //  質量
	DirectX::SimpleMath::Vector3 m_acceleration; //  加速度
	DirectX::SimpleMath::Vector3 m_gravity;      //　重力
	bool m_ballTaking;							 // ボールを持っている状態か持っていない状態か
	float m_forceCharge;						 // ボールのチャージ量

	//  カメラの情報++++++++++++++++++++++++++++++++++++++++++++++++++
	DirectX::SimpleMath::Matrix m_cameraView;			 //  カメラのビュー行列
	DirectX::SimpleMath::Matrix m_cameraProjection;		 //  カメラプロジェクション
	DirectX::SimpleMath::Quaternion m_cameraQuaternion;	 // カメラの回転角


	PlayerBody* m_body;
};