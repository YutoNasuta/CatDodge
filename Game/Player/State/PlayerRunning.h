//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/01
// <file>			PlayerRunning.h
// <概要>		　　プレイヤーの走りステート
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"pch.h"
#include"Interface/IState.h"

// 前方宣言
class Player;
class CommonResources;

class PlayerRunning : public IState
{
public:
	// コンストラクタ
	PlayerRunning(Player* player);
	// デストラクタ
	~PlayerRunning();
	// 初期化
	void Initialize() override;
	// 立ち状態
	void Update() override;
	// 立ちの描画
	void Render() override;
	// 入った時
	void OnEnter() override;
	// 出たとき
	void OnExit() override;
	// 後始末
	void Finalize() override;
	// キーでState変更
	void ChangeStateKey(const DirectX::Keyboard::State& keyboardStateTracker);
	// 移動処理
	void Moving(const DirectX::Keyboard::State& keyboardStateTracker);
	// 角度を変える
	void SlerpRotate(const DirectX::SimpleMath::Vector3 velocity);

	// プレイヤーの子パーツ達の変化
	void MoveChild();
	// 手の動き
	void MoveHand();
	// 胴の動き
	void MoveBody();
	// しっぽの動き
	void MoveTail();
	
private:
	Player* m_player;
	// 共通リソース
	CommonResources* m_commonResources;
};
