//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/17
// <file>			Camera.h
// <�T�v>		�@�@�J����
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
/// �v���W�F�N�V�����s��̌v�Z
/// </summary>
void Camera::CalculateProjectionMatrix()
{
	const float width = static_cast<float>(Screen::WIDTH);
	const float height = static_cast<float>(Screen::HEIGHT);

	// ��ʏc����
	const float aspectRatio = width / height;

	m_projection = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		FOV, aspectRatio, NEAR_PLANE, FAR_PLANE
	);
}

/// <summary>
/// �J�������W�̌v�Z
/// </summary>
/// <param name="rotate"></param>
void Camera::CalculateEyePosition(const DirectX::SimpleMath::Quaternion& rotate)
{
	// ����̐i�s�����x�N�g��
	DirectX::SimpleMath::Vector3 forward = DirectX::SimpleMath::Vector3::Forward;

	// �J�������^�[�Q�b�g����ǂꂭ�炢����Ă��邩
	forward.y = GetCameraHIGHT();
	forward.z = GetCameraDistance();

	// �^�[�Q�b�g�̌����Ă�������ɒǏ]����
	forward = DirectX::SimpleMath::Vector3::Transform(forward, rotate);

	// �J�������W���v�Z����
	SetEyePosition(GetTargetPosition() + forward);

}

/// <summary>
/// �r���[�s��̌v�Z
/// </summary>
void Camera::CalculateViewMatrix()
{
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(
		m_eye,
		m_target,
		m_up);

}