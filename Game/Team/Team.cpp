#include"pch.h"
#include"Game/Team/Team.h"

// プレイヤーチーム番号初期化
int Team::s_playerTeamNumber = 0;
// エネミーチーム番号初期化
int Team::s_enemyTeamNumber = 1;

// チームリスト
std::unordered_map<int, std::vector<int>> Team::s_teamList =
{
	{0,{1}},			// プレイヤー側
	{1,{2}},			// エネミー側
};

// 参照リストの初期化
std::unordered_map<int, IComponent* > Team::s_nodeReferenceList = {};