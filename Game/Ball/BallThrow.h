//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/05/27
// <file>			BallThrow.h
// <�T�v>			�{�[����������ꂽ���
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"pch.h"
#include"Interface/IState.h"
#include"Game/Ball/Ball.h"
#include"Game/Player/Player.h"

class Ball;
class CommonResources;
class Player;

class BallThrow : public IState
{
public:
	// �R���X�g���N�^
	BallThrow(Ball* ball);
	// �f�X�g���N�^
	~BallThrow();

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
	// �v���C���[�ɒǏ]����
	void ToFollow();

private:
	Ball* m_ball;

	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
};