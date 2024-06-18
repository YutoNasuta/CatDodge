//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/05/27
// <file>			BallThrow.h
// <�T�v>			�{�[���̓����i�ʏ��ԁj
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
	// �R���X�g���N�^
	BallMove(Ball* balls);
	// �f�X�g���N�^
	~BallMove();

	// ������
	void Initialize() override;
	// �������
	void Update() override;
	// �����̕`��
	void Render() override;
	// ��������
	void OnEnter() override;
	// �o���Ƃ�
	void OnExit() override;
	// ��n��
	void Finalize() override;
	// State�ύX
	void ChangeState();

private:
	Ball* m_ball;
	
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
};