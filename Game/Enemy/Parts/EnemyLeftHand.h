//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/01
// <file>			EnemyLeftHand.h
// <概要>		　　プレイヤーの左手パーツ
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"Game/Player/PlayerBase.h"
#include"Framework/DeviceResources.h"
class CommonResources;

class EnemyLeftHand : public PlayerBase
{
public:

	// 現在の位置を取得する
	DirectX::SimpleMath::Vector3 GetPosition() const override { return m_position; }
	// 現在の位置を設定する
	void SetPosition(const DirectX::SimpleMath::Vector3& position) override { m_position = position; }
	// 現在の回転角を取得する
	DirectX::SimpleMath::Quaternion GetQuaternion() const  override { return m_quaternion; }
	// 現在の回転角を設定する
	void SetAngle(const DirectX::SimpleMath::Quaternion& quaternion) override { m_quaternion = quaternion; }
	// 質量を取得
	float GetMass() const override { return m_mass; }
	// 質量を設定
	void SetMass(const float& mass) override { m_mass = mass; }

	DirectX::Model* GetModel() override { return m_model; }

	void SetAddQuaternion(const DirectX::SimpleMath::Quaternion& quaternion) { m_addQuaternion = quaternion; }
	DirectX::SimpleMath::Quaternion GetAddQUaternion() const { return m_addQuaternion; }
	DirectX::SimpleMath::Vector3 GetVelocity() const { return m_velocity; }
	void SetVelocity(const DirectX::SimpleMath::Vector3& velocity) { m_velocity = velocity; }
public:
	// コンストラクタ
	EnemyLeftHand(IComponent* parent, 
		const DirectX::SimpleMath::Vector3& position, 
		const DirectX::SimpleMath::Quaternion& quaternion);
	// デストラクタ
	 ~EnemyLeftHand() ;
	// 初期化する
	void Initialize() override;
	// 更新する
	void Update(const DX::StepTimer& timer, 
		const DirectX::SimpleMath::Vector3& position, 
		const DirectX::SimpleMath::Quaternion& quaternion) override;
	// 描画する
	void Render(const DirectX::SimpleMath::Matrix& view,
		const DirectX::SimpleMath::Matrix& projection) override;
	// 後処理を行う
	void Finalize();
private:
	// 共通
	CommonResources* m_commonResources;
	// 部品ID
	int m_partID;
	// モデル
	DirectX::Model* m_model;	
	// 現在の位置
	DirectX::SimpleMath::Vector3 m_position;
	// 速度
	DirectX::SimpleMath::Vector3 m_velocity;
	// 現在の回転角
	DirectX::SimpleMath::Quaternion m_quaternion;
	// 質量
	float m_mass;
	//	ワールド行列
	DirectX::SimpleMath::Matrix m_worldMatrix;
	// 追加のクォータニオン
	DirectX::SimpleMath::Quaternion m_addQuaternion;
	// ノード番号
	int m_nodeNumber;
	
};