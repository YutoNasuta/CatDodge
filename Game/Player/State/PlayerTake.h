//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/01
// <file>			PlayerTake.h
// <�T�v>		�@�@�v���C���[�̎󂯎��X�e�[�g
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"pch.h"
#include"Interface/IState.h"
#include"Game/Player/Player.h"
#include"Game/Scene/PlayScene.h"

// �O���錾
class Player;

class PlayerTake : public IState
{
public:
	// �R���X�g���N�^
	PlayerTake(Player* player);
	// �f�X�g���N�^
	~PlayerTake();
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
	void ChangeStateKey(const DirectX::Keyboard::State& keyboardStateTracker);
	// �{�[������铮��
	void BallTakeMove();
	// ���������ς�鏈��
	void ChangeDirection(const DirectX::Keyboard::State& keyboardStateTracker);
	// ���`�ۊǗp
	void SlarpRotate(DirectX::SimpleMath::Vector3 direction);
	// �q�̓���
	void MoveChild();
	// �r�̓���
	void MoveHand();
	// �����ۂ̓���
	void MoveTail();
private:
	// �v���C���[
	Player* m_player;
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;

};