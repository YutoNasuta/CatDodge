#include"pch.h"
#include"Game/Team/Team.h"

// �v���C���[�`�[���ԍ�������
int Team::s_playerTeamNumber = 0;
// �G�l�~�[�`�[���ԍ�������
int Team::s_enemyTeamNumber = 1;

// �`�[�����X�g
std::unordered_map<int, std::vector<int>> Team::s_teamList =
{
	{0,{1}},			// �v���C���[��
	{1,{2}},			// �G�l�~�[��
};

// �Q�ƃ��X�g�̏�����
std::unordered_map<int, IComponent* > Team::s_nodeReferenceList = {};