/*
	@file	PlayScene.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "Interface/IScene.h"
#include"Game/Camera/TPSCamera.h"

#include"Libraries/Microsoft/DebugDraw.h"

#include"Game/Ball/Ball.h"

// �O���錾
class CommonResources;
class Ball;
class TPSCamera;
class Enemy;

class Player;

class GenerateStage;



namespace mylib
{
	class GridFloor;
}

namespace NakashiLib
{
	class Resources;
	class CollisionMesh;
	class CreateRay;
}

class PlayScene final :
    public IScene
{

public:
	// �ʒu
	static const DirectX::SimpleMath::Vector3 HOME_POSITION;
private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;

	

	// �i�q��
	std::unique_ptr<mylib::GridFloor> m_gridFloor;

	// �ˉe�s��
	DirectX::SimpleMath::Matrix m_projection;

	// �V�[���`�F���W�t���O
	bool m_isChangeScene;
	
	// ��]�p(�x)
	int m_angle;


	std::unique_ptr<NakashiLib::Resources> m_resources;


	// �n�ʈʒu����
	DirectX::SimpleMath::Vector3 m_ground;

	DirectX::SimpleMath::Quaternion m_debugQ;

	// �{�[��
	std::unique_ptr<Ball> m_ball;

	// TPS�J����
	std::unique_ptr<TPSCamera> m_tpsCamera;

	std::unique_ptr<Player> m_player;

	std::unique_ptr<Enemy> m_enemy;

	std::unique_ptr<GenerateStage> m_stage;

	// �����̊�ɂȂ���W
	DirectX::SimpleMath::Vector3 m_rayPosition;
	DirectX::SimpleMath::Vector3 m_ballRayPosition;

	std::unique_ptr<NakashiLib::CreateRay> m_ray;


public:
	PlayScene();
	~PlayScene() override;

	void Initialize() override;
	void Update(float elapsedTime)override;
	void Render() override;
	void Finalize() override;

	SceneID GetNextSceneID() const;
	
public:
	DirectX::SimpleMath::Matrix GetProjection() const { return m_projection; }

	DirectX::SimpleMath::Vector3 GetGround() const { return m_ground; }

	// �ǂݎ���p
	Ball* GetBall() { return m_ball.get(); }
	Player* GetPlayer() { return m_player.get(); }
};
