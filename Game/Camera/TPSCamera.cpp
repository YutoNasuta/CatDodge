//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/01/20
// <file>			TPSCamera.cpp
// <概要>			TPSカメラの実装
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include"pch.h"
#include"TPSCamera.h"
#include"Game/Screen.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="target">ターゲットの取得</param>
TPSCamera::TPSCamera(const DirectX::SimpleMath::Vector3& target)
	:
	m_view{},
	m_projection{},
	m_eye{},
	m_target{target},
	m_up{DirectX::SimpleMath::Vector3::UnitY},
	m_rotate{},
	m_cameraAngle{}
{
	CalculateEyePosition(DirectX::SimpleMath::Quaternion::Identity);
	CalculateViewMatrix();
	CalculateProjectionMatrix();
	m_mousePointer = std::make_unique<NakashiLib::MousePoint>();
	m_mousePointer->SetMouseMove(true);
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="newTarget">現在のターゲット</param>
void TPSCamera::Update(
	const DirectX::SimpleMath::Vector3& newTarget
)
{
	// マウスを動かす
	m_mousePointer->Update();

	// targetの位置を更新する
	m_target = DirectX::SimpleMath::Vector3(newTarget.x, newTarget.y * 0.7f , newTarget.z);

	// カメラ座標を計算する
	CalculateEyePosition(m_rotate);

	// ビュー行列を更新する
	CalculateViewMatrix();

	// マウスから角度を取得して、クォータニオンの計算をする
	CalculateCameraAngle();

	CameraAngleMaxMin();
}

/// <summary>
/// ビュー行列の計算
/// </summary>
void TPSCamera::CalculateViewMatrix()
{
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_eye, m_target, m_up);
}

/// <summary>
/// プロジェクション行列の計算
/// </summary>
void TPSCamera::CalculateProjectionMatrix()
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
void TPSCamera::CalculateEyePosition(const DirectX::SimpleMath::Quaternion& rotate)
{
	// 既定の進行方向ベクトル
	DirectX::SimpleMath::Vector3 forward = DirectX::SimpleMath::Vector3::Forward;

	// カメラがターゲットからどれくらい離れているか
	forward.y = CAMERA_HIGHT;
	forward.z = CAMERA_DISTANCE;

	// ターゲットの向いている方向に追従する
	forward = DirectX::SimpleMath::Vector3::Transform(forward, rotate);

	// カメラ座標を計算する
	m_eye = m_target + forward;

}

/// <summary>
/// マウスポインタの動きに合わせて回転
/// </summary>
void TPSCamera::CalculateCameraAngle()
{
	m_cameraAngle.x -= m_mousePointer->GetMouseDeltaY() * 0.05f;
	m_cameraAngle.y -= m_mousePointer->GetMouseDeltaX() * 0.05f;

	CameraAngleMaxMin();
	CalculateQuaternion();
}

/// <summary>
/// カメラの最大角度を設定
/// </summary>
void TPSCamera::CameraAngleMaxMin()
{
	if (m_cameraAngle.x < -50) { m_cameraAngle.x = -50; }
	if (m_cameraAngle.x > 50) { m_cameraAngle.x = 50; }
}

/// <summary>
/// クォータニオンの生成
/// </summary>
void TPSCamera::CalculateQuaternion()
{
	// X軸周りの回転を表すクォータニオンを作成
	DirectX::SimpleMath::Quaternion rotationX = 
		DirectX::SimpleMath::Quaternion::CreateFromRotationMatrix(DirectX::SimpleMath::Matrix::CreateRotationX(DirectX::XMConvertToRadians(m_cameraAngle.x)));

	// Y軸周りの回転を表すクォータニオンを作成
	DirectX::SimpleMath::Quaternion rotationY = 
		DirectX::SimpleMath::Quaternion::CreateFromRotationMatrix(DirectX::SimpleMath::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_cameraAngle.y)));

	// 既存の回転に新しい回転を合成する
	m_rotate = rotationX * rotationY;
}