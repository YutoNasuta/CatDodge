#pragma once
#include<unordered_map>
#include<vector>
#include"Interface/IComponent.h"


class Team
{
public:
	// �v���C���[�`�[���ԍ��̎擾
	static int GetPlayerTeamNumber() { return s_playerTeamNumber; }
	// �v���C���[�`�[���ԍ��ݒ�
	static void SetPlayerTeamNumber(int teamNumber) { s_playerTeamNumber = teamNumber; }
	// �G�l�~�[�`�[���ԍ��擾
	static int GetEnemyTeamNumber() { return s_enemyTeamNumber; }
	// �G�l�~�[�`�[���ԍ��ݒ�
	static void SetEnemyTeamNumber(int teamNumber) { s_enemyTeamNumber = teamNumber; }
	// �w�肳�ꂽ�`�[���ԍ��ƓG�΂���`�[���ԍ��擾
	static int GetOpposingTeamNumber(int teamNumber) { return (teamNumber == s_playerTeamNumber) ? s_enemyTeamNumber : s_playerTeamNumber; }

public:
	// �`�[���ԍ�����m�[�h���X�g�擾
	static std::vector<int> GetNodeListForTeam(int teamNumber)
	{
		//�`�[���ԍ�����m�[�h���X�g�T��
		auto it = s_teamList.find(teamNumber);
		// ���o�������A�m�[�h���X�g�z���Ԃ�
		if (it != s_teamList.end())
		{
			return it->second;
		}
		// ������Ȃ����A��̔z��
		return {};
	}

	// �m�[�h�ԍ�����`�[���ԍ����擾
	static int GetTeamNumberForNodeNumber(int nodeNumber)
	{
		for (auto& team : s_teamList)
		{
			// �m�[�h���X�g�z����擾
			std::vector<int>& nodeArray = team.second;
			// �m�[�h���X�g�z��̃m�[�h�I��
			for (int node : nodeArray)
			{
				// �m�[�h���X�g�z��̔ԍ��ƃm�[�h�ԍ������������A�`�[���ԍ���Ԃ�
				if (node == nodeNumber)
				{
					return team.first;
				}
			}
		}
		// �ǂ̃`�[���ɂ������Ȃ��Ƃ��́A-1
		return -1;
	}

	// ���X�g����m�[�h���폜����
	static IComponent* GetNodeFromReferenceList(int nodeNumber)
	{
		// �m�[�h�ԍ������t�@�����X���X�g����T��
		auto it = s_nodeReferenceList.find(nodeNumber);
		// �m�[�h�ԍ������t�@�����X���X�g�ɑ��݂���ꍇ�m�[�h���폜����
		if (it != s_nodeReferenceList.end())
		{
			s_nodeReferenceList.erase(it);
		}
	}


private:
	// �v���C���[�`�[���ԍ�
	static int s_playerTeamNumber;
	// �G�l�~�[�`�[���ԍ�
	static int s_enemyTeamNumber;
	// �`�[�����X�g
	static std::unordered_map<int, std::vector<int>> s_teamList;
	// �Q�ƃ��X�g
	static std::unordered_map<int, IComponent*> s_nodeReferenceList;

};