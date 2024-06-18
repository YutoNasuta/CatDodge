//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/01/20
// <file>			TPSCamera.h
// <概要>			TPSカメラの実装
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"pch.h"
#include"Libraries/NakashiLib/MousePoint.h"

// 前方宣言
namespace NakashiLib
{
	class MousePoint;
}

class TPSCamera
{
private:
	// ターゲットからのデフォルト距離
	const float CAMERA_DISTANCE = 14.0f;
	const float CAMERA_HIGHT = 5.0f;

	// 画角
	const float FOV = DirectX::XMConvertToRadians(45.0f);

	// 近い投影面
	const float NEAR_PLANE = 1.0f;

	// 遠い投影面
	const float FAR_PLANE = 500.0f;

	// ビュー行列
	DirectX::SimpleMath::Matrix m_view;

	// プロジェクション行列
	DirectX::SimpleMath::Matrix m_projection;

	// カメラ座標
	DirectX::SimpleMath::Vector3 m_eye;

	// 注視点
	DirectX::SimpleMath::Vector3 m_target;

	// カメラの頭の方向
	DirectX::SimpleMath::Vector3 m_up;

	// マウスポインタ
	std::unique_ptr<NakashiLib::MousePoint> m_mousePointer;

	// カメラ回転用クォータニオン
	DirectX::SimpleMath::Quaternion m_rotate;

	// カメラ用角度
	DirectX::SimpleMath::Vector2 m_cameraAngle;

public:
	// コンストラクタ
	TPSCamera(const DirectX::SimpleMath::Vector3& target = DirectX::SimpleMath::Vector3::Zero);

	// デストラクタ
	~TPSCamera() = default;

	// 更新処理
	void Update(
		const DirectX::SimpleMath::Vector3& newTarget
	);

public:
	// プロパティ
	const DirectX::SimpleMath::Matrix& GetViewMatrix() const { return m_view; }

	const DirectX::SimpleMath::Matrix& GetProjectionMatrix() const { return m_projection; }

	const DirectX::SimpleMath::Vector3& GetEyePosition() const { return m_eye; }

	const DirectX::SimpleMath::Vector3& GetTargetPosition() const { return m_target; }

	const DirectX::SimpleMath::Vector3& GetUpVector() const { return m_up; }

	const DirectX::SimpleMath::Quaternion& GetCameraRotate() const { return m_rotate; }
	void  SetCameraRotate(const DirectX::SimpleMath::Quaternion& quaternion){ m_rotate = quaternion; }

	const NakashiLib::MousePoint* GetMousePoint() const { return m_mousePointer.get(); }

	void SetMouseMove(const bool moveCheck) { m_mousePointer->SetMouseMove(moveCheck); }

private:
	// ビュー行列を計算する
	void CalculateViewMatrix();

	// プロジェクション行列を計算する
	void CalculateProjectionMatrix();

	// カメラ座標を計算する
	void CalculateEyePosition(const DirectX::SimpleMath::Quaternion& rotate);

	// マウスポインタの移動を元に、カメラの角度を計算する
	void CalculateCameraAngle();
	// 角度の限界を設定する
	void CameraAngleMaxMin();
	// 回転行列（クォータニオン）をつくる
	void CalculateQuaternion();
};
