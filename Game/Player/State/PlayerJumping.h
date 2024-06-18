//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/01
// <file>			PlayerJumping.h
// <�T�v>		�@�@�v���C���[�̃W�����v�X�e�[�g
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"pch.h"
#include"Interface/IState.h"
#include"Game/Scene/PlayScene.h"

// �O���錾
class Player;

class PlayerJumping : public IState
{
public:
	// �R���X�g���N�^
	PlayerJumping(Player* player);
	// �f�X�g���N�^
	~PlayerJumping();
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
	// �q�̓���
	void MoveChild();
	// �r�̓���
	void MoveHand();
private:
	// �v���C���[
	Player* m_player;
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;

};
