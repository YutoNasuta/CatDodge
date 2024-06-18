#pragma once
#include"pch.h"

class Collision
{
public:
	//++++++++++++++++++++++++++++++++++
	// �����ƎO�p�`�̌�������p
	//++++++++++++++++++++++++++++++++++

	// �O�p�`�̍\����
	struct Triangle
	{
		// �O�p�`�̕��ʕ�����
		DirectX::SimpleMath::Plane p;
		// ��BC�̕��ʕ������i�d�S���W�̒��_a�ɑ΂���d��u��^����)
		DirectX::SimpleMath::Plane edgePlaneBC;
		// ��CA�̕��ʕ������i�d�S���W�̒��_b�ɑ΂���d��v��^����j
		DirectX::SimpleMath::Plane edgePlaneCA;

		// �R���X�g���N�^���ŏՓ˔�����y�����邽�߂ɑO�����Ōv�Z���Ă���
		Triangle(DirectX::SimpleMath::Vector3 a, DirectX::SimpleMath::Vector3 b, DirectX::SimpleMath::Vector3 c)
		{
			// �O�p�`�̖@���x�N�g�����v�Z
			DirectX::SimpleMath::Vector3 n = (c - a).Cross(b - a);

			// �O�p�` , ��BC , ��CA�@�̕��ʕ�������������
			p = DirectX::SimpleMath::Plane(a, n);
			edgePlaneBC = DirectX::SimpleMath::Plane(b, n.Cross(b - c));
			edgePlaneCA = DirectX::SimpleMath::Plane(c, n.Cross(c - a));

			// �O�p�`�̕��ʂƁA�ӂ̕��ʂ𐳋K��
			p.Normalize();
			edgePlaneBC.Normalize();
			edgePlaneCA.Normalize();

			// �X�P�[���W�����v�Z
			float bc_scale = 1.0f / (a.Dot(edgePlaneBC.Normal()) + edgePlaneBC.D());
			float ca_scale = 1.0f / (b.Dot(edgePlaneCA.Normal()) + edgePlaneCA.D());

			// �@���x�N�g�����X�P�[�����O
			edgePlaneBC.x *= bc_scale;	edgePlaneBC.y *= bc_scale;	edgePlaneBC.z *= bc_scale;
			edgePlaneCA.x *= ca_scale;	edgePlaneCA.y *= ca_scale;	edgePlaneCA.z *= ca_scale;
		}

		//����
		// ���ʌv�Z�T�C�g
		//https://keisan.casio.jp/exec/system/1202458197#:~:text=%EF%BC%93%E7%82%B9A%E3%80%81B%E3%80%81C,d%3D0%20%E3%82%92%E6%B1%82%E3%82%81%E3%81%BE%E3%81%99%E3%80%82&text=%E3%83%99%E3%82%AF%E3%83%88%E3%83%ABAB%E3%81%A8%E3%83%99%E3%82%AF%E3%83%88%E3%83%ABAC,%E5%AE%9A%E6%95%B0%E9%83%A8%E5%88%86%E3%81%8C%E5%B0%8E%E5%87%BA%E3%81%A7%E3%81%8D%E3%82%8B%E3%80%82&text=%E5%BA%83%E7%BE%A9%E5%9B%BA%E6%9C%89%E7%A9%BA%E9%96%93%E3%82%92%E6%B1%82%E3%82%81%E3%82%8B%E3%81%9F%E3%82%81%E3%80%82
		// �@���x�N�g���ƃX���[�W���O�p
		//http://tegetegeosprey.g1.xrea.com/opengl/opengl_normalvecotr.htm
	};

	/// <summary>
	/// �����ƎO�p�`�̌����_
	/// </summary>
	/// <param name="p">�����̎n�_</param>
	/// <param name="q">�����̏I�_</param>
	/// <param name="tri">�O�p�`</param>
	/// <param name="s">�����ƎO�p�`�̌����_</param>
	/// <returns></returns>
	static bool IntersectSegmentTriangle(DirectX::SimpleMath::Vector3 p, DirectX::SimpleMath::Vector3 q, Triangle triangle, DirectX::SimpleMath::Vector3* s)
	{
		// ���������_�̌덷�œ�����ʂ�����̂ŏ����]�T������
		constexpr float EPSILON = 1e-6F;

		// �����̎n�_�����O�p�`�̕��ʂ̂ǂ��瑤�ɂ��邩���v�Z
		float distp = p.Dot(triangle.p.Normal()) + triangle.p.D();
		// �n�_�����ʂ̗����ɂ���ꍇ�͌������Ȃ�
		if (distp < 0.0f) return false;

		// �����̏I�_�����O�p�`�̕��ʂ̂ǂ��瑤�ɂ��邩���v�Z
		float distq = q.Dot(triangle.p.Normal()) + triangle.p.D();
		// �I�_�����ʂ̕\���ɂ���ꍇ�͌������Ȃ�
		if (distq >= 0.0f) return false;

		// �����̎n�_�ƏI�_�̕��ʂ���̋����̍����v�Z
		float denom = distp - distq;

		// �����ƕ��ʂ̌����_�̃p�����[�^�����v�Z
		float t = distp / denom;

		// �����_�̍��W���v�Z
		*s = p + t * (q - p);

		// �����_����BC�̕��ʂ̂ǂ��瑤�ɂ��邩���v�Z
		float u = s->Dot(triangle.edgePlaneBC.Normal()) + triangle.edgePlaneBC.D();
		// �덷�̍l��
		if (fabsf(u) < EPSILON) u = 0.0f;
		// u �� 0 �` 1 �͈̔͊O�Ȃ�������Ȃ�
		if (u < 0.0f || u >1.0f) return false;

		// �����_����CA�̕��ʂ̂ǂ��瑤�ɂ��邩���v�Z
		float v = s->Dot(triangle.edgePlaneCA.Normal()) + triangle.edgePlaneCA.D();
		// �덷�̍l��
		if (fabsf(v) < EPSILON) v = 0.0f;
		// v �� 0 ��菬�����Ȃ�������Ȃ�
		if (v < 0.0f) return false;

		// �d�S���W�̂R�ڂ̐��� w ���v�Z
		float w = 1.0f - u - v;
		// �덷�̍l��
		if (fabsf(w) < EPSILON) w = 0.0f;
		// w �� 0 ��菬�����ꍇ�͌������Ȃ�
		if (w < 0.0f) return false;

		// ���ׂĂ̏����𖞂������ꍇ�A�����͎O�p�`�ƌ������Ă���
		return true;

		// ����
		// �d�S���W�ɂ���
		//https://www.try-it.jp/chapters-6533/sections-6534/lessons-6551/example-2/#:~:text=%E9%87%8D%E5%BF%83%E3%81%AF%E3%80%8C3%E9%A0%82%E7%82%B9%E3%81%AE,%E8%B6%B3%E3%81%97%E3%81%A63%E3%81%A7%E5%89%B2%E3%82%8B%E3%80%8D&text=x%E5%BA%A7%E6%A8%99%E3%80%81y%E5%BA%A7%E6%A8%99%E3%80%81%E3%81%9D%E3%82%8C%E3%81%9E%E3%82%8C,%E3%81%93%E3%81%A8%E3%81%8C%E3%81%A7%E3%81%8D%E3%81%BE%E3%81%99%E3%81%AD%E3%80%82
	    // ���E�ǂ���ɂ���̂�
		//https://note.com/shozotanaka/n/nc68758878b84
	}


};