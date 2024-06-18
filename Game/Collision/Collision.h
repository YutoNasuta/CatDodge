#pragma once
#include"pch.h"

class Collision
{
public:
	//++++++++++++++++++++++++++++++++++
	// 線分と三角形の交差判定用
	//++++++++++++++++++++++++++++++++++

	// 三角形の構造体
	struct Triangle
	{
		// 三角形の平面方程式
		DirectX::SimpleMath::Plane p;
		// 辺BCの平面方程式（重心座標の頂点aに対する重みuを与える)
		DirectX::SimpleMath::Plane edgePlaneBC;
		// 辺CAの平面方程式（重心座標の頂点bに対する重みvを与える）
		DirectX::SimpleMath::Plane edgePlaneCA;

		// コンストラクタ内で衝突判定を軽くするために前処理で計算しておく
		Triangle(DirectX::SimpleMath::Vector3 a, DirectX::SimpleMath::Vector3 b, DirectX::SimpleMath::Vector3 c)
		{
			// 三角形の法線ベクトルを計算
			DirectX::SimpleMath::Vector3 n = (c - a).Cross(b - a);

			// 三角形 , 辺BC , 辺CA　の平面方程式を初期化
			p = DirectX::SimpleMath::Plane(a, n);
			edgePlaneBC = DirectX::SimpleMath::Plane(b, n.Cross(b - c));
			edgePlaneCA = DirectX::SimpleMath::Plane(c, n.Cross(c - a));

			// 三角形の平面と、辺の平面を正規化
			p.Normalize();
			edgePlaneBC.Normalize();
			edgePlaneCA.Normalize();

			// スケール係数を計算
			float bc_scale = 1.0f / (a.Dot(edgePlaneBC.Normal()) + edgePlaneBC.D());
			float ca_scale = 1.0f / (b.Dot(edgePlaneCA.Normal()) + edgePlaneCA.D());

			// 法線ベクトルをスケーリング
			edgePlaneBC.x *= bc_scale;	edgePlaneBC.y *= bc_scale;	edgePlaneBC.z *= bc_scale;
			edgePlaneCA.x *= ca_scale;	edgePlaneCA.y *= ca_scale;	edgePlaneCA.z *= ca_scale;
		}

		//文献
		// 平面計算サイト
		//https://keisan.casio.jp/exec/system/1202458197#:~:text=%EF%BC%93%E7%82%B9A%E3%80%81B%E3%80%81C,d%3D0%20%E3%82%92%E6%B1%82%E3%82%81%E3%81%BE%E3%81%99%E3%80%82&text=%E3%83%99%E3%82%AF%E3%83%88%E3%83%ABAB%E3%81%A8%E3%83%99%E3%82%AF%E3%83%88%E3%83%ABAC,%E5%AE%9A%E6%95%B0%E9%83%A8%E5%88%86%E3%81%8C%E5%B0%8E%E5%87%BA%E3%81%A7%E3%81%8D%E3%82%8B%E3%80%82&text=%E5%BA%83%E7%BE%A9%E5%9B%BA%E6%9C%89%E7%A9%BA%E9%96%93%E3%82%92%E6%B1%82%E3%82%81%E3%82%8B%E3%81%9F%E3%82%81%E3%80%82
		// 法線ベクトルとスムージング角
		//http://tegetegeosprey.g1.xrea.com/opengl/opengl_normalvecotr.htm
	};

	/// <summary>
	/// 線分と三角形の交差点
	/// </summary>
	/// <param name="p">線分の始点</param>
	/// <param name="q">線分の終点</param>
	/// <param name="tri">三角形</param>
	/// <param name="s">線分と三角形の交差点</param>
	/// <returns></returns>
	static bool IntersectSegmentTriangle(DirectX::SimpleMath::Vector3 p, DirectX::SimpleMath::Vector3 q, Triangle triangle, DirectX::SimpleMath::Vector3* s)
	{
		// 浮動小数点の誤差で当たりぬけするので少し余裕をもつ
		constexpr float EPSILON = 1e-6F;

		// 線分の始点ｐが三角形の平面のどちら側にあるかを計算
		float distp = p.Dot(triangle.p.Normal()) + triangle.p.D();
		// 始点が平面の裏側にある場合は交差しない
		if (distp < 0.0f) return false;

		// 線分の終点ｑが三角形の平面のどちら側にあるかを計算
		float distq = q.Dot(triangle.p.Normal()) + triangle.p.D();
		// 終点が平面の表側にある場合は交差しない
		if (distq >= 0.0f) return false;

		// 線分の始点と終点の平面からの距離の差を計算
		float denom = distp - distq;

		// 線分と平面の交差点のパラメータｔを計算
		float t = distp / denom;

		// 交差点の座標を計算
		*s = p + t * (q - p);

		// 交差点が辺BCの平面のどちら側にあるかを計算
		float u = s->Dot(triangle.edgePlaneBC.Normal()) + triangle.edgePlaneBC.D();
		// 誤差の考慮
		if (fabsf(u) < EPSILON) u = 0.0f;
		// u が 0 ～ 1 の範囲外なら交差しない
		if (u < 0.0f || u >1.0f) return false;

		// 交差点が辺CAの平面のどちら側にあるかを計算
		float v = s->Dot(triangle.edgePlaneCA.Normal()) + triangle.edgePlaneCA.D();
		// 誤差の考慮
		if (fabsf(v) < EPSILON) v = 0.0f;
		// v が 0 より小さいなら交差しない
		if (v < 0.0f) return false;

		// 重心座標の３つ目の成分 w を計算
		float w = 1.0f - u - v;
		// 誤差の考慮
		if (fabsf(w) < EPSILON) w = 0.0f;
		// w が 0 より小さい場合は交差しない
		if (w < 0.0f) return false;

		// すべての条件を満たした場合、線分は三角形と交差している
		return true;

		// 文献
		// 重心座標について
		//https://www.try-it.jp/chapters-6533/sections-6534/lessons-6551/example-2/#:~:text=%E9%87%8D%E5%BF%83%E3%81%AF%E3%80%8C3%E9%A0%82%E7%82%B9%E3%81%AE,%E8%B6%B3%E3%81%97%E3%81%A63%E3%81%A7%E5%89%B2%E3%82%8B%E3%80%8D&text=x%E5%BA%A7%E6%A8%99%E3%80%81y%E5%BA%A7%E6%A8%99%E3%80%81%E3%81%9D%E3%82%8C%E3%81%9E%E3%82%8C,%E3%81%93%E3%81%A8%E3%81%8C%E3%81%A7%E3%81%8D%E3%81%BE%E3%81%99%E3%81%AD%E3%80%82
	    // 左右どちらにあるのか
		//https://note.com/shozotanaka/n/nc68758878b84
	}


};