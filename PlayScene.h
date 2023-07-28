#pragma once
#include "Scene.h"

/// <summary>
/// プレイシーン
/// </summary>
class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene() override;

	TAG_SCENE Update(float deltaTime) override;
	void Draw() override;

private:
};
