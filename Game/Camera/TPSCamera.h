//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/01/20
// <file>			TPSCamera.h
// <�T�v>			TPS�J�����̎���
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"pch.h"
#include"Libraries/NakashiLib/MousePoint.h"

// �O���錾
namespace NakashiLib
{
	class MousePoint;
}

class TPSCamera
{
private:
	// �^�[�Q�b�g����̃f�t�H���g����
	const float CAMERA_DISTANCE = 14.0f;
	const float CAMERA_HIGHT = 5.0f;

	// ��p
	const float FOV = DirectX::XMConvertToRadians(45.0f);

	// �߂����e��
	const float NEAR_PLANE = 1.0f;

	// �������e��
	const float FAR_PLANE = 500.0f;

	// �r���[�s��
	DirectX::SimpleMath::Matrix m_view;

	// �v���W�F�N�V�����s��
	DirectX::SimpleMath::Matrix m_projection;

	// �J�������W
	DirectX::SimpleMath::Vector3 m_eye;

	// �����_
	DirectX::SimpleMath::Vector3 m_target;

	// �J�����̓��̕���
	DirectX::SimpleMath::Vector3 m_up;

	// �}�E�X�|�C���^
	std::unique_ptr<NakashiLib::MousePoint> m_mousePointer;

	// �J������]�p�N�H�[�^�j�I��
	DirectX::SimpleMath::Quaternion m_rotate;

	// �J�����p�p�x
	DirectX::SimpleMath::Vector2 m_cameraAngle;

public:
	// �R���X�g���N�^
	TPSCamera(const DirectX::SimpleMath::Vector3& target = DirectX::SimpleMath::Vector3::Zero);

	// �f�X�g���N�^
	~TPSCamera() = default;

	// �X�V����
	void Update(
		const DirectX::SimpleMath::Vector3& newTarget
	);

public:
	// �v���p�e�B
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
	// �r���[�s����v�Z����
	void CalculateViewMatrix();

	// �v���W�F�N�V�����s����v�Z����
	void CalculateProjectionMatrix();

	// �J�������W���v�Z����
	void CalculateEyePosition(const DirectX::SimpleMath::Quaternion& rotate);

	// �}�E�X�|�C���^�̈ړ������ɁA�J�����̊p�x���v�Z����
	void CalculateCameraAngle();
	// �p�x�̌��E��ݒ肷��
	void CameraAngleMaxMin();
	// ��]�s��i�N�H�[�^�j�I���j������
	void CalculateQuaternion();
};
