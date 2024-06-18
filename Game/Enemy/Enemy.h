//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/09
// <file>			Enemy.h
// <概要>			エネミーの中心核
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"pch.h"
#include"Interface/IComponent.h"
#include"Game/Enemy/EnemyBase.h"

class CommonResources;

class EnemyBody;

class Enemy : public EnemyBase 
{
public:
    // インタフェース用++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    DirectX::SimpleMath::Vector3 GetPosition() const override { return m_position; }						// 現在の位置を取得する
    void SetPosition(const DirectX::SimpleMath::Vector3& position) override { m_position = position; }		// 現在の位置を設定する

    DirectX::SimpleMath::Quaternion GetQuaternion() const override { return m_quaternion; }						//  現在の回転角を取得する
    void SetAngle(const DirectX::SimpleMath::Quaternion& quaternion)override { m_quaternion = quaternion; }		// 現在の回転角を設定する

    float GetMass() const override { return m_mass; }				// 質量を設定
    void SetMass(const float& mass) override { m_mass = mass; }		// 質量を設定


    EnemyBody* GetBody() const { return m_body; }

public:
    Enemy(
        IComponent* parent,
        const DirectX::SimpleMath::Vector3& position,
        const DirectX::SimpleMath::Quaternion& quaternion);
    ~Enemy();

    void Initialize() override;
    void Update(
        const DX::StepTimer& timer,
        const DirectX::SimpleMath::Vector3& position,
        const DirectX::SimpleMath::Quaternion& quaternion) override;

    // 描画する
    void Render(
        const DirectX::SimpleMath::Matrix& view,
        const DirectX::SimpleMath::Matrix& projection) override;

    const float GetNumber() const { return Number; }
    void SetDebug(float value) { Debug = value; }
    const float GetDebug() const { return Debug; }

private:
    CommonResources* m_commonResources;


    float Number;
    float Debug;

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

    EnemyBody* m_body;
};