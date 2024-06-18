//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/16
// <file>			Resources.cpp
// <�T�v>			�Q�[���Ŏg���摜�⃂�f���B
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"Resources.h"
#include"CommonResources.h"
#include"Libraries/NakashiLib/ResourcesManager.h"
/// <summary>
/// �R���X�g���N�^
/// </summary>
NakashiLib::Resources::Resources()
{
	m_commonResources = CommonResources::GetInstance();
	CreateModels();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
NakashiLib::Resources::~Resources()
{

}

/// <summary>
///	���f���̐ݒ�
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
/// �摜�̐ݒ�
/// </summary>
void NakashiLib::Resources::CreateSrvs()
{

}