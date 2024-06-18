//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/01/14
// <file>			MousePoint.cpp
// <概要>			パーリンノイズの作成
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
		// 計算で使用するハッシュテーブル
		std::array<unsigned int, 512u> m_permutation{};

	public:
		// コンストラクタ
		explicit PerlinNoise( int seed)
		{
			SetSeed(seed);
		}
		// デストラクタ
		~PerlinNoise() = default;

		// SEED値（ハッシュテーブル）を設定
		inline void SetSeed(const unsigned int seed)
		{
			// 配列の前半部分に「0-255」のシーケンシャルな値を得る
			std::iota(m_permutation.begin(), (m_permutation.begin() + 256), 0);

			// ランダムエンジンの作成
			std::default_random_engine engine(seed);

			// 配列の前半部分をシャッフル
			std::shuffle(m_permutation.begin(), (m_permutation.begin() + 256), engine);

			// 後半部分に前半部分の値をコピー
			for (int i = 0; i < 256; i++)
			{
				m_permutation[256 + i] = m_permutation[i];
			}
		}

		// オクターブありノイズを取得
		inline float GetNoise(unsigned int octaves, float x = 0, float y = 0) const
		{
			// ノイズの値を補正
			const float noiseValue = Octave(octaves, x, y) * 0.5f + 0.5f;
			// ノイズを0.0f～1.0fの間にクランプする
			return ((noiseValue >= 1.0f) ? 1.0f : ((noiseValue <= 0.0f) ? 0.0f : noiseValue));
		}

	private:
		// フェードの計算
		inline float Fade(float t) const
		{
				return t * t * t * (t * (t * 6 - 15) + 10);
		}

		// 線形補完をする
		inline float Lerp(float t, float a, float b)const
		{
			return a + t * (b - a);
		}

		// 勾配の計算
		inline float Grad(unsigned int hash, float x, float y, float z = 0.0f) const
		{
			int h = hash & 15;
			float u = h < 8 ? x : y;
			float v = h < 4 ? y : h == 12 || h == 14 ? x : z;
			return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
		}

		// ノイズの計算
		inline float Noise(float x, float y)const
		{
			// 引数以下で最大の整数値を得る
			const float tx = std::floorf(x);
			const float ty = std::floorf(y);
			// int化する時、下位８ビットをマスクして取り出す
			const int ix = static_cast<int>(tx) & 255;
			const int iy = static_cast<int>(ty) & 255;
			// 引数xと整数化した引数の差分取得
			const float fx = x - tx;
			const float fy = y - ty;
			// Fadeする
			const float u = Fade(fx);
			const float v = Fade(fy);
			// 勾配用の添え字計算
			const int a0 = m_permutation[ix] + iy;
			const int a1 = m_permutation[a0];
			const int a2 = m_permutation[a0 + 1];
			const int b0 = m_permutation[ix + 1] + iy;
			const int b1 = m_permutation[b0];
			const int b2 = m_permutation[b0 + 1];
			// 勾配する
			const float g0 = Grad(m_permutation[a1], fx, fy);
			const float g1 = Grad(m_permutation[b1], fx - 1, fy);
			const float g2 = Grad(m_permutation[a2], fx, fy - 1);
			const float g3 = Grad(m_permutation[b2], fx - 1, fy - 1);
			// Lerpする
			const float le0 = Lerp(u, g0, g1);
			const float le1 = Lerp(u, g2, g3);
			
			return Lerp(v, le0, le1);
		}

		// オクターブノイズの計算
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

	// 文献
	// https://postd.cc/understanding-perlin-noise/
	// https://qiita.com/gis/items/ba7d715901a0e572b0e9
	// https://dioltista.blogspot.com/2019/06/c-directx11_8.html
	// https://github.com/AsPJT/DungeonTemplateLibrary/wiki/dtl::shape::PerlinIsland-(%E5%BD%A2%E7%8A%B6%E3%82%AF%E3%83%A9%E3%82%B9)
	// https://zenn.dev/baroqueengine/books/a19140f2d9fc1a/viewer/95c334
	// https://github.com/Reputeless/PerlinNoise
	// https://ekulabo.com/unity-perlin-noise
	// https://dntf.hatenablog.com/entry/unity_perlinnoise
}