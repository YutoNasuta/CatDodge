//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//   製作者 NakashimaYuto	2024/06/01
//		@ file   IComponent.h
//		コンポ―ネット関係のインターフェース
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"pch.h"
#include"Framework/StepTimer.h"

// 前方宣言
class IComponent;
 
class IComponent
{
public:
	// 現在の位置を取得する
	virtual DirectX::SimpleMath::Vector3 GetPosition() const = 0;
	// 現在の位置を取得する
	virtual void SetPosition(const DirectX::SimpleMath::Vector3& position) = 0;
	// 現在の回転角を取得する
	virtual DirectX::SimpleMath::Quaternion GetQuaternion() const = 0;
	// 現在の回転角を設定する
	virtual void SetAngle(const DirectX::SimpleMath::Quaternion& quaternion) = 0;
	// 質量を取得する
	virtual float GetMass() const = 0;
	// 質量を設定する
	virtual void SetMass(const float& mass) = 0;
	// モデルの取得
	virtual DirectX::Model* GetModel() = 0;

public:

	// デストラクタ
	virtual ~IComponent() = default;
	// 初期化
	virtual void Initialize() = 0;
	// 更新
	virtual void Update(const DX::StepTimer& timer, 
		const DirectX::SimpleMath::Vector3& position , 
		const DirectX::SimpleMath::Quaternion& quaternion) = 0;
	// 子にする
	virtual void SetChild(std::unique_ptr<IComponent> part) = 0;

	// 描画
	virtual void Render(
		const DirectX::SimpleMath::Matrix& view , 
		const DirectX::SimpleMath::Matrix& projection) = 0;

};