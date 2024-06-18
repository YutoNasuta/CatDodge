//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/01
// <file>			EnemyLeftHand.h
// <�T�v>		�@�@�v���C���[�̍���p�[�c
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"Game/Player/PlayerBase.h"
#include"Framework/DeviceResources.h"
class CommonResources;

class EnemyLeftHand : public PlayerBase
{
public:

	// ���݂̈ʒu���擾����
	DirectX::SimpleMath::Vector3 GetPosition() const override { return m_position; }
	// ���݂̈ʒu��ݒ肷��
	void SetPosition(const DirectX::SimpleMath::Vector3& position) override { m_position = position; }
	// ���݂̉�]�p���擾����
	DirectX::SimpleMath::Quaternion GetQuaternion() const  override { return m_quaternion; }
	// ���݂̉�]�p��ݒ肷��
	void SetAngle(const DirectX::SimpleMath::Quaternion& quaternion) override { m_quaternion = quaternion; }
	// ���ʂ��擾
	float GetMass() const override { return m_mass; }
	// ���ʂ�ݒ�
	void SetMass(const float& mass) override { m_mass = mass; }

	DirectX::Model* GetModel() override { return m_model; }

	void SetAddQuaternion(const DirectX::SimpleMath::Quaternion& quaternion) { m_addQuaternion = quaternion; }
	DirectX::SimpleMath::Quaternion GetAddQUaternion() const { return m_addQuaternion; }
	DirectX::SimpleMath::Vector3 GetVelocity() const { return m_velocity; }
	void SetVelocity(const DirectX::SimpleMath::Vector3& velocity) { m_velocity = velocity; }
public:
	// �R���X�g���N�^
	EnemyLeftHand(IComponent* parent, 
		const DirectX::SimpleMath::Vector3& position, 
		const DirectX::SimpleMath::Quaternion& quaternion);
	// �f�X�g���N�^
	 ~EnemyLeftHand() ;
	// ����������
	void Initialize() override;
	// �X�V����
	void Update(const DX::StepTimer& timer, 
		const DirectX::SimpleMath::Vector3& position, 
		const DirectX::SimpleMath::Quaternion& quaternion) override;
	// �`�悷��
	void Render(const DirectX::SimpleMath::Matrix& view,
		const DirectX::SimpleMath::Matrix& projection) override;
	// �㏈�����s��
	void Finalize();
private:
	// ����
	CommonResources* m_commonResources;
	// ���iID
	int m_partID;
	// ���f��
	DirectX::Model* m_model;	
	// ���݂̈ʒu
	DirectX::SimpleMath::Vector3 m_position;
	// ���x
	DirectX::SimpleMath::Vector3 m_velocity;
	// ���݂̉�]�p
	DirectX::SimpleMath::Quaternion m_quaternion;
	// ����
	float m_mass;
	//	���[���h�s��
	DirectX::SimpleMath::Matrix m_worldMatrix;
	// �ǉ��̃N�H�[�^�j�I��
	DirectX::SimpleMath::Quaternion m_addQuaternion;
	// �m�[�h�ԍ�
	int m_nodeNumber;
	
};