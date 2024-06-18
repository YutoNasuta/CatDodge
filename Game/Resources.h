//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/16
// <file>			Resources.h
// <概要>			ゲームで使う画像やモデル達
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"pch.h"

// 前方宣言
class CommonResources;
namespace NakashiLib
{
	class Resources
	{
	private:
		CommonResources* m_commonResources;

	public:
		Resources();
		~Resources();

		void CreateModels();
		void CreateSrvs();
	};
}
