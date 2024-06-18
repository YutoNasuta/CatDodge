//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/05/27
// <file>			Ball.h
// <�T�v>			�{�[���̒��S�N���X
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"pch.h"
#include"Interface/IState.h"
#include"BallMove.h"
#include"BallThrow.h"
// �O���錾
class CommonResources;
class Player;
class BallMove;
class BallThrow;


class Ball
{

public:
	// ���݂̃X�e�[�g��Ԃ��擾����
	IState* GetNowState() { return m_currentState; }
	// �A�C�h����Ԏ擾
	BallMove* GetMove() { return m_ballMove.get(); }
	// ������Ԏ擾
	BallThrow* GetThrow() { return m_ballThrow.get(); }
	// �v���C���[�̏�Ԏ擾�p
	Player* GetPlayer() { return m_player; }


	DirectX::Model* GetBallModel();

	void ChangeState(IState* currentState);

public:
	// �d�͉����x
	static const float GRAVITATION_ACCELERATION;
	// ��C��R
	static const float AIR_RESISTANCE;
	// ����
	static const float MASS;
	// ���a
	static const float RADIUS;
	// ���a
	static const float DIAMETER;
	// ��C��R�W��
	static const float DRAG_COEFFICIENT;
	// �f�ʐ�
	static const float CROSS_SECTION;
	// ��C���x
	static const float AIR_DENSITY;
	// ���C�W��
	static const float FRICTION;
	// �ő�ړ����x
	static const float MAX_SPEED;
	// �������苗��
	static const float INTERSECT_JUDGEMENT_DISTANCE;

public:
	Ball();
	~Ball();

	void Initialize(Player* player);
	void Update(float elapsedTime);
	void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
	void Finalize();

private:
	// ���ʃX�e�[�g
	CommonResources* m_commonResources;

	// �v���C���[
	Player* m_player;

	// ���݂̏��
	IState* m_currentState;

	// �ʒu
	DirectX::SimpleMath::Vector3 m_position;

	// ���x
	DirectX::SimpleMath::Vector3 m_velocity;

	// �����x
	DirectX::SimpleMath::Vector3 m_acceleration;

	// ���C
	float m_friction;

	// �N�H�[�^�j�I��::���f���̉�]����
	DirectX::SimpleMath::Quaternion m_rotate;

	// ���f���̐i�s�����x�N�g���F���K���x�N�g��
	DirectX::SimpleMath::Vector3 m_forward;

	// ��]���x�N�g��
	DirectX::SimpleMath::Vector3 m_horizontal;

	// ���f���̑���
	float m_speed;

	// �{�[���̃��f��
	DirectX::Model m_ballModel;

	// �A�C�h�����
	std::unique_ptr<BallMove> m_ballMove;

	// �������
	std::unique_ptr<BallThrow> m_ballThrow;

	// �r���[�i�[�p
	DirectX::SimpleMath::Matrix m_view;
	DirectX::SimpleMath::Matrix m_projection;

	// ���a
	float m_radius;

	// �f�o�b�O�p
	int m_debugLog;
	
	// �m�[�h�ԍ�
	int m_nodeNumber;

	// �n�ʈʒu
	DirectX::SimpleMath::Vector3 m_ground;

public:	// �v���p�e�B
	// �ʒu�̐ݒ�
	const DirectX::SimpleMath::Vector3 GetPosition() const {  return m_position; }
	void SetPosition(const DirectX::SimpleMath::Vector3& position) { m_position = position; }

	// ���x�̐ݒ�
	const DirectX::SimpleMath::Vector3 GetVelocity() const { return m_velocity; }
	void SetVelocity(const DirectX::SimpleMath::Vector3& velocity) { m_velocity = velocity; }

	// �N�H�[�^�j�I���̐ݒ�
	const DirectX::SimpleMath::Quaternion GetQuaternion() const { return m_rotate; }
	void SetQuaternion(const DirectX::SimpleMath::Quaternion& quaternion) { m_rotate = quaternion; }

	// �����x�̐ݒ�
	const DirectX::SimpleMath::Vector3 GetAcceleration() const { return m_acceleration; }
	void SetAcceleration(const DirectX::SimpleMath::Vector3& acceleration) { m_acceleration = acceleration; }

	// ���a�̐ݒ�
	const float GetRadius() const { return m_radius; }


	const DirectX::SimpleMath::Matrix GetView() const { return m_view; }
	const DirectX::SimpleMath::Matrix GetProj() const { return m_projection; }

	// �f�o�b�O�擾
	const int GetDebugLog() const { return m_debugLog; }
	void SetDebugLog(const int& suzi) { m_debugLog = suzi; }

	// �n�ʐݒ�
	const DirectX::SimpleMath::Vector3 GetGround() const { return m_ground; }
	void SetGround(const DirectX::SimpleMath::Vector3& ground) { m_ground = ground; }
	
};