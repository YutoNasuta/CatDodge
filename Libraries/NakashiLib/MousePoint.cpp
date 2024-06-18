//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/01/20
// <file>			MousePoint.cpp
// <概要>			マウスポインタの取得
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"MousePoint.h"
#include "Game/Screen.h"

/// <summary>
/// コンストラクタ
/// </summary>
NakashiLib::MousePoint::MousePoint()
	:
	previousMousePos{},
	currentMousePos{},
	DeltaX{},
	DeltaY{},
	m_mouseMove{}
{

}

/// <summary>
/// デストラクタ
/// </summary>
NakashiLib::MousePoint::~MousePoint()
{

}

/// <summary>
/// 更新処理
/// </summary>
void NakashiLib::MousePoint::Update()
{
	if (m_mouseMove == false) { return; }								//処理をしない

	GetCursorPos(&currentMousePos);

	DeltaX = currentMousePos.x - previousMousePos.x;					//マウス座標の差分計算
	DeltaY = currentMousePos.y - previousMousePos.y;					//Y軸

	POINT center = { Screen::CENTER_X , Screen::CENTER_Y };				//マウスを中央に固定させるために、どこにするのかを決める。

	ShowCursor(FALSE);													//カーソルを見えないようにする
			
	SetCursorPos(center.x, center.y);									//マウスを中央に固定

	previousMousePos = center;											//過去のマウスポインタの位置を変更させる

	Sleep(0);															//何フレで移動させるのか

}


