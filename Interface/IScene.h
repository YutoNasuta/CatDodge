//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//   製作者 NakashimaYuto	2024/05/28
//		@ file   Iscene.h
//		シーンのインターフェース
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once

// 前方宣言
class CommonResources;

class IScene
{
public:
	// シーンＩＤ
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
