//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//   ����� NakashimaYuto	2024/05/28
//		@ file   Iscene.h
//		�V�[���̃C���^�[�t�F�[�X
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once

// �O���錾
class CommonResources;

class IScene
{
public:
	// �V�[���h�c
	enum class SceneID : unsigned int
	{
		NONE,
		TITLE,
		PLAY,
		RESULT
	};


public:
	virtual ~IScene() = default;

	virtual void Initialize() = 0;

	virtual void Update(float elapsedTime) = 0;

	virtual void Render() = 0;

	virtual void Finalize() = 0;

	virtual SceneID GetNextSceneID() const = 0;
};
