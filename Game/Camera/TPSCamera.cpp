//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/01/20
// <file>			TPSCamera.cpp
// <�T�v>			TPS�J�����̎���
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include"pch.h"
#include"TPSCamera.h"
#include"Game/Screen.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="target">�^�[�Q�b�g�̎擾</param>
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
/// �X�V����
/// </summary>
/// <param name="newTarget">���݂̃^�[�Q�b�g</param>
void TPSCamera::Update(
	const DirectX::SimpleMath::Vector3& newTarget
)
{
	// �}�E�X�𓮂���
	m_mousePointer->Update();

	// target�̈ʒu���X�V����
	m_target = DirectX::SimpleMath::Vector3(newTarget.x, newTarget.y * 0.7f , newTarget.z);

	// �J�������W���v�Z����
	CalculateEyePosition(m_rotate);

	// �r���[�s����X�V����
	CalculateViewMatrix();

	// �}�E�X����p�x���擾���āA�N�H�[�^�j�I���̌v�Z������
	CalculateCameraAngle();

	CameraAngleMaxMin();
}

/// <summary>
/// �r���[�s��̌v�Z
/// </summary>
void TPSCamera::CalculateViewMatrix()
{
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_eye, m_target, m_up);
}

/// <summary>
/// �v���W�F�N�V�����s��̌v�Z
/// </summary>
void TPSCamera::CalculateProjectionMatrix()
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
void TPSCamera::CalculateEyePosition(const DirectX::SimpleMath::Quaternion& rotate)
{
	// ����̐i�s�����x�N�g��
	DirectX::SimpleMath::Vector3 forward = DirectX::SimpleMath::Vector3::Forward;

	// �J�������^�[�Q�b�g����ǂꂭ�炢����Ă��邩
	forward.y = CAMERA_HIGHT;
	forward.z = CAMERA_DISTANCE;

	// �^�[�Q�b�g�̌����Ă�������ɒǏ]����
	forward = DirectX::SimpleMath::Vector3::Transform(forward, rotate);

	// �J�������W���v�Z����
	m_eye = m_target + forward;

}

/// <summary>
/// �}�E�X�|�C���^�̓����ɍ��킹�ĉ�]
/// </summary>
void TPSCamera::CalculateCameraAngle()
{
	m_cameraAngle.x -= m_mousePointer->GetMouseDeltaY() * 0.05f;
	m_cameraAngle.y -= m_mousePointer->GetMouseDeltaX() * 0.05f;

	CameraAngleMaxMin();
	CalculateQuaternion();
}

/// <summary>
/// �J�����̍ő�p�x��ݒ�
/// </summary>
void TPSCamera::CameraAngleMaxMin()
{
	if (m_cameraAngle.x < -50) { m_cameraAngle.x = -50; }
	if (m_cameraAngle.x > 50) { m_cameraAngle.x = 50; }
}

/// <summary>
/// �N�H�[�^�j�I���̐���
/// </summary>
void TPSCamera::CalculateQuaternion()
{
	// X������̉�]��\���N�H�[�^�j�I�����쐬
	DirectX::SimpleMath::Quaternion rotationX = 
		DirectX::SimpleMath::Quaternion::CreateFromRotationMatrix(DirectX::SimpleMath::Matrix::CreateRotationX(DirectX::XMConvertToRadians(m_cameraAngle.x)));

	// Y������̉�]��\���N�H�[�^�j�I�����쐬
	DirectX::SimpleMath::Quaternion rotationY = 
		DirectX::SimpleMath::Quaternion::CreateFromRotationMatrix(DirectX::SimpleMath::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_cameraAngle.y)));

	// �����̉�]�ɐV������]����������
	m_rotate = rotationX * rotationY;
}