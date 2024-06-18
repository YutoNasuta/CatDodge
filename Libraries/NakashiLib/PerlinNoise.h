//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/01/14
// <file>			MousePoint.cpp
// <�T�v>			�p�[�����m�C�Y�̍쐬
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include<array>
#include<random>
#include<algorithm>
#include<numeric>

namespace NakashiLib
{
	class PerlinNoise
	{
	private:
		// �v�Z�Ŏg�p����n�b�V���e�[�u��
		std::array<unsigned int, 512u> m_permutation{};

	public:
		// �R���X�g���N�^
		explicit PerlinNoise( int seed)
		{
			SetSeed(seed);
		}
		// �f�X�g���N�^
		~PerlinNoise() = default;

		// SEED�l�i�n�b�V���e�[�u���j��ݒ�
		inline void SetSeed(const unsigned int seed)
		{
			// �z��̑O�������Ɂu0-255�v�̃V�[�P���V�����Ȓl�𓾂�
			std::iota(m_permutation.begin(), (m_permutation.begin() + 256), 0);

			// �����_���G���W���̍쐬
			std::default_random_engine engine(seed);

			// �z��̑O���������V���b�t��
			std::shuffle(m_permutation.begin(), (m_permutation.begin() + 256), engine);

			// �㔼�����ɑO�������̒l���R�s�[
			for (int i = 0; i < 256; i++)
			{
				m_permutation[256 + i] = m_permutation[i];
			}
		}

		// �I�N�^�[�u����m�C�Y���擾
		inline float GetNoise(unsigned int octaves, float x = 0, float y = 0) const
		{
			// �m�C�Y�̒l��␳
			const float noiseValue = Octave(octaves, x, y) * 0.5f + 0.5f;
			// �m�C�Y��0.0f�`1.0f�̊ԂɃN�����v����
			return ((noiseValue >= 1.0f) ? 1.0f : ((noiseValue <= 0.0f) ? 0.0f : noiseValue));
		}

	private:
		// �t�F�[�h�̌v�Z
		inline float Fade(float t) const
		{
				return t * t * t * (t * (t * 6 - 15) + 10);
		}

		// ���`�⊮������
		inline float Lerp(float t, float a, float b)const
		{
			return a + t * (b - a);
		}

		// ���z�̌v�Z
		inline float Grad(unsigned int hash, float x, float y, float z = 0.0f) const
		{
			int h = hash & 15;
			float u = h < 8 ? x : y;
			float v = h < 4 ? y : h == 12 || h == 14 ? x : z;
			return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
		}

		// �m�C�Y�̌v�Z
		inline float Noise(float x, float y)const
		{
			// �����ȉ��ōő�̐����l�𓾂�
			const float tx = std::floorf(x);
			const float ty = std::floorf(y);
			// int�����鎞�A���ʂW�r�b�g���}�X�N���Ď��o��
			const int ix = static_cast<int>(tx) & 255;
			const int iy = static_cast<int>(ty) & 255;
			// ����x�Ɛ��������������̍����擾
			const float fx = x - tx;
			const float fy = y - ty;
			// Fade����
			const float u = Fade(fx);
			const float v = Fade(fy);
			// ���z�p�̓Y�����v�Z
			const int a0 = m_permutation[ix] + iy;
			const int a1 = m_permutation[a0];
			const int a2 = m_permutation[a0 + 1];
			const int b0 = m_permutation[ix + 1] + iy;
			const int b1 = m_permutation[b0];
			const int b2 = m_permutation[b0 + 1];
			// ���z����
			const float g0 = Grad(m_permutation[a1], fx, fy);
			const float g1 = Grad(m_permutation[b1], fx - 1, fy);
			const float g2 = Grad(m_permutation[a2], fx, fy - 1);
			const float g3 = Grad(m_permutation[b2], fx - 1, fy - 1);
			// Lerp����
			const float le0 = Lerp(u, g0, g1);
			const float le1 = Lerp(u, g2, g3);
			
			return Lerp(v, le0, le1);
		}

		// �I�N�^�[�u�m�C�Y�̌v�Z
		inline float Octave(unsigned int octaves, float x, float y) const
		{
			float noiseValue = 0.0f;
			float amplitude = 1.0f;
			for (size_t i = 0; i < octaves; i++)
			{
				noiseValue += (Noise(x, y) * amplitude);
				x *= 2.0f;
				y *= 2.0f;
				amplitude *= 0.5f;
			}

			return noiseValue;
		}
	};

	// ����
	// https://postd.cc/understanding-perlin-noise/
	// https://qiita.com/gis/items/ba7d715901a0e572b0e9
	// https://dioltista.blogspot.com/2019/06/c-directx11_8.html
	// https://github.com/AsPJT/DungeonTemplateLibrary/wiki/dtl::shape::PerlinIsland-(%E5%BD%A2%E7%8A%B6%E3%82%AF%E3%83%A9%E3%82%B9)
	// https://zenn.dev/baroqueengine/books/a19140f2d9fc1a/viewer/95c334
	// https://github.com/Reputeless/PerlinNoise
	// https://ekulabo.com/unity-perlin-noise
	// https://dntf.hatenablog.com/entry/unity_perlinnoise
}