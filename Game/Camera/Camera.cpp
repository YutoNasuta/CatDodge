//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/17
// <file>			Camera.h
// <概要>		　　カメラ
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"Camera.h"
#include"Game/Screen.h"

Camera::Camera()
	:
	m_currentState{},
	m_eye{},
	m_projection{},
	m_rotate{},
	m_target{},
	m_tpsCamera{},
	m_up{},
	m_view{}
{
	
}

Camera::~Camera()
{

}

void Camera::Initialize()
{
	m_tpsCamera = std::make_unique<TPSCamera>(this);

	CalculateEyePosition(DirectX::SimpleMath::Quaternion::Identity);
	CalculateViewMatrix();
	CalculateProjectionMatrix();

	

	m_currentState = m_tpsCamera.get();
}

void Camera::Update(
	const DirectX::SimpleMath::Vector3& newTarget,
	const DirectX::SimpleMath::Vector3& player)
{
	m_currentState->Update(newTarget , player);

}


/// <summary>
/// プロジェクション行列の計算
/// </summary>
void Camera::CalculateProjectionMatrix()
{
	const float width = static_cast<float>(Screen::WIDTH);
	const float height = static_cast<float>(Screen::HEIGHT);

	// 画面縦横比
	const float aspectRatio = width / height;

	m_projection = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		FOV, aspectRatio, NEAR_PLANE, FAR_PLANE
	);
}

/// <summary>
/// カメラ座標の計算
/// </summary>
/// <param name="rotate"></param>
void Camera::CalculateEyePosition(const DirectX::SimpleMath::Quaternion& rotate)
{
	// 既定の進行方向ベクトル
	DirectX::SimpleMath::Vector3 forward = DirectX::SimpleMath::Vector3::Forward;

	// カメラがターゲットからどれくらい離れているか
	forward.y = GetCameraHIGHT();
	forward.z = GetCameraDistance();

	// ターゲットの向いている方向に追従する
	forward = DirectX::SimpleMath::Vector3::Transform(forward, rotate);

	// カメラ座標を計算する
	SetEyePosition(GetTargetPosition() + forward);

}

/// <summary>
/// ビュー行列の計算
/// </summary>
void Camera::CalculateViewMatrix()
{
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(
		m_eye,
		m_target,
		m_up);

}