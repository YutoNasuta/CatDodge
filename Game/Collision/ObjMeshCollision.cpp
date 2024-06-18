#include"pch.h"
#include"ObjMeshCollision.h"
#include<fstream>
// �R���X�g���N�^
ObjMeshCollision::ObjMeshCollision(const wchar_t* filename)
{
	// obj�`���t�@�C���ǂݍ���
	std::ifstream ifs(filename);

	std::string str;
	while (std::getline(ifs, str))
	{
		// ���_
		if (str[0] == 'v')
		{
			DirectX::VertexPosition val = {};
			sscanf_s(str.data(), "v %f %f %f", &val.position.x, &val.position.y, &val.position.z);
			m_vertexes.push_back(val);
		}
		// �C���f�b�N�X
		if (str[0] == 'f')
		{
			int a, b, c;
			sscanf_s(str.data(), "f %d %d %d", &a, &b, &c);
			// �O�p�`�̒��_�C���f�b�N�X�ԍ����������̂��܂ޏꍇ�͖�������
			if (a != b && a != c && b != c)
			{
				m_indexes.push_back(static_cast<uint16_t>(a - 1));
				m_indexes.push_back(static_cast<uint16_t>(c - 1));
				m_indexes.push_back(static_cast<uint16_t>(b - 1));
			}
		}
	}
	ifs.close();

	// �O�p�`���X�g�ɓo�^
	for (size_t i = 0; i < m_indexes.size() / 3; i++)
	{
		AddTriangle(m_vertexes[m_indexes[i * 3]].position, m_vertexes[m_indexes[i * 3 + 1]].position, m_vertexes[m_indexes[i * 3 + 2]].position);
	}
}

// �R���W�����p�O�p�`�f�[�^�̒ǉ��֐�
void ObjMeshCollision::AddTriangle(DirectX::XMFLOAT3 a, DirectX::XMFLOAT3 b, DirectX::XMFLOAT3 c)
{
	Collision::Triangle t(a, b, c);
	m_triangles.push_back(t);
}

// �R���W�������̍X�V
void ObjMeshCollision::UpdateBoundingInfo(const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& rotate)
{
	m_position = position;
	m_rotation = rotate;
}

// �����Ƃ̌�������֐�
bool ObjMeshCollision::IntersectLineSegment(
	DirectX::SimpleMath::Vector3 a,
	DirectX::SimpleMath::Vector3 b,
	DirectX::SimpleMath::Vector3* hitPosition,
	DirectX::SimpleMath::Vector3* normal
)
{
	// �����ɋt�s����|����
	DirectX::SimpleMath::Matrix rotate = DirectX::SimpleMath::Matrix::CreateFromQuaternion(m_rotation);
	DirectX::SimpleMath::Matrix trans = DirectX::SimpleMath::Matrix::CreateTranslation(m_position);
	DirectX::SimpleMath::Matrix world = rotate * trans;
	DirectX::SimpleMath::Matrix matInvert = world.Invert();
	a = DirectX::SimpleMath::Vector3::Transform(a, matInvert);
	b = DirectX::SimpleMath::Vector3::Transform(b, matInvert);

	for (int i = 0; i < m_triangles.size(); i++)
	{
		if (Collision::IntersectSegmentTriangle(a, b, m_triangles[i], hitPosition) == true)
		{
			// �Փˈʒu�����[���h���W�n�֕ϊ�
			*hitPosition = DirectX::SimpleMath::Vector3::Transform(*hitPosition, world);
			// �Փ˂����O�p�`�̖@�������擾
			if (normal) *normal = DirectX::SimpleMath::Vector3::Transform(m_triangles[i].p.Normal(), rotate);
			return true;
		}
	}
	return false;
}

void ObjMeshCollision::AddDisplayCollision(DisplayCollision* displayCollision, DirectX::FXMVECTOR lineColor) const
{
	displayCollision->AddBoundingVolume(m_vertexes, m_indexes, m_position, m_rotation, lineColor);
}