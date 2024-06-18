//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/05/27
// <file>			BallThrow.h
// <概要>			ボールの動き（通常状態）
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"pch.h"
#include"Interface/IState.h"
#include"Game/Ball/Ball.h"

class Ball;
class CommonResources;

class BallMove : public IState
{
public:
	// コンストラクタ
	BallMove(Ball* balls);
	// デストラクタ
	~BallMove();

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
	void ChangeState();

private:
	Ball* m_ball;
	
	// 共通リソース
	CommonResources* m_commonResources;
};