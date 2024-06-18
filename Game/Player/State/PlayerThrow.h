//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/01
// <file>			PlayerThrow.h
// <�T�v>		�@�@�v���C���[�̓�����X�e�[�g
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"pch.h"
#include"Interface/IState.h"
#include"Game/Player/Player.h"
#include"Game/Scene/PlayScene.h"

// �O���錾
class Player;

class PlayerThrow : public IState
{
public:
	// �R���X�g���N�^
	PlayerThrow(Player* player);
	// �f�X�g���N�^
	~PlayerThrow();
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
	// �{�[���𓊂��铮��
	void BallThrowMove();
	// ���������ς�鏈��
	void ChangeDirectionMove(const DirectX::Keyboard::State& keyboardStateTracker);
	// ���`�ۊǗp
	void SlarpRotate(DirectX::SimpleMath::Vector3 direction);
	// �͂��`���[�W
	void AddForce();
	// �q�̓���
	void MoveChild();
	// ��̓���
	void MoveHand();
	// �����ۂ̓���
	void MoveTail();

private:
	// �v���C���[
	Player* m_player;
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;

};