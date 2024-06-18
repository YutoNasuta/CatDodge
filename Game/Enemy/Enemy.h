//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/09
// <file>			Enemy.h
// <�T�v>			�G�l�~�[�̒��S�j
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"pch.h"
#include"Interface/IComponent.h"
#include"Game/Enemy/EnemyBase.h"

class CommonResources;

class EnemyBody;

class Enemy : public EnemyBase 
{
public:
    // �C���^�t�F�[�X�p++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    DirectX::SimpleMath::Vector3 GetPosition() const override { return m_position; }						// ���݂̈ʒu���擾����
    void SetPosition(const DirectX::SimpleMath::Vector3& position) override { m_position = position; }		// ���݂̈ʒu��ݒ肷��

    DirectX::SimpleMath::Quaternion GetQuaternion() const override { return m_quaternion; }						//  ���݂̉�]�p���擾����
    void SetAngle(const DirectX::SimpleMath::Quaternion& quaternion)override { m_quaternion = quaternion; }		// ���݂̉�]�p��ݒ肷��

    float GetMass() const override { return m_mass; }				// ���ʂ�ݒ�
    void SetMass(const float& mass) override { m_mass = mass; }		// ���ʂ�ݒ�


    EnemyBody* GetBody() const { return m_body; }

public:
    Enemy(
        IComponent* parent,
        const DirectX::SimpleMath::Vector3& position,
        const DirectX::SimpleMath::Quaternion& quaternion);
    ~Enemy();

    void Initialize() override;
    void Update(
        const DX::StepTimer& timer,
        const DirectX::SimpleMath::Vector3& position,
        const DirectX::SimpleMath::Quaternion& quaternion) override;

    // �`�悷��
    void Render(
        const DirectX::SimpleMath::Matrix& view,
        const DirectX::SimpleMath::Matrix& projection) override;

    const float GetNumber() const { return Number; }
    void SetDebug(float value) { Debug = value; }
    const float GetDebug() const { return Debug; }

private:
    CommonResources* m_commonResources;


    float Number;
    float Debug;

    //  �v���C���[�̏��+++++++++++++++++++++++++++++++++++++++++++
    int m_partID;								 //ID
    DirectX::SimpleMath::Vector3 m_position;	 //  ���݂̈ʒu
    DirectX::SimpleMath::Vector3 m_velocity;	 //  ���݂̑��x
    DirectX::SimpleMath::Quaternion m_quaternion;//  ���݂̉�]�p
    DirectX::SimpleMath::Matrix m_worldMatrix;   //  ���[���h�s�� 
    DirectX::SimpleMath::Vector3 m_friction;	 //�@���C
    float m_mass;								 //  ����
    DirectX::SimpleMath::Vector3 m_acceleration; //  �����x
    DirectX::SimpleMath::Vector3 m_gravity;      //�@�d��
    bool m_ballTaking;							 // �{�[���������Ă����Ԃ������Ă��Ȃ���Ԃ�
    float m_forceCharge;						 // �{�[���̃`���[�W��

    EnemyBody* m_body;
};