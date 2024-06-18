//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/01/20
// <file>			MousePoint.h
// <概要>			マウスポインタの取得
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"pch.h"

namespace NakashiLib
{
	class MousePoint
	{
	private:
		POINT previousMousePos;		//過去のマウスの位置を取得する用

		POINT currentMousePos;		//現在のマウスの位置を取得する用

		int DeltaX;					//X軸マウス座標の差分を計算する用
		int DeltaY;					//Y軸マウス座標の差分を計算する用

		bool m_mouseMove;			//このマウスの動きをOnにするかOffにするかを決める

	public:
		MousePoint();
		~MousePoint();

		void Update();

		const int GetMouseDeltaX() const { return DeltaX; }			//x軸マウスの差分をゲットする
		const int GetMouseDeltaY() const { return DeltaY; }			//y軸マウスの差分をゲットする

		void SetMouseMove(const bool check) { m_mouseMove = check; }		//trueなら動く　falseなら停止

	};
}



