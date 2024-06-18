//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/16
// <file>			Resources.cpp
// <概要>			ゲームで使う画像やモデル達
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"Resources.h"
#include"CommonResources.h"
#include"Libraries/NakashiLib/ResourcesManager.h"
/// <summary>
/// コンストラクタ
/// </summary>
NakashiLib::Resources::Resources()
{
	m_commonResources = CommonResources::GetInstance();
	CreateModels();
}

/// <summary>
/// デストラクタ
/// </summary>
NakashiLib::Resources::~Resources()
{

}

/// <summary>
///	モデルの設定
/// </summary>
void NakashiLib::Resources::CreateModels()
{
	auto ResourcesManager = m_commonResources->GetResourcesManager();

	ResourcesManager->CreateModel(L"PlayerBody", L"PlayerBody.cmo");
	ResourcesManager->CreateModel(L"PlayerLeftHand", L"PlayerLeftHand.cmo");
	ResourcesManager->CreateModel(L"PlayerHead", L"PlayerHead.cmo");
	ResourcesManager->CreateModel(L"PlayerLeg", L"PlayerLeg.cmo");
	ResourcesManager->CreateModel(L"PlayerRightHand", L"PlayerRightHand.cmo");
	ResourcesManager->CreateModel(L"PlayerTail", L"PlayerTail.cmo");

}

/// <summary>
/// 画像の設定
/// </summary>
void NakashiLib::Resources::CreateSrvs()
{

}