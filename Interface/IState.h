//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//   ����� NakashimaYuto	2024/05/28
//		@ file   IState.h
//		�X�e�[�g�̃C���^�[�t�F�[�X
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"pch.h"



//�@�C���^�[�t�F�[�X�̒�`
class IState
{
public:
	// ������
	virtual void Initialize() = 0;
	// ��������
	virtual void OnEnter() = 0;
	// �o���Ƃ�
	virtual void OnExit() = 0;
	// �A�b�v�f�[�g
	virtual void Update() = 0;
	// �`��
	virtual void Render() = 0;
	// ��n��
	virtual void Finalize() = 0;


	// �f�X�g���N�^
	virtual ~IState() = default;

};

