#pragma once
#include<unordered_map>
#include<vector>
#include"Interface/IComponent.h"


class Team
{
public:
	// プレイヤーチーム番号の取得
	static int GetPlayerTeamNumber() { return s_playerTeamNumber; }
	// プレイヤーチーム番号設定
	static void SetPlayerTeamNumber(int teamNumber) { s_playerTeamNumber = teamNumber; }
	// エネミーチーム番号取得
	static int GetEnemyTeamNumber() { return s_enemyTeamNumber; }
	// エネミーチーム番号設定
	static void SetEnemyTeamNumber(int teamNumber) { s_enemyTeamNumber = teamNumber; }
	// 指定されたチーム番号と敵対するチーム番号取得
	static int GetOpposingTeamNumber(int teamNumber) { return (teamNumber == s_playerTeamNumber) ? s_enemyTeamNumber : s_playerTeamNumber; }

public:
	// チーム番号からノードリスト取得
	static std::vector<int> GetNodeListForTeam(int teamNumber)
	{
		//チーム番号からノードリスト探す
		auto it = s_teamList.find(teamNumber);
		// 検出した時、ノードリスト配列を返す
		if (it != s_teamList.end())
		{
			return it->second;
		}
		// 見つからない時、空の配列
		return {};
	}

	// ノード番号からチーム番号を取得
	static int GetTeamNumberForNodeNumber(int nodeNumber)
	{
		for (auto& team : s_teamList)
		{
			// ノードリスト配列を取得
			std::vector<int>& nodeArray = team.second;
			// ノードリスト配列のノード選択
			for (int node : nodeArray)
			{
				// ノードリスト配列の番号とノード番号が等しい時、チーム番号を返す
				if (node == nodeNumber)
				{
					return team.first;
				}
			}
		}
		// どのチームにも属さないときは、-1
		return -1;
	}

	// リストからノードを削除する
	static IComponent* GetNodeFromReferenceList(int nodeNumber)
	{
		// ノード番号をリファレンスリストから探す
		auto it = s_nodeReferenceList.find(nodeNumber);
		// ノード番号がリファレンスリストに存在する場合ノードを削除する
		if (it != s_nodeReferenceList.end())
		{
			s_nodeReferenceList.erase(it);
		}
	}


private:
	// プレイヤーチーム番号
	static int s_playerTeamNumber;
	// エネミーチーム番号
	static int s_enemyTeamNumber;
	// チームリスト
	static std::unordered_map<int, std::vector<int>> s_teamList;
	// 参照リスト
	static std::unordered_map<int, IComponent*> s_nodeReferenceList;

};