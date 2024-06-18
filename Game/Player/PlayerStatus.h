//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/17
// <file>			PlayerStatus.h
// <�T�v>		�@�@�v���C���[�̏����X�e�[�^�X�����߂�
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
