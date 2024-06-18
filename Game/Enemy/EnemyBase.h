//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/01
// <file>			EnemyBase.h
// <概要>		　　エネミーのベース
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"pch.h"
#include"Interface/IComponent.h"
#include"Game/CommonResources.h"
// 前方宣言
class CommonResources;

class EnemyBase : public IComponent
{
public:
	// 子ID
	enum PartID : int
	{
		ROOT = -1,
		BODY = 0 ,
		HAND_RIGHT = 1,
		HAND_LEFT = 2,
		LEG = 3,
		HEAD = 4,
		TAIL = 5
	};


public:
	// 親の取得
	IComponent* GetParent() const { return m_parent; }

	// 初期位置を取得する
	DirectX::SimpleMath::Vector3 GetInitialPosition() const { return m_initialPosition; }
	
	// 初期回転角を取得する
	DirectX::SimpleMath::Quaternion GetInitialQuaternion() const { return m_initialQuaternion; }

	// 質量取得
	float GetMass() const { return m_mass; }

	// 質量を設定
	void SetMass(const float& mass) { m_mass = mass; }

	// モデルの取得
	DirectX::Model* GetModel() { return m_model; }

	// ワールド行列を取得する
	DirectX::SimpleMath::Matrix& GetWorldMatrix() { return m_worldMatrix; }

public:
	// コンストラクタ
	EnemyBase(IComponent* parent, 
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& quaternion);
	// デストラクタ
	 ~EnemyBase();
	// 初期化
	virtual void Initialize();
	// 初期化
	virtual void Initialize(DirectX::Model* model);
	// 更新
	inline virtual void Update(const DX::StepTimer& timer ,
		const DirectX::SimpleMath::Vector3& position, 
		const DirectX::SimpleMath::Quaternion& quaternion);
	// 子の追加
	virtual void SetChild(std::unique_ptr<IComponent> part);

	// 描画
	inline void Render(
		const DirectX::SimpleMath::Matrix& view , 
		const DirectX::SimpleMath::Matrix& projection);
	// 描画
	inline virtual void Render(
		const DirectX::SimpleMath::Matrix& matrix ,
		const DirectX::SimpleMath::Matrix& view , 
		const DirectX::SimpleMath::Matrix& projection);
	// モデルの描画
	virtual void DrawModel(
		const DirectX::SimpleMath::Matrix& matrix, 
		const DirectX::SimpleMath::Matrix& view, 
		const DirectX::SimpleMath::Matrix& projection);
	// 境界ボックスを描画
	inline void DrawBoundingBox(
	const DirectX::SimpleMath::Matrix& matrix ,
	const DirectX::SimpleMath::Matrix& view, 
	const DirectX::SimpleMath::Matrix& projection);



private:
	// 共通リソース
	CommonResources* m_commonResources;
	// モデル
	DirectX::Model* m_model;
	// 親
	IComponent* m_parent;
	// 初期位置
	DirectX::SimpleMath::Vector3 m_initialPosition;
	// 初期回転角
	DirectX::SimpleMath::Quaternion m_initialQuaternion;
	// 質量
	float m_mass;
	// パーツの配列
	std::vector<std::unique_ptr<IComponent>> m_enemyParts;
	//	ワールド行列
	DirectX::SimpleMath::Matrix m_worldMatrix;
	// 境界ボックス
	DirectX::BoundingBox m_boundingBox;
	// 境界ボックス配列
	std::vector<DirectX::BoundingBox*> m_enemyBoundingBoxes;
	bool m_collision;


};