//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//   製作者 NakashimaYuto	2024/05/28
//		@ file   IState.h
//		ステートのインターフェース
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"pch.h"



//　インターフェースの定義
class IState
{
public:
	// 初期化
	virtual void Initialize() = 0;
	// 入った時
	virtual void OnEnter() = 0;
	// 出たとき
	virtual void OnExit() = 0;
	// アップデート
	virtual void Update() = 0;
	// 描画
	virtual void Render() = 0;
	// 後始末
	virtual void Finalize() = 0;


	// デストラクタ
	virtual ~IState() = default;

};

