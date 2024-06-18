//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/09
// <file>			Enemy.cpp
// <�T�v>			�G�l�~�[�̒��S�j
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include "Enemy.h"
#include"Game/Enemy/Parts/EnemyBody.h"
#include "Game/CommonResources.h"
#include "Libraries/NakashiLib/InputManager.h"

Enemy::Enemy(IComponent* parent,
    const DirectX::SimpleMath::Vector3& position,
    const DirectX::SimpleMath::Quaternion& quaternion
)
    :
    EnemyBase(parent , position , quaternion),
    m_commonResources{},
    m_partID{EnemyBase::PartID::ROOT} ,
    m_position{position},
    m_velocity{},
    Number{ 1 }, 
    Debug{ 1 }
{
    m_commonResources = CommonResources::GetInstance();
}

Enemy::~Enemy()
{

}

void Enemy::Initialize() 
{


    EnemyBase::Initialize();				// �x�[�X�̏��������Ă�

    auto body = std::make_unique<EnemyBody>(				// �v���C���[�{�f�B���쐬
        this,
        DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f),
        DirectX::SimpleMath::Quaternion::Identity
    );
    m_body = body.get();									// �Ăяo���pbody�Ɋi�[
    SetChild(std::move(body));					// �v���C���[�̎q��body��ݒ�
}

void Enemy::Update(
    const DX::StepTimer& timer,
    const DirectX::SimpleMath::Vector3& position,
    const DirectX::SimpleMath::Quaternion& quaternion
)
{
    EnemyBase::Update(
        timer,
        m_position + GetInitialPosition(),
        m_quaternion
    );
}


void Enemy::Render(
    const DirectX::SimpleMath::Matrix& view,
    const DirectX::SimpleMath::Matrix& projection
)
{
    EnemyBase::Render(view, projection);
}