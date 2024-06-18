//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/01/20
// <file>			MousePoint.h
// <�T�v>			�}�E�X�|�C���^�̎擾
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"pch.h"

namespace NakashiLib
{
	class MousePoint
	{
	private:
		POINT previousMousePos;		//�ߋ��̃}�E�X�̈ʒu���擾����p

		POINT currentMousePos;		//���݂̃}�E�X�̈ʒu���擾����p

		int DeltaX;					//X���}�E�X���W�̍������v�Z����p
		int DeltaY;					//Y���}�E�X���W�̍������v�Z����p

		bool m_mouseMove;			//���̃}�E�X�̓�����On�ɂ��邩Off�ɂ��邩�����߂�

	public:
		MousePoint();
		~MousePoint();

		void Update();

		const int GetMouseDeltaX() const { return DeltaX; }			//x���}�E�X�̍������Q�b�g����
		const int GetMouseDeltaY() const { return DeltaY; }			//y���}�E�X�̍������Q�b�g����

		void SetMouseMove(const bool check) { m_mouseMove = check; }		//true�Ȃ瓮���@false�Ȃ��~

	};
}



