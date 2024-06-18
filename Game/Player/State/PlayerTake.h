//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/01
// <file>			PlayerTake.h
// <概要>		　　プレイヤーの受け取るステート
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"pch.h"
#include"Interface/IState.h"
#include"Game/Player/Player.h"
#include"Game/Scene/PlayScene.h"

// 前方宣言
class Player;

class PlayerTake : public IState
{
public:
	// コンストラクタ
	PlayerTake(Player* player);
	// デストラクタ
	~PlayerTake();
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
	// State変更
	void ChangeStateKey(const DirectX::Keyboard::State& keyboardStateTracker);
	// ボールを取る動作
	void BallTakeMove();
	// 向きだけ変わる処理
	void ChangeDirection(const DirectX::Keyboard::State& keyboardStateTracker);
	// 線形保管用
	void SlarpRotate(DirectX::SimpleMath::Vector3 direction);
	// 子の動き
	void MoveChild();
	// 腕の動き
	void MoveHand();
	// しっぽの動き
	void MoveTail();
private:
	// プレイヤー
	Player* m_player;
	// 共通リソース
	CommonResources* m_commonResources;

};