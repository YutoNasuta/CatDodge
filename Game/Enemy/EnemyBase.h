//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/01
// <file>			EnemyBase.h
// <�T�v>		�@�@�G�l�~�[�̃x�[�X
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"pch.h"
#include"Interface/IComponent.h"
#include"Game/CommonResources.h"
// �O���錾
class CommonResources;

class EnemyBase : public IComponent
{
public:
	// �qID
	enum PartID : int
	{
		ROOT = -1,
		BODY = 0 ,
		HAND_RIGHT = 1,
		HAND_LEFT = 2,
		LEG = 3,
		HEAD = 4,
		TAIL = 5
	};


public:
	// �e�̎擾
	IComponent* GetParent() const { return m_parent; }

	// �����ʒu���擾����
	DirectX::SimpleMath::Vector3 GetInitialPosition() const { return m_initialPosition; }
	
	// ������]�p���擾����
	DirectX::SimpleMath::Quaternion GetInitialQuaternion() const { return m_initialQuaternion; }

	// ���ʎ擾
	float GetMass() const { return m_mass; }

	// ���ʂ�ݒ�
	void SetMass(const float& mass) { m_mass = mass; }

	// ���f���̎擾
	DirectX::Model* GetModel() { return m_model; }

	// ���[���h�s����擾����
	DirectX::SimpleMath::Matrix& GetWorldMatrix() { return m_worldMatrix; }

public:
	// �R���X�g���N�^
	EnemyBase(IComponent* parent, 
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& quaternion);
	// �f�X�g���N�^
	 ~EnemyBase();
	// ������
	virtual void Initialize();
	// ������
	virtual void Initialize(DirectX::Model* model);
	// �X�V
	inline virtual void Update(const DX::StepTimer& timer ,
		const DirectX::SimpleMath::Vector3& position, 
		const DirectX::SimpleMath::Quaternion& quaternion);
	// �q�̒ǉ�
	virtual void SetChild(std::unique_ptr<IComponent> part);

	// �`��
	inline void Render(
		const DirectX::SimpleMath::Matrix& view , 
		const DirectX::SimpleMath::Matrix& projection);
	// �`��
	inline virtual void Render(
		const DirectX::SimpleMath::Matrix& matrix ,
		const DirectX::SimpleMath::Matrix& view , 
		const DirectX::SimpleMath::Matrix& projection);
	// ���f���̕`��
	virtual void DrawModel(
		const DirectX::SimpleMath::Matrix& matrix, 
		const DirectX::SimpleMath::Matrix& view, 
		const DirectX::SimpleMath::Matrix& projection);
	// ���E�{�b�N�X��`��
	inline void DrawBoundingBox(
	const DirectX::SimpleMath::Matrix& matrix ,
	const DirectX::SimpleMath::Matrix& view, 
	const DirectX::SimpleMath::Matrix& projection);



private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	// ���f��
	DirectX::Model* m_model;
	// �e
	IComponent* m_parent;
	// �����ʒu
	DirectX::SimpleMath::Vector3 m_initialPosition;
	// ������]�p
	DirectX::SimpleMath::Quaternion m_initialQuaternion;
	// ����
	float m_mass;
	// �p�[�c�̔z��
	std::vector<std::unique_ptr<IComponent>> m_enemyParts;
	//	���[���h�s��
	DirectX::SimpleMath::Matrix m_worldMatrix;
	// ���E�{�b�N�X
	DirectX::BoundingBox m_boundingBox;
	// ���E�{�b�N�X�z��
	std::vector<DirectX::BoundingBox*> m_enemyBoundingBoxes;
	bool m_collision;


};