//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/17
// <file>			PlayerStatus.h
// <概要>		　　プレイヤーの初期ステータスを決める
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"pch.h"

class PlayerStatus
{
private:



	DirectX::SimpleMath::Vector3 gravity = DirectX::SimpleMath::Vector3{ 0.0f,0.098f,0.0f };

	DirectX::SimpleMath::Vector3 friction;

	DirectX::SimpleMath::Vector3 acceleration;

	float m_weight;

public:
	PlayerStatus();
	~PlayerStatus();
	DirectX::SimpleMath::Vector3 GetGravity() { return gravity; }

};
