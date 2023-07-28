#pragma once
#include "Scene.h"

/// <summary>
/// シーンマネージャー
/// </summary>
class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void GameLoop();

	void SetNowScene(const TAG_SCENE& tag);
private:
	void ClearScene();
	Scene* currentScene;
};
