//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/12
// <file>			NearPlayerCheck.h
// <概要>		　　近くにプレイヤーがいるかどうか
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
