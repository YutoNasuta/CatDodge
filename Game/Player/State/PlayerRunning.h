//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/01
// <file>			PlayerRunning.h
// <�T�v>		�@�@�v���C���[�̑���X�e�[�g
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"pch.h"
#include"Interface/IState.h"

// �O���錾
class Player;
class CommonResources;

class PlayerRunning : public IState
{
public:
	// �R���X�g���N�^
	PlayerRunning(Player* player);
	// �f�X�g���N�^
	~PlayerRunning();
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
	// �L�[��State�ύX
	void ChangeStateKey(const DirectX::Keyboard::State& keyboardStateTracker);
	// �ړ�����
	void Moving(const DirectX::Keyboard::State& keyboardStateTracker);
	// �p�x��ς���
	void SlerpRotate(const DirectX::SimpleMath::Vector3 velocity);

	// �v���C���[�̎q�p�[�c�B�̕ω�
	void MoveChild();
	// ��̓���
	void MoveHand();
	// ���̓���
	void MoveBody();
	// �����ۂ̓���
	void MoveTail();
	
private:
	Player* m_player;
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
};
