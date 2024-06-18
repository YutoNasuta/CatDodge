//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/12
// <file>			NearPlayerCheck.h
// <�T�v>		�@�@�߂��Ƀv���C���[�����邩�ǂ���
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include <random>

class NearPlayerCheck
{
public:
	bool operator()()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(0, 1);
		return dis(gen) == 1;
	}
};
