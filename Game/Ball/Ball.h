//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/05/27
// <file>			Ball.h
// <概要>			ボールの中心クラス
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"pch.h"
#include"Interface/IState.h"
#include"BallMove.h"
#include"BallThrow.h"
// 前方宣言
class CommonResources;
class Player;
class BallMove;
class BallThrow;


class Ball
{

public:
	// 現在のステート状態を取得する
	IState* GetNowState() { return m_currentState; }
	// アイドル状態取得
	BallMove* GetMove() { return m_ballMove.get(); }
	// 投げ状態取得
	BallThrow* GetThrow() { return m_ballThrow.get(); }
	// プレイヤーの状態取得用
	Player* GetPlayer() { return m_player; }


	DirectX::Model* GetBallModel();

	void ChangeState(IState* currentState);

public:
	// 重力加速度
	static const float GRAVITATION_ACCELERATION;
	// 空気抵抗
	static const float AIR_RESISTANCE;
	// 質量
	static const float MASS;
	// 半径
	static const float RADIUS;
	// 直径
	static const float DIAMETER;
	// 空気抵抗係数
	static const float DRAG_COEFFICIENT;
	// 断面積
	static const float CROSS_SECTION;
	// 空気密度
	static const float AIR_DENSITY;
	// 摩擦係数
	static const float FRICTION;
	// 最大移動速度
	static const float MAX_SPEED;
	// 交差判定距離
	static const float INTERSECT_JUDGEMENT_DISTANCE;

public:
	Ball();
	~Ball();

	void Initialize(Player* player);
	void Update(float elapsedTime);
	void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
	void Finalize();

private:
	// 共通ステート
	CommonResources* m_commonResources;

	// プレイヤー
	Player* m_player;

	// 現在の状態
	IState* m_currentState;

	// 位置
	DirectX::SimpleMath::Vector3 m_position;

	// 速度
	DirectX::SimpleMath::Vector3 m_velocity;

	// 加速度
	DirectX::SimpleMath::Vector3 m_acceleration;

	// 摩擦
	float m_friction;

	// クォータニオン::モデルの回転制御
	DirectX::SimpleMath::Quaternion m_rotate;

	// モデルの進行方向ベクトル：正規化ベクトル
	DirectX::SimpleMath::Vector3 m_forward;

	// 回転軸ベクトル
	DirectX::SimpleMath::Vector3 m_horizontal;

	// モデルの速さ
	float m_speed;

	// ボールのモデル
	DirectX::Model m_ballModel;

	// アイドル状態
	std::unique_ptr<BallMove> m_ballMove;

	// 投げ状態
	std::unique_ptr<BallThrow> m_ballThrow;

	// ビュー格納用
	DirectX::SimpleMath::Matrix m_view;
	DirectX::SimpleMath::Matrix m_projection;

	// 半径
	float m_radius;

	// デバッグ用
	int m_debugLog;
	
	// ノード番号
	int m_nodeNumber;

	// 地面位置
	DirectX::SimpleMath::Vector3 m_ground;

public:	// プロパティ
	// 位置の設定
	const DirectX::SimpleMath::Vector3 GetPosition() const {  return m_position; }
	void SetPosition(const DirectX::SimpleMath::Vector3& position) { m_position = position; }

	// 速度の設定
	const DirectX::SimpleMath::Vector3 GetVelocity() const { return m_velocity; }
	void SetVelocity(const DirectX::SimpleMath::Vector3& velocity) { m_velocity = velocity; }

	// クォータニオンの設定
	const DirectX::SimpleMath::Quaternion GetQuaternion() const { return m_rotate; }
	void SetQuaternion(const DirectX::SimpleMath::Quaternion& quaternion) { m_rotate = quaternion; }

	// 加速度の設定
	const DirectX::SimpleMath::Vector3 GetAcceleration() const { return m_acceleration; }
	void SetAcceleration(const DirectX::SimpleMath::Vector3& acceleration) { m_acceleration = acceleration; }

	// 半径の設定
	const float GetRadius() const { return m_radius; }


	const DirectX::SimpleMath::Matrix GetView() const { return m_view; }
	const DirectX::SimpleMath::Matrix GetProj() const { return m_projection; }

	// デバッグ取得
	const int GetDebugLog() const { return m_debugLog; }
	void SetDebugLog(const int& suzi) { m_debugLog = suzi; }

	// 地面設定
	const DirectX::SimpleMath::Vector3 GetGround() const { return m_ground; }
	void SetGround(const DirectX::SimpleMath::Vector3& ground) { m_ground = ground; }
	
};