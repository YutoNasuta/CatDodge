//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/01
// <file>			PlayerJumping.h
// <概要>		　　プレイヤーのジャンプステート
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"pch.h"
#include"Interface/IState.h"
#include"Game/Scene/PlayScene.h"

// 前方宣言
class Player;

class PlayerJumping : public IState
{
public:
	// コンストラクタ
	PlayerJumping(Player* player);
	// デストラクタ
	~PlayerJumping();
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
	// 子の動き
	void MoveChild();
	// 腕の動き
	void MoveHand();
private:
	// プレイヤー
	Player* m_player;
	// 共通リソース
	CommonResources* m_commonResources;

};
